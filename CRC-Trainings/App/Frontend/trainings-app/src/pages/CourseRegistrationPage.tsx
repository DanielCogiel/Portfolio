import React from 'react';
import { Button, Form, InputGroup, Row, Col } from 'react-bootstrap';
import { Navigate } from 'react-router-dom';
import { toast } from 'react-toastify'

import MainLayout from '../layouts/MainLayout';
import CreatorWrapper from '../layouts/CreatorWrapper';
import CourseModel from '../interfaces/CourseModel';
import { API_URLS } from '../config/api';
import { Level, Language } from '../config/enums';
import '../styles/CourseRegistrationPage.scss'


interface CourseRegistrationPageProps {
    
}
 
interface CourseRegistrationPageState extends CourseModel {
    isRemote: boolean,
    redirect: boolean,
    validated: boolean
}
 
class CourseRegistrationPage extends React.Component<CourseRegistrationPageProps, CourseRegistrationPageState> {
    ENDPOINT: string = API_URLS.COURSES.REGISTER;
    UPLOAD_ENDPOINT: string = API_URLS.FILES.UPLOAD;

    constructor(props: CourseRegistrationPageProps) {
        super(props);
        this.state = {
            title: '',
            language: 'PL',
            date: {
                start: '',
                finish: ''
            },
            hours: {
                start: '',
                finish: '',
                times: 1
            },
            level: 'Beginner',
            location: '',
            trainer: '',
            isRemote: false,
            redirect: false,
            validated: false,
            image: undefined
        };
    }

    componentDidMount(): void {
        document.body.classList.add('body-purple');
    }

    componentWillUnmount(): void {
        document.body.classList.remove('body-purple');
    }

    handleChanges = (event: any) => {
        this.setState({
            ...this.state,
            [event.target.id]: event.target.value
        });
    }

    handleDateChange = (event: React.ChangeEvent<HTMLInputElement>) => {
        this.setState({
            ...this.state,
            date: {
                ...this.state.date,
                [event.target.id]: event.target.value 
            }
        });
    } 

    handleTimeChange = (event: React.ChangeEvent<HTMLInputElement>) => {
        this.setState({
            ...this.state,
            hours: {
                ...this.state.hours,
                [event.target.id]: event.target.value 
            }
        });
    } 

    checkRemote = () => {
        this.setState({
          ...this.state,
            isRemote: !this.state.isRemote,
            location: !this.state.isRemote ? 'Remote' : ''
        })
    }

    submitForm = (event: any) => {
        event.preventDefault();

        const form = event.currentTarget;
        if (form.checkValidity()) {
            this.postCourse();
        }
    }

    async postCourse(): Promise<void> {
        let formData = new FormData();

        formData.append('username', sessionStorage.getItem('username') || '');
        formData.append('title', this.state.title);
        formData.append('language', this.state.language.toLowerCase());
        formData.append('date', JSON.stringify({start: this.state.date.start, finish: this.state.date.finish}))
        formData.append('hours', JSON.stringify({
            start: this.state.hours.start,
            finish: this.state.hours.finish,
            times: this.state.hours.times
        }))
        formData.append('level', this.state.level.toLowerCase())
        formData.append('location', this.state.location)
        formData.append('trainer', this.state.trainer)
        formData.append('image', this.state.image)

        try {
            const response = await fetch(this.ENDPOINT, {
                method: 'POST',
                body: formData
            });
            const message = await response.text();
            toast.info(message);
            if (response.status === 200) {
                this.setState({
                    ...this.state,
                    redirect: true
                })
            }
        } catch (error: any) {}
    }

    handleUpload = (event: any) => {
        this.setState({
            ...this.state,
            image: event.target.files[0]
        })
    }

