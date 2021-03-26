
authDict = [] // contains user: password value

const addRegisteredUser = (user)=> {
    const isExisting = authDict.find((currUser)=> currUser.userName === user.userName );
    if(isExisting){
        return {error: 'Username is already taken'}
    }

    authDict.push(user);
    return {user: user};
}

const checkLoggedInUser = ({userName, password})=> {
    const index = authDict.findIndex((currUser)=> currUser.userName === userName);

    if(index === -1)
    {
        return {error: 'No such username found!!'}
    }

    if(authDict[index].password !== password)
    {
        return {error: 'Invalid password given!!'}
    }

    return {user: authDict[index]};
}
module.exports = {addRegisteredUser,checkLoggedInUser}