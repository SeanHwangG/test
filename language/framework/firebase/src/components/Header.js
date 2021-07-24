import React, { useEffect } from "react";
import { Button } from "@material-ui/core";
import { auth } from "../database/firebase";

export default function Header() {
  useEffect = () => {
      
  };
  return (
    <>
      <h1>Hi {}</h1>
      <Button
        type="submit"
        variant="contained"
        color="secondary"
        onClick={() => auth.signInWithRedirect(new auth.GoogleAuthProvider())}
        to="/login"
      >
        Sign in
      </Button>
    </>
  );
}
