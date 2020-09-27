import React from 'react';
import TodoItem from './TodoItem';
import ListGroup from 'react-bootstrap/ListGroup';


class TodoList extends React.Component {

  constructor(props)  {
    super(props);
    this.state={location:''};
  } 
  componentDidMount(){

    console.log(this.props.filter);
    if(this.state.location!==window.location.pathname){
      this.setState({location:window.location.pathname});
      console.log('Mount: '+this.props.tasks);
      if(this.props.project){
        this.props.filterTasks(this.props.filter,this.props.project);
      }
      else{
      this.props.filterTasks(this.props.filter);
      }
    }
    
  }
  componentDidUpdate(){
    if(this.state.location!==window.location.pathname){
      this.setState({location:window.location.pathname});
      console.log('UPDATE: '+this.props.tasks);
      if(this.props.project){
        this.props.filterTasks(this.props.filter,this.props.project);
      }
      else{
      this.props.filterTasks(this.props.filter);
      }
    }
  }
  render(){
    return (
      <React.Fragment>
        {this.props.tasks && 
        <ListGroup as="ul" variant="flush">
          {this.props.tasks.map((task) => <TodoItem key={task.id} task={task} editTask={this.props.editTask} deleteTask={this.props.deleteTask} />) }
        </ListGroup>}
      </React.Fragment>
    );
  }
}



export default TodoList;
