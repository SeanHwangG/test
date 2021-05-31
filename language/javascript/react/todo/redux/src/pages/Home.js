import React from "react";
import Todo from "../components/Todo";
import TodoForm from "../components/TodoForm";
import { connect } from "react-redux";

function Home({ todos }) {
  return (
    <>
      <TodoForm></TodoForm>
      {todos.map(todo => (
        <Todo key={todo.id} id={todo.id} title={todo.title}></Todo>
      ))}
    </>
  );
}

const mapStateToProps = state => ({
  todos: state.todos
});

export default connect(mapStateToProps)(Home);
