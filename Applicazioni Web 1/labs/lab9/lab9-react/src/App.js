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

class App extends React.Component {

  constructor(props)  {
    super(props);
    this.state = {tasks: [], projects: [], filter: 'All', openMobileMenu: false, modalOpen: false, editedTask: null};
  }

  getProjects(tasks) {
    return [...new Set(tasks.map(task => task.project))];
  }

  componentDidMount() {
    // fake loading the tasks from the API server, and create the projects list
    API.getTasks().then((tasks) => this.setState({tasks: tasks, projects: this.getProjects(tasks)}));
  }
  
  toggleModal = () => {
    this.setState((state) => ({modalOpen: !state.modalOpen, editedTask: null}));
  }

  showSidebar = () => {
    this.setState((state) => ({openMobileMenu: !state.openMobileMenu}));
  }

  filterTasks = (filter, project) => {
    switch(filter){
      case 'filter-important':
        API.getImportantTasks().then((tasks) => this.setState({tasks: tasks, filter: 'Important'}));
        break;
      case 'filter-today':
        API.getTodayTasks().then((tasks) => this.setState({tasks: tasks, filter: 'Today'}));
        break;
      case 'filter-week':
        API.getWeeklyTasks().then((tasks) => this.setState({tasks: tasks, filter: 'Next Week'}));
        break;
      case 'filter-private':
        API.getPrivateTasks().then((tasks) => this.setState({tasks: tasks, filter: 'Private'}));
        break;
      case 'filter-shared':
        API.getSharedTasks().then((tasks) => this.setState({tasks: tasks, filter: 'Shared'}));
        break;
      case 'filter-project':
        API.getByProject(project).then((tasks) => this.setState({tasks: tasks, filter: project}));
        break;
      default:
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
      <React.Fragment>
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
            <TodoList tasks = {this.state.tasks} editTask = {this.editTask} deleteTask = {this.deleteTask} />
            <Button variant="success" size="lg" className="fixed-right-bottom" onClick={this.toggleModal}>&#43;</Button>
            </Col>

            {this.state.modalOpen && <TodoForm modalOpen={this.state.modalOpen} toggleModal={this.toggleModal} addOrEditTask={this.addOrEditTask} task={this.state.editedTask}/>}
          </Row>
        </Container>
      </React.Fragment>
    );
  }
}

export default App;
