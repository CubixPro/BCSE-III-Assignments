import React, { Component } from "react";
import "bootstrap/dist/css/bootstrap.css";
import "bootstrap/dist/css/bootstrap.min.css";
import Flight from "./flight";
class Form extends Component {
  state = {
    cities: [],
    flights: [],
    acity: "",
    dcity: "",
  };
  constructor(props) {
    super(props);
    console.log("inside form", this.props.cities);
    this.state.cities = this.props.cities;
  }

  handleChange = (e) => {
    this.setState({ [e.target.name]: e.target.value });
    console.log("city1", this.state.acity);
    console.log("city2", this.state.dcity);
  };

  fetchFlights = (e) => {
    e.preventDefault();
    fetch(
      "http://localhost:3333/First_App/flights?acity=" +
        this.state.acity +
        "&dcity=" +
        this.state.dcity
    )
      .then((res) => res.json())
      .then((response) => {
        console.log(response.flights);
        this.setState({ flights: response.flights });
        console.log("flight123", this.state.flights.length);
      });
  };

  render() {
    console.log(this.state);
    return (
      <div>
        <form onSubmit={this.fetchFlights}>
          <div class="mb-3">
            <label for="exampleFormControlInput1" class="form-label">
              Destination City
            </label>
            <input
              class="form-control"
              list="datalistOptions"
              id="dcity"
              placeholder="Type to search..."
              name="dcity"
              onChange={this.handleChange}
            />
            <datalist id="datalistOptions">
              {this.props.cities.map((acity) => (
                <option value={acity} />
              ))}
            </datalist>
          </div>
          <div class="mb-3">
            <label for="exampleFormControlInput1" class="form-label">
              Arrival City
            </label>
            <input
              class="form-control"
              list="datalistOptions"
              id="acity"
              placeholder="Type to search..."
              name="acity"
              onChange={this.handleChange}
            />
            <datalist id="datalistOptions">
              {this.props.cities.map((acity) => (
                <option value={acity} />
              ))}
            </datalist>
          </div>
          <div class="col-auto">
            <button type="submit" class="btn btn-primary mb-3">
              Search
            </button>
          </div>
        </form>
        {this.state.flights.length > 0 && this.state.flights.map(flight => <div className="row"><div className="card col-sm-4" style={{ width: "20rem", margin: "10px", padding: "0px" }}><Flight flight={flight}/></div></div>)}
      </div>
    );
  }
}

export default Form;

/*
<div>

          <select className="form-select form-select-lg mb-3" >
            <option selected> Kolkata </option>
            {this.props.acities.map((acity) => (
              <option value={acity}> {acity} </option>
            ))}
          </select>
          <select className="form-select form-select-lg mb-3" >
            <option selected> Siliguri </option>
            {this.props.dcities.map((dcity) => (
              <option value={dcity}> {dcity} </option>
            ))}
          </select>
        
      </div>
      */
<div className="card col-sm-4" style={{ width: "20rem", margin: "10px", padding: "0px" }}></div>