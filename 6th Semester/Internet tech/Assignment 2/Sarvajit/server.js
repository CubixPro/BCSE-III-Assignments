const io = require("socket.io")(3000); // starts the server at the port 3000
const messageStore = {};
const authStore = {};
io.on("connection", (socket) => {
  socket.on("new-user", ({ name, password }) => {
    if (name in authStore) {
      if (authStore[name] === password) {
        io.emit("connection-status", { name, status: true });
        socket.broadcast.emit("user-connected", name);
        const messagesPrevious = messageStore[name];
        console.log(messagesPrevious);
        socket.join(name);
        io.emit("users-list", Object.keys(authStore));
        io.to(name).emit("prev-chat-message", messagesPrevious);
      } else {
        io.emit("connection-status", { name, status: false });
      }
    } else {
      authStore[name] = password;
      messageStore[name] = [];
      io.emit("connection-status", { name: name, status: true });
      socket.broadcast.emit("user-connected", name);
      socket.join(name);
      io.emit("users-list", Object.keys(authStore));
    }
  });
  socket.on("chat-message", ({ message, image, time, name, recipients }) => {
    messageStore[name].push({ message, image, time, name: "You" });
    if (name in authStore) {
      for (idx = 0; idx < recipients.length; idx++) {
        const receiver = recipients[idx];
        if (receiver === name) {
          continue;
        }
        messageStore[receiver].push({ message, image, time, name });
        io.to(recipients[idx]).emit("chat-message", {
          message,
          image,
          time,
          name,
        });
      }
    }
  });
  socket.on("disconnect", () => {
    // io.emit("user-disconnected", usersOnline[socket.id]);
    io.emit("users-list", Object.keys(authStore));
  });
});
