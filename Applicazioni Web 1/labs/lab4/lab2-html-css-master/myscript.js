"use strict";




let tasks=Array.of();

const printTask=function(task){
    //stampa il task appena creato
    let list=document.getElementById('taskList');
    let i=0;
    
    //DYNAMIC -> creazione della riga in base ai parametri
    i=i+1;
    let node=document.createElement('LI');
    node.classList.add('list-group-item');
    let box=document.createElement('div');
    box.classList.add('d-flex','w-100','justify-content-between');
    let ctrl=document.createElement('div');
    ctrl.classList.add("custom-control", "custom-control", "custom-checkbox");
    let checkbox=document.createElement("INPUT");
    checkbox.setAttribute('type','checkbox');
    checkbox.classList.add('custom-control-input');
    checkbox.id=`check-t${i}`;
    if(task.urgent=='Y'){
        checkbox.classList.add('important');
    }
    let label=document.createElement('label');
    label.classList.add('custom-control-label');
    let desc=document.createTextNode(task.description);
    label.setAttribute('for','check-t'+i);
    label.appendChild(desc);
    let span=document.createElement('span');
    span.classList.add('badge','badge-primary', 'ml-4');
    let proj=document.createTextNode(task.project);

    span.appendChild(proj);
    ctrl.append(checkbox)
    ctrl.append(label)
    ctrl.append(span);
    box.append(ctrl);
    
    if(task.private=="N"){
        box.insertAdjacentHTML('beforeend',`<svg class="bi bi-person-square" width="1.2em" height="1.2em" viewBox="0 0 16 16" fill="currentColor" xmlns="http://www.w3.org/2000/svg">
        <path fill-rule="evenodd" d="M14 1H2a1 1 0 00-1 1v12a1 1 0 001 1h12a1 1 0 001-1V2a1 1 0 00-1-1zM2 0a2 2 0 00-2 2v12a2 2 0 002 2h12a2 2 0 002-2V2a2 2 0 00-2-2H2z" clip-rule="evenodd"/>
        <path fill-rule="evenodd" d="M2 15v-1c0-1 1-4 6-4s6 3 6 4v1H2zm6-6a3 3 0 100-6 3 3 0 000 6z" clip-rule="evenodd"/>
      </svg>`)
    }
    let d=document.createTextNode(task.deadline.toUTCString());
    let date=document.createElement('div');
    date.append(d);
    if(task.deadline.getTime()<(new Date()).getTime()){
        date.classList.add("expired");
    }
    else{
        setTimeout(
            (date)=>{
                console.log("EXPIRED");
                date.classList.add("expired");                
            },task.deadline.getTime()-(new Date()).getTime(),date
        );
    }
    box.append(date)
    node.append(box);
    node.classList.add("task");
    if(task.private=="N"){
    node.classList.add("shared");
    }
    if(task.urgent=="Y"){
        node.classList.add("urgent");
    }
    list.append(node);
}

function Task(pars){
    this.project=pars[0];
    this.description=pars[1];
    this.urgent=pars[2]||'N';
    this.private=pars[3]||'Y';
    this.deadline=pars[4];
    printTask(this); //per stampare nella finestra il task appena creato
}


console.log('HEY!');
tasks.push(new Task(new Array('Web Application 1','Complete LAB2','Y','N',new Date("2020-04-05 19:00"))));
tasks.push(new Task(new Array('Personal','Buy Easter Eggs','N','Y',new Date("2020-04-03 16:18"))));
tasks.push(new Task(new Array('SDP','Complete Schemes','Y','N',new Date("2020-04-04 16:00"))));
tasks.push(new Task(new Array('Personal','Buy Airpods','N','Y',new Date("2020-04-01 17:00"))));
tasks.push(new Task(new Array('Web Application 1','Complete Lessons','Y','Y',new Date("2020-04-03 10:00"))));
tasks.push(new Task(new Array('Personal','Go to shopping','N','N',new Date("2020-04-07 19:00"))));
tasks.push(new Task(new Array('Personal','Buy a new PC','Y','Y',new Date("2020-04-10 12:00"))));

console.log(tasks);

let filters=document.getElementsByClassName("list-group-item-action");
/*
0->all
1->important
2->today
3-> next 7 days
4-> private
5->shared with
6... ->projects
 */
