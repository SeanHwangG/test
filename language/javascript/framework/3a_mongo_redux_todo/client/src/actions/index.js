import { ADD_TODO, DELETE_TODO, GET_TODOS, LOADING_TODOS } from "./types";

const axios = require("axios").create({ baseURL: "http://localhost:5000" });

export const getTodos = () => dispatch => {
  dispatch(setTodosLoading());
  axios
    .get("/api/todos")
    .then(res =>
      dispatch({
        type: GET_TODOS,
        payload: res.data
      })
    )
    .catch(err => console.log("error"));
};

export const addTodo = todo => (dispatch, getState) => {
  console.log("In actions/addTodo");
  console.log(todo);
  axios
    .post("/api/todos", todo)
    .then(res => dispatch({ type: ADD_TODO, payload: res.data }))
    .catch(err => console.log(err));
};

export const delTodo = id => (dispatch, getState) => {
  axios
    .delete(`/api/todos/${id}`)
    .then(res =>
      dispatch({
        type: DELETE_TODO,
        payload: id
      })
    )
    .catch(err => console.log(err));
};

export const setTodosLoading = () => {
  return {
    type: LOADING_TODOS
  };
};
