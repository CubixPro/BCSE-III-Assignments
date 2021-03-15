import React from 'react';

const addImage = (files) => {
    console.log(files[0])
    const reader = new FileReader();
    reader.onload = () => {
        const bytes = new Uint8Array();
        //socket.emit('image', base64);
        console.log(1)
        console.log(base64);
    };
    reader.readAsArrayBuffer(files[0]);
}

const Input = ({ setMessage, sendMessage, message, image, setImage }) => (
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
        <input 
            className="image-input"
            id="fileDialog" 
            type="file" 
            onChange={({ target: { value, files } }) => {
                setImage(value);
                addImage(files);
            }}/>
    </form>
)

export default Input;