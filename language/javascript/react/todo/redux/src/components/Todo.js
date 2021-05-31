import React from "react";
import { delTodo } from "../actions";
import { connect } from "react-redux";

function Todo(props) {
  return (
    <div>
      <p style={{ display: "inline" }}>{props.title}</p>
      <button
        onClick={() => {
          props.delTodo(props.id);
        }}
      >
        x
      </button>
    </div>
  );
}

const mapDispatchToProps = dispatch => ({
  delTodo: id => dispatch(delTodo(id))
});

export default connect(null, mapDispatchToProps)(Todo);