filters[0].addEventListener('click',event=>{
    //show all events
    let tasks=document.getElementsByClassName("task");
    for(let task of tasks){
        task.style.visibility="visible";
    }
});
filters[1].addEventListener('click',event=>{
    //show all important events
    let tasks=document.getElementsByClassName("task");
    for(let task of tasks){
        if(!(task.classList.contains("urgent"))){    
        task.style.visibility="hidden";
        }
        else{
            task.style.visibility="visible";
        }
    }
});

filters[2].addEventListener('click',event=>{
    //show all important events
    let tasks=document.getElementsByClassName("task");
    let td=new Date()
    let day=td.getDate();
    let month=td.getMonth();
    let year=td.getFullYear();
    td=new Date(`${year}-${month+1}-${day}`);

    let today=td.getTime();
    for(let task of tasks){
        let dd=new Date(Date.parse(task.children[0].lastChild.textContent));
        let dead_day=dd.getTime();
         if((dead_day-today)<86400000){
            task.style.visibility="visible";
        }
        else{
            task.style.visibility="hidden";
        }

    }
});

filters[3].addEventListener('click',event=>{
    let tasks=document.getElementsByClassName("task");
    //show all important events
    let td=new Date()
    let day=td.getDate();
    let month=td.getMonth();
    let year=td.getFullYear();
    td=new Date(`${year}-${month+1}-${day}`);
    let today=td.getTime()+86400000;
    for(let task of tasks){
        let dd=new Date(Date.parse(task.children[0].lastChild.textContent));
        let dead_day=dd.getTime();
        if((dead_day-today)<(7*86400000)){
            task.style.visibility="visible";
        }
        else{
            task.style.visibility="hidden";
        }

    }
});

filters[4].addEventListener('click',event=>{
    //show all important events
    let tasks=document.getElementsByClassName("task");
    for(let task of tasks){
        if((task.classList.contains("shared"))){    
        task.style.visibility="hidden";
        }
        else{
            task.style.visibility="visible";
        }
    }
});
filters[5].addEventListener('click',event=>{
    //show all important events
    let tasks=document.getElementsByClassName("task");
    for(let task of tasks){
        if(!(task.classList.contains("shared"))){    
        task.style.visibility="hidden";
        }
        else{
            task.style.visibility="visible";
        }
    }
});

