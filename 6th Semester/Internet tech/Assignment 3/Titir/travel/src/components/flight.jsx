import React, { Component } from 'react';

class Flight extends Component {
    state = { 
        id: 0,
        dcity: "",
        acity: "",
        atime: "",
        dtime: "",
        cost: 0,
        flightid: "",
        company: "",
        logourl: ""
    }

    constructor(props){
        super(props);
        console.log(this.props.flight)
        this.state.id = this.props.flight.id;
        this.state.dcity = this.props.flight.dcity ;
        this.state.acity = this.props.flight.acity
        this.state.atime = this.props.flight.atime
        this.state.dtime = this.props.flight.dtime 
        this.state.cost = this.props.flight.cost
        this.state.flightid = this.props.flight.code
        this.state.company = this.props.flight.company
        this.state.logourl = this.props.flight.logourl
    }



    render() { 

        console.log("inside flight");

        return ( <div style={{ margin:"10px" }}>
            
            <h1 className="display-5">{ this.state.company }</h1>
            <h1 className="display-6">ID: { this.state.flightid }</h1>
            <div><mark>{ this.state.acity }</mark> to <mark>{ this.state.dcity }</mark></div>
            <div><medium>{ this.state.atime } - { this.state.dtime }</medium></div>
            <div><muted>Rs { this.state.cost } </muted></div>

        </div>  );
    }
}
 
export default Flight;

//popover on click