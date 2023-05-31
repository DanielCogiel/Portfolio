import React from 'react';
import { Link } from 'react-router-dom';

interface NotFoundPageProps {
    
}
 
interface NotFoundPageState {
    
}
 
class NotFoundPage extends React.Component<NotFoundPageProps, NotFoundPageState> {
    constructor(props: NotFoundPageProps) {
        super(props);
        this.state = {};
    }
    render() { 
        return ( 
            <>
                <h1>Error 404 - Page Not Found</h1>
                <Link to='/'>Back to main page</Link>
            </>
         );
    }
}
 
export default NotFoundPage;