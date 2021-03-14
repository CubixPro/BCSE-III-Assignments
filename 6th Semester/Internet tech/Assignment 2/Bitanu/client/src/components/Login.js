import React, { Component } from "react";

export default class Login extends Component {
  constructor(props) {
    super(props);
    this.state = { value: "" };
  }
  handleChange(e) {
    this.setState({ value: e.target.value });
  }
  handleSubmit(e) {
    e.preventDefault();
    this.props.onUsernameSelect(this.state.value);
  }
  render() {
    return (
      <div>
        <form onSubmit={(e) => this.handleSubmit(e)}>
          <label>
            Name:
            <input type="text" onChange={(e) => this.handleChange(e)} />
          </label>
          <input type="submit" value="Submit" />
        </form>
      </div>
    );
  }
}
