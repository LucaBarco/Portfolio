import React  from 'react';
import './App.css';
import TodoList from './js/TodoList';
import NavBar from './js/NavBar';
import Filters from './js/Filters';
import moment from 'moment';
import TodoForm from './js/TodoForm';
const tasks=[
  {
      "id": 1,
      "description" : "Complete Lab 3",
      "important": true,
      "privateTask": false,
      "deadline": moment("2020-04-03T11:00:00"),
      "project": "WebApp I",
      "completed": true
  },
  {
      "id": 2,
      "description" : "Watch Mr. Robot",
      "important": false,
      "privateTask": true,
      "deadline": moment("2020-05-31T18:59:00"),
      "project": "Personal",
      "completed": false
  },
  {
      "id": 3,
      "description" : "Go for a walk",
      "important": true,
      "privateTask": true,
      "deadline": moment("2020-04-18T08:00:00"),
      "project": "Personal",
      "completed": false
  }];


class App extends React.Component {

  getProjects(){
    return [...new Set(this.state.tasks.map(task => task.project))];
  }
  

  constructor(props) {
    super(props);
    this.state={tasks: tasks};
    this.state.id= tasks.length+1;
    this.handleFilterAll=this.handleFilterAll.bind(this);
    this.handleFilterImportant=this.handleFilterImportant.bind(this);
    this.handleFilterPrivate=this.handleFilterPrivate.bind(this);
    this.handleFilterShared=this.handleFilterShared.bind(this);
    this.handleFilterToday=this.handleFilterToday.bind(this);
    this.handleFilterWeek=this.handleFilterWeek.bind(this);
    this.handleForm=this.handleForm.bind(this);
    this.handleCloseForm=this.handleCloseForm.bind(this);
    this.addNewTask=this.addNewTask.bind(this);
    this.deleteTask=this.deleteTask.bind(this);
    this.getProjects=this.getProjects.bind(this);
    this.state.mode="hide";
    
  }
  render() {
    
    return (
      <div>
        <NavBar/>
        <div className="container-fluid">
          <div className="row vheight-100">
            <aside className="collapse d-sm-block col-sm-4 col-12 bg-light below-nav" id="left-sidebar">
              <Filters projects={this.getProjects()} tasks={this.state.tasks} handleFilterAll={this.handleFilterAll} handleFilterImportant={this.handleFilterImportant} handleFilterPrivate={this.handleFilterPrivate} handleFilterShared={this.handleFilterShared} handleFilterToday={this.handleFilterToday} handleFilterWeek={this.handleFilterWeek} handleFilterProject={this.handleFilterProject}/>
            </aside>
            <main className="col-sm-8 col-12 below-nav">
              <TodoList tasks={this.state.tasks} deleteTask={this.deleteTask}/>
              <button type="button" className="btn btn-lg btn-success fixed-right-bottom" onClick={this.handleForm}>&#43;</button>
              <TodoForm mode={this.state.mode} handleCloseForm={this.handleCloseForm} addNewTask={this.addNewTask} id={this.state.id}/>
            </main>
          </div>
        </div>
      </div>
    );
  }

  handleForm=()=>{
    this.setState({mode:'add'});
  }
handleCloseForm=()=>{
  this.setState({mode:'hide'});
}
addNewTask(task){
  tasks=tasks.concat(task);
  this.setState({tasks: tasks});
  this.setState({id:this.state.id+1});
  this.handleCloseForm();
}
deleteTask(id){
  tasks=tasks.filter((t)=>t.id!=id);
  this.setState({tasks:tasks});
}
handleFilterAll = ()=>{
 //let tasks=tasks;
    this.setState({tasks:tasks});
}
handleFilterImportant=()=>{
   // let tasks=tasks;
    let filteredTasks=tasks.filter((task)=>{return task.important===true});
    this.setState({tasks:filteredTasks});
}
handleFilterPrivate=()=>{
   // let tasks=tasks;
    let filteredTasks=tasks.filter((task)=>{return task.privateTask===true});
    this.setState({tasks:filteredTasks});
}
handleFilterShared=()=>{
   // let tasks=tasks;
    let filteredTasks=tasks.filter((task)=>{return task.privateTask===false});
    filteredTasks.forEach((t)=>console.log(t));
    this.setState({tasks:filteredTasks});
}
handleFilterToday=()=>{
   // let tasks=tasks;
    let filteredTasks=tasks.filter((task)=>{
        let now=moment().format("YYYY-MM-DD");
        return (task.deadline.diff(now,'days')===0);
    });
    this.setState({tasks:filteredTasks});
}
handleFilterWeek=()=>{
   // let tasks=tasks;
    let filteredTasks=tasks.filter((task)=>{
        let now=moment().format("YYYY-MM-DD");
        return (task.deadline.diff(now,'days')<=7 && !task.deadline.isBefore(moment()));
    });
    this.setState({tasks:filteredTasks});
}
handleFilterProject=(project)=>{
  //let tasks=tasks;
  let filteredTasks=tasks.filter((task)=>{return task.project.localeCompare(project)===0});
  this.setState({tasks:filteredTasks});
}
}

export default App;
