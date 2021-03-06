authDict = [];

const addRegisteredUser = (user) => {
    const isAlreadyExists = authDict.find((existingUser) => existingUser.username === user.username);

    if(isAlreadyExists) {
        return {error: 'Username already taken'};
    }

    authDict.push(user);
    return {user: user};
}

const deleteRegisteredUser = (name) => {
    const index = authDict.findIndex((existingUser)  => existingUser.username === name);

    authDict.splice(index, 1)[0];
}

const checkRegisteredUser = ({username, password}) => {
    const index = authDict.findIndex((existingUser)  => existingUser.username === username);

    if(index === -1) 
        return {error: 'No such username found'};

    if (authDict[index].password !== password)
        return {error: 'Wrong Password'};

    return {user: authDict[index]};
}

module.exports = { addRegisteredUser, deleteRegisteredUser, checkRegisteredUser };