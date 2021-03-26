import React from 'react';

//import onlineIcon from '../../icons/onlineIcon.png'

import './RoomUserList.css';

const RoomUserList = ({users}) => (

    <div className='roomUserList'>
        {/* <div>
            <h1>Realtime Chat Application <span role="img" aria-label="emoji">💬</span></h1>
            <h2>Created with React, Express, Node and Socket.IO <span role="img" aria-label="emoji">❤️</span></h2>
            <h2>Try it out right now! <span role="img" aria-label="emoji">⬅️</span></h2>
        </div> */}
        {
            users 
            ? (
                <div>
                     <h1>People currently chatting:</h1>
                     <div className="activePeoples">
                         <h3>
                             {users.map(({userName , id})=> (

                                 <div key={userName} className="activeItem">
                                     
                                     <div className='itemBox backgroundBlues'>
                                        <p className='sentTexts colorWhites'>{userName}</p>
                                    </div>
                                     
                                      
                                 </div>
                             ))}
                         </h3>
                    </div>
                </div>
            )
            : null
        }
    </div>
);

export default RoomUserList;