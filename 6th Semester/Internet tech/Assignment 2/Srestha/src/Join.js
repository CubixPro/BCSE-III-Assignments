import React, {Component} from "react";
import {Link} from "react-router-dom";
import "./Join.css";
import "./Chat";

class Join extends React.Component {
    constructor(props) {
        super(props);
        this.state = {value: ""};
        this.handleChange = this.handleChange.bind(this);
    }

    handleChange(event) {
        this.setState({value: event.target.value});
    }

    render() {
        return (
            <div className="joinContainer">
                <div className="heading">
                  <h1><center>Login</center></h1>
                </div>
                <form>
                    <center>
                    <label>Name : </label>
                    <input type="text" name="name" value={this.state.value} onChange={this.handleChange}/>  <br></br><br></br>
                    
                    <Link to={`/chat/${this.state.value}`}><input type="submit" className="button" value="Sign-In"/></Link>
                    </center>
                </form>    
            </div>
          );
    }
}



export default Join;