import React from 'react';

import './RoomInputField.css'

const RoomInputField = ({room, setRoom, addRoom}) =>(
    <form className='roomInputForm'> 
    <input
        className = 'roomInput'
        type='text'
        placeholder='Insert Room name...'
        value = {room}
        onChange = {(event)=> setRoom(event.target.value)}
        onKeyPress = {(event)=> event.key === 'Enter' ? addRoom : null}
    />

    <button className='roomButtons' onClick={(event)=> addRoom(event)}>Join</button>

    </form>
)

export default RoomInputField;