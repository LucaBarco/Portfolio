"use strict";
import * as Api from './api.js';

class Task{
    /*constructor(pars,id){
        this.project=pars[0];
        this.description=pars[1];
        this.urgent=pars[2]||0;
        this.shared=pars[3]||0;
        this.deadline=pars[4];
        this.id=id;
        console.log(this); //per stampare nella finestra il task appena creato
    }*/
    constructor (id,description,important,prvt,project,deadline,completed){
        if(id&&deadline){
        this.id=id;
        this.description=description;
        this.important=important||0;
        this.private=prvt||10;
        this.project=project;
        this.deadline=new moment(deadline,"YYYY-MM-DD HH:mm");
        console.log(typeof(this.deadline));
        this.completed=completed||0;
        console.log(this);
        }
    }
   
    static from=function(json){
        console.log(json);
        const res= Object.assign(new Task(),json);
        console.log(typeof(res));
        console.log(typeof(res.deadline));
     
        return res;
    }
    static getId= function(task){
        return task.id;
    }
}
export default Task;

class App{
    
    constructor(){
        this.tasklist= Array.of();
        this.projectlist= Array.of();
        this.i=0;
        this.pj_id=0;
    }
    addTask= function(pars){
        
        this.i=this.i+1;
        const tsk=new Task(this.i,pars[1],pars[2],pars[3],pars[0],pars[4],pars[5]);
        this.tasklist.push(tsk);
        addTasktoServer(tsk);
    }
    

    createNewTask=function(task){
        
        let node=document.createElement('LI');
        node.classList.add('list-group-item');
        node.id="task"+task.id;
        let box=document.createElement('div');
        box.classList.add('d-flex','w-100','justify-content-between');
        let ctrl=document.createElement('div');
        ctrl.classList.add("custom-control", "custom-control", "custom-checkbox");
        let checkbox=document.createElement("INPUT");
        checkbox.setAttribute('type','checkbox');
        checkbox.classList.add('custom-control-input');
        checkbox.id=`check-t${task.id}`;
        if(task.important==1){
            checkbox.classList.add('important');
        }
        let label=document.createElement('label');
        label.classList.add('custom-control-label');
        let desc=document.createTextNode(task.description);
        label.setAttribute('for','check-t'+task.id);
        label.appendChild(desc);
        let span=document.createElement('span');
        span.classList.add('badge','badge-primary', 'ml-4');
        let proj=document.createTextNode(task.project);

        span.appendChild(proj);
        ctrl.append(checkbox)
        ctrl.append(label)
        ctrl.append(span);
        box.append(ctrl);
        
        if(task.private==0){
            box.insertAdjacentHTML('beforeend',`<svg class="bi bi-person-square" width="1.2em" height="1.2em" viewBox="0 0 16 16" fill="currentColor" xmlns="http://www.w3.org/2000/svg">
            <path fill-rule="evenodd" d="M14 1H2a1 1 0 00-1 1v12a1 1 0 001 1h12a1 1 0 001-1V2a1 1 0 00-1-1zM2 0a2 2 0 00-2 2v12a2 2 0 002 2h12a2 2 0 002-2V2a2 2 0 00-2-2H2z" clip-rule="evenodd"/>
            <path fill-rule="evenodd" d="M2 15v-1c0-1 1-4 6-4s6 3 6 4v1H2zm6-6a3 3 0 100-6 3 3 0 000 6z" clip-rule="evenodd"/>
        </svg>`)
        }
        let deadline=new moment(task.deadline,'MMMM Do YYYY, h:mm:ss a');

        let d=document.createTextNode(deadline.format('MMMM Do YYYY, h:mm:ss a'));
        let date=document.createElement('div');
        date.className='date';
        date.append(d);
        if(deadline.diff(moment())<0){
            date.classList.add("expired");
        }
    /* else{
            setTimeout(
                (date)=>{
                    console.log("EXPIRED");
                    date.classList.add("expired");                
                },task.deadline.getTime()-(new Date()).getTime(),date
            );
        }*/
        box.append(date)
        node.append(box);
        node.classList.add("task");
        if(task.private==0){
        node.classList.add("shared");
        }
        if(task.important==1){
            node.classList.add("urgent");
        }
    //check if there are a new project
        let projs=document.getElementsByClassName("list-group-flush")[1];
            if((application.projectlist.some(x=>{
                    if(x.localeCompare(task.project)==0){
                        return true;
                    }
                        return false;
            }))==false){
                application.projectlist.push(task.project);
                let a=document.createElement('a');
                        a.classList.add("list-group-item","list-group-item-action");
                        a.setAttribute('href','#');
                        application.pj_id=application.pj_id+1;
                        a.id='project-'+application.pj_id;
                        node.classList.add('project-'+application.pj_id);
                        let t=document.createTextNode(task.project);
                        a.append(t);
                        projs.append(a);
                        a.addEventListener('click',event=>{
                            let tasks=document.getElementsByClassName("task");

                            for(let task of tasks){
                                if(task.classList.contains(a.id)){
                                    task.style.visibility="visible";
                                    task.style.display="block";
                                }
                                else{
                                    task.style.visibility="hidden";
                                    task.style.display="none";
                                }
                            }

                        });
            }
            else{
                node.classList.add('project-'+(application.projectlist.findIndex(x=>{return x==task.project})+1));
            }


        return node;
    }
    
