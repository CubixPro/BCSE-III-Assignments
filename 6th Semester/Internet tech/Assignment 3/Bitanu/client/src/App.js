import React, { useState, useEffect } from "react";
import { BrowserRouter as Router, Switch, Route, Link } from "react-router-dom";
var moment = require("moment");

export default function App() {
  return (
    <Router>
      <Switch>
        <Route path="/bookFlights">
          <BookFlights />
        </Route>
        <Route path="/">
          <Home />
        </Route>
      </Switch>
    </Router>
  );
}

function Home() {
  const [offers, setOffers] = useState([]);
  useEffect(() => {
    fetch("http://localhost:8090/FlightsApp/getFlightInfo")
      .then((response) => response.json())
      .then((data) => {
        console.log(data);
        setOffers(
          data.filter((offer) => {
            let time = new Date();
            time.setHours(offer.time, 0, 0);
            let curr_time = new Date();
            return time <= curr_time;
          })
        );
      })
      .catch((error) => console.log(error, "ERROR!"));
  }, []);
  return (
    <div>
      <div
        style={{
          background: "blue",
          color: "white",
          padding: "2%",
          fontSize: "24px",
        }}
      >
        <h2>Flights Booking App</h2>
      </div>
      <div
        style={{
          margin: "30px",
          padding: "30px",
          display: "flex",
        }}
      >
        <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
          SOURCE
        </span>
        <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
          DESTINATION
        </span>
        <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
          DISCOUNTED PRICE
        </span>
        <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
          DEPARTURE TIME
        </span>
      </div>
      {offers.map((offer, idx) => {
        let time = new Date();
        time.setHours(offer.time, 0, 0);
        return (
          <div
            key={idx}
            style={{
              margin: "30px",
              padding: "30px",
              background: "cyan",
              display: "flex",
            }}
          >
            <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
              {offer.source}
            </span>
            <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
              {offer.destination}
            </span>
            <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
              Rs {offer.reduced_cost}
            </span>
            <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
              {moment(time).format("hh:mm A")}
            </span>
          </div>
        );
      })}
      <div style={{ padding: "15%", paddingTop: "3%", fontSize: "20px" }}>
        <Link to="bookFlights">Book Flight</Link>
      </div>
    </div>
  );
}

function BookFlights() {
  const [source, setSource] = useState("");
  const [dest, setDest] = useState("");
  const [time, setTime] = useState("");
  const [flights, setFlights] = useState([])
  const onChangeSource = (e) => {
    setSource(e.target.value);
  };
  const onChangeDest = (e) => {
    setDest(e.target.value);
  };
  const onChangeTime = (e) => {
    setTime(e.target.value);
  };
  const handleSubmit = (e) => {
    e.preventDefault();
    fetch(`http://localhost:8090/FlightsApp/showFlightInfo?source=${source}&destination=${dest}&time=${time}`)
      .then((response) => {
        console.log(response);
        return response.json();
      })
      .then((data) =>
        setFlights(data)
      )
      .catch((error) => console.log(error));
  };
  
  return (
    <div>
      <div
        style={{
          background: "blue",
          color: "white",
          padding: "2%",
          fontSize: "24px",
        }}
      >
        <h2>Flights Booking App</h2>
      </div>

      <div style={{ padding: "15%", paddingTop: "3%", paddingBottom: "3%", fontSize: "20px" }}>
        <form onSubmit={handleSubmit}>
          <span style={{ margin: "2%" }}>
            <labeL>Enter Source: </labeL>
            <input
              type="text"
              name="source"
              value={source}
              onChange={onChangeSource}
            />
          </span>
          <span style={{ margin: "2%" }}>
            <labeL>Enter Destination: </labeL>
            <input
              type="text"
              name="destination"
              value={dest}
              onChange={onChangeDest}
            />
          </span>
          <span style={{ margin: "2%" }}>
            <labeL>Enter Flight Time: </labeL>
            <input
              type="text"
              name="time"
              value={time}
              onChange={onChangeTime}
            />
          </span>
          <span style={{ margin: "2%" }}>
            <input type="submit" value="Submit"></input>
          </span>
        </form>
      </div>
      <div
        style={{
          margin: "30px",
          padding: "30px",
          display: "flex",
        }}
      >
        <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
          SOURCE
        </span>
        <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
          DESTINATION
        </span>
        <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
          PRICE
        </span>
        <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
          DEPARTURE TIME
        </span>
        <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
          LEGS
        </span>
      </div>
      {flights.map((offer, idx) => {
        let time = new Date();
        time.setHours(offer.time, 0, 0);
        return (
          <div
            key={idx}
            style={{
              margin: "30px",
              padding: "30px",
              background: "cyan",
              display: "flex",
            }}
          >
            <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
              {offer.source}
            </span>
            <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
              {offer.destination}
            </span>
            <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
              Rs {offer.price}
            </span>
            <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
              {moment(time).format("hh:mm A")}
            </span>
            <span style={{ width: "300px", margin: "20px", fontSize: "20px" }}>
              {offer.legs}
            </span>
          </div>
        );
      })}
    </div>
  );
}
