import React from 'react';

const Input = ({ setMessage, sendMessage, message }) => (
    <form className="form">
        <input
            className="input"
            id="text-bar"
            type="text"
            placeholder="Type a message"
            value={message}
            autoComplete='off'
            onChange={({ target: { value } }) => setMessage(value)}
            onKeyPress={event => {
                if(event.key === 'Enter') {
                    sendMessage(event);
                    document.getElementById('text-bar').value = '';
                }}
            }
        />
        <button className="sendButton" onClick={e => {document.getElementById('text-bar').value = ''; sendMessage(e)} }>Send</button>
    </form>
)

export default Input;