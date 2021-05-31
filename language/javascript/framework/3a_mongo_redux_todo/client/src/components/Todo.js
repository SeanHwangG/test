import React from "react";
import { delTodo } from "../actions";
import { connect } from "react-redux";

function Todo(props) {
  return (
    <div>
      <p style={{ display: "inline" }}>{props.title}</p>
      <button
        onClick={() => {
          props.delTodo(props._id);
        }}
      >
        x
      </button>
    </div>
  );
}

export default connect(null, { delTodo })(Todo);
