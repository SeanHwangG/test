import React from "react";

export default function Todo(props) {
  return (
    <div>
      <p style={{ display: "inline" }}>{props.title}</p>
      <button onClick={() => { props.delTodo(props.id); }} >
        x
      </button>
    </div>
  );
}
