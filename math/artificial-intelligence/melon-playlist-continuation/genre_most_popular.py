# -*- coding: utf-8 -*-
from collections import Counter

import fire
import numpy as np
from tqdm import tqdm
from arena_util import load_json
from arena_util import write_json
from arena_util import remove_seen


class GenreMostPopular:
    def _song_mp_per_genre(self, id2meta, global_mp):
        res = {}

        for sid, song in id2meta.items():
            for genre in song['song_gn_dtl_gnr_basket']:
                res.setdefault(genre, []).append(sid)

        for genre, sids in res.items():
            count = Counter({k: global_mp.get(int(k), 0) for k in sids})
            res[genre] = [k for k, v in count.most_common(200)]

        return res

    def _most_popular(self, playlists, col, topk_count):
        c = Counter()

        for doc in playlists:
            c.update(doc[col])

        topk = c.most_common(topk_count)
        return c, [k for k, v in topk]

    def _generate_answers(self, song_json, train_json, test_json):
        id2meta = {int(song["id"]): song for song in song_json}
        song_mp_counter, song_mp = self._most_popular(train_json, "songs", 200)
        tag_mp_counter, tag_mp = self._most_popular(train_json, "tags", 100)
        genre2mp_song = self._song_mp_per_genre(id2meta, song_mp_counter)

        results = []
        debug = 0
        for plylst in tqdm(test_json):
            genre_counter = Counter()  # genre : total_like

            for sid in plylst["songs"]:
                for genre in id2meta[sid]["song_gn_dtl_gnr_basket"]:
                    genre_counter.update({genre: 1})

            top_songs = [gnr for gnr, count in genre_counter.most_common(10)]
            top_count = [count for gnr, count in genre_counter.most_common(10)]
            top_percents = [c / sum(top_count) for c in top_count]

            pool = []
            for song, percent in zip(top_songs, top_percents):
                pool += genre2mp_song[genre][:int(200 * percent)]
            pool += song_mp

            pool = remove_seen(plylst["songs"], pool)
            rag_mp = remove_seen(plylst["tags"], tag_mp)
            if debug % 1000 == 0:
                debug += 1
                print(pool)
            if len(pool) < 100 or len(tag_mp) < 10:
                print(pool)
                exit(self)

            results.append({
                "id": plylst["id"],
                "songs": pool[:100],
                "tags": tag_mp[:10]
            })

        return results

    def run(self, song_fname, train_fname, test_fname):
        song_json = load_json(song_fname)
        train_json = load_json(train_fname)
        test_json = load_json(test_fname)

        print("Writing results...")
        results = self._generate_answers(song_json, train_json, test_json)
        write_json(results, "results.json")


if __name__ == "__main__":
    fire.Fire(GenreMostPopular)
