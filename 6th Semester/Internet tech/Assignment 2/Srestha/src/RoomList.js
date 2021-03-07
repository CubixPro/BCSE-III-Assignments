import React, { Component } from 'react'
import RoomForm from './RoomForm'
import "./RoomList.css"

  
class RoomList extends Component{ 
  constructor(props){ 
    super(props);
    this.state = { 
      rooms : [],
      cur_room : ''
     } 
    this.createRoom = this.createRoom.bind(this) 
    this.renderRooms = this.renderRooms.bind(this) 
    this.handleClick = this.handleClick.bind(this)
  } 

  
  createRoom(room){ 
    this.setState({ 
      rooms : [...this.state.rooms, room] 
    }) 
  } 


  handleClick(event){
    this.setState({cur_room : event.target.value});
    console.log(this.state.cur_room);
    this.props.parentCallback(this.state.cur_room);
  }
  
  
  renderRooms(){ 
    const rooms = this.state.rooms.map(room => (
        <button className="button" type="submit" onClick={this.handleClick} value={room.roomname}>{room.roomname}</button>
    )) 
    return <ul>{rooms}</ul>
  } 
  
  render(){ 
    return(
      <div className="panel"> 
      <center>
      <div className="roomnames">
        
        <h2 className="label">Room List</h2> 
        <label className="label">To broadcast to all users: </label>
        <button className="button" type="submit" onClick={this.handleClick} value="broadcast">Broadcast</button>
        <label className="label">Rooms/Users you are connected to: </label><br></br>
        {this.renderRooms()} 
      </div>
      <div >
        <RoomForm create={this.createRoom} socketdata = {this.props.socketfromParent} userdata = {this.props.namefromParent}/> 
      </div> 
      </center>
      </div>
    ) 
  } 
} 
  
export default RoomList