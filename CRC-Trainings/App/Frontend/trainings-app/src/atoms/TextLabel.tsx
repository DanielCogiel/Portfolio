import React from 'react';
import '../styles/TextLabel.scss'

interface TextLabelProps {
    imgURL: string,
    text: string
}
 
interface TextLabelState {
    
}
 
class TextLabel extends React.Component<TextLabelProps, TextLabelState> {
    constructor(props: TextLabelProps) {
        super(props);
        this.state = {};
    }
    render() { 
        return ( 
            <div className='training-content-item'>
                <img src={this.props.imgURL} />
                <span>{this.props.text}</span>
            </div>
         );
    }
}
 
export default TextLabel;