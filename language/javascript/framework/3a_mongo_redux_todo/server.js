const express = require("express");
const mongoose = require("mongoose");
const bodyParser = require("body-parser");
const todos = require("./routes/api/todos");
const cors = require("cors");

const app = express();

// Bodyparser Middleware
app.use(bodyParser.json());
app.use(cors());
/*
app.use(function(req, res, next) {
  res.setHeader("Access-Control-Allow-Origin", "http://localhost:3000");
  res.setHeader(
    "Access-Control-Allow-Methods",
    "GET, POST, OPTIONS, PUT, PATCH, DELETE"
  );
  res.setHeader(
    "Access-Control-Allow-Headers",
    "X-Requested-With,content-type"
  );
  res.setHeader("Access-Control-Allow-Credentials", true);
  next();
});
*/

// DB config
const db = require("./config/keys").mongoURI;

// Connect to Mongo
mongoose
  .connect(db, { useNewUrlParser: true, useUnifiedTopology: true })
  .then(() => console.log("MongoDB Connected..."))
  .catch(err => console.log(err));

app.use("/api/todos", todos);

const port = process.env.PORT || 5000;

app.listen(port, () => console.log(`Server started on port ${port}`));
