import { ADD_TODO, DELETE_TODO } from "../actions/types";
const uuid = require("uuid/v1");

const todos = (state = [], action) => {
  switch (action.type) {
    case ADD_TODO:
      return [...state, { id: uuid(), title: action.payload }];
    case DELETE_TODO:
      return state.filter(todo => todo.id !== action.payload);
    default:
      return state;
  }
};
export default todos;
