const users = []; // {userName: name, id: null}
const rooms = []; // room = {roomName: name, users = []}

// id constst of id, name, roomList
// user = {name: name, roomList: []}

// after authentication adding user
const addUser = ({userName, socketID}) => {
    //userName = userName.trim().toLowerCase();
    //room = room.trim().toLowerCase();

    //const existingUser = users.find((user)=> user.room === room && user.name === name);

    //const existingUser = users.find((user)=> ( user.name === name && user.room.find((roomName)=> roomName === room)));

    // const existingUser = users.find((user)=> {
    //     if(user.name === name)
    //     {
    //         for(roomName in user.room)
    //         {
    //             if(roomName === room) return true;
    //         }
    //     }
    //     return false;
    // })

    const existingUserIndex = users.findIndex((user)=> user.userName === userName)
        
    if(existingUserIndex !== -1){
        //return { user : existingUser, status: 'exist', room: room};
        users[existingUserIndex].id = socketID
        console.log("Inside user! yoooo founddd!!")
        return {user: users[existingUserIndex], status: 'exist'}
    }

    //const user = { id, name, room};

    // let user = new User(name);
    // user.addUserToRoom(room,id);

    // //existingUser.room.push(room);
    // users.push(user);

    // return { user: user, status: 'new', room: room};
    console.log("Inside user! Not found :((((((")
    const user = {userName: userName, id: socketID}
    users.push(user)
    return {user: user, status: 'new'}

}

const addIdToUser = ({name, Id}) => {
    const index = users.findIndex((user)=> user.userName === name);
    users[index].id = Id;
} 

const addUserToRoom = ({userName, room}) => {

    const index = rooms.findIndex((currRoom) => currRoom.roomName === room);
    console.log("INSIDE ADDUSERTOAROOM::::::::::::::::::::::::::::::::", room, index)
    if(index !== -1)
    {
        const userIndex = rooms[index].users.findIndex((user) => user.userName === userName);
        if(userIndex !== -1)
            // new user
            return rooms[index]; // returning the room object
        
        const indexOfUser = users.findIndex((user)=> user.userName === userName);

        rooms[index].users.push(users[indexOfUser]);
        return rooms[index];
    }
    else{
        // room doesn't exist
        // create one

        const newRoom = {roomName: room, users: []}
        const indexOfUser = users.findIndex((user)=> user.userName === userName);
        newRoom.users.push(users[indexOfUser])
        rooms.push(newRoom)
        console.log("ROOM CREATED!!", newRoom)
        return newRoom
        

    }
}

const removeUserFromRoom = ({roomName, userName}) => {
    // const index = users.findIndex((user)=> user.socketId.find((id)=> id === socketId));
    // if(index != -1)
    // {
    //     return users.splice(index,1)[0];
    // }

    const index = users.findIndex((currRoom) => currRoom.room === roomName);
    const indexOfUser = rooms[index].users.findIndex((user)=> user.userName === userName);

    return rooms[index].users.splice(indexOfUser,1)[0];
}

//const getUser = (name) => users.find((user) => user.name === name);

const getUser = (id)=>{

    // const index = users.find((user)=> user.socketId.find((id)=> id === socketId));
    // const user = users[index];
    // return { user: user, room: user.room[index] };

    return users.find((user)=> user.id === id);
}

const getUserByName = (userName)=>{
    return users.find((user)=> user.userName === userName);
}

const removeUser = (id)=> {
    const index = users.findIndex((user)=> user.id === id);
    return users.splice(index, 1)[0];
}


const getUsersInRoom = (roomName) => {
    console.log('pita', roomName)
    console.log("All rooms: ", rooms)
    let roomArray = rooms.findIndex((room)=> room.roomName === roomName)
    console.log("Inside getUsersInToom=> ", roomArray)
    return rooms[roomArray].users
}
const getAllUsers = ()=> users;
const getAllRooms = () => rooms; 

const getAllRoomsForAUser = (userName)=> {

    let allRooms = []
    var room;
    for(room in rooms)
    {
        const decision = (room)=> room.users.findIndex((user)=> user.userName === userName);
        if(decision !== -1) allRooms.push(room.roomName);
    }
    return allRooms;
}

const getAllRoomForASocket = (socketID)=>{

    
    let allRooms = []
    var room;
    for(room in rooms)
    {
        const decision = (room)=> room.users.findIndex((user)=> user.id === socketID);
        if(decision !== -1) allRooms.push(room.roomName);
    }
    return allRooms;
}

const existUser = (userName)=>{
    const index = users.findIndex((user)=> user.userName === userName);
    if(index !== -1) return {status: false, value: null};
    else {
        return { status: true, value: users[index].id };
    } ;
}
module.exports = { addUser, addIdToUser, addUserToRoom, removeUserFromRoom, 
        getUser, removeUser, getUser, getUsersInRoom, getAllUsers, 
        getAllRooms, getAllRoomsForAUser, getAllRoomForASocket, 
        existUser, getUserByName};