    appendNewTask=function(task){
        let deadline=new moment(task.deadline,'MMMM Do YYYY, h:mm:ss a');
        let list=document.getElementById('taskList');
        const newElement = this.createNewTask(task);
        list.append(newElement);
        if(!Number.isNaN(deadline.valueOf())){
            const now=new Date();
            console.log("I will set a time out for task"+task.id+" value: "+deadline.diff(moment()));
            setTimeout(function() {
                    const li = document.getElementById("task" + task.id);
                    const date = li.getElementsByClassName("date")[0];
                    date.classList.add('expired');
                }, deadline.diff(moment()), task);
            }
            
           
            /* application.tasklist.forEach(element => {
                if(document.getElementById('project-'+element.project)==null){
                    let a=document.createElement('a');
                    a.classList.add("list-group-item","list-group-item-action");
                    a.setAttribute('href','#');
                    pj_id=pj_id+1;
                    a.id='project-'+pj_id;
                    let t=document.createTextNode(element.project);
                    a.append(t);
                    projs.append(a);
                    a.addEventListener('click',event => {
                        let tasks=document.getElementsByClassName("task");
                        tasks.forEach(x => {
                            if(x.classList.contains(element.project)){
                                task.style.visibility="visible";
                                task.style.display="block";
                            }
                            else{
                                task.style.visibility="hidden";
                                task.style.display="none";
                            }
                        })
                    })
                }
            });*/
    }

    createAllTasks=function(){
        for(const task of this.tasklist){
            if(task.id && task.deadline){
           this.appendNewTask(task);
            }
        }
        
    }
}
const filters=new Filter();

const application= new App();

document.getElementById('new-task').addEventListener('submit',event=>{   
                                                                    event.preventDefault();
                                                                    console.log('submit');
                                                                    let d=document.getElementById('task-description').value;
                                                                    let p=document.getElementById('task-project').value;
                                                                    let sh=1;
                                                                    let ur=0;
                                                                    if(document.querySelector('#task-private:checked')!=null){
                                                                         sh=0;
                                                                    }
                                                                   
                                                                    if(document.querySelector('#task-urgent:checked')!=null){
                                                                         ur=1;
                                                                    }
                                                                    
                                                                    let dd=moment(document.getElementById('task-deadline').value,"YYYY-MM-DD HH:mm");
                                                                    if(d!=undefined && p != undefined && dd!=undefined){
                                                                        application.addTask(new Array(p,d,ur,sh,dd,0));
                                                                        application.appendNewTask(application.tasklist[application.tasklist.length-1]);
                                                                    }
                                                                    $('#newTaskModal').modal('toggle');
                                                                    });

/*application.addTask(new Array('Web Application 1','Complete LAB2',1,1,moment("2020-04-17 19:00","YYYY-MM-DD HH:mm")));
application.addTask(new Array('Personal','Buy Easter Eggs',0,0,new moment("2020-04-23 16:18","YYYY-MM-DD HH:mm")));
application.addTask(new Array('SDP','Complete Schemes',1,1,new moment("2020-04-24 16:00","YYYY-MM-DD HH:mm")));
application.addTask(new Array('Personal','Buy Airpods',0,0,new moment("2020-04-17 17:00","YYYY-MM-DD HH:mm")));
application.addTask(new Array('Web Application 1','Complete Lessons',1,0,new moment("2020-04-03 10:00","YYYY-MM-DD HH:mm")));
application.addTask(new Array('Personal','Go to shopping',0,0,new moment("2020-04-07 19:00","YYYY-MM-DD HH:mm")));
application.addTask(new Array('Personal','Buy a new PC',1,0,new moment("2020-04-17 13:22","YYYY-MM-DD HH:mm")));*/
async function addTasktoServer(task){
    await Api.insertNewTask(task);
}
async function populateTask(){
    const tasks = await Api.getAllTasks();
    tasks.forEach(element => {
        if(element.id && element.deadline){
        application.i=application.i+1;
        application.appendNewTask(element);
        }
    });
}

