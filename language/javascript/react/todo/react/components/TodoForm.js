import React, { useState } from "react";

export default function TodoForm(props) {
  const [title, setTitle] = useState("");
  return (
    <form
      onSubmit={e => {
        e.preventDefault();
        props.addTodo(title);
        setTitle("");
      }}
    >
      <input onChange={e => setTitle(e.target.value)} value={title}></input>
      <button>submit</button>
    </form>
  );
}
