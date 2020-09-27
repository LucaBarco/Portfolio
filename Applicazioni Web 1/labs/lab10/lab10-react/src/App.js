import React from 'react';
import './App.css';
import Header from './components/Header';
import Container from 'react-bootstrap/Container';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';
import Button from 'react-bootstrap/Button';
import Collapse from 'react-bootstrap/Collapse';
import Filters from './components/Filters';
import TodoList from './components/TodoList';
import TodoForm from './components/TodoForm';
import API from './api/API';
import moment from 'moment';
 
import {BrowserRouter as Router,Route,Link, Switch,useHistory} from 'react-router-dom'

class App extends React.Component {

  constructor(props)  {
    super(props);
    this.state = {tasks: [], projects: [], filter: 'All', openMobileMenu: false, modalOpen: false, editedTask: null,loading:true,location:''};
  }

  getProjects(tasks) {
    return [...new Set(tasks.map(task => task.project))];
  }

  componentDidMount() {
    // loading the tasks from the API server, and create the projects list
    //questo perchè andrebbe modificata la API -> prima va fatta la chiamata a getAll per av
    API.getTasks().then((tasks) => {console.log(tasks);this.setState({projects: this.getProjects(tasks),loading:false,location:window.location.pathname});});
    
  }

   componentDidUpdate(){
     console.log(this.state.location);
    if(window.location.pathname!== this.state.location){
      this.setState({location:window.location.pathname});
    }
  }
  
  toggleModal = () => {
    this.setState((state) => ({modalOpen: !state.modalOpen, editedTask: null}));
  }

  showSidebar = () => {
    this.setState((state) => ({openMobileMenu: !state.openMobileMenu}));
  }
 
  filterTasks = (filter, project) => {
    switch(filter){
      case '/important':
        API.getImportantTasks().then((tasks) => this.setState({tasks: tasks, filter: 'Important'}));
        break;
      case '/today':
        API.getTodayTasks().then((tasks) => this.setState({tasks: tasks, filter: 'Today'}));
        break;
      case '/week':
        API.getWeeklyTasks().then((tasks) => this.setState({tasks: tasks, filter: 'Next Week'}));
        break;
      case '/private':
        API.getPrivateTasks().then((tasks) => this.setState({tasks: tasks, filter: 'Private'}));
        break;
      case '/shared':
        API.getSharedTasks().then((tasks) => this.setState({tasks: tasks, filter: 'Shared'}));
        break;
      case `/${project}`:
        API.getByProject(project).then((tasks) => this.setState({tasks: tasks, filter: project}));
        break;
      case '/':
        API.getTasks().then((tasks) => this.setState({tasks: tasks, filter: 'All'}));
        break;
    }
  }

  addOrEditTask = (task) => {
    this.setState((state) => {
      // add a fake id for properly rendering the list
      if(!task.id)
        task.id = state.tasks.slice(-1)[0].id + 1;
      // remove possible duplicates 
      let buildState = state.tasks.filter((t) => t.id !== task.id);
      // add new task
      buildState.push(task);
      //sort tasks by id
      buildState = buildState.sort((a, b) => a.id - b.id);
      return {tasks: buildState};
    });
    if(this.state.editedTask!==null){
      API.updateTask(task);
    }
    else{
      API.addTask(task);
    }
    API.getTasks().then((tasks) => this.setState({tasks: tasks, projects: this.getProjects(tasks)}));
  }

  editTask = (task) => {
    this.toggleModal();
    this.setState({editedTask: task});
  }

  deleteTask = (task) => {
    this.setState((state) => ({tasks: state.tasks.filter((t) => t.id !== task.id)}));
    API.deleteTask(task);
    API.getTasks().then((tasks) => this.setState({tasks: tasks, projects: this.getProjects(tasks)}));
  }
  
  render() {
    return(
      <Router>
      
        <Header showSidebar={this.showSidebar} />
        <Container fluid>
          <Row className="vheight-100">
            <Collapse in={this.state.openMobileMenu}>
              <Col sm={4} bg="light" id="left-sidebar" className="collapse d-sm-block below-nav">
                <Filters projects = {this.state.projects} filterTasks = {this.filterTasks}/>
              </Col>
            </Collapse>
            <Col sm={8} className="below-nav">
            <h1>{this.state.filter}</h1>
            <Switch>
              
              <Route exact path='/'>
              <TodoList tasks = {this.state.tasks} editTask = {this.editTask} deleteTask = {this.deleteTask} filter='/' filterTasks={this.filterTasks}/>
              <Button variant="success" size="lg" className="fixed-right-bottom" onClick={this.toggleModal}>&#43;</Button>
              </Route>
              
              <Route  path='/important' render={ ()=>{
                //let tasks=this.state.tasks.filter((el) => el.important);
              /*console.log("i'm in the render method");
               API.getImportantTasks().then((tasks)=>{
                 console.log("I'm in then");
                 console.log(tasks);
                 this.setState(()=>{tasks:tasks});*/
               return  <TodoList tasks = {this.state.tasks} editTask = {this.editTask} deleteTask = {this.deleteTask} filter='/important' filterTasks={this.filterTasks}/>
               }}/>



              <Route  path='/today' render={()=>{
                /*let tasks=this.state.tasks.filter((el) => {
                  if(el.deadline)
                      return API.isToday(el.deadline);
                  else
                      return false;
              });*/
                return  <TodoList tasks = {this.state.tasks} editTask = {this.editTask} deleteTask = {this.deleteTask} filter='/today' filterTasks={this.filterTasks}/>}}/>

                
              <Route  path='/week' render={()=>{
                /*let tasks=this.state.tasks.filter((el) => {
                  if(el.deadline)
                      return API.isNextWeek(el.deadline);
                  else
                      return false;
              });*/
                return  <TodoList tasks = {this.state.tasks} editTask = {this.editTask} deleteTask = {this.deleteTask} filter='/week' filterTasks={this.filterTasks}/>}}/>
                
             
              <Route  path='/private' render={()=>{
                /*let tasks=this.state.tasks.filter((el) => {
                  return el.privateTask;
              });*/
           
                return  <TodoList tasks = {this.state.tasks} editTask = {this.editTask} deleteTask = {this.deleteTask} filter='/private' filterTasks={this.filterTasks}/>}}/>
             
              <Route  path='/shared' render={()=>{
                /*let tasks=this.state.tasks.filter((el) => {
                  return !el.privateTask;
              });*/
                return  <TodoList tasks = {this.state.tasks} editTask = {this.editTask} deleteTask = {this.deleteTask} filter='/shared' filterTasks={this.filterTasks}/>}}/>
             
              <Route  path='/:project' render={(props)=>{
                  /*let tasks=this.state.tasks.filter((el) => {
                    return el.project === props.match.params.project;});*/
                    return  <TodoList tasks = {this.state.tasks} editTask = {this.editTask} deleteTask = {this.deleteTask} filter={`/${props.match.params.project}`} project={props.match.params.project} filterTasks={this.filterTasks}/>}}/>
            </Switch>
            
              <Button variant="success" size="lg" className="fixed-right-bottom" onClick={this.toggleModal}>&#43;</Button>
             </Col>

            {this.state.modalOpen && <TodoForm modalOpen={this.state.modalOpen} toggleModal={this.toggleModal} addOrEditTask={this.addOrEditTask} task={this.state.editedTask}/>}
          </Row>
        </Container>
      
      </Router>
    );
  }
}

export default App;
