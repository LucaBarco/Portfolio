"use strict";
class Filter{
    constructor(){

        this.filters=document.getElementsByClassName("list-group-item-action");
    }

    clearAll=function(){
        function clearTasks(){
            const taskList = document.getElementById("taskList");
            taskList.innerHTML = '';
        }
    }
    

    activateFilters=function(){
        const filters=this.filters;
        filters[0].addEventListener('click',event=>{
            //show all events
            let tasks=document.getElementsByClassName("task");
            for(let task of tasks){
                task.style.visibility="visible";
                task.style.display="block";
            }
        });
        filters[1].addEventListener('click',event=>{
            //show all important events
            let tasks=document.getElementsByClassName("task");
            for(let task of tasks){
                if(!(task.classList.contains("urgent"))){    
                task.style.visibility="hidden";
                task.style.display="none";
                }
                else{
                    task.style.visibility="visible";
                    task.style.display="block";
                }
            }
        });
        
        filters[2].addEventListener('click',event=>{
            //show today
            let tasks=document.getElementsByClassName("task");
            let now=moment().format("YYYY-MM-DD");
            for(let task of tasks){
                let li= document.getElementById(task.id);
                let date=li.getElementsByClassName("date")[0].firstChild.textContent;
                let d=moment(date,'MMMM Do YYYY, h:mm:ss a');
                console.log(date);
                console.log(d);
                 if(d.diff(now,'days')==0){
                    task.style.visibility="visible";
                    task.style.display="block";
                }
                else{
                    task.style.visibility="hidden";
                    task.style.display="none";
                }
        
            }
        });
        
        filters[3].addEventListener('click',event=>{
            //show next week
            let tasks=document.getElementsByClassName("task");
            let now=moment().format("YYYY-MM-DD");
            for(let task of tasks){
                let li= document.getElementById(task.id);
                let date=li.getElementsByClassName("date")[0].firstChild.textContent;
                let d=moment(date,'MMMM Do YYYY, h:mm:ss a');
                console.log(li.classList.contains('expired'));
                 if(d.diff(now,'week')<=7 && !(li.getElementsByClassName("date")[0].classList.contains('expired'))){
                    task.style.visibility="visible";
                    task.style.display="block";
                }
                else{
                    task.style.visibility="hidden";
                    task.style.display="none";
                }
        
            }
        });
        
        filters[4].addEventListener('click',event=>{
            //show all private events
            let tasks=document.getElementsByClassName("task");
            for(let task of tasks){
                if((task.classList.contains("shared"))){    
                task.style.visibility="hidden";
                task.style.display="none";
                }
                else{
                    task.style.visibility="visible";
                    task.style.display="block";
                }
            }
        });
        filters[5].addEventListener('click',event=>{
            //show all shared events
            let tasks=document.getElementsByClassName("task");
            for(let task of tasks){
                if(!(task.classList.contains("shared"))){    
                task.style.visibility="hidden";
                task.style.display="none";
                }
                else{
                    task.style.visibility="visible";
                    task.style.display="block";
                }
            }
        });

        
        
    }
}