import React from 'react';

const Message = ({ message: { text, user, type }, name }) => {
    let isSentByCurrUser = false;

    if (user === name) {
        isSentByCurrUser = true;
    }

    if(type !== 'multi') user = null

    if(isSentByCurrUser) {
        return (
            <div className="messageContainerSelf">
                <div className="messageBox backgroundBlue">
                    <p className="messageText">{text}</p>
                </div>
            </div>
        )
    }

    else {
        return (
            <div className="messageContainerOthers">
                <div className="messageBox backgroundWhite">
                    <p className="messageText">{text}</p>
                </div>
                <p className="sentUser">{user}</p>
            </div>
        )
    }
}

export default Message;