import React, { Component } from "react";

export default class App extends Component {
  constructor() {
    super();
    this.state = {
      number: 0
    };
  }
  render() {
    return (
      <div className="App">
        <p>{this.state.number}</p>
        <button onClick={() => { this.setState({ number: this.state.number + 1 }); }}> + </button>
        <button onClick={() => { this.setState({ number: this.state.number - 1 }); }}> - </button>
        <button onClick={() => { this.setState({ number: 0 }); }}> Reset </button>
      </div>
    );
  }
}
