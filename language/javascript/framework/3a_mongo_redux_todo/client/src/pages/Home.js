import React, { useEffect } from "react";
import Todo from "../Todo";
import TodoForm from "../TodoForm";
import { getTodos } from "../../actions";
import { connect } from "react-redux";

function Home(props) {
  useEffect(() => {
    props.getTodos();
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);
  return (
    <>
      {props.todos.items.map(todo => (
        <Todo key={todo._id} _id={todo._id} title={todo.title}></Todo>
      ))}
      <TodoForm></TodoForm>
    </>
  );
}

const mapStateToProps = state => ({
  todos: state.todos
});

export default connect(mapStateToProps, { getTodos })(Home);
