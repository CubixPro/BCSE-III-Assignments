import React from 'react';

import closeIcon from "../../icons/closeIcon.png";
import onlineIcon from "../../icons/onlineIcon.png";

import './InfoBar.css';

const InfoBar = ({ room })=>(
    <div className='InfoBar'>
        <div className='leftInnerContainer'>
            <img className="onlineIcon" src={onlineIcon} alt="Online icon" />
            <h2>{room}</h2>
        </div>
        <div className='rightInnerContainer'>
            <a href="/"> <img src={closeIcon} alt="close icon" /></a>
        </div>

    </div>
)

export default InfoBar;