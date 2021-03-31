import React, { Component } from "react";

class Counter extends Component {
  
  constructor(props) {
      super(props);
      this.state.count = this.props.value;
      console.log(this);
  }
state = {
    count: 0,
    imageUrl: "https://picsum.photos/200",
    tags: ["tag1", "tag2", "tag3"],
  };

  styles = {
    fontSize: "10px",
    fontWeight: "bold",
  };

  renderTags() {
    if (this.state.tags.length === 0) return <p> There are no Tags !</p>;
    return (
      <ul>
        {this.state.tags.map((tag) => (
          <li key={tag}>{tag}</li>
        ))}
      </ul>
    );
  }


  handleIncrement = (product) => {
      this.setState({ count: this.state.count + 1 });
      console.log("increment clicked", this.state.count)
  }
  render () { 
    console.log("props", this.props.value);
    return <div>
        { this.state.tags.length === 0 && "Please create a new Tag"}
        { this.renderTags() }
        {this.props.children} 
        <button onClick={ () => this.handleIncrement('1') } className="btn btn-secondary btn-sm">{ this.formatCount() }</button>
    </div> 
  }

  getBadgeClasses() {
    let classes = "badge m-2 ";
    classes += this.state.count === 0 ? "badge-warning" : "primary";
    return classes;
  }

  formatCount() {
    console.log(this.state.count)
    return this.state.count === 0 ? <h1>Zero</h1> : this.state.count;
  }
}

export default Counter;
