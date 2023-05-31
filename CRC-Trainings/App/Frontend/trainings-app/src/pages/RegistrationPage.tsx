import React from 'react';
import { Form, Button, Row, Col, InputGroup } from 'react-bootstrap';
import { Navigate } from 'react-router-dom';
import '../styles/LoginPage.scss'
import UserModel from '../interfaces/UserModel';
import { API_URLS } from '../config/api';
import { toast } from 'react-toastify';

interface RegistrationPageProps {
    
}
 
interface RegistrationPageState {
    username: string, 
    firstName: string,
    lastName: string, 
    email: string,
    password: string,
    confirmedPassword: string,
    redirectToLogin: boolean,
    isCreator: boolean,
    validated: boolean
}
 
class RegistrationPage extends React.Component<RegistrationPageProps, RegistrationPageState> {
    ENDPOINT = API_URLS.AUTH.REGISTER;

    constructor(props: RegistrationPageProps) {
        super(props);
        this.state = {
            username: '', 
            firstName: '',
            lastName: '', 
            email: '',
            password: '',
            confirmedPassword: '',
            redirectToLogin: false,
            isCreator: false,
            validated: false
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

        const form = event.currentTarget
        if (form.checkValidity()) {
            this.postUser();
        }
    }

    async postUser(): Promise<void> {
        const data: UserModel = {
            username: this.state.username,
            password: this.state.password,
            confirmedPassword: this.state.confirmedPassword,
            name: this.state.firstName,
            surname: this.state.lastName,
            email: this.state.email,
            isCreator: this.state.isCreator
        }

        let redirect: boolean = false;
       
        fetch(this.ENDPOINT, {
            method: 'POST', 
            body: JSON.stringify(data),
            headers: {
                'Content-Type': 'application/json'
            }
        })
        .then(response => {
            if (response.status === 200)
                redirect = true;
            return response.text();
        })
        .then(message => toast.info(message))
        .then(() => {
            if (redirect) {
                this.setState({
                    ...this.state,
                    redirectToLogin: true
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

    checkCreator = (event: any) => {
        this.setState({
            ...this.state, 
            isCreator: !this.state.isCreator
        })
    }

    navigateToLogin = () => {
        this.setState({
            ...this.state,
            redirectToLogin: true
        });
    }

    render() { 
        return (  
            <>
                <h1 className='section-header' style={{marginBottom: '-50px'}}>Register</h1>
                <div className='container'>
                    <div className='row justify-content-center'>
                        <div className='col-8'>
                            <Form validated={this.state.validated} className='login-form rounded p-3' onSubmit={this.handleSubmit}>
                               
                                <Form.Group>
                                    <Form.Label>Username (check if you want to be creator)</Form.Label>
                                    <InputGroup>
                                        <Form.Control
                                        required
                                        minLength={5}
                                        maxLength={50}
                                        id='username'
                                        placeholder='Enter your username'
                                        type='text'
                                        value={this.state.username}
                                        onChange={this.handleChange}></Form.Control>
                                        <InputGroup.Checkbox id='isCreator' checked={this.state.isCreator} onChange={this.checkCreator} />
                                    </InputGroup>
                                </Form.Group>
                               
                                <Row>
                                    <Form.Group as={Col}>
                                        <Form.Label>First name</Form.Label>
                                        <Form.Control
                                        required
                                        minLength={2}
                                        maxLength={50}
                                        id='firstName'
                                        placeholder='Enter your first name'
                                        type='text'
                                        value={this.state.firstName}
                                        onChange={this.handleChange}></Form.Control>
                                    </Form.Group>
                                    <Form.Group as={Col}>
                                        <Form.Label>Last name</Form.Label>
                                        <Form.Control
                                        required
                                        minLength={2}
                                        maxLength={50}
                                        id='lastName'
                                        placeholder='Enter your last name'
                                        type='text'
                                        value={this.state.lastName}
                                        onChange={this.handleChange}></Form.Control>
                                    </Form.Group>
                                </Row>
                                <Form.Group>
                                    <Form.Label>Email</Form.Label>
                                    <Form.Control 
                                    required
                                    minLength={5}
                                    maxLength={255}
                                    id='email'
                                    placeholder='Enter your E-mail'
                                    type='email'
                                    value={this.state.email}
                                    onChange={this.handleChange}></Form.Control>
                                </Form.Group>
                                <Row>
                                    <Form.Group as={Col}>
                                        <Form.Label>Password</Form.Label>
                                        <Form.Control 
                                        required
                                        minLength={5}
                                        maxLength={60}
                                        id='password'
                                        placeholder='Enter your password'
                                        type='password'
                                        value={this.state.password}
                                        onChange={this.handleChange}></Form.Control>
                                    </Form.Group>
                                    <Form.Group as={Col}>
                                        <Form.Label>Confirm password</Form.Label>
                                        <Form.Control
                                        required
                                        minLength={5}
                                        maxLength={60}
                                        id='confirmedPassword'
                                        placeholder='Enter password again' 
                                        type='password'
                                        value={this.state.confirmedPassword}
                                        onChange={this.handleChange}></Form.Control>
                                    </Form.Group>
                                </Row>
                                <Row>
                                    <Button type='submit'>Register</Button>
                                    <Button onClick={this.navigateToLogin}>Log in</Button>
                                </Row>
                            </Form>
                            {
                                this.state.redirectToLogin && <Navigate to='/login' />
                            }
                        </div>
                    </div>
                </div>
            </>
        );
    }
}
 
export default RegistrationPage;