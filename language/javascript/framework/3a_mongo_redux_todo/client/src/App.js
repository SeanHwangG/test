import React from "react";
import { BrowserRouter as Router, Route } from "react-router-dom";

import Home from "./pages/Home";
import About from "./pages/About";
import Header from "./components/Header";
import Footer from "./components/Footer";

export default function App() {
  return (
    <Router>
      <Header></Header>
      <Route exact path="/" component={Home}></Route>
      <Route path="/about" component={About}></Route>
      <Footer></Footer>
    </Router>
  );
}
