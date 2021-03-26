const express = require('express');
const socketio = require('socket.io');
const http = require('http');


const { addUser, addIdToUser, addUserToRoom, removeUserFromRoom, 
    getUser, removeUser, getUsersInRoom, getAllUsers, 
    getAllRooms, getAllRoomsForAUser, getAllRoomForASocket, 
    existUser, getUserByName} = require('./users');

const {addRegisteredUser, checkLoggedInUser} = require('./authentication.js');
const PORT = process.env.PORT || 5000;
const router = require('./router');
const app = express();
const server = http.createServer(app);
const io = socketio(server,{
    cors:
    {
        origin: "*",
        methods: ["GET","POST"],
        credentials: true
    }
});

app.use(router); 


io.on('connect', (socket)=>{
    console.log("We have a new connection!!");

    // socket.on('authenticate', ()=>{
    //     // authentication code here
    // });


    socket.on('register', ({userName, password}, callback)=> {
        //console.log("Inside register")
        //console.log('inside register=> ', socket.id)
        const newUser = {userName: userName, password: password};
        const {error, user} = addRegisteredUser(newUser);
        //console.log(user.userName);
        if(error) return callback(error);

        addUser({userName: userName, socketID: socket.id})
        return callback();
    })



    socket.on('login', ({userName, password}, callback)=> {
        //console.log("Inside login")
        const {error, user} = checkLoggedInUser({userName, password});
        if(error) return callback(error);
        //console.log(user.userName);
        addUser({userName: userName, socketID: socket.id});

        return  callback();

    });

    socket.on('getRoomsForAUser', ({userName}, callback)=>{

        const allRooms = getAllRoomsForAUser(userName);
        socket.emit('allRooms', {allRooms: allRooms});
    })

    // will be triggered when user adds in a new room
    // multicast
    socket.on('join',({name:name, room:room}, callback)=>{
        //callback(); // basically for error handling and needed to pass as 3rd argument in the client part
        //console.log(name, room);
        const currUser = addUser({userName: name, socketID: socket.id});
        //console.log("Inside join=>", currUser.user.userName, currUser.user.id);
        const roomData = addUserToRoom({ userName:name, room: room}); // it can return 2 things user object and exist or new
        //if(error) return callback(error);

        // for no error
        const nameOfTheRoom = roomData.roomName
        //console.log(nameOfTheRoom, 'inside join')
        socket.join(nameOfTheRoom);

        // user inside the room

        // if unicast socket.to(user.room).emit(message)
        
        socket.emit('message', {user: 'admin', text: `Welcome ${name}!!`, room: `${nameOfTheRoom}`});
        socket.broadcast.to(roomData.roomName).emit('message', {user: 'admin', text: `${name} just slid into the room!`, room: `${nameOfTheRoom}`});
        
        io.to(roomData.roomName).emit('roomData', {room: `${roomData.roomName}`, users: getUsersInRoom(nameOfTheRoom)})
        console.log("Users In a room: ", getUsersInRoom(nameOfTheRoom))
        //callback();
    });
//////////////////////////////////////////////////////////////////////////
    socket.on('join_private_chat' , ({otherPersonName}, callback)=> {

        const existance = existUser(otherPersonName);
        if(existance.status){
            socket.to(existance.value).emit('private_message', {user: 'admin', id: existance.value, text: 'Happy Chatting!'}) 
        } else{
            socket.to(existance.value).emit('private message', {user: 'admin', id: existance.value, text: 'Ask your frind to get online :)'});

        }        
    });
    socket.on('private_message', ({myName, userName/*kake pathacchi*/, message}) => {

        const user = getUser(userName)
        socket.to(user.id).emit("send private message", {user: myName/*jar theke msg ta eseche */, text: message/*, id: socket.id*/});
    });

/////////////////////////////////////////////////////////////////////////////////
    socket.on('sendMessage', ({room, message}, callback)=> {
        //console.log('inside sendMessage=> ', socket.id)
        const user = getUser(socket.id);
        //console.log(user.id, user.userName)

        io.to(room).emit('message', {user: user.userName, text: message, room: room});
        io.to(room).emit('roomData', {room: room, users: getUsersInRoom(room)});

        callback();
    });

    socket.on('leaveRoom', ({room, userName}, callback)=> {

        const user = removeUserFromRoom(room, userName);

        io.to(room).emit('message', {user: 'admin', text: `${user.userName} left the room!`});
        io.to(room).emit('roomData', {room: room, users: getUsersInRoom(room)});

        callback()
    })

    socket.on('disconnect', ()=>{
        console.log("User left!!");
        const user = removeUser(socket.id);

        if(user)
        {
            
            let allRooms = getAllRoomForASocket(socket.id);
            for(room in allRooms)
            {
                io.to(room).emit('message', {user:'admin', text: `${user.userName} left the room!!`});
                io.to(room).emit('roomData', { room: room, users: getUsersInRoom(room)});
            }
            
        }
    });
});

server.listen(PORT, ()=> console.log(`Server has started on port ${PORT}`));