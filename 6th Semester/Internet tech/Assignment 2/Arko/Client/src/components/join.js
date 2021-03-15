import React, {Component} from 'react';
import { Redirect } from 'react-router-dom';
import io from 'socket.io-client';

let socket;

class Join extends Component {

    constructor(props) {
        super(props);
        this.state ={
            username: '',
            password: '',
            redirect: false,        
        }
        this.registerUser = this.registerUser.bind(this);
        this.loginUser = this.loginUser.bind(this);

        socket = io('http://localhost:5000', { withCredentials: true });
    }

    registerUser() {
        if (this.state.username !== '' && this.state.password !== '') {
            socket.emit('register', { username: this.state.username, password: this.state.password}, (error) => {
                if(error) console.log(error);
                else {
                    console.log('Successfully Registered');
                    this.setState({redirect: '/dashboard'})
                }
            });
        }
    }

    loginUser() {
        if (this.state.username !== '' && this.state.password !== '') {
            socket.emit('login', { username: this.state.username, password: this.state.password}, (error) => {
                if(error) console.log(error);
                else {
                    console.log('Login Successful');
                    this.setState({redirect: '/dashboard'})
                }
            });
        }
    }

    render() {
        if (this.state.redirect) {
            socket.disconnect()
            socket.off();
            return <Redirect to={{
                pathname: '/dashboard',
                state: {name: this.state.username}
            }} />
        }

        return (
            <div className="joinOuterContainer">
                <div className="joinInnerContainer">
                    <h1 className="heading">Signup</h1>
                    <div><input placeholder="Username" className="joinInput" type="text" onChange={(event) =>this.setState({ username: event.target.value})} /></div>
                    <div><input placeholder="Password" className="joinInput mt-20" type="text" onChange={(event) =>this.setState({ password: event.target.value})} /></div>
                    <button className="joinButton mt-20" type="sumbit" onClick={() => this.registerUser()}>Submit</button>
                </div>
                <div className="joinInnerContainer mt-100">
                    <h1 className="heading">Login</h1>
                    <div><input placeholder="Username" className="joinInput" type="text" onChange={(event) =>this.setState({ username: event.target.value})} /></div>
                    <div><input placeholder="Password" className="joinInput mt-20" type="text" onChange={(event) =>this.setState({ password: event.target.value})} /></div>
                    <button className="joinButton mt-20" type="sumbit" onClick={() => this.loginUser()}>Submit</button>
                </div>
            </div>
        )
    }
};

export default Join;