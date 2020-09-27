import Task from './app.js';

async function getAllTasks(){
    //call REST API : GET /tasks
    const response=await fetch('/tasks');
    const tasks_json=await response.json();
    if(response.ok){
        console.log(tasks_json);
        return tasks_json.map((tsk)=>Task.from(tsk));
        
    }
    else{
        throw tasks_json;
    }
}

async function getTask(taskId){
    const response=await fetch(`/tasks/${taskId}`);
    const task_json=await response.json();
    if(response.ok){
        return task_json.map((tsk)=>Task.from(tsk));
    }
    else{
        throw tasks_json;
    }
}

async function getImportantTasks(){
    const response=await fetch('/tasks/filter/important');
    const task_json=await response.json();
    if(response.ok){
        return task_json.map((tsk)=>Task.from(tsk));
    }
    else{
        throw tasks_json;
    }
}

async function getPrivateTasks(){
    const response=await fetch('/tasks/filter/private/1');
    const task_json=await response.json();
    if(response.ok){
        return task_json.map((tsk)=>Task.from(tsk));
    }
    else{
        throw tasks_json;
    }
}

async function getSharedTasks(){
    const response=await fetch('/tasks/filter/private/0');
    const task_json=await response.json();
    if(response.ok){
        return task_json.map((tsk)=>Task.from(tsk));
    }
    else{
        throw tasks_json;
    }
}

async function getTodayTasks(){
   
    const response=await fetch('/tasks/filter/today');
    const task_json=await response.json();
    if(response.ok){
        return task_json.map((tsk)=>Task.from(tsk));
    }
    else{
        throw tasks_json;
    }
    
}
async function getThisWeekTasks(){
   
    const response=await fetch('/tasks/filter/week');
    const task_json=await response.json();
    if(response.ok){
        return task_json.map((tsk)=>Task.from(tsk));
    }
    else{
        throw tasks_json;
    }
    
}

async function getProjectTasks(project){
   
    const response=await fetch(`/tasks/filter/project/${project}`);
    const task_json=await response.json();
    if(response.ok){
        return task_json.map((tsk)=>Task.from(tsk));
    }
    else{
        throw tasks_json;
    }
    
}

async function insertNewTask(task){
    console.log(JSON.stringify(task));

    return new Promise((resolve,reject)=>{
        fetch('/tasks/insert',{
            method:'POST',
            headers:{
                'Content-Type':'application/json'
            }, body: JSON.stringify(task),
        }).then((response)=>{
            if(response.ok){
                resolve(null);
            }
            else{
                response.json().then((obj)=>{reject(obj);})
                .catch((err)=>{reject({errors:[{param:"Application", msg:"Cannot parse server response"}]})})
            }
        }).catch((err)=>{reject({errors:[{param:"Server",msg:"Cannot communicate"}]})});
    });
}

async function updateTask(task){
    return new Promise((resolve,reject)=>{
        fetch(`/tasks/update/${Task.getId(task)}`,{
            method:'PUT',
            headers:{
                'Content-Type':'application/json'
            }, body:JSON.stringify(task),
        }).then((response)=>{
            if(response.ok){
                resolve(null);
            }
            else{
                response.json().then((obj)=>{reject(obj);})
                .catch((err)=>{reject({errors:[{param:"Application", msg:"Cannot parse server response"}]})})
            }
        }).catch((err)=>{reject({errors:[{param:"Server",msg:"Cannot communicate"}]})});
    });
}

async function deleteTask(taskId){
    return new Promise((resolve,reject)=>{
        fetch(`/tasks/${taskId}`,{
            method:'DELETE',
        }).then((response)=>{
            if(response.ok){
                resolve(null);
            }
            else{
                response.json().then((obj)=>{reject(obj);})
                .catch((err)=>{reject({errors:[{param:"Application", msg:"Cannot parse server response"}]})})
            }
        }).catch((err)=>{reject({errors:[{param:"Server",msg:"Cannot communicate"}]})});
    });
}

async function completeTask(taskId){
    return new Promise((resolve,reject)=>{
        fetch(`/tasks/complete/${taskId}`,{
            method:'PATCH'
        }).then((response)=>{
            if(response.ok){
                resolve(null);
            }
            else{
                response.json().then((obj)=>{reject(obj);})
                .catch((err)=>{reject({errors:[{param:"Application", msg:"Cannot parse server response"}]})})
            }
        }).catch((err)=>{reject({errors:[{param:"Server",msg:"Cannot communicate"}]})});
    });
}

export{getAllTasks,getTask,getImportantTasks,getPrivateTasks, getSharedTasks,getTodayTasks,getThisWeekTasks,getProjectTasks,insertNewTask,updateTask,deleteTask,completeTask };