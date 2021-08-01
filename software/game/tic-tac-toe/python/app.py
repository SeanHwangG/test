from flask import Flask, render_template, session, redirect, url_for
from flask_session import Session
from tempfile import mkdtemp
from livereload import Server


app = Flask(__name__)


@app.route("/")
def index():
  if "G" not in session:  # First move
    reset()

  return render_template("stage1.html", G=session["G"], turn=session["turn"], winner=session["winner"])


@app.route("/play/<int:row>/<int:col>")
def play(row, col):
  session["G"][row][col] = session["turn"]
  if session["turn"] == "X":
    session["turn"] = "O"
  else:
    session["turn"] = "X"
  session["winner"] = get_winner(session["G"])

  return redirect(url_for("index"))


@app.route("/reset")
def reset():
  session["G"] = [[None, None, None], [None, None, None], [None, None, None]]
  session["turn"] = "X"
  session["winner"] = False
  session["draw"] = False
  return redirect(url_for("index"))


def get_winner(G):
  """
    @params G : current grid
    @return winner of the game
  """
  for i in range(len(G)):
    if(G[i][0] == None):
      break
    if (G[i][0] == G[i][1] and G[i][0] == G[i][2]):
      return G[i][0]
  for i in range(len(G)):
    if G[0][i] == None:
      break
    if G[0][i] == G[1][i] and G[0][i] == G[2][i]:
      return G[0][1]
  if G[0][0] == G[1][1] == G[2][2] != None or G[2][0] == G[1][1] == G[0][2] != None:
    return G[0][0]

  for i in range(len(G)):
    for j in range(len(G)):
      if(G[i][j] == None):
        return ""

  return "draw"


if __name__ == "__main__":
  app.secret_key = 'super secret key'
  app.config['SESSION_TYPE'] = 'filesystem'
  server = Server(app.wsgi_app)
  Session(app)
  server.serve()
