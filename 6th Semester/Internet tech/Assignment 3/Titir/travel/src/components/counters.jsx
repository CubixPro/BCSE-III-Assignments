import React, { Component } from 'react';
import Counter from "./counter"

class Counters extends Component {
    state = { 
        counters: [
            {id: 1, value: 4},
            {id: 1, value: 0},
            {id: 1, value: 0}
        ],
        data : "hello"
     }
     componentDidMount(){
         fetch("http://127.0.0.1:3333/First_App/deals")
         .then(res => res.json())
         .then(
             (response) =>{
                this.setState({
                    data: response.dcity
                });
             },
             (error) => {
                 console.log(error);
                 this.setState({
                     data: "null" 
                 });
             }
         );

     }
    render() { 
        return ( 
            <div>
               {this.state.counters.map(
                   counter => <Counter key={counter.id} value={counter.value} selected={true} >
                       <h4> { this.state.data } </h4>
                       </Counter>
               )} 
            </div>
         );
    }
}
 
export default Counters;




//DONE TODO CREATE A BETTER API
//DONE RENDER SPECIAL DEALS
// CREATE BETTER UI
//DONE GET FLIGHTS
//SHOW FLIGHT UI
//create flight card
//show flights form

//CONNECT