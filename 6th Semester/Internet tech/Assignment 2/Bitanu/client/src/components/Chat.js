import React, { Component } from "react";
import socket from "../socket.js";

export default class Chat extends Component {
  constructor(props) {
    super(props);
    this.state = {
      selectedUser: null,
      users: [],
      value: "",
    };
  }

  onMessage(content) {
    if (this.state.selectedUser) {
      socket.emit("unicast", {
        content,
        to: this.state.selectedUser.userID,
      });
      let user = this.state.selectedUser;
      user.messages.push({ content, fromSelf: true });
      this.setState({ selectedUser: user });
    }
  }
  onImageClick(e) {
    e.preventDefault();
    console.log("event ", e);
    if (e.target.files && e.target.files.length > 0) {
      let file = e.target.files[0];
      let reader = new FileReader();
      if (!reader) return;
      reader.onload = (event) => {
        socket.emit("img", {
          content: event.target.result,
          to: this.state.selectedUser.userID,
          image: true,
        });
        let user = this.state.selectedUser;
        user.messages.push({
          content: event.target.result,
          image: true,
          fromSelf: true,
        });
        this.setState({ selectedUser: user });
      };
      reader.readAsDataURL(file);
    }
  }
  onSelectUser(user) {
    this.setState({ selectedUser: user });
  }
  handleChange(e) {
    this.setState({ value: e.target.value });
  }
  handleSubmit(e) {
    e.preventDefault();
    this.onMessage(this.state.value);
  }
  componentDidMount() {
    socket.on("connect", () => {
      let currentUsers = this.state.users;
      currentUsers.forEach((user) => {
        if (user.self) {
          user.connected = true;
        }
      });
      this.setState({ users: currentUsers });
    });

    socket.on("disconnect", () => {
      let currentUsers = this.state.users;
      currentUsers.forEach((user) => {
        if (user.self) {
          user.connected = false;
        }
      });
      this.setState({ users: currentUsers });
    });

    const initReactiveProperties = (user) => {
      user.connected = true;
      user.messages = [];
      user.hasNewMessages = false;
    };

    socket.on("users", (users) => {
      users.forEach((user) => {
        for(let i=0;i<this.state.users.length;i++){
          if (this.state.users[i].userID===user.userID)
            return;
        }
        user.self = user.userID === socket.userID;
        initReactiveProperties(user);
        let currentUsers = this.state.users;
        currentUsers.push(user);
        this.setState({users: currentUsers});
      });
      this.setState({
        users: users.sort((a, b) => {
          if (a.self) return -1;
          if (b.self) return 1;
          if (a.username < b.username) return -1;
          return a.username > b.username ? 1 : 0;
        }),
      });
    });

    socket.on("user connected", (user) => {
      for(let i=0;i<this.state.users.length;i++){
        if (this.state.users[i].userID===user.userID)
          return;
      }
      initReactiveProperties(user);
      let currentUsers = this.state.users;
      currentUsers.push(user);
      this.setState({ users: currentUsers });
    });

    socket.on("user disconnected", (id) => {
      let currentUsers = this.state.users;
      for (let i = 0; i < currentUsers.length; i++) {
        if (currentUsers[i].userID === id) {
          currentUsers[i].connected = false;
          break;
        }
      }
      this.setState({ users: currentUsers });
    });

    socket.on("unicast", ({ content, from }) => {
      let currentUsers = this.state.users;

      for (let i = 0; i < currentUsers.length; i++) {
        if (currentUsers[i].userID === from) {
          currentUsers[i].messages.push({
            content,
            fromSelf: false,
          });
          break;
        }
      }
      this.setState({ users: currentUsers });
    });
    
    socket.on("newimg", ({ content, image, from, to }) => {
      let currentUsers = this.state.users;

      for (let i = 0; i < currentUsers.length; i++) {
        const fromSelf = socket.userID === from;
        if (currentUsers[i].userID === (fromSelf ? to : from)) {
          currentUsers[i].messages.push({
            content,
            image,
            fromSelf,
          });
          if (currentUsers[i] !== this.state.selectedUser) {
            currentUsers[i].hasNewMessages = true;
          }
          this.setState({ users: currentUsers });
          break;
        }
      }
    });
   
  }
  componentWillUnmount() {
    socket.off("connect");
    socket.off("disconnect");
    socket.off("users");
    socket.off("user connected");
    socket.off("user disconnected");
    socket.off("unicast");

  }
  render() {
    return (
      <div style={{}}>
        <ul>
          {this.state.users.map((user) => (
            <li key={`${user.userID}`}>
              {user.userID}
              {user.username}
              <button onClick={() => this.onSelectUser(user)}>Select</button>
            </li>
          ))}
        </ul>
        <div>
          <ul>
            {this.state.selectedUser &&
              this.state.selectedUser.messages.map((message, index) => (
                <li key={index}>{message.image ? (
                      <div>
                        <img
                          style={{ height: "300px", width: "300px" }}
                          src={`${message.content}`}
                          alt=""
                        />
                      </div>
                    ) : (
                      message.content
                    )}</li>
              ))}
          </ul>
          <form onSubmit={(e) => this.handleSubmit(e)}>
            <label>
              Message:
              <input type="text" onChange={(e) => this.handleChange(e)} />
            </label>
            <input type="submit" value="Send" />
          </form>
        <label htmlFor="sendImage">
                <input
                  id="sendImage"
                  type="file"
                  value=""
                  onChange={(e) => this.onImageClick(e)}
        />
        </label>
        </div>
      </div>
    );
  }
}
