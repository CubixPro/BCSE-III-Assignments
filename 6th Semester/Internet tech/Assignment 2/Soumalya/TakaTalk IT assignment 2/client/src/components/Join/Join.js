import React, { useEffect, useState } from 'react';
import { Link } from 'react-router-dom'; // use to liink to chat server

import io from 'socket.io-client';
import "./Join.css";
let socket, socketID;
const ENDPOINT = 'localhost:5000';


const RegisterUser = ({userName, password})=> {
    //console.log("On register frontend")
    socket = io(ENDPOINT);
    socketID = socket.id
        socket.emit('register', {userName: userName, password: password}, (error)=>{
            if(error) alert(error);
        })
        return ()=> {
            socket.emit('disconnect');
            socket.removeAllListeners();
            socket.off();
        }
        
}

const LogInUser = ({userName, password})=> {
    console.log("On login frontend")
    socket = io(ENDPOINT);
    socketID = socket.id
    socket.emit('login', {userName: userName, password: password}, (error)=>{
        if(error) alert(error);
    })
    return ()=> {
        socket.emit('disconnect');
        socket.removeAllListeners();
        socket.off();
    }
}


const Join = () => {

    
    const [name, setName] = useState('');
    const [password, setPassword] = useState('');

    const room = 'broadcast';

   return(
       <div className="joinOuterContainer">
           <div className="joinInnerContainer">
               <h1 className="heading">Join</h1>
               <div> <input placeholder="Name" className="joinInput" type="text" onChange={(event)=> setName(event.target.value)} /> </div>
               <div> <input placeholder="Password" className="joinInput mt-20" type="text" onChange={(event)=> setPassword(event.target.value)} /> </div>
               <Link onClick={(event)=>(!name || !password) ? event.preventDefault() : RegisterUser({userName: name, password: password}) } to={`/chat?name=${name}&room=${room}`}>
                    <button className="button mt-20" type="submit ">sign In</button>
               </Link>
               <Link onClick={(event)=>(!name || !password) ? event.preventDefault() : LogInUser({userName: name, password: password}) } to={`/chat?name=${name}&room=${room}`}>
                    <button className="button mt-20" type="submit ">Log In</button>
               </Link>
           </div>

       </div>
   ); 
};

export default Join;