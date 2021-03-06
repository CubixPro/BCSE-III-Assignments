import React, { Component } from 'react';
import { Redirect } from 'react-router-dom';
import io from 'socket.io-client';
import ScrollToBottom from 'react-scroll-to-bottom';
import '../styles/dashboard.css';

import Message from './message';
import Input from './input';
let socket;

class Dashboard extends Component {

    constructor(props) {
        super();
        socket = io('http://localhost:5000', { withCredentials: true });

        this.state = {
            name: props.location.state.name,
            currRoom: null,
            users: null,
            rooms: null,
            usersBool: false,
            roomsBool: false,
            newRoomBool: false,
            chatBool: false,
            messages: [],
            currMessage: '',
            usersInCurrRoom: [],
            redirect: false
        }
        this.toggleUsers = this.toggleUsers.bind(this);
        this.toggleRooms = this.toggleRooms.bind(this);
        this.toggleNewRoom = this.toggleNewRoom.bind(this);
        this.createNewRoom = this.createNewRoom.bind(this);
        this.userLogout = this.userLogout.bind(this);
        this.switchRoom = this.switchRoom.bind(this);
        this.sendMessage = this.sendMessage.bind(this);
        this.setMessage = this.setMessage.bind(this);
        this.leaveRoom = this.leaveRoom.bind(this);

        socket.emit('addId', {name: props.location.state.name});
    }

    componentDidMount() {

        socket.on('message', message => {
            this.setState({
                messages: [...this.state.messages, message]
            });
        });
    
        socket.on('roomData', ({ room, users}) => {
            this.setState({ usersInCurrRoom: users});
        });
    }

    toggleUsers() {
        socket.emit('getUsers', (users) => {
            let change = !this.state.usersBool;
            this.setState({
                users: users,
                usersBool: change
            });
        });      
    }

    toggleRooms() {
        socket.emit('getRooms', (rooms) => {
            let change = !this.state.roomsBool;
            this.setState({
                rooms: rooms,
                roomsBool: change
            });
        });
    }

    toggleNewRoom() {
        let change = !this.state.newRoomBool;
        this.setState({ newRoomBool: change});
    }

    leaveRoom() {
        socket.emit('leaveRoom', {roomName: this.state.currRoom, name: this.state.name}, () => {
            console.log(`${this.state.name} has left the room`);
            this.setState({
                chatBool: false,
                currRoom: null,
                messages: [],
                currMessage: '',
                usersInCurrRoom: []
            })
        })
    }

    createNewRoom(roomName) {
        socket.emit('newRoom', {roomName: roomName, name: this.state.name}, ({newRoom, error}) => {
            if(error) console.log(error);
            else{
                this.setState({ 
                    chatBool: true,
                    currRoom: newRoom.room,
                    messages: [],
                    currMessage: '',
                    usersInCurrRoom: []
                }, () => {
                    socket.emit('join', { name: this.state.name, room: this.state.currRoom })
                })
            }
        });
    }

    switchRoom(room) {

        if(!this.state.currRoom) {
            this.setState({ 
                chatBool: true, 
                currRoom: room 
            }, () => {
                socket.emit('join', { name: this.state.name, room: this.state.currRoom })
            })
        }
        else if(this.state.currRoom !== room) {
            socket.emit('leaveRoom', {roomName: this.state.currRoom, name: this.state.name}, () => {
                console.log(`${this.state.name} has left the room`);
                this.setState({currRoom: room,
                            messages: [],
                            currMessage: '',
                            usersInCurrRoom: []}, () => {
                            socket.emit('join', { name: this.state.name, room: this.state.currRoom })
                        });
            }) 
        }
    }

    userLogout() {
        if(this.state.currRoom) {
            socket.emit('leaveRoom', {roomName: this.state.currRoom, name: this.state.name}, () => {
                console.log(`${this.state.name} has left the room`);
            })
        }
        socket.emit('logout', () => {
            console.log('Logged out successfully');
            this.setState({
                redirect: true,
                chatBool: false,
                currRoom: null,
            })
        })
    }

    sendMessage(event) {
        event.preventDefault();
        if(this.state.currMessage) {
            socket.emit('sendMessage', {room: this.state.currRoom, message: this.state.currMessage});
            this.setState({ currMessage: ''});
        }
    }

    setMessage(value) {
        this.setState({ currMessage: value});
    }

    render() {
        if (this.state.redirect) {
            socket.disconnect()
            socket.off();
            return <Redirect to= '/' />
        }

        const showUsers = (() => {
            if(this.state.usersBool) {
                return (
                    <div>
                        {this.state.users.map((user, index) => {
                            return (
                                <div key={index}>{user.username}</div>
                            )
                        })}
                    </div>
                )
            }
            else return <div></div>
        })

        const showRooms = (() => {
            if(this.state.roomsBool) {
                return (
                    <div>
                        {this.state.rooms.map((room, index) => {
                            return (
                                <div>
                                    <span className="roomList">{room.room}</span>
                                    <button key={index} onClick= {() => this.switchRoom(room.room)}>Join</button>
                                </div>
                            )
                        })}
                    </div>
                )
            }
            else return <div></div>
        })

        const createRoom = (() => {
            if(this.state.newRoomBool) {
                return (
                    <div>
                        <input className="newRoomInput" type="text" placeholder="New Room Name" id="new-room-name" />
                        <button onClick={ () => {
                            this.createNewRoom(document.getElementById('new-room-name').value);
                            document.getElementById('new-room-name').value = '';
                        }}>Create</button>
                    </div>
                )
            }
            else return <div></div>
        })

        const showChatBox = () => {
            if(this.state.chatBool) {

                return(
                    <div className="container">
                        <div className="chatBar">
                            <h2>{this.state.currRoom}</h2>
                            <button className="leaveBtn" onClick={() => this.leaveRoom()} >Leave Room</button>
                        </div>
                        <div className="memberDetails">
                            <span>Members : </span>
                            {this.state.usersInCurrRoom.map((user, index) => {
                                if(index === 0) return <span>{user.username}</span>
                                else return <span>, {user.username}</span>
                            })}
                        </div>
                        <ScrollToBottom className="messages">
                            {this.state.messages.map((message, index) => <div key={index}><Message message={message} name={this.state.name} /></div>)}
                        </ScrollToBottom>
                        <Input id="text-bar" message={this.state.currmessage} setMessage={this.setMessage} sendMessage={this.sendMessage} />
                    </div>
                )
            }
            else return <div className="chatInitial">Start a Chat</div>
        }

        return(
            <div className="OuterContainer">
                <div className="DashboardList">
                    <h2 className="DashboardUser">{this.state.name}</h2>
                    <button className="dashboardButtons" onClick={() => this.toggleUsers()}>Start Personal Chat</button>
                    <div className="dashboardItems">{showUsers()}</div>
                    <button className="dashboardButtons" onClick={() => this.toggleRooms()}>Start Group Chat</button>
                    <div className="dashboardItems">{showRooms()}</div>
                    <button className="dashboardButtons" onClick={() => this.toggleNewRoom()}>Create New Group</button>
                    <div className="dashboardItems">{createRoom()}</div>
                    <button className="dashboardButtons logoutButton" onClick={() => this.userLogout()}>Logout</button>
                </div>
                <div className="DashboardChat">
                    {showChatBox()}
                </div>
            </div>
        )
    }
}

export default Dashboard;