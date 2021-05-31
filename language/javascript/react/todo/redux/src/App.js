import React from "react";
import { BrowserRouter as Router, Route } from "react-router-dom";

import Home from "./pages/Home";
import Header from "./components/Header";

export default function App() {
  return (
    <Router>
      <Header></Header>
      <Route exact path="/" component={Home}></Route>
    </Router>
  );
}
