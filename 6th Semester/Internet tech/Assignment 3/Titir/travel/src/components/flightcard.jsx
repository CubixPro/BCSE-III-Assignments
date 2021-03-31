import React, { Component } from 'react';
import Flight from './flight'
import "bootstrap/dist/css/bootstrap.css"
class CardFlight extends Component {
    state = {  }
    render() { 
        console.log("Inside card flight" , this.props.flight.dealflight);
        return ( 
            <div className="card col-sm-4">
                
            </div>
         );
    }
}
 

export default CardFlight;


//<Flight  flight={this.props.flight.dealflight}/>