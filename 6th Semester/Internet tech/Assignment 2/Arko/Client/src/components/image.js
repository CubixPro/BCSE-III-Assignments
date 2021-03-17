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
                        <div className="image"><img width="280" src={this.props.message.image} alt={this.props.message.imageName} /></div>
                        <p className="messageText userText">{this.props.message.text}</p>
                    </div>
                </div>
            )
        }
    
        else {
            if(this.props.message.type !== 'multi') this.props.message.user = null;
            return (
                <div className="messageContainerOthers">
                    <div className="messageBox backgroundWhite">
                        <div className="image"> <img width="280" src={this.props.message.image} alt={this.props.message.imageName} /> </div>
                        <p className="messageText">{this.props.message.text}</p>
                    </div>
                    <p className="sentUser">{this.props.message.user}</p>
                </div>
            )
        }
    }
}

export default Image;