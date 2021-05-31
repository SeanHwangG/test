import fire
import json
import pandas as pd
import itertools
import operator
import pickle
from functools import reduce
from tqdm import tqdm
from collections import defaultdict, Counter
from arena_util import load_json, write_json, remove_seen
from concurrent.futures import ProcessPoolExecutor


class NearestNeighbor:
    def _most_popular(self, playlists, col, topk_count):
        c = Counter()

        for doc in playlists:
            c.update(doc[col])

        topk = c.most_common(topk_count)
        return c, [k for k, v in topk]

    def _song_mp_per_genre(self, id2meta, global_mp):
        res = {}

        for sid, song in id2meta.items():
            for genre in song['song_gn_dtl_gnr_basket']:
                res.setdefault(genre, []).append(sid)

        for genre, sids in res.items():
            count = Counter({k: global_mp.get(int(k), 0) for k in sids})
            res[genre] = [k for k, v in count.most_common(200)]

        return res

    def _generate_answers(self, song_json, train_json, test_json):
        song2song = defaultdict(Counter)
        tag2tag = defaultdict(Counter)

        for plylst in tqdm(train_json):
            for a, b in itertools.permutations(plylst['songs'], 2):
                song2song[a][b] += 1
            for a, b in itertools.permutations(plylst['tags'], 2):
                tag2tag[a][b] += 1

        _, top_songs = self._most_popular(train_json, 'songs', 200)
        _, top_tags = self._most_popular(train_json, 'tags', 20)

        results = []
        debug = 0
        for plylst in tqdm(test_json):
            song2count = reduce(operator.add, [song2song[s] for s in plylst['songs']], Counter())
            gnr2count = reduce(operator.add, [tag2tag[t] for t in plylst['tags']], Counter())

            close_songs = [song for song, count in song2count.most_common(100)]
            close_tags = [song for song, count in gnr2count.most_common(20)]
            if debug % 100 == 0:
                print(close_songs)
            debug += 1

            results.append({
                "id": plylst["id"],
                "songs": remove_seen(plylst["songs"], close_songs + top_songs)[:100],
                "tags": remove_seen(plylst["tags"], close_tags + top_tags)[:10]
            })

        return results

    def run(self, song_fname, train_fname, test_fname):
        print("Loading train file...")

        song_json = load_json(song_fname)
        train_json = load_json(train_fname)
        test_json = load_json(test_fname)
        results = self._generate_answers(song_json, train_json, test_json)
        write_json(results, "results.json")

if __name__ == "__main__":
    fire.Fire(NearestNeighbor)


