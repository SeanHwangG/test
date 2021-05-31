import Home from "./pages/Home";
import Login from "./pages/Login";
import app from "./database/firebase";
import React, { useState, useEffect } from "react";
import firebase, { auth, firestore } from "firebase";

import { BrowserRouter as Router, Switch, Route } from "react-router-dom";

function App() {
  const [user, setUser] = useState(null);

  useEffect(() => {
    console.dir(firestore);
    const todos = firestore.collection("todos").get();
  }, []);

  return (
    <Router>
      <Switch>
        <Route exact path="/" component={Home} />
        <Route exact path="/login" component={Login} />
      </Switch>
    </Router>
  );
}

export default App;
