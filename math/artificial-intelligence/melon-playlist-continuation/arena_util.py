import os
import json
import distutils.dir_util
import numpy as np
import numpy as np
from time import gmtime, strftime
from collections import Counter


def evaluate(answer_json, result_json):
    def idcg(l):
        return sum((1.0 / np.log(i + 2) for i in range(l)))

    def ndcg(gt, rec):
        idcgs = [idcg(i) for i in range(101)]

        dcg = 0.0
        for i, r in enumerate(rec):
            if r in gt:
                dcg += 1.0 / np.log(i + 2)

        return dcg / idcgs[len(gt)]

    gt_ids = set([g["id"] for g in answer_json])
    rec_ids = set([r["id"] for r in result_json])

    rec_song_counts = [len(set(p["songs"])) for p in result_json]
    rec_tag_counts = [len(set(p["tags"])) for p in result_json]

    if set(rec_song_counts) != set([100]):
        print(set(rec_song_counts))
        raise Exception("추천 곡 결과의 개수가 맞지 않습니다.")

    if set(rec_tag_counts) != set([10]):
        raise Exception("추천 태그 결과의 개수가 맞지 않습니다.")

    music_ndcg = 0.0
    tag_ndcg = 0.0

    id2answer = {g["id"]: g for g in answer_json}

    for rec in result_json:
        answer = id2answer[rec["id"]]
        music_ndcg += ndcg(answer["songs"], rec["songs"][:100])
        tag_ndcg += ndcg(answer["tags"], rec["tags"][:10])

    music_ndcg = music_ndcg / len(result_json)
    tag_ndcg = tag_ndcg / len(result_json)
    score = music_ndcg * 0.85 + tag_ndcg * 0.15

    return music_ndcg, tag_ndcg, score


def write_json(data, fname):
    def _conv(o):
        if isinstance(o, np.int64):
            return int(o)

    with open(strftime("%d%H%M", gmtime()) + ".json", "w", encoding="utf8") as f:
        json_str = json.dumps(data, ensure_ascii=False, default=_conv)
        f.write(json_str)


def load_json(fname):
    with open(fname) as f:
        json_obj = json.load(f)

    return json_obj


def debug_json(r):
    print(json.dumps(r, ensure_ascii=False, indent=4))


def remove_seen(seen, l):
    seen = set(seen)
    return [x for x in set(l) if not (x in seen)]
