import React from 'react';
import './RoomList.css';

const RoomList = ({allRooms, addRoom})=> (
    <div className= 'roomList'>
        {
            allRooms 
            ? (
                <div> 
                    <h1> Rooms: </h1>
                    <div className= 'activeRooms'> 
                        <h3>
                            {
                                allRooms.map((room)=> (
                                    <div className= 'oneParticularRoom'>
                                        <button className='roomButton' onClick={(event)=> addRoom}>{room}</button>
                                    </div>
                                ))
                            }
                        </h3>
                    </div>
                </div>
            )
            : null
        }
    </div>
)

export default RoomList;