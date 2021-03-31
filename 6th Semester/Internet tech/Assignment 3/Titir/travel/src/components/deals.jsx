import React, { Component } from 'react';
import Deal from './deal'
import "bootstrap/dist/css/bootstrap.css"
import Form from './form'
import CardFlight from './flightcard'

class Deals extends Component {
    state = { 
        deals: [],
        cities: []

     }
    
    componentDidMount(){
        fetch("http://127.0.0.1:3333/First_App/getall")
        .then(res => res.json())
        .then(
            (response) =>{
            this.setState({
                deals: response.deals,
                cities: response.cities

            });
        },
        (error) => {
            console.log(error);
        }
        )
    }
    
    render() { 
        console.log("Inside body ",this.state.deals[1]);
        return ( 
            <div>
            <div style={{margin:"10px"}} className="row">
                { this.state.deals.map((deal) =>  <Deal deal={deal} /> )}
            </div>
            <Form cities={this.state.cities} />
            </div>
         );
    }
}
 
export default Deals;