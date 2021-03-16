const users = [];
const rooms = [];

const addRoom = (roomName) => {
    const isAlreadyExists = rooms.findIndex((existingRoom) => existingRoom.room === roomName);

    if(isAlreadyExists !== -1) {
        return {error: 'RoomName already taken'};
    }

    const newRoom = {room: roomName, users: []}
    rooms.push(newRoom);
    return {newRoom: newRoom}
}

const addUser = ({username}) => {
    const user = {username: username, id:null};
    users.push(user);
}

const addUserToRoom = (requiredRoom, name) => {
    const index = rooms.findIndex((currRoom)  => currRoom.room === requiredRoom);

    const existingUserIndex = rooms[index].users.findIndex((user) => user.username === name)
    if(existingUserIndex !== -1) 
        return rooms[index];

    const indexUser = users.findIndex((user)  => user.username === name);

    rooms[index].users.push(users[indexUser]);
    return rooms[index];
}

const removeUserFromRoom = (requiredRoom, name) => {
    const index = rooms.findIndex((currRoom)  => currRoom.room === requiredRoom);
    const indexUser = rooms[index].users.findIndex((user)  => user.username === name);

    return rooms[index].users.splice(indexUser, 1)[0];
}

const removeUser = (id) => {
    const index = users.findIndex((user)  => user.id === id);

    return users.splice(index, 1)[0];
}

const getUser = (id) => {
    return users.find((user) => user.id === id);
}

const getUserByUsername = (name) => {
    const index = users.findIndex((user) => user.username === name);
    return users[index].id;
}

const getAllUsersInRoom = (requiredRoom) => {
    return rooms.filter((room) => room.room === requiredRoom)[0].users;
}

const getAllUsers = () => {
    return users;
}

const getAllRooms = () => {
    return rooms;
}

const addIdToUsers = (name, socketId) => {
    const index = users.findIndex((user)  => user.username === name);

    users[index].id = socketId;
}

module.exports = { addRoom, addUser, addUserToRoom, removeUserFromRoom, removeUser, getUser, getUserByUsername, getAllUsersInRoom, getAllRooms, getAllUsers, addIdToUsers};