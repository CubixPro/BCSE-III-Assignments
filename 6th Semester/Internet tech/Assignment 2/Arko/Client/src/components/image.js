import React, { Component } from 'react';

class Image extends Component {

    constructor(props) {
        super(props);
        this.state ={
            isSentByCurrUser: (props.message.user === props.name),
        }
    }

    render() {

        if(this.state.isSentByCurrUser) {
            return (
                <div className="messageContainerSelf">
                    <div className="messageBox backgroundBlue">
                        <p className="messageText">{this.props.message.text}</p>
                        <div className="image"><img width="325" src={this.props.message.image} alt={this.props.message.imageName} /></div>
                    </div>
                </div>
            )
        }
    
        else {
            return (
                <div className="messageContainerOthers">
                    <div className="messageBox backgroundWhite">
                        <p className="messageText">{this.props.message.text}</p>
                        <div className="image"> <img width="325" src={this.props.message.image} alt={this.props.message.imageName} /> </div>
                    </div>
                    <p className="sentUser">{this.props.name}</p>
                </div>
            )
        }
    }
}

export default Image;