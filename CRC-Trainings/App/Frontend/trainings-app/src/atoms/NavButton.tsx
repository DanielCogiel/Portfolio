import React from 'react';
import { NavLink } from 'react-router-dom';

interface NavButtonProps {
    path: string,
    children?: React.ReactNode,
    isAlternative?: boolean
}
 
interface NavButtonState {
    
}
 
class NavButton extends React.Component<NavButtonProps, NavButtonState> {
    constructor(props: NavButtonProps) {
        super(props);
        this.state = {};
    }
    render() { 
        return (
            <NavLink to={this.props.path} children={({isActive}) => 
                (
                    <button className={`trainings-button ${isActive ? 'selected' : ''} ${this.props.isAlternative ? 'alternative' : ''}`} >
                        {this.props.children}
                    </button>
                )} />
          );
    }
}
 
export default NavButton;