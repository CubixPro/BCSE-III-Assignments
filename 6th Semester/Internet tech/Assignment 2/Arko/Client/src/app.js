import React, {Component} from 'react';
import { BrowserRouter, Route} from 'react-router-dom';
import Join from './components/join';
import Dashboard from './components/dashboard';

class App extends Component {
    render() {
        return (
            <BrowserRouter>
                <Route path="/" exact component={Join} />
                <Route path="/dashboard" render={(props) => <Dashboard {...props} />} />
            </BrowserRouter>
        );
    }
};

export default App;