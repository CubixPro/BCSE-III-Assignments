import React from 'react';
import ScrollToBottom from 'react-scroll-to-bottom';

import './Messages.css';
import Message from './Message/Message';

const Messages = ({messages, type, name, room}) => {
    // let currRoom = '';
    // if(type === 'r') currRoom = 'r/'.concat(room)
    // else if(type === 'u') currRoom = 'u/'.concat(room)

    // const currObj = .find((obj)=> obj.room === currRoom)
    // const messages = currObj.messages
    return (

    <ScrollToBottom className="messages" > 
        {messages.map((message, i) => 
        <div key={i}>
            <Message message={message} name={name} />
        </div>)}
    </ScrollToBottom>

)};
// basically we are getting every message and wrapping them into 'Message' component
export default Messages;