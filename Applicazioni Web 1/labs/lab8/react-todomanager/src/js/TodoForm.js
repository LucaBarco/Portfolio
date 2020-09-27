import React from 'react';
import ReactDOM from 'react-dom';
import {Modal,Button,Form} from 'react-bootstrap';
import Task from './task';
import moment from 'moment';


class TodoForm extends React.Component{ 
    constructor(props){  
        super(props);
        
            this.state={show:false};  
            this.description=React.createRef();
            this.project=React.createRef();
            this.deadline=React.createRef();
            this.state={privateTask:false};
            this.state={important:false};
            

            this.handlePrivateCheckbox=this.handlePrivateCheckbox.bind(this);
            this.handleImportantCheckbox=this.handleImportantCheckbox.bind(this);
        
    }
    static getDerivedStateFromProps(props,state){
        if(props.mode.localeCompare('add')===0){
            return {show:true};   
        }
        else{
            return {show:false};  
        }
    }
    createNewTask(){
        const d=this.description.current.value;
        const p=this.project.current.value;
        const dl=this.deadline.current.value;
        console.log(d);
        console.log(this.state.privateTask);
        console.log(this.state.important);
        this.setState({privateTask:false});
        this.setState({important:false});
        this.props.addNewTask(new Task(this.props.id,d,this.state.important,this.state.privateTask,moment(dl),p,false));
    }
    render(){
        
                return(
                    <div>
                    <Modal show={this.state.show} onHide={this.props.handleCloseForm}>
                <Modal.Header>
                <Modal.Title>Add Task</Modal.Title>
                </Modal.Header>
                <Modal.Body>
                <Form>
                    <Form.Group controlId="taskDescription">
                        <Form.Label>Description</Form.Label>
                        <Form.Control required ref={this.description} type="text" placeholder="Insert Description"/>
                    </Form.Group>
                    <Form.Group controlId="taskProject">
                        <Form.Label>Project</Form.Label>
                        <Form.Control required ref={this.project} type="text" placeholder="Insert Project"/>
                    </Form.Group>
                    <Form.Group controlId="taskPrivate">
                        <Form.Check   type="checkbox" label="Private" onClick={this.handlePrivateCheckbox}/>
                    </Form.Group>
                    <Form.Group controlId="taskImportant">
                        <Form.Check  type="checkbox" label="Important" onClick={this.handleImportantCheckbox}/>
                    </Form.Group>
                    <Form.Group controlId="taskDeadline">
                        <Form.Label>Deadline</Form.Label>
                        <Form.Control required ref={this.deadline} type="text" placeholder="YYYY-MM-DDTHH:MM:SS"/>
                    </Form.Group>
                </Form>    
                </Modal.Body>
                <Modal.Footer>
                <Button variant="secondary" onClick={this.props.handleCloseForm}>
                    Close
                </Button>
                <Button variant="primary" onClick={()=>this.createNewTask()}>
                    Save Changes
                </Button>
                </Modal.Footer>
            </Modal>
            </div>
                );
        
    }
    handlePrivateCheckbox(){
        this.setState({privateTask:!this.state.privateTask});
    }
    handleImportantCheckbox(){
        this.setState({important:!this.state.important});
    }
}

export default TodoForm;

