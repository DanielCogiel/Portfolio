import React from 'react';
import { Navigate } from 'react-router-dom';

interface AuthWrapperProps {
    children?: React.ReactNode
}
 
interface AuthWrapperState {
    isAuthenticated: boolean
}
 
class AuthWrapper extends React.Component<AuthWrapperProps, AuthWrapperState> {
    constructor(props: AuthWrapperProps) {
        super(props);
        this.state = {
            isAuthenticated: !!sessionStorage.getItem('username')
        };
    }

    render() { 
        return ( 
            <> { this.state.isAuthenticated ? this.props.children : <Navigate to='/login' /> } </>
         );
    }
}
 
export default AuthWrapper;