/*
let list=document.getElementById('taskList');
let i=0;
for(let task of tasks){
    //DYNAMIC -> creazione della riga in base ai parametri
    i=i+1;
    let node=document.createElement('LI');
    node.classList.add('list-group-item');
    let box=document.createElement('div');
    box.classList.add('d-flex','w-100','justify-content-between');
    let ctrl=document.createElement('div');
    ctrl.classList.add("custom-control", "custom-control", "custom-checkbox");
    let checkbox=document.createElement("INPUT");
    checkbox.setAttribute('type','checkbox');
    checkbox.classList.add('custom-control-input');
    checkbox.id=`check-t${i}`;
    if(task.urgent=='Y'){
        checkbox.classList.add('important');
    }
    let label=document.createElement('label');
    label.classList.add('custom-control-label');
    let desc=document.createTextNode(task.description);
    label.setAttribute('for','check-t'+i);
    label.appendChild(desc);
    let span=document.createElement('span');
    span.classList.add('badge','badge-primary', 'ml-4');
    let proj=document.createTextNode(task.project);

    span.appendChild(proj);
    ctrl.append(checkbox)
    ctrl.append(label)
    ctrl.append(span);
    box.append(ctrl);
    
    if(task.private=="N"){
        box.insertAdjacentHTML('beforeend',`<svg class="bi bi-person-square" width="1.2em" height="1.2em" viewBox="0 0 16 16" fill="currentColor" xmlns="http://www.w3.org/2000/svg">
        <path fill-rule="evenodd" d="M14 1H2a1 1 0 00-1 1v12a1 1 0 001 1h12a1 1 0 001-1V2a1 1 0 00-1-1zM2 0a2 2 0 00-2 2v12a2 2 0 002 2h12a2 2 0 002-2V2a2 2 0 00-2-2H2z" clip-rule="evenodd"/>
        <path fill-rule="evenodd" d="M2 15v-1c0-1 1-4 6-4s6 3 6 4v1H2zm6-6a3 3 0 100-6 3 3 0 000 6z" clip-rule="evenodd"/>
      </svg>`)
    }
    let date=document.createTextNode(task.deadline);
    box.append(date)
    node.append(box);
    list.append(node);

    /* STATIC -> check caso per caso
if(task.private=="Y" && task.urgent=="N"){
list.insertAdjacentHTML('beforeend',`
<li class="list-group-item">
              <div class="d-flex w-100 justify-content-between">
                <div class="custom-control custom-checkbox">
                  <input type="checkbox" class="custom-control-input" id="check-t${i}">
                  <label class="custom-control-label" for="check-t${i}">${task.description}</label>
                  <span class="badge badge-primary ml-4">${task.project}</span>
                </div>
                <small>${task.deadline}</small>
              </div>
            </li>`);
}
if(task.private=="Y" && task.urgent=="Y"){
    list.insertAdjacentHTML('beforeend',`
    <li class="list-group-item">
                  <div class="d-flex w-100 justify-content-between">
                    <div class="custom-control custom-checkbox">
                      <input type="checkbox" class="custom-control-input important" id="check-t${i}">
                      <label class="custom-control-label" for="check-t${i}">${task.description}</label>
                      <span class="badge badge-primary ml-4">${task.project}</span>
                    </div>
                    <small>${task.deadline}</small>
                  </div>
                </li>`);
    }
if(task.private=="N" && task.urgent=="N"){
    list.insertAdjacentHTML('beforeend',`
    <li class="list-group-item">
                  <div class="d-flex w-100 justify-content-between">
                    <div class="custom-control custom-checkbox">
                      <input type="checkbox" class="custom-control-input" id="check-t${i}">
                      <label class="custom-control-label" for="check-t${i}">${task.description}</label>
                      <span class="badge badge-primary ml-4">${task.project}</span>
                    </div>
                    <svg class="bi bi-person-square" width="1.2em" height="1.2em" viewBox="0 0 16 16" fill="currentColor" xmlns="http://www.w3.org/2000/svg">
                  <path fill-rule="evenodd" d="M14 1H2a1 1 0 00-1 1v12a1 1 0 001 1h12a1 1 0 001-1V2a1 1 0 00-1-1zM2 0a2 2 0 00-2 2v12a2 2 0 002 2h12a2 2 0 002-2V2a2 2 0 00-2-2H2z" clip-rule="evenodd"/>
                  <path fill-rule="evenodd" d="M2 15v-1c0-1 1-4 6-4s6 3 6 4v1H2zm6-6a3 3 0 100-6 3 3 0 000 6z" clip-rule="evenodd"/>
                </svg>
                    <small>${task.deadline}</small>
                  </div>
                </li>`);
    }
    if(task.private=="N" && task.urgent=="Y"){
        list.insertAdjacentHTML('beforeend',`
        <li class="list-group-item">
                      <div class="d-flex w-100 justify-content-between">
                        <div class="custom-control custom-checkbox">
                          <input type="checkbox" class="custom-control-input  important" id="check-t${i}">
                          <label class="custom-control-label" for="check-t${i}">${task.description}</label>
                          <span class="badge badge-primary ml-4">${task.project}</span>
                        </div>
                        <svg class="bi bi-person-square" width="1.2em" height="1.2em" viewBox="0 0 16 16" fill="currentColor" xmlns="http://www.w3.org/2000/svg">
                  <path fill-rule="evenodd" d="M14 1H2a1 1 0 00-1 1v12a1 1 0 001 1h12a1 1 0 001-1V2a1 1 0 00-1-1zM2 0a2 2 0 00-2 2v12a2 2 0 002 2h12a2 2 0 002-2V2a2 2 0 00-2-2H2z" clip-rule="evenodd"/>
                  <path fill-rule="evenodd" d="M2 15v-1c0-1 1-4 6-4s6 3 6 4v1H2zm6-6a3 3 0 100-6 3 3 0 000 6z" clip-rule="evenodd"/>
                </svg>
                        <small>${task.deadline}</small>
                      </div>
                    </li>`);
        }*//*
}
*/
