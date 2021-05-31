import React from "react";
import ReactDOM from "react-dom";
import App from "./App";
import { ThemeProvider } from "@material-ui/styles";
import createMuiTheme from "./ui/Theme.js";

ReactDOM.render(
  <ThemeProvider theme={createMuiTheme}>
    <App />
  </ThemeProvider>,
  document.getElementById("root")
);
