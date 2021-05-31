import {
  ADD_TODO,
  GET_TODOS,
  DELETE_TODO,
  LOADING_TODOS
} from "../actions/types";

const initialState = {
  items: [],
  loading: false
};

const todos = (state = initialState, action) => {
  console.log("IN todos reducers");
  console.log(action.type);
  switch (action.type) {
    case GET_TODOS:
      return { ...state, loading: false, items: action.payload };
    case ADD_TODO:
      return { ...state, items: [action.payload, ...state.items] };
    case DELETE_TODO:
      return {
        ...state,
        items: state.items.filter(todo => todo._id !== action.payload)
      };
    case LOADING_TODOS:
      return {
        ...state,
        loading: true
      };
    default:
      return state;
  }
};
export default todos;
