const express = require("express");
const router = express.Router();

// Todo Model
const Todo = require("../../models/Todos");

// @route   GET api/todos
// @desc    Get All Todos
// @access  Public
router.get("/", (req, res) => {
  Todo.find().then(todos => res.json(todos));
});

// @route   POST api/todos
// @desc    Create An Todo
// @access  Private
router.post("/", (req, res) => {
  const newTodo = new Todo({
    title: req.body.title,
    id: req.body.id
  });

  newTodo.save().then(todo => res.json(todo));
});

// @route   DELETE api/todos/:id
// @desc    Delete A Todo
// @access  Private
router.delete("/:id", (req, res) => {
  Todo.findById(req.params.id)
    .then(todo => todo.remove().then(() => res.json({ success: true })))
    .catch(err => res.status(404).json({ success: false }));
});

module.exports = router;
