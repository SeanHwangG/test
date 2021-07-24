import React, { Component } from "react";

/**
 *  type 0 : normal
 *       1 : takeout
 *       2 : mission
 */
export default class Point extends Component {
  constructor(props) {
    const takeouts = [0, 10, 18, 39, 41, 49, 54, 59];
    const missions = [7, 17, 24, 32, 8, 30, 5, 14, 23, 36, 40];
    super(props);
    this.state = {
      index: props.index,
      X: props.X,
      Y: props.Y,
      type: props.index in takeouts ? 1 : props.index in missions ? 2 : 0,
      connected: props.connected
    };
    this.X = props.X;
  }
  render() {
    return <div></div>;
  }
}
