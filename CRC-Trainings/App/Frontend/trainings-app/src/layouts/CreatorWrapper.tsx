import React from 'react';
import { Navigate } from 'react-router-dom';

interface CreatorWrapperProps {
    children?: React.ReactNode
}
 
interface CreatorWrapperState {
    isCreator: boolean
}
 
class CreatorWrapper extends React.Component<CreatorWrapperProps, CreatorWrapperState> {
    constructor(props: CreatorWrapperProps) {
        super(props);
        this.state = { isCreator: sessionStorage.getItem('role') === 'creator' };

    }
    render() { 
        return (
            <>
                { this.state.isCreator ? this.props.children : <Navigate to='/courses/all' /> }
            </>
        );
    }
}
 
export default CreatorWrapper;