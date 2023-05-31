import React from 'react';
import { Route, Routes } from 'react-router-dom';
import { ToastContainer } from 'react-toastify'
import 'react-toastify/dist/ReactToastify.css';

import RouteModel from './interfaces/RouteModel';
import routes from './config/routes';
import './App.scss';

interface AppProps {
  
}
 
interface AppState {
  
}
 
class App extends React.Component<AppProps, AppState> {
  constructor(props: AppProps) {
    super(props);
    this.state = {};
  }
  render() { 
    return ( 
    <>
      <Routes>
        { routes.map((route: RouteModel, idx: number) => { return <Route key={idx} path={route.path} element={route.component} /> }) }
      </Routes>
      <ToastContainer
        position="bottom-right"
        autoClose={3000}
        hideProgressBar={false}
        newestOnTop={false}
        rtl={false}
        pauseOnFocusLoss
        pauseOnHover
        style={{ fontSize: '20px' }}
      />
    </>
    );
  }
}

export default App;