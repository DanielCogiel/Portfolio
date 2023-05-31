import React from 'react';
import '../styles/CourseBanner.scss'
import { COURSES_API_URL } from '../config/api';
import {toast} from 'react-toastify'

interface CourseBannerProps {
    id: number,
    imgURL: string,
    isEnrolled: boolean
}
 
interface CourseBannerState {
    isEnrolled: boolean;
}
 
class CourseBanner extends React.Component<CourseBannerProps, CourseBannerState> {
    ENDPOINT = COURSES_API_URL;

    constructor(props: CourseBannerProps) {
        super(props);
        this.state = {
            isEnrolled: this.props.isEnrolled
        };
    }

    enroll = (): void => {
        fetch(`${this.ENDPOINT}/${this.props.id}/enroll`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({username: sessionStorage.getItem('username')})
        })
        .then(response => response.text())
        .then(message => {
            toast.info(message);
            this.setState({
                isEnrolled: true
            })
        })
        .catch(error => {})
    }

    leave = (): void => {
        fetch(`${this.ENDPOINT}/${this.props.id}/leave`, {
            method: 'DELETE',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({username: sessionStorage.getItem('username')})
        })
        .then(response => response.text())
        .then(message => {
            toast.info(message);
            this.setState({
                isEnrolled: false
            })
        })
        .catch(error => {})
    }

    render() { 
        return ( 
            <div className="training-image">
                <img src={this.props.imgURL} />
                <button onClick={this.state.isEnrolled ? this.leave : this.enroll}>{ this.state.isEnrolled ? '-' : '+' }</button>
            </div>
         );
    }
}
 
export default CourseBanner;