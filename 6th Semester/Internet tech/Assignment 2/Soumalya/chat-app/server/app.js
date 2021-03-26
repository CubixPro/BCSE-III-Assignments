const express = require('express');
const { isPrimitive } = require('util');
const app = express();
const http = require('http').Server(app)
const io = require('socket.io')(http)
const { joinUser, removeUser } = require('./users');
const bodyParser = require("body-parser")
const fs = require('fs');

var messages = {}
var path = require('path');
var users_id = {}
var router = express.Router();
var passwords = {}
var userlist = []

messages["broadcast"] = [];

app.use(express.static(path.resolve(__dirname + "/public")));

app.use(bodyParser.urlencoded({
    extended: true
}));

const broadcastRoom = "broadcast";

users_id[broadcastRoom] = broadcastRoom;

app.use('/favicon.ico', express.static(path.resolve(__dirname + "/../favicon.png")));

app.set("view engine", "ejs");
//app.get("/", (req, res) => {
//    res.sendFile(path.resolve(__dirname + "/public/chat.html"));
//});

//app.get("/login", (req, res) => {
//    res.sendFile(path.resolve(__dirname + "/public/index.html"));
//});

router.get("/chat", (req, res) => {
    res.sendFile(__dirname + "/public/chat_try.html");
});

router.get("/login", (req, res) => {
    res.sendFile(__dirname + "/public/index.html");
});

router.get("/altlogin", (req, res) => {
    res.render("index");
});

router.post("/login", (req, res) => {
    // console.log(userlist.length);
    // console.log("hello")
    if (req.body.u in passwords) {
        if (req.body.p == passwords[req.body.u]) {
            //res.send("successful");
            res.render("chat_try", { messages: messages[req.body.u], username: req.body.u, num: userlist.length });
            //res.render("chat_try");
        }
        else {
            //res.send("Wrong");
            //res.sendFile(__dirname + "/public/index.html");
            res.render("index", { error: "Wrong password" });
            //res.rendor(__dirname +  "public/index.html", {error: "Wrong password"});
        }
    }
    else {
        passwords[req.body.u] = req.body.p;
        messages[req.body.u] = [];
        userlist.push(req.body.u);
        res.render("chat_try", { messages: messages[req.body.u], username: req.body.u, num: userlist.length });
        //res.render("chat_try");

    }



    //res.send(req.body);
})

app.use(router);

let thisRoom = "";

io.on("connection", (socket) => {
    console.log("connected");
    socket.on("new user", (data) => {
        console.log("in room");
        let Newuser = joinUser(socket.id, data.username, data.roomName);
        //messages[data.username] = []
        socket.emit('send data', {
            id: socket.id,
            username: Newuser.username,
            roomname: Newuser.roomname
        })
        thisRoom = Newuser.roomname;
        console.log(Newuser);
        users_id[data.username] = socket.id;
        socket.join(broadcastRoom);
    });


    //-------------- DEAL WITH IMAGES --------------------------



    socket.on('img', function (image, receiver, username) {
        console.log("Receiver: " + receiver);
        var time = new Date();
        time_val = time.toLocaleString('en-US', { hour: 'numeric', minute: 'numeric', hour12: true });
        console.log(time_val);
        if (receiver != "broadcast") {
            socket.emit('newImg', image, receiver, username, time_val);

            console.log(username);
            messages[username].push({
                username: username,
                t: time_val,
                value: "Image sent by" + username,
                image: image
            })
        }
        else {
            messages[username].push({
                username: username,
                t: time_val,
                value: "Image sent by" + username,
                image: image
            })

        }
        var nameArr = receiver.split(",");
        nameArr.forEach(d => {
            //console.log(nameArr);
            /* messages[nameArr].push({
                 username: data.user,
                 value: data.value
             });*/
            console.log(d);
            io.to(users_id[d]).emit('newImg', image, receiver, username, time_val);
            messages[d].push({
                username: username,
                t: time_val,
                value: "Image sent by " + username,
                image: image
            });

        });
        //console.log("Emitted" + data.msg);
    })



    //---------------------------------------------------------------





    //-----------------DEAL WITH TEXT MESSAGES-------------------------



    socket.on("send chat message", (data) => {
        console.log(data.image);
        var time = new Date();
        time_val = time.toLocaleString('en-US', { hour: 'numeric', minute: 'numeric', hour12: true });
        if (data.receiver != "broadcast") {
            socket.emit('show chat message', {
                username: data.user,
                value: data.value,
                t: time_val,

            })
            console.log("data.user:"+ data.user)
            messages[data.user].push({
                username: data.user,
                value: data.value,
                t: time_val,
                image: ""
            })
        }
        else {
            userlist.forEach((d) => {
                messages[d].push({
                    username: data.user,
                    value: data.value,
                    t: time_val,
                    image: ""
                });
            })
        }

        var nameArr = data.receiver.split(",");
        //messages[data.user].push(data.value);

        nameArr.forEach(d => {
            //console.log(nameArr);
            /* messages[nameArr].push({
                 username: data.user,
                 value: data.value
             });*/
            io.to(users_id[d]).emit('show chat message', {
                username: data.user,
                value: data.value,
                t: time_val,
                image: ""
            });
           
            messages[d].push({
                username: data.user,
                value: data.value,
                t: time_val,
                image: ""
            })
        });

        //console.log(messages);
    })


    //---------------------------------------------------------------


});

http.listen(5000);


//TODO: enable multiple logins
//DONE store messages and render on logging in
//DONE broadcast
//DONE gui better
//DONE scroll to the bottom
//DONE time feature in messages
//DONE image
//DONE image broadcast bug
//DONE show total number of users
//DONE first image sending time issue
//DONE change login page name
//give padding to sender receiver input box