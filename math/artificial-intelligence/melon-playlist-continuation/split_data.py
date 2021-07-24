# -*- coding: utf-8 -*-
import copy
import random

import fire
import numpy as np
from arena_util import load_json
from arena_util import write_json


class ArenaSplitter:
    def _split_data(self, playlists):
        tot = len(playlists)
        train = playlists[:int(tot*0.80)]
        val = playlists[int(tot*0.80):]

        return train, val

    def _mask(self, playlists, mask_cols, del_cols):
        q_pl = copy.deepcopy(playlists)
        a_pl = copy.deepcopy(playlists)

        for i in range(len(playlists)):
            for del_col in del_cols:
                q_pl[i][del_col] = []
                if del_col == 'songs':
                    a_pl[i][del_col] = a_pl[i][del_col][:100]
                elif del_col == 'tags':
                    a_pl[i][del_col] = a_pl[i][del_col][:10]

            for col in mask_cols:
                mask_len = len(playlists[i][col])
                mask = np.full(mask_len, False)
                mask[:mask_len//2] = True
                np.random.shuffle(mask)

                q_pl[i][col] = list(np.array(q_pl[i][col])[mask])
                a_pl[i][col] = list(np.array(a_pl[i][col])[np.invert(mask)])

        return q_pl, a_pl

    def _mask_data(self, plylists):
        plylists = copy.deepcopy(plylists)
        n_plylists = len(plylists)
        song = plylists[:int(n_plylists * 0.3)]
        song_tag = plylists[int(n_plylists * 0.3):int(n_plylists * 0.8)]
        tag = plylists[int(n_plylists * 0.8):int(n_plylists * 0.95)]
        title = plylists[int(n_plylists * 0.95):]

        print(f"""Total: {len(plylists)},
              Song only: {len(song)},
              Song & Tags: {len(song_tag)},
              Tags only: {len(tag)},
              Title only: {len(title)} """)

        song_q, song_a = self._mask(song, ['songs'], ['tags'])
        songtag_q, songtag_a = self._mask(song_tag, ['songs', 'tags'], [])
        tag_q, tag_a = self._mask(tag, ['tags'], ['songs'])
        title_q, title_a = self._mask(title, [], ['songs', 'tags'])

        q = song_q + songtag_q + tag_q + title_q
        a = song_a + songtag_a + tag_a + title_a

        shuffle_indices = np.arange(len(q))
        np.random.shuffle(shuffle_indices)

        q = list(np.array(q)[shuffle_indices])
        a = list(np.array(a)[shuffle_indices])

        return q, a

    def run(self, fname):
        random.seed(777)

        print("Reading data...\n")
        playlists = load_json(fname)
        random.shuffle(playlists)
        print(f"Total playlists: {len(playlists)}")

        print("Splitting data...")

        train, val = self._split_data(playlists)
        write_json(train, "process/train.json")
        write_json(val, "process/val.json")

        val_q, val_a = self._mask_data(val)
        write_json(val_q, "process/val_q.json")
        write_json(val_a, "process/val_a.json")


if __name__ == "__main__":
    fire.Fire(ArenaSplitter)
