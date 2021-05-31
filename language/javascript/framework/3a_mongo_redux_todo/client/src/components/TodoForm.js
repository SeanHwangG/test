import React from "react";
import { connect } from "react-redux";
import { addTodo } from "../actions";

function TodoForm(props) {
  let input;
  return (
    <div>
      <form
        onSubmit={e => {
          e.preventDefault();
          console.log("In form/submit");
          console.log(input.value);
          const newTodo = {
            title: input.value
          };
          props.addTodo(newTodo);
          input.value = "";
        }}
      >
        <input ref={node => (input = node)} />
        <button type="submit">Add Todo</button>
      </form>
    </div>
  );
}
const mapStateToProps = state => ({
  todos: state.todos
});

export default connect(mapStateToProps, { addTodo })(TodoForm);
