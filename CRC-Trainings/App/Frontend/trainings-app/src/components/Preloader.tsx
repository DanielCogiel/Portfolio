import React from 'react';
import '../styles/Preloader.scss'

interface PreloaderProps {
    
}
 
interface PreloaderState {
    
}
 
class Preloader extends React.Component<PreloaderProps, PreloaderState> {
    constructor(props: PreloaderProps) {
        super(props);
        this.state = {};
    }
    render() { 
        return ( 
            <div id='preloader'></div>
         );
    }
}
 
export default Preloader;