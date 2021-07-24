import React, { useEffect, useState } from "react";
import { BrowserRouter as Router, Route } from "react-router-dom";
import Home from "./pages/Home";
import About from "./pages/About";
import Profile from "./pages/Profile";
import Signin from "./pages/Signin";
import Signup from "./pages/Signup";
import Header from "./components/Header";
import { firestore, auth } from "./database/Firebase";

export default function App() {
  const [user, setUser] = useState();

  useEffect(() => {
    auth.onAuthStateChanged((user) => {
      setUser(user);
    });
  }, []);

  const signin = (form) => {
    auth.signInWithEmailAndPassword(form.email, form.password);
  };

  const signup = (form) => {
    auth
      .createUserWithEmailAndPassword(form.email, form.password)
      .catch((e) => console.log(e));
    firestore.collection()
    
  };

  return (
    <Router>
      <Header user={user} />
      <Route exact path="/" render={() => <Home user={user} />} />
      <Route path="/about" component={About}></Route>
      <Route path="/profile" render={() => <Profile user={user} />}></Route>
      <Route path="/signup" render={() => <Signup signup={signup} />}></Route>
      <Route path="/signin" render={() => <Signin signin={signin} />}></Route>
    </Router>
  );
}
