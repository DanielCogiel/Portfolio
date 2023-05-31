import React from 'react';
import NavButton from '../atoms/NavButton';
import { Navigate } from 'react-router-dom';

import AppLogo from '../resources/images/graduation_school_icon.svg'
import '../styles/Header.scss'
import routes from '../config/routes';
import { PERSONAL_COURSES_URL } from '../config/api';

interface HeaderProps {
    isAlternative?: boolean
}
 
interface HeaderState {
    redirectToLogin: boolean,
    coursesNumber?: number
}
 
class Header extends React.Component<HeaderProps, HeaderState> {
    ENDPOINT: string = `${PERSONAL_COURSES_URL}/count`

    constructor(props: HeaderProps) {
        super(props);
        this.state = {
            redirectToLogin: false
        };
    }

    componentDidMount(): void {
        fetch(`${this.ENDPOINT}?username=${sessionStorage.getItem('username')}`)
        .then(response => response.json())
        .then(count => {
            this.setState({
                ...this.state,
                coursesNumber: count.count
            })
        })
        .catch(error => {})
    }

    logout = ():void => {
        sessionStorage.removeItem('username');
        sessionStorage.removeItem('role');
        this.setState({
            ...this.state,
            redirectToLogin: true
        })
    }

    render() { 
        return ( 
            <header id="header" className={this.props.isAlternative ? 'alternative' : ''}>
                <div id="header-left">
                    <img src={AppLogo} alt="Trainings logo" title="Trainings" />
                    <h1>Trainings</h1>
                </div>
                <div id="header-right">
                    { routes.filter(route => route.HeaderRouteName && ((sessionStorage.getItem('role') === 'regular' && !route.isCreatorOnly) || sessionStorage.getItem('role') === 'creator')  ).map(
                        (route, idx) => <NavButton
                        isAlternative={this.props.isAlternative} 
                        key={idx} 
                        path={route.path}>
                            {route.HeaderRouteName}{route.hasNotificationNumber 
                            && <div className="notification-number">{this.state.coursesNumber}</div> }
                            </NavButton>
                    ) }  
                    <button onClick={this.logout} className='trainings-button'>Logout</button>
                </div>
                { this.state.redirectToLogin && <Navigate to='/login' /> }
            </header>
        );
    }
}
 
export default Header;