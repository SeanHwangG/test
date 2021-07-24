import React, { useState, useEffect } from "react";
import { Link } from "react-router-dom";
import { auth, provider } from "../database/Firebase";

export default function Header(props) {
  return (
    <div>
      <h1>Todo app</h1>
      <Link to="/">Home</Link>
      <> | </>
      <Link to="/about">About</Link>
      <> | </>
      <Link to="/profile">Profile</Link>
      {props.user && (
        <>
          |{" "}
          <Link to="/" onClick={() => auth.signOut()}>
            sign out
          </Link>
        </>
      )}
      {!props.user && (
        <>
          | <Link to="/signin">Sign in</Link>
        </>
      )}
      {!props.user && (
        <>
          | <Link to="/signup">Sign up</Link>
        </>
      )}
    </div>
  );
}
