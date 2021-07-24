import React from "react";
import Header from "./components/Header";
import { BrowserRouter, Route, Switch } from "react-router-dom";

export default function App() {
  return (
    <div className="App">
      <BrowserRouter>
        <Header />
        <Switch>
          <Route exact path="/" component={() => <div>Home</div>}></Route>
          <Route path="/services" component={() => <div>services</div>}></Route>
          <Route
            path="/customsoftware"
            component={() => <div>custom software</div>}
          ></Route>
          <Route
            path="/mobileapps"
            component={() => <div>mobile apps</div>}
          ></Route>
          <Route path="/websites" component={() => <div>websites</div>}></Route>
          <Route
            path="/revolution"
            component={() => <div>The Revolution</div>}
          ></Route>
          <Route path="/about" component={() => <div>About us</div>}></Route>
          <Route path="/contact" component={() => <div>Contact</div>}></Route>
          <Route path="/estimate" component={() => <div>Estimate</div>}></Route>
        </Switch>
      </BrowserRouter>
    </div>
  );
}
