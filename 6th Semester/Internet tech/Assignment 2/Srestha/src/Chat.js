import React from "react";
import "./Chat.css";
import RoomList from "./RoomList";
import Chatmessages from "./Chatmessages";
import socketClient  from "socket.io-client";
const SERVER = "http://127.0.0.1:8080";



class Chat extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      username: "",
      current_room: "",
      message: "",
      socket: null
    }
    this.handleChange = this.handleChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
  }

  socket;

  callbackFunction = (childData) => {
    this.setState({current_room: childData})
  }

  componentDidMount() {
    this.setState({username: `${this.props.match.params.name}`});
    this.setState({current_room: ""});
    this.setState({message : ""});
    this.configureSocket();
  }

  configureSocket(){
    var socket = socketClient (SERVER);
    console.log("hello world!!!");
    socket.on('connect', () => {
        console.log(`I'm connected with the back-end`);
        socket.emit("hello", `${this.state.username}`);
    });

    

    socket.on("disconnect", () => {
        console.log(socket.connected); // false
    });

    this.socket = socket;
  }

  handleChange(event){ 
    this.setState({ 
      [event.target.name] : event.target.value 
    }) 
  }

  handleSubmit(event) {
    event.preventDefault()  
    var socket = socketClient (SERVER);
    console.log("Sending message!!!");
    let dm = "No"
    if (`${this.state.current_room}`.split(" ").length > 1)
      dm = "Yes";
    else
      dm = "No";
    socket.on('connect', () => {
      console.log(`The message sent is: ${this.state.username}  ${this.state.current_room}  ${this.state.message}`, dm)
        socket.emit("sendmessage", `${this.state.username}`, `${this.state.current_room}`, `${this.state.message}`, dm);
    });
    this.socket = socket;
  {/*this.setState({ message : '' })
     Hello! {this.state.current_room} receives {this.state.message}*/}
  }

  render() {
    return (
      <div>
        <center><h1>Welcome to the chat box {this.state.username}!!!</h1></center>
        <RoomList parentCallback = {this.callbackFunction} socketfromParent = {this.state.socket} namefromParent = {this.state.username}/>
        <div className="chatspace">
          <Chatmessages username = {this.state.username} />
        </div>
        <div className="sendbox">
        <label className="label">Message:   </label>
        <input
            className="typemessage"  
            name='message'
            value={this.state.message} 
            onChange={this.handleChange} 
          />
          <button className="sendbutton" type="submit" onClick={this.handleSubmit}>Send</button>
        </div>
      </div>
      
    );
  }
}
export default Chat;
