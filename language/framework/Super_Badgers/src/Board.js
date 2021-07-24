import React, { Component } from "react";
import "./index.css";

export default class Board extends Component {
  render() {
    let P = this.props.G.players;
    let C = this.props.G.cells;
    let D = this.props.G.die;
    let T = this.props.ctx.currentPlayer;

    const distance = (player, index) => {
      let BFS = [player];
      let visited = new Set([player]);
      let ret = 0;

      while (BFS.length > 0) {
        for (let i = BFS.length; i > 0; i--) {
          let cur = BFS.shift();
          if (cur === index) {
            return ret;
          }
          for (let j = 0; j < C.length; j++) {
            if (C[cur].connected[j] === 1 && !(j in visited)) {
              visited.add(j);
              BFS.push(j);
            }
          }
        }
        ret++;
      }
      return -1;
    };

    /** check if mouse is in a cell
     *  @return index of clicked cell, -1 otherwise
     */
    const Click = (x, y) => {
      console.log(x + " " + y);
      // eslint-disable-next-line
      for (let c of C) {
        if (
          Math.sqrt((c.X - x) ** 2 + (c.Y - y) ** 2) < 10 &&
          distance(P[T].position, c.index) <= D
        ) {
          if (c.type === 1) {
          }
          return this.props.moves.move(c.index);
        }
      }
      return -1;
    };

    let main = [],
      side = [],
      foot = [];
    main.push(
      <img
        className="board"
        src="board.jpeg"
        alt="f"
        onClick={e => CLIck(e.clientX, e.clientY)}
      ></img>
    );

    for (let i = 0; i < P.length; i++) {
      main.push(
        <img
          className="icon"
          style={{
            top: C[P[i].position].Y - 30,
            left: C[P[i].position].X - 30
          }}
          src={"icon" + P[i].type + ".jpg"}
          alt="c"
        ></img>
      );
    }
    const missionLoc = {
      7: { X: 106, Y: 64, id: 1 },
      17: { X: 292, Y: 94, id: 2 },
      24: { X: 458, Y: 81, id: 3 },
      32: { X: 611, Y: 135, id: 4 },
      8: { X: 135, Y: 246, id: 5 },
      30: { X: 432, Y: 248, id: 6 },
      5: { X: 122, Y: 479, id: 7 },
      14: { X: 219, Y: 403, id: 8 },
      23: { X: 357, Y: 473, id: 9 },
      36: { X: 538, Y: 478, id: 10 },
      40: { X: 701, Y: 478, id: 11 }
    };
    // eslint-disable-next-line
    for (let m of M) {
      main.push(
        <img
          className="mission"
          style={{
            top: missionLoc[m].Y - 50,
            left: missionLoc[m].X - 50
          }}
          src={"el" + missionLoc[m].id + ".jpg"}
          alt="c"
        ></img>
      );
    }
    // eslint-disable-next-line
    for (let o of O) {
      main.push(
        <img
          className="takeout"
          style={{
            top: C[o].Y - 15,
            left: C[o].X - 18
          }}
          onClick={e => CLIck(e.clientX, e.clientY)}
          src={"takeout.png"}
          alt="c"
        ></img>
      );
    }

    side.push(
      <React.Fragment>
        <p>{this.props.G.die}</p>
        <br></br>
        <button onClick={() => this.props.moves.roll()}>Roll Die</button>
        <br></br>
      </React.Fragment>
    );

    if (C[P[T].position].type === 2) {
      side.push(
        <button onClick={() => this.props.moves.pick()}>Attack?</button>
      );
    } else {
      side.push(<button> {C[P[T].position].type} </button>);
    }

    for (let i = 0; i < P.length; i++) {
      let stat = [];
      stat.push(
        <img
          className="playerCard"
          src={"character" + P[i].type + ".jpg"}
          alt="as"
        ></img>
      );
      foot.push(
        <div style={{ height: "50%", float: "top", position: "relative" }}>
          {stat}
        </div>
      );
    }

    //main.push(<div style={{ width: "65%" }}>{{ main }}</div>);
    return (
      <div className="container">
        <div className="main">{main}</div>
        <div className="side">{side}</div>
        <div className="foot">{foot}</div>
      </div>
    );
  }
}
