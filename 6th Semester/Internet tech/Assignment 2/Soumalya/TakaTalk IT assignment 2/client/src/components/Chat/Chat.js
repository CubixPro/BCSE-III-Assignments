import React, {useState, useEffect } from 'react';
import io from 'socket.io-client';
import queryString from 'query-string';


import './Chat.css';

import InfoBar          from '../InfoBar/InfoBar'
import Input            from '../Input/Input'
import Messages         from '../Messages/Messages'
import RoomUserList     from '../RoomUserList/RoomUserList'
import RoomInputField   from '../RoomInputField/RoomInputField'
import RoomList         from '../RoomList/RoomList'
let socket;


const Chat = ({ location }) => {

    const [name, setName] = useState('');
    const [room, setRoom] = useState('broadcast');
    const [users, setUsers] = useState('');
    const [message, setMessage] = useState(''); // track state of a single message
    const [messages, setMessages] = useState([]);// track state of all the messages
    const ENDPOINT = 'localhost:5000';



    const [roomName, setRoomName] = useState(''); // roomName to be send to server
    const [allRooms, setAllRooms] = useState(['r/broadcast'])
    const [type, setType] = useState('r') // type can be r or u
    //const [messageStore, setMessageStore] = useState([{room: 'r/broadcast', messages: []}])
    let temporary;
    const messageStore = [{room: 'r/broadcast', messages: []}]
    useEffect(()=>{

        const { name, room } = queryString.parse(location.search);
        // returns a json and we are restructing the object to name=name and room=room
        // we also could have const data = ... and data.room or data.name
        
        socket = io(ENDPOINT);
        setName(name);

        if(type === 'r'){
            socket.emit('join', {name: name, room: room}, (error)=>{
                if(error) alert(error);
            }); // eventName, actual payload
        }

        if(type === 'u')
        {
            socket.emit('join_private_chat', {otherPersonName: room}, (error)=> {
                if(error) 
                    alert(error)
            })
        }
        
       
        // this return statement is used for unmounting of the data

        // return ()=> {
        //     socket.emit("disconnect");
        //     socket.off();
        // } ;

    }, [ENDPOINT, location.search, room]);
    // basically if they changes we need to rerender the whole part



    // hooks for handling messages
    useEffect(()=> {

        socket.on('message',(message)=>{
             // admin generated messages
             //setMessages(messages => [...messages, message]);

             const messageToStore = {user: message.user, text: message.text}
             const currRoom = 'r/'.concat(message.room)

            //  setMessageStore(messageStore => {
            //     const nowRoomIndex = messageStore.findIndex((obj)=> obj.room === currRoom)
            //     if(nowRoomIndex !== -1)
            //         messageStore[nowRoomIndex].messages.push(messageToStore)

            //     else{
            //         messageStore.push({room: `${currRoom}`, users: []})
            //         const len = messageStore.length()

            //         messageStore[len-1].messages.push(messageToStore)
            //     }
            //  })

            const nowRoomIndex = messageStore.findIndex((obj)=> obj.room === currRoom)
            if(nowRoomIndex !== -1){
                messageStore[nowRoomIndex].messages.push(messageToStore)
                setMessages([...messageStore[nowRoomIndex].messages])
            }
            else{
                messageStore.push({room: `${currRoom}`, messages: []})
                const len = messageStore.length()
                messageStore[len-1].messages.push(messageToStore)
                setMessages([...messageStore[len-1].messages])
            }

        });

        socket.on("roomData", ({room: room, users: users }) => {
            setUsers(users);
        });

        socket.on("private_message", (message)=> {
            // setMessages(messages => [...messages, message]);
            // setUsers('')
            const currUserName = 'u/'.concat(message.user)
            const nowUserIndex = messageStore.findIndex((obj)=> obj.room === currUserName)
            if(nowUserIndex !== -1)
            {
                // already found 
                messageStore[nowUserIndex].messages.push({user: message.user, text: message.text})
                setMessages([...messageStore[nowUserIndex].messages])
            }
            else{
                messageStore.push({room: `${currUserName}`, messages: []})
                const len = messageStore.length()
                messageStore[len-1].messages.push({user: message.user, text: message.text})
                setMessages([...messageStore[len-1].messages])
            }
        })

    }, []);

    const sendMessage = (event)=> {
        event.preventDefault();

        if(message && type === 'r'){
            socket.emit('sendMessage',{ room:room, message: message}, ()=> setMessage(''));
            // 3rd parameter is a cleanup code for textField
        }
        else if(message && type == 'u'){
            socket.emit('private_message', {myName: name, userName: room, message: message}, ()=> setMessage(''))
        }
        else{
            alert("Invalid userName")
        }
    }

    const addRoom = (event)=>{
        event.preventDefault();
        if(roomName && roomName.startsWith('r/'))
        {
            //socket.emit('join',{name: name , room: roomName.substring(2)})
            

            setAllRooms(allRooms => [...allRooms, roomName])
            setType('r')
            setRoom(roomName.substring(2))
            setRoomName("") // hopefully does the cleanup
            setMessages([])
            //console.log(allRooms)
        }

        else if(roomName && roomName.startsWith('u/'))
        {
            //socket.emit('join private chat', {otherPersonName: roomName.substring(2)})
            setAllRooms(allRooms => [...allRooms, roomName])
            setType('u')
            setRoom(roomName.substring(2))
            setRoomName("") // hopefully does the cleanup
            setMessages([])
        }
        else
        {
            setRoomName("")
            alert("Invalid name!!!")
        }
        //console.log("hello!")
    }
    
    return (
        <div className='outerContainer'>
            <div className='roomsOfAUser'>
                <RoomInputField room= {roomName} setRoom ={setRoomName} addRoom={addRoom}/>
                <RoomList allRooms={allRooms} addRoom={addRoom}/> 
            </div>

            <div className='container'> 
                <InfoBar room={ room }/>
                <Messages messages={messages} type= {type} name={name} room={room} />
                <Input message={message} setMessage={setMessage} sendMessage={sendMessage} />
                
                {/* <input 
                value={message} 
                onChange={(event)=> setMessage(event.target.value)}
                onKeyPress= {(event)=> event.key === 'Enter' ? sendMessage(event) : null}  */}
            </div>

            <div className='roomUserLists'>
            <RoomUserList users={users}/>
            </div>
           
        </div>
    )
};
export default Chat;