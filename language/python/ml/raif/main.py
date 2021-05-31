import pandas as pd
import numpy as np
import typing as tp
import json
from catboost import CatBoostRegressor

columns = ['full_time_home_goals', 'full_time_away_goals', 'half_time_home_goals', 'half_time_away_goals', 'home_shots',
           'away_shots', 'home_shots_on_target', 'away_shots_on_target', 'home_fouls', 'away_fouls', 'home_corners', 'away_corners',
           'home_yellow_cards', 'away_yellow_cards', 'home_red_cards', 'away_red_cards']
columns_known_before_match = ['Division', 'Time', 'home_team', 'away_team', 'Referee', 'home_coef', 'draw_coef', 'away_coef']

def get_team_profitability(teams_profitability: tp.Dict[int, tp.List], team_id, n_matches):
    if team_id in teams_profitability:
        return np.mean(teams_profitability[team_id][-n_matches:])
    else:
        return 0


def get_profitability(teams_profitability, row, n_matches=5):
    home_team_profitability = get_team_profitability(teams_profitability, row['home_team'], n_matches)
    away_team_profitability = get_team_profitability(teams_profitability, row['away_team'], n_matches)
    return home_team_profitability, away_team_profitability


def get_profitability_multiple_n_matches(teams_profitability, row, n_matches_range: tp.List):
    answer = []
    for n_matches in n_matches_range:
        home_team_profitability, away_team_profitability = get_profitability(teams_profitability, row, n_matches)
        answer.append(home_team_profitability)
        answer.append(away_team_profitability)
    return answer


def update_teams_profitability(home_coef, away_coef, home_goals, away_goals, home_team, away_team, teams_profitability):
    bet_on_home_profit = home_coef * (home_goals > away_goals) - 1
    if home_team in teams_profitability:
        teams_profitability[home_team].append(bet_on_home_profit)
    else:
        teams_profitability[home_team] = [bet_on_home_profit]
    bet_on_away_profit = away_coef * (home_goals < away_goals) - 1
    if away_team in teams_profitability:
        teams_profitability[away_team].append(bet_on_away_profit)
    else:
        teams_profitability[away_team] = [bet_on_away_profit]


# threshold from fit
def make_bet(model, features: list, threshold=0.0802):
    predict = model.predict(features, verbose=False)
    if predict > threshold:
        return 'HOME'
    else:
        return 'SKIP'

def float_for_time(a):
    try:
        return float(a)
    except:
        return -1

model = CatBoostRegressor()
model.load_model('model.cbm')
#doesnt work otherwise
model._init_params['verbose'] = None

with open('current_profitability.json', 'r') as fp:
    teams_profitability = json.load(fp)

n_matches = int(input())
predict_columns = ['Division']
match_not_happened = True
for _ in range(2 * n_matches):
    if match_not_happened:
        row = list(map(float_for_time, input().split()))
        row = pd.Series(row, index=columns_known_before_match)
        all_profitability = get_profitability_multiple_n_matches(teams_profitability, row, list(range(1, 10, 2)))
        features = [*all_profitability, *row[predict_columns]]
        print(make_bet(model, features), flush=True)
        match_not_happened = False
    else:
        home_goals, away_goals, *args = input().split()
        update_teams_profitability(row['home_coef'], row['away_coef'], home_goals, away_goals, row['home_team'], row['away_team'], teams_profitability)
        match_not_happened = True
