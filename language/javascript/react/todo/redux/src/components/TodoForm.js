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
          props.addTodo(input.value);
          input.value = "";
        }}
      >
        <input ref={node => (input = node)} />
        <button type="submit">Add Todo</button>
      </form>
    </div>
  );
}

const mapDispatchToProps = dispatch => ({
  addTodo: title => dispatch(addTodo(title))
});

export default connect(null, mapDispatchToProps)(TodoForm);
