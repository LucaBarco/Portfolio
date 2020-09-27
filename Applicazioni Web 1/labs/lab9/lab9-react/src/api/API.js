import moment from 'moment';
import Task from './Task.js'
const APIURL=new URL('http://localhost:3001');

let tasks = [/*
    {
        'id': 1,
        'description' : 'Complete Lab 3',
        'important': true,
        'privateTask': false,
        'deadline': moment('2020-04-03T11:00:00'),
        'project': 'WebApp I',
        'completed': true
    },
    {
        'id': 2,
        'description' : 'Watch Mr. Robot',
        'important': false,
        'privateTask': true,
        'deadline': moment('2020-05-31T18:59:00'),
        'project': 'Personal',
        'completed': false
    },
    {
        'id': 3,
        'description' : 'Go for a walk',
        'important': true,
        'privateTask': true,
        'deadline': moment('2020-04-18T08:00:00'),
        'project': 'Personal',
        'completed': false
    }*/];


const isToday = (date) => {
    return date.isSame(moment(), 'day');
}

const isNextWeek = (date) => {
    const nextWeek = moment().add(1, 'weeks');
    const tomorrow = moment().add(1, 'days');
    return date.isAfter(tomorrow) && date.isBefore(nextWeek);
}

async function getTasks() {
    
   const resp= await fetch(new URL('/tasks',APIURL));
   tasks=await resp.json();
  
   tasks.forEach((e)=>{
       if(e.deadline){
           e.deadline=moment(e.deadline);
       }
   });
   
   return tasks;


}

async function getImportantTasks() {
    return tasks.filter((el) => {
        return el.important;
    });
}

async function getTodayTasks() {
    return tasks.filter((el) => {
        if(el.deadline)
            return isToday(el.deadline);
        else
            return false;
    });
}

async function getWeeklyTasks() {
    return tasks.filter((el) => {
        if(el.deadline)
            return isNextWeek(el.deadline);
        else
            return false;
    });
}

async function getPrivateTasks() {
    return tasks.filter((el) => {
        return el.privateTask;
    });
}

async function getSharedTasks() {
    return tasks.filter((el) => {
        return !el.privateTask;
    });
}

async function getByProject(project) {
    return tasks.filter((el) => {
        return el.project === project;
    });
}

async function updateTask(task){
    return await fetch(new URL(`/tasks/${task.id}`,APIURL),{method:'PUT',
    headers:{
        'Content-Type':'application/json'
    }, body: JSON.stringify(task),
});
}

async function addTask(task){
    return await fetch(new URL(`/tasks`,APIURL),{method:'POST',
    headers:{
        'Content-Type':'application/json'
    }, body: JSON.stringify(task),
});
}


async function deleteTask(task){
    return await fetch(new URL(`/tasks/${task.id}`,APIURL),{method:'DELETE',
    });
}

const API = { getTasks,getImportantTasks, getTodayTasks,getWeeklyTasks,getPrivateTasks,getSharedTasks, getByProject,updateTask, addTask,deleteTask} ;
export default API;
