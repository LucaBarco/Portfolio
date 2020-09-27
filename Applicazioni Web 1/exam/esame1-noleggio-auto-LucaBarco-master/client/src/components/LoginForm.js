import React from 'react'
import Form from 'react-bootstrap/Form'
import Button from 'react-bootstrap/Button'
import Col from 'react-bootstrap/Col'
import Row from 'react-bootstrap/Row'
import Alert from 'react-bootstrap/Alert'
import Spinner from 'react-bootstrap/Spinner'

class LoginForm extends React.Component{

    constructor(props){
        super(props);
        this.state={username:'',password:'',submitted:false}
    }

    onChangeUsername = (event) => {
        this.setState({username : event.target.value});
    }; 
    
    onChangePassword = (event) => {
        this.setState({password : event.target.value});
    };

    handleSubmit=(event)=>{
        this.setState({submitted:true});
        event.preventDefault();
        this.props.loginMethod(this.state.username,this.state.password);
        
    }
    
    render(){
        return(
            <Row className="justify-content-md-center below-nav">
            <Col sm={3} >
                
                {this.props.authErr===404 && <Alert variant="danger"> Credenziali errate</Alert>}
                {this.props.authErr===401 && <Alert variant="danger"> Password errata</Alert>}
                
            <Form method="POST" onSubmit={(event)=>{this.handleSubmit(event)}}>
                <Form.Group controlId="formBasicEmail">
                    <Form.Label>Email</Form.Label>
                    <Form.Control type="email" placeholder="Inserisci email" value = {this.state.username} onChange={(ev) => this.onChangeUsername(ev)} required autoFocus/>
                </Form.Group>

                <Form.Group controlId="formBasicPassword">
                    <Form.Label>Password</Form.Label>
                    <Form.Control type="password" placeholder="Inserisci password" value = {this.state.password} onChange={(ev) => this.onChangePassword(ev)} required/>
                </Form.Group>
                
                <Button variant="primary" type="submit">
                    Login
                </Button>
            </Form>
            {this.props.authErr===null && this.state.submitted && <Alert variant="primary"><Spinner animation="border" variant="primary"/> Accesso in corso ...</Alert>}
            </Col>
            </Row>
        );
    }
}

export default LoginForm;