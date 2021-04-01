import React, { Component } from "react";
import "bootstrap/dist/css/bootstrap.css";
import "bootstrap/dist/css/bootstrap.min.css";
import Flight from "./flight";
import SimplePopover from "./popover"
class Deal extends Component {
  state = {
    code: "",
    discount: 0,
    hoursactive: 0,
    flightid: "",
    img: "",
  };

  constructor(props) {
    super(props);
    this.state.code = this.props.deal.code;
    this.state.discount = this.props.deal.discount;
    this.state.hoursactive = this.props.deal.hoursvalid;
    this.state.flightid = this.props.deal.dealflight.code;
    this.state.img = this.props.deal.dealflight.logourl;
  }

  render() {
    //var imgName = require(this.state.img);
    return (
      <div
        className="card col-sm-4"
        style={{ width: "20rem", margin: "10px", padding: "0px" }}
      >
        <div className="card-header" style={{ color: "red" }}>
          Discount : {this.state.discount}%{" "}
        </div>
        <div className="card-body">
          <h5 className="card-title">Offer Code : {this.state.code}</h5>
          <h6 className="card-subtitle">Flight Code : {this.state.flightid}</h6>
        <SimplePopover key={ this.props.deal.dealflight.code }  flight={ this.props.deal.dealflight }/>
          <p className="card-footer text-muted">
            Hours Valid : {this.state.hoursactive}{" "}
          </p>
        </div>

      </div>



    );
  }
}

export default Deal;
