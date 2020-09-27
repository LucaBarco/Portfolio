"use strict";
const readline=require('readline-sync');
let choice=0;
let tasks=Array.of();
const showMenu= function(){
    console.log("1. Insert a new task");
    console.log("2. Remove a task");
    console.log("3. Show all tasks");
    console.log("4. Exit");
    return ; 
}
function Task(pars){
    this.description=pars[0];
    this.urgent=pars[1]||'N';
    this.private=pars[2]||'Y';
    if(pars[3]){
    this.deadline=pars[3];
    }
    
}

const newTask=function(tasks){
    let pars=Array.of();
    pars.push(readline.question('> Insert a description: '));
    pars.push(readline.question('> Is this task urgent? [Y/N]: '));
    pars.push(readline.question('> Is this task private? [Y/N]: '));
    let dl=readline.question('> There is a deadline? [Y/N]: ');
    if (dl=='Y'){
        pars.push(new Date(readline.question('> Insert deadline [AAAA-MM-DD] :')));
        tasks.push(new Task(pars));
        let i=tasks.length-1;
        setTimeout(
            (tasks,i)=>{
                console.log("task "+tasks[i].description+" correctly deleted!")
                tasks.splice(i,1);
                
            },tasks[i].deadline.getTime()-Date.now(),tasks,i
        );
       

    }
    else{
    tasks.push(new Task(pars));
    }
    return;
}

const deleteTask=function(tasks){

    let del=readline.question('> Insert the description of the task to delete: ');
    
    tasks=tasks.filter((v)=>{return v.description!=del
        /* if(v.description==del){
            console.log(v.description+" deleted");
            return 1;
        }
        return 0; */
    }

    );
   
return tasks;
}
const deleteTaskOnDeadline=function(tasks){

    let del=new Date(readline.question('> Insert the deadline YYYY-MM-DD: '));
    
    tasks=tasks.filter((v)=>{if(v.deadline){
        return v.deadline.getDate()!=del.getDate()}else{return 1;}
      
    }

    );
  
return tasks;
}

const showTasks=function(tasks){
    tasks.sort(function(a, b) {
        var nameA = a.description.toUpperCase(); // ignora maiuscole e minuscole
        var nameB = b.description.toUpperCase(); // ignora maiuscole e minuscole
        if (nameA < nameB) {
          return -1;
        }
        if (nameA > nameB) {
          return 1;
        }
      
        // i nomi devono essere uguali
        return 0;
      });
    console.log(tasks);
}
const autoDeleteTask=function(tasks,i){
     tasks.splice(i,1);
    console.log("task deleted!");
    };



const menu=function(){

        showMenu();
        choice=parseInt(readline.question('> Take a choice [1-4]: '));
        //console.log(choice);
        switch(choice){
            case 1:
                newTask(tasks);
                
            
            break;
            case 2:
                let choice2=parseInt(readline.question('>Do you want delete a specific task or all tasks on a specified deadline? [1-2]: '));
                if(choice2==1){
                    tasks=deleteTask(tasks);
                }
                else if(choice2==2){
                    tasks=deleteTaskOnDeadline(tasks);
                }
            //console.log("> case 1");
            break;
            case 3:
            showTasks(tasks);
            //console.log("> case 1");
            break;
        }

}
setTimeout(()=>{console.log("hello");},1000);

setInterval(menu,1000) //NECESSARIA PERCHE' SE SI FA DIRETTAMENTE IL WHILE BLOCCA L'ESECUZIONE E SETTIMEOUT NON VIENE ESEGUITO!