populateTask();
filters.activateFilters();



function autocomplete(inp, arr) {
    /*the autocomplete function takes two arguments,
    the text field element and an array of possible autocompleted values:*/
    var currentFocus;
    /*execute a function when someone writes in the text field:*/
    inp.addEventListener("input", function(e) {
        var a, b, i, val = this.value;
        /*close any already open lists of autocompleted values*/
        closeAllLists();
        if (!val) { return false;}
        currentFocus = -1;
        /*create a DIV element that will contain the items (values):*/
        a = document.createElement("DIV");
        a.setAttribute("id", this.id + "autocomplete-list");
        a.setAttribute("class", "autocomplete-items");
        /*append the DIV element as a child of the autocomplete container:*/
        this.parentNode.appendChild(a);
        /*for each item in the array...*/
        for (i = 0; i < arr.length; i++) {
          /*check if the item starts with the same letters as the text field value:*/
          if (arr[i].substr(0, val.length).toUpperCase() == val.toUpperCase()) {
            /*create a DIV element for each matching element:*/
            b = document.createElement("DIV");
            /*make the matching letters bold:*/
            b.innerHTML = "<strong>" + arr[i].substr(0, val.length) + "</strong>";
            b.innerHTML += arr[i].substr(val.length);
            /*insert a input field that will hold the current array item's value:*/
            b.innerHTML += "<input type='hidden' value='" + arr[i] + "'>";
            /*execute a function when someone clicks on the item value (DIV element):*/
                b.addEventListener("click", function(e) {
                /*insert the value for the autocomplete text field:*/
                inp.value = this.getElementsByTagName("input")[0].value;
                /*close the list of autocompleted values,
                (or any other open lists of autocompleted values:*/
                closeAllLists();
            });
            a.appendChild(b);
          }
        }
    });
    /*execute a function presses a key on the keyboard:*/
    inp.addEventListener("keydown", function(e) {
        var x = document.getElementById(this.id + "autocomplete-list");
        if (x) x = x.getElementsByTagName("div");
        if (e.keyCode == 40) {
          /*If the arrow DOWN key is pressed,
          increase the currentFocus variable:*/
          currentFocus++;
          /*and and make the current item more visible:*/
          addActive(x);
        } else if (e.keyCode == 38) { //up
          /*If the arrow UP key is pressed,
          decrease the currentFocus variable:*/
          currentFocus--;
          /*and and make the current item more visible:*/
          addActive(x);
        } else if (e.keyCode == 13) {
          /*If the ENTER key is pressed, prevent the form from being submitted,*/
          e.preventDefault();
          if (currentFocus > -1) {
            /*and simulate a click on the "active" item:*/
            if (x) x[currentFocus].click();
          }
        }
    });
    function addActive(x) {
      /*a function to classify an item as "active":*/
      if (!x) return false;
      /*start by removing the "active" class on all items:*/
      removeActive(x);
      if (currentFocus >= x.length) currentFocus = 0;
      if (currentFocus < 0) currentFocus = (x.length - 1);
      /*add class "autocomplete-active":*/
      x[currentFocus].classList.add("autocomplete-active");
    }
    function removeActive(x) {
      /*a function to remove the "active" class from all autocomplete items:*/
      for (var i = 0; i < x.length; i++) {
        x[i].classList.remove("autocomplete-active");
      }
    }
    function closeAllLists(elmnt) {
      /*close all autocomplete lists in the document,
      except the one passed as an argument:*/
      var x = document.getElementsByClassName("autocomplete-items");
      for (var i = 0; i < x.length; i++) {
        if (elmnt != x[i] && elmnt != inp) {
        x[i].parentNode.removeChild(x[i]);
      }
    }
  }
  /*execute a function when someone clicks in the document:*/
  document.addEventListener("click", function (e) {
      closeAllLists(e.target);
  });
  } 

  autocomplete(document.getElementById("task-project"), application.projectlist);

 