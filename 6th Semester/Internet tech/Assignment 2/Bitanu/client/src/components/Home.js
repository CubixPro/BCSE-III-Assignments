import socket from "../socket.js";
import Chat from "./Chat.js";
import Login from "./Login.js";

import React, { Component } from "react";

export default class Home extends Component {
  constructor(props) {
    super(props);
    this.state = {
      userNameAlreadySelected: false,
    };
    this.onUsernameSelect = this.onUsernameSelect.bind(this);
  }
  onUsernameSelect(username) {
    this.setState({ userNameAlreadySelected: true });
    socket.auth = { username };
    socket.connect();
  }

  componentDidMount() {
    const sessionID = localStorage.getItem("sessionID");

    if (sessionID) {
      this.setState({userNameAlreadySelected : true});
      socket.auth = { sessionID };
      socket.connect();
    }

    socket.on("session", ({ sessionID, userID }) => {
      // attach the session ID to the next reconnection attempts
      socket.auth = { sessionID };
      // store it in the localStorage
      localStorage.setItem("sessionID", sessionID);
      // save the ID of the user
      socket.userID = userID;
    });

    socket.on("connect_error", (err) => {
      if (err.message === "invalid username") {
        this.setState({userNameAlreadySelected : false});
      }
    });
  
  }
  componentWillUnmount() {
    socket.off("connect_error");
  }
  render() {
    return (
      <div>{this.state.userNameAlreadySelected ? <Chat /> : <Login onUsernameSelect={this.onUsernameSelect} />}</div>
    );
  }
}
