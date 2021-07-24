import React, { useState, useEffect } from "react";
import AppBar from "@material-ui/core/AppBar";
import Toolbar from "@material-ui/core/Toolbar";
import Button from "@material-ui/core/Button";
import useScrollTrigger from "@material-ui/core/useScrollTrigger";
import { makeStyles } from "@material-ui/styles";
import { Link } from "react-router-dom";
import Slide from "@material-ui/core/Slide";
import logo from "../assets/logo.svg";
import Tab from "@material-ui/core/Tab";
import Tabs from "@material-ui/core/Tabs";

const useStyles = makeStyles((theme) => ({
  toolbarMargin: { ...theme.mixins.toolbar, marginBottom: "3em" },
  logo: {
    height: "7em",
  },
  logoContainer: { padding: 0, "&:hover": { backgroundColor: "transparent" } },
  tabContainer: {
    margin: "auto",
  },
  tab: {
    ...theme.typography.tab,
    minWidth: 10,
    marginLeft: "25px",
  },
  button: {
    borderRadius: "50px",
    marginLeft: "50px",
    marginRight: "25px",
    fontFamily: "Pacifico",
    fontSize: "1rem",
    textTransform: "none",
    height: "45px",
    color: "white",
  },
}));

function HideOnScroll(props) {
  const { children, window } = props;
  const trigger = useScrollTrigger({ target: window ? window() : undefined });

  return (
    <Slide appear={false} direction="down" in={!trigger}>
      {children}
    </Slide>
  );
}

export default function Header(props) {
  const [value, setValue] = useState(0);
  const classes = useStyles();
  const handleChange = (e, value) => {
    setValue(value);
  };
  useEffect(() => {
    if (window.location.pathname === "/" && value !== 0) setValue(0);
    if (window.location.pathname === "/services" && value !== 1) setValue(1);
    if (window.location.pathname === "/about" && value !== 2) setValue(2);
    if (window.location.pathname === "/contact" && value !== 3) setValue(3);
  }, [value]);

  return (
    <React.Fragment>
      <HideOnScroll>
        <AppBar position="fixed" color="primary">
          <Toolbar disableGutters>
            <Button
              className={classes.logoContainer}
              component={Link}
              to="/"
              disableRipple
            >
              <img className={classes.logo} alt="logo" src={logo} />
            </Button>
            <Tabs
              className={classes.tabContainer}
              value={value}
              onChange={handleChange}
            >
              <Tab
                className={classes.tab}
                component={Link}
                to="/"
                label="Home"
              />
              <Tab
                className={classes.tab}
                component={Link}
                to="/services"
                label="Services"
              />
              <Tab
                className={classes.tab}
                component={Link}
                to="/about"
                label="About us"
              />
              <Tab
                className={classes.tab}
                component={Link}
                to="/contact"
                label="Contact"
              />
            </Tabs>
            <Button
              variant="contained"
              color="secondary"
              className={classes.button}
            >
              Free Estimate
            </Button>
          </Toolbar>
        </AppBar>
      </HideOnScroll>
      <div className={classes.toolbarMargin} />
    </React.Fragment>
  );
}
