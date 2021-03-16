const express = require('express');
const socket = require("socket.io")
const http = require('http');

const PORT = 5000;
const router = require('./router')
const { addRoom, addUser, addUserToRoom, removeUserFromRoom, removeUser, getUser, getUserByUsername, getAllUsersInRoom, getAllRooms, getAllUsers, addIdToUsers } = require('./users');
const { addRegisteredUser, deleteRegisteredUser, checkRegisteredUser} = require('./auth');
const e = require('cors');

const app = express();
const server = http.createServer(app);
const io = socket(server, {
    cors: {
        origin: "http://localhost:3000",
        methods: ["GET", "POST"],
        credentials: true
    }
});;

io.on('connection', (socket) => {

    socket.on('register', ({ username, password}, callback) => {
        const newUser = {username: username, password: password};

        const {error, user} = addRegisteredUser(newUser);
        if(error) return callback(error);      
        addUser({username}); 
        return callback();
    })

    socket.on('login', ({ username, password}, callback) => {

        const {error, user} = checkRegisteredUser({username, password});
        addUser({username});
        if(error) return callback(error);
        return callback();
    })

    socket.on('getUsers', (callback) => {
        return callback(getAllUsers());
    })

    socket.on('getRooms', (callback) => {
        return callback(getAllRooms());
    })

    socket.on('newRoom', ({roomName, name}, callback) => {
        const {error, newRoom} = addRoom(roomName);
        
        if(error) return callback({error: error});
        return callback({newRoom: newRoom});
    })

    socket.on('addId', ({name}) => {
        addIdToUsers(name, socket.id);
    })

    socket.on('join', ({ name, room}) => {
        console.log(`${name} joined in room ${room}`);

        const roomData = addUserToRoom(room, name);

        socket.emit('message', { user: 'admin', text: `${name}, Welcome to the room ${roomData.room}`, type: 'multi'});
        socket.broadcast.to(roomData.room).emit('message', { user: 'admin', text: `${name}, has joined.`, type: 'multi'});

        socket.join(roomData.room);

        io.to(roomData.room).emit('roomData', { room: roomData.room, users: getAllUsersInRoom(roomData.room)});
    });

    socket.on('sendMessage', ({room, sender, message, type}) => {
        const user = getUser(socket.id);
        if(type === 'multi') io.to(room).emit('message', {user: user.username, text: message, type: type});
        else {
            const id = getUserByUsername(sender);
            io.to(id).emit('message', {user: user.username, text: message, type: type})
            socket.emit('message', {user: user.username, text: message, type: type})
        }
    })

    socket.on('sendMessageWithImage', ({room, sender, message, image, imageName, type}) => {
        const user = getUser(socket.id);
        if(type === 'multi') io.to(room).emit('message', {user: user.username, text: message, image: image, imageName: imageName, type: type});
        else {
            const id = getUserByUsername(sender);
            io.to(id).emit('message', {user: user.username, text: message, image: image, imageName: imageName, type: type});
            socket.emit('message', {user: user.username, text: message, image: image, imageName: imageName, type: type});
        }
    })

    socket.on('leaveRoom', ({roomName, name}, callback) => {
        const user = removeUserFromRoom(roomName, name);
    
        io.to(roomName).emit('message', { user: 'admin', text: `${user.username} has left.`, type: 'multi'});
        io.to(roomName).emit('roomData', { room: `${user.username}`, users: getAllUsersInRoom(roomName)});
        console.log(`${name} has left room ${roomName}`);

        return callback();
    })
    
    socket.on('logout', (callback) => {
        const user = removeUser(socket.id);

        console.log(`${user.username} has left.`);
        return callback();
    });

});

app.use(router);

server.listen(PORT, () => console.log(`Server has started on port ${PORT}`))