    render() { 
        return ( 
            <CreatorWrapper>
                <MainLayout isAlternative>
                <h1 className="section-header">Register new course</h1>
                <div className="container">
                    <div className="row justify-content-center">
                        <div className="col-10">
                        <Form validated={this.state.validated} style={{border: 'none', color: 'white'}} onSubmit={this.submitForm}>
                            <Row>
                                <Form.Group as={Col}>
                                    <Form.Label>Course title</Form.Label>
                                    <Form.Control required minLength={10} maxLength={100} size='lg' id="title" value={this.state.title} type='text'
                                    onChange={this.handleChanges} placeholder="Course title" />
                                </Form.Group>

                                <Form.Group as={Col}>
                                    <Form.Label>Course image</Form.Label>
                                    <Form.Control required size='lg' id="title" type='file' accept='.jpg, .jpeg, .png'
                                    onChange={this.handleUpload} />
                                </Form.Group>
                            </Row>

                            <Row>
                                <Form.Group as={Col}>
                                    <Form.Label >First day</Form.Label>
                                    <Form.Control required size='lg' id="start" value={this.state.date.start} 
                                    onChange={this.handleDateChange} type='date' />
                                </Form.Group> 

                                <Form.Group as={Col}>
                                    <Form.Label>Last day</Form.Label>
                                    <Form.Control min={this.state.date.start} required size='lg' id="finish" value={this.state.date.finish}
                                    onChange={this.handleDateChange} type='date' />
                                </Form.Group>

                                <Form.Group as={Col}>
                                    <Form.Label >Beginning hour</Form.Label>
                                    <Form.Control required size='lg' id="start" value={this.state.hours.start}
                                    onChange={this.handleTimeChange} type='time' />
                                </Form.Group>

                                <Form.Group as={Col}>
                                    <Form.Label >Finishing hour</Form.Label>
                                    <Form.Control required min={this.state.hours.start} size='lg' id="finish" value={this.state.hours.finish}
                                    onChange={this.handleTimeChange} type='time' />
                                </Form.Group>

                                <Form.Group as={Col}>
                                    <Form.Label >Number of lessons</Form.Label>
                                    <Form.Control required size='lg' id="times" value={this.state.hours.times}
                                    onChange={this.handleTimeChange} type='number' min='1' placeholder="Number of lessons" />
                                </Form.Group>
                            </Row>
                            
                            <Row>
                                <Form.Group as={Col}>
                                    <Form.Label >Language</Form.Label>
                                    <Form.Select id='language' value={this.state.language}
                                    onChange={this.handleChanges} size="lg">
                                        { Object.values(Language).map(lang => {return <option key={lang}>{lang}</option>}) }
                                    </Form.Select>
                                </Form.Group>

                                <Form.Group as={Col}>
                                    <Form.Label >Level</Form.Label>
                                    <Form.Select id='level' value={this.state.level}
                                    onChange={this.handleChanges} size="lg">
                                        { Object.values(Level).map(level => {return <option key={level}>{level}</option>}) } 
                                    </Form.Select>
                                </Form.Group>

                                <Form.Group as={Col}>
                                    <Form.Label >Location (check if remote)</Form.Label>
                                    <InputGroup>
                                        <Form.Control required disabled={this.state.isRemote} value={this.state.location}
                                        onChange={this.handleChanges} size='lg' id="location" type='text' placeholder="Course location" />
                                        <InputGroup.Checkbox checked={this.state.isRemote} onChange={this.checkRemote} />
                                    </InputGroup>
                                </Form.Group>
                                
                                <Form.Group>
                                    <Form.Label >Trainer's name</Form.Label>
                                    <Form.Control required min='3' max='100' size='lg' id="trainer" value={this.state.trainer}
                                    onChange={this.handleChanges} type='text' placeholder="Trainer's name" />
                                    <Button variant='primary' style={{marginTop: '10px'}} size='lg' type='submit'>Register new course</Button>  
                                </Form.Group>
                            </Row>

                        </Form>
                        {
                            this.state.redirect && <Navigate to='/courses/all' />
                        }
                        </div>
                    </div>
                </div>
                </MainLayout>
            </CreatorWrapper>
         );
    }
}
 
export default CourseRegistrationPage;