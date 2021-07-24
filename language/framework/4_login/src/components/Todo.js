import React, { useState } from "react";
import { auth } from "../database/Firebase";

export default function Todo(props) {
  const [user, setUser] = useState();
  auth.onAuthStateChanged(user => {
    setUser(user);
  });

  return (
    <div>
      <p style={{ display: "inline" }}>{props.title}</p>
      {user ? (
        <button
          onClick={() => {
            props.delTodo(props.id);
          }}
        >
          x
        </button>
      ) : (
        <></>
      )}
    </div>
  );
}
