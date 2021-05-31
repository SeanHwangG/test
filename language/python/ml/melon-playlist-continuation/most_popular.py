# -*- coding: utf-8 -*-
import fire

from collections import Counter
from tqdm import tqdm
from arena_util import load_json
from arena_util import write_json
from arena_util import remove_seen


class MostPopular:
    def _generate_answers(self, train_json, test_json):
        top_song = self._most_popular(train_json, "songs", 200)
        top_tag = self._most_popular(train_json, "tags", 100)

        results = []

        for q in tqdm(test_json):
            results.append({
                "id": q["id"],
                "songs": remove_seen(q["songs"], top_song)[:100],
                "tags": remove_seen(q["tags"], top_tag)[:10],
            })

        return results

    def _most_popular(self, playlists, col, topk_count):
        c = Counter()

        for doc in playlists:
            c.update(doc[col])

        topk = c.most_common(topk_count)
        return [k for k, v in topk]

    def run(self, train_fname, test_fname):
        train_json = load_json(train_fname)
        test_json = load_json(test_fname)
        answers = self._generate_answers(train_json, test_json)
        write_json(answers, "results/results.json")


if __name__ == "__main__":
    fire.Fire(MostPopular)
