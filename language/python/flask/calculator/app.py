from flask import Flask, render_template, request
from livereload import Server
app = Flask(__name__)


@app.route('/')
def index():
  return render_template('index.html')


@app.route('/stage1', methods=['GET', 'POST'])
def stage1():
  if request.method == "POST":
    var_1 = request.form.get("var_1", type=int)
    var_2 = request.form.get("var_2", type=int)
    if request.form.get("cars") == "subtract":
      answer = var_1 - var_2
    else:
      answer = var_1 + var_2
  return render_template('stage1.html', entry="result")


@app.route('/stage2', methods=['GET', 'POST'])
def stage2():
  answer = "select operations"
  if request.method == "POST":
    var_1 = request.form.get("var_1", type=int)
    var_2 = request.form.get("var_2", type=int)
    op = request.form.get("op")
    if not var_1 or not var_2:
      answer = "Please enter value"
    elif op == "-":
      answer = var_1 - var_2
    elif op == '+':
      answer = var_1 + var_2
    elif op == '*':
      answer = var_1 * var_2
    elif op == '/':
      if var_2 == 0:
        answer = "divide by 0 error"
      else:
        answer = var_1 / var_2
  return render_template('stage2.html', entry=answer)


results = []


@app.route('/stage3', methods=['GET', 'POST'])
def stage3():
  if request.method == "POST":
    # TODO eval / try, list
    pass
  return render_template('stage3.html', results=results)


@app.route('/stage4', methods=['GET', 'POST'])
def stage4():
  if request.method == "POST":
    try:
      ans = eval(request.form.get("equation"))
    except:
      ans = "ERROR"
    results.append(ans)
    return render_template('stage4.html', results=results)
  return render_template('stage4.html', results=results)


if __name__ == '__main__':
  server = Server(app.wsgi_app)
  server.serve()
