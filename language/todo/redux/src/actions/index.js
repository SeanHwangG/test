import { ADD_TODO, DELETE_TODO } from "./types";
export const addTodo = title => {
  return {
    type: ADD_TODO,
    payload: title
  };
};

export const delTodo = id => {
  return {
    type: DELETE_TODO,
    payload: id
  };
};
