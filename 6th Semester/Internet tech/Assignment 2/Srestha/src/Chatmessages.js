import React from "react";
import "./Chatmessages.css";
import ReactEmoji from "react-emoji";
import socketClient  from "socket.io-client";
const SERVER = "http://127.0.0.1:8080";



class Chatmessages extends React.Component {
    constructor(props) {
        super(props);
        this.state = { 
            name : "",
            messages : []
    }
    }

    componentDidMount() {
        this.setState({ name : this.props.username });
        this.getmessages();
    }

    getmessages() {
        console.log("Hiiiiiiiiiii");
        var socket = socketClient (SERVER);
        socket.on('sentmessage', (arg1, arg2, arg3) => {
            console.log(`Sender: ${arg1}, Receiver: ${arg2}, the message: ${arg3}`);
            let message = {
                sender : `${arg1}`,
                receiver : `${arg2}`,
                body : `${arg3}`
            }
            this.setState({ 
                messages : [...this.state.messages, message]
              })
        });

        socket.on('startmessage', ({sender, receiver, body}) => {
            console.log(`Sender: ${sender}, Receiver: ${receiver}, the message: ${body}`);
            let message = {
                sender : `${sender}`,
                receiver : `${receiver}`,
                body : `${body}`
            }
            this.setState({ 
                messages : [...this.state.messages, message]
              })
        });
         
        this.socket = socket;
    }

    showmessages() {
        console.log(this.state.messages);
        const messages1 = this.state.messages.map(message => (
            <div className="messages">
                <div>
                    Sender:{message.sender}   /   Receiver:{message.receiver} <div className="message">{message.body}</div><br></br>
                </div>   
            </div>           
        )); 
        return <ul>{messages1}</ul>
    }

    render() {
        return (
            <div className="chatmessage">
                <h1>Messages for you---</h1>
                {this.showmessages()}              
            </div>
        )
    }
}


export default Chatmessages;