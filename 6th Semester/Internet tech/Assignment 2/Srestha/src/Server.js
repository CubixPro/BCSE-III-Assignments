'use strict';
const fs = require('fs');
const jsonfile = require('jsonfile');
const express = require('express');
const cors = require("cors");
const http = require("http");
const socket = require("socket.io");
const app = express();
const port = 8080;
const server = http.createServer(app);
const io = socket(server, {
  cors: {
    origin : "http://localhost:3000",
    methods : ["GET", "POST"],
    credentials : true
  }
})

var socketname_id = {};

var rooms = [];


server.listen(port, () => {
  console.log(`Listening at http://localhost:${port}`)
})


io.on('connection', (socket) => { 
    socket.on("hello", (arg) => {
      socketname_id[`${arg}`] = socket;
      console.log(`The client ${arg} is connected`);
      let data = {
        sender : "admin",
        receiver : `${arg}`,
        message : `The client ${arg} is connected!`
      }
      socket.emit('sentmessage', data.sender, data.receiver, data.message);
      console.log(`sender: ${data.sender}, receiver: ${data.receiver}, body: ${data.message}`);
    });

    socket.on("joinroom", (arg1, arg2, arg3) => {
      let dm = `${arg3}`;
      if (dm.localeCompare("No") == 0)
      {
        console.log(`${arg1} joined room ${arg2}`);
      var exist = 0;
      rooms.forEach( room => {
        if (room.name.localeCompare(`${arg2}`) == 0)
        {
          room.users.push(`${arg1}`);
          exist = 1;
        }
      });
      if (exist == 0) 
      {
        let room = {
          name : `${arg2}`,
          users : [`${arg1}`]
        }
        rooms.push(room);
      }       
      console.log(rooms);
      }
      
      else
      {
        console.log(`${arg1} has connected with ${arg2}`);
      }
    });

    socket.on("sendmessage", (arg1, arg2, arg3, arg4) => {
      let data = {
        sender : `${arg1}`,
        receiver : `${arg2}`,
        message : `${arg3}`,
        dm : `${arg4}`
      };

    if (data.receiver.localeCompare("broadcast") == 0)
    {
      socket.broadcast.emit("sentmessage", data.sender, data.receiver, data.message);
    }
    else if (data.dm.localeCompare("No") == 0)
    {
      console.log(`Room message to: ${data.receiver}`);
      socket.to(socket.id).emit("sentmessage", data.sender, data.receiver, data.message);
      rooms.forEach(room => {
        if (room.name.localeCompare(`${data.receiver}`) == 0)
        {
          room.users.forEach(user => {
            socket.to(socketname_id[`${user}`].id).emit("sentmessage", data.sender, data.receiver, data.message);
          })
        }
      })
      socket.to(data.receiver).emit("sentmessage", data.sender, data.receiver, data.message);
    }
    else
    {
      console.log(`Personal message to: ${data.receiver}`)
      socket.to(socket.id).emit("sentmessage", data.sender, data.receiver, data.message);
      socket.to(socketname_id[`${data.receiver}`].id).emit("sentmessage", data.sender, data.receiver, data.message);
    }
      
});

});

