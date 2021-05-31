import React from "react";
import ReactDOM from "react-dom";
import SuperBadger from "./SuperBadger";
import * as serviceWorker from "./serviceWorker";

ReactDOM.render(<SuperBadger />, document.getElementById("root"));

serviceWorker.unregister();
