import React from 'react';
import { Form, Button, Row } from 'react-bootstrap';
import { Navigate } from 'react-router-dom';
import '../styles/LoginPage.scss'
import { API_URLS } from '../config/api';
import { toast } from 'react-toastify';

interface LoginPageProps {
    
}
 
interface LoginPageState {
    username: string, 
    password: string,
    redirectToRegistration: boolean,
    redirectToHome: boolean
}
 
class LoginPage extends React.Component<LoginPageProps, LoginPageState> {
    ENDPOINT = API_URLS.AUTH.LOGIN

    constructor(props: LoginPageProps) {
        super(props);
        this.state = {
            username: '',
            password: '',
            redirectToRegistration: false,
            redirectToHome: false
        };
    }

    componentDidMount(): void {
        document.body.classList.add('body-with-image');
    }

    componentWillUnmount(): void {
        document.body.classList.remove('body-with-image');
    }

    handleSubmit = (event: any) => {
        event.preventDefault();
        this.logIn();
    }

    async logIn(): Promise<void> {
        const data = {
            username: this.state.username,
            password: this.state.password
        }

        fetch(this.ENDPOINT, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(data)
        })
        .then(response => response.json())
        .then(parameters => {
            toast.info(parameters.message);
            if (parameters.isAuthenticated) {
                sessionStorage.setItem('username', data.username);
                sessionStorage.setItem('role', parameters.role.toLowerCase());
                this.setState({
                    ...this.state,
                    redirectToHome: true
                })
            }
        })
    }

    handleChange = (event: any) => {
        this.setState({
            ...this.state,
            [event.target.id]: event.target.value
        });
    }

    navigateToRegistration = (event: any) => {
        this.setState({
            ...this.state,
            redirectToRegistration: true
        });
    }

    render() { 
        return (  
            <>
            <h1 className='section-header'>Login</h1>
            <div className='container'>
                <div className='row justify-content-center'>
                    <div className='col-5'>
                        <Form className='login-form rounded p-3' onSubmit={this.handleSubmit}>
                            <Form.Group>
                                <Form.Label>Username</Form.Label>
                                <Form.Control 
                                id='username'
                                value={this.state.username} 
                                placeholder='Enter your username' 
                                type='text'
                                onChange={this.handleChange}>
                                </Form.Control>
                            </Form.Group>
                            <Form.Group>
                                <Form.Label>Password</Form.Label>
                                <Form.Control 
                                id='password'
                                value={this.state.password}
                                placeholder='Enter your password' 
                                type='password'
                                onChange={this.handleChange}>
                                </Form.Control>
                            </Form.Group>
                            <Row>
                                <Button type='submit'>Login</Button>
                                <Button onClick={this.navigateToRegistration}>Register</Button>
                            </Row>
                        </Form>
                        { this.state.redirectToRegistration && <Navigate to='/register' /> }
                        { this.state.redirectToHome && <Navigate to='/' /> }
                    </div>
                </div>
            </div>
            </>
        );
    }
}
 
export default LoginPage;