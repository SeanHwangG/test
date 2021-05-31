import React, { useState, useEffect } from "react";
import Todo from "../components/Todo";
import TodoForm from "../components/TodoForm";

export default function Home(props) {
  const [todos, setTodos] = useState([]);

  return (
    <>
      {todos.map((todo) => (
        <Todo
          key={todo.id}
          id={todo.id}
          title={todo.title}
          done={todo.done}
          delTodo={props.deleteTodos}
        ></Todo>
      ))}
      <TodoForm addTodo={props.addTodos}></TodoForm>
    </>
  );
}
