"use strict";

const express=require('express');
const morgan=require('morgan');

const sqlite=require('sqlite3');
const db= new sqlite.Database('./db/tasks.db',(err)=>{console.error("Error in db: "+err);});

const app=express();
const port=3000;

//set-up logging
app.use(morgan('tiny'));
// Process body content
app.use(express.json());
//Set-up the 'client' component as a static website
app.use(express.static('client'));
app.get('/',(req,res)=>res.redirect('./index.html'));

//REST API endpoints

//Resources: task

//GET /tasks
//Retrieve list of all tasks
//Request body: empty
//Response body: Array of objects, each describing a Task
//Errors: none
app.get('/tasks',(req,res)=>{
    const sql='SELECT * from tasks';
    db.all(sql,(err,rows)=>{
        if(err){
            throw err;
        }
        console.log(rows);
        const courses=rows.map((row)=>({
            id: row.id,
            description: row.description,
            important: row.important,
            private: row.private,
            project: row.project,
            deadline: row.deadline,
            completed: row.completed,

        }));
        res.json(courses);
    })
});

//GET /tasks/<task_id>
//retrieve info about one task 
//Request body: empty
//Response body: Object describing a Task
//Errors: none
app.get('/tasks/:id',(req,res)=>{
    const task_id=req.params.id;
    const sql='SELECT * FROM tasks WHERE id=?';
    db.get(sql,[task_id],(err,row)=>{
        if(err){
            throw err;
        }
        if(row){
            res.json({ id: row.id,
                description: row.description,
                important: row.important,
                private: row.private,
                project: row.project,
                deadline: row.deadline,
                completed: row.completed,});
        }
    });

});

//POST /tasks/insert
// insert a new task 
//Request body: Object describing a Task (json)
//Response body: Object describing the new Task
//Errors: none
app.post('/tasks/insert',(req,res)=>{
    const new_task=req.body;
    if(new_task.description && new_task.project){
        new_task.private=new_task.private||1;
        new_task.completed=new_task.complete||0;
        new_task.important=new_task.important||0;
        new_task.deadline=new_task.deadline||"";
        const sql='INSERT INTO tasks VALUES(?,?,?,?,?,?,?)';
        const sql_id='SELECT MAX(id) FROM tasks';
        let id=0;
        db.run(sql_id,(err,row)=>{
            if(err){
                id=1;
            }
            else{
                id=row +1;
            }
            db.run(sql,[id,new_task.description,new_task.important,new_task.private,new_task.project,new_task.deadline,new_task.completed],(err,row)=>{
                if(err){
                    throw err;
                     }
                else{
                        res.json({
                            id: id,
                            description: new_task.description,
                            important: new_task.important,
                            private: new_task.private,
                            project: new_task.project,
                            deadline: new_task.deadline,
                            completed: new_task.completed,
                            
                        });;
                    }
                
            });
        });
       
    }
});
//PUT /task/update/<task_id>
//update a task
//Request body: Object describing a Task
//Response body: empty (or "okay")
//Errors: string "error"
app.put('/tasks/update/:id',(req,res)=>{
    const new_task=req.body;
    const task_id=req.params.id;
    if(new_task.description && new_task.project){
        new_task.private=new_task.private||1;
        new_task.completed=new_task.complete||0;
        new_task.important=new_task.important||0;
        new_task.deadline=new_task.deadline||"";
        const sql='UPDATE tasks SET description=?, important=? , private=? , project=? , deadline=? , completed=? WHERE id=?';
        
        db.run(sql,[new_task.description,new_task.important,new_task.private,new_task.project,new_task.deadline,new_task.completed,task_id],(err,row)=>{
            if(err){
                throw err;
                 }
            else{
                    res.json({
                        id: task_id,
                        description: new_task.description,
                        important: new_task.important,
                        private: new_task.private,
                        project: new_task.project,
                        deadline: new_task.deadline,
                        completed: new_task.completed,
                        
                    });;
                }
            
        });
    }
});
//DELETE /tasks/<task_id>
//delete a task
//Request body: empty
//Response body: String "deleted"
//Errors: none
app.delete('/tasks/:id',(req,res)=>{
    const sql='DELETE FROM tasks WHERE id=?';
    const task_id=req.params.id;
    db.run(sql,[task_id],(err)=>{
        if(err){
            throw err;
           
        }
        else{
            res.json({"result":'deleted'});
        }
    })
});
//PATCH /tasks/complete/<task_id>
//complete a task
//Request body: empty
//Response body: Object describing a Task
//Errors: none
app.patch('/tasks/complete/:id',(req,res)=>{
    const task_id=req.params.id;
    const sql="UPDATE tasks SET completed=1 WHERE id=?";
    db.run(sql,[task_id],(err,row)=>{
        if(err){
            
            throw err;
        }
        else{
        res.json({
            "result":'completed'
        });}
    })
})

//GET /tasks/filter/important
//retrieve the list of all important tasks
//Request body: empty
//Response body: Array of tasks: each object describing a Task
//Errors: none
app.get('/tasks/filter/important',(req,res)=>{
    const sql='SELECT * FROM tasks WHERE important=1';
    db.all(sql,(err,rows)=>{
        if(err){
            throw err;
        }
        else{
        console.log(rows);
        const courses=rows.map((row)=>({
            id: row.id,
            description: row.description,
            important: row.important,
            private: row.private,
            project: row.project,
            deadline: row.deadline,
            completed: row.completed,

        }));
        res.json(courses);}
    });
});

//GET /tasks/filter/private/<flag>
//retrieve the list of all private(flag:1) or shared(flag:0) tasks 
//flag: 0 for shared, 1 for private
//Request body: empty
//Response body: Array of tasks: each object describing a Task
//Errors: none
app.get('/tasks/filter/private/:flag',(req,res)=>{
    const sql='SELECT * FROM tasks WHERE private=?';
    const flag=req.params.flag;
    db.all(sql,[flag],(err,rows)=>{
        if(err){
            throw err;
        }
        else{
        console.log(rows);
        const courses=rows.map((row)=>({
            id: row.id,
            description: row.description,
            important: row.important,
            private: row.private,
            project: row.project,
            deadline: row.deadline,
            completed: row.completed,

        }));
        res.json(courses);
    }
    });
});


//GET /tasks/filter/today
//retrieve the list of all  tasks that will expire today
//Request body: empty
//Response body: Array of tasks: each object describing a Task
//Errors: none
app.get('/tasks/filter/today',(req,res)=>{
    const sql='SELECT * FROM tasks WHERE DATE(deadline)=DATE(\'now\')';
    db.all(sql,(err,rows)=>{
        if(err){
            throw err;
        }
        else{
        console.log(rows);
        const courses=rows.map((row)=>({
            id: row.id,
            description: row.description,
            important: row.important,
            private: row.private,
            project: row.project,
            deadline: row.deadline,
            completed: row.completed,

        }));
        res.json(courses);
    }
    });
});

//GET /tasks/filter/week
//retrieve the list of all  tasks that will expire in this week
//Request body: empty
//Response body: Array of tasks: each object describing a Task
//Errors: none
app.get('/tasks/filter/week',(req,res)=>{
    const sql='SELECT * FROM tasks WHERE DATE(deadline)<=DATE(\'now\',\'+7 days\') AND  DATE(deadline)>=DATE(\'now\')';
    db.all(sql,(err,rows)=>{
        if(err){
            throw err;
        }
        console.log(rows);
        const courses=rows.map((row)=>({
            id: row.id,
            description: row.description,
            important: row.important,
            private: row.private,
            project: row.project,
            deadline: row.deadline,
            completed: row.completed,
        }));
        res.json(courses);
    });
});

//GET /tasks/filter/project/<project_name>
//retrieve the list of all  tasks of a specific project
//Request body: empty
//Response body: Array of tasks: each object describing a Task
//Errors: none
app.get('/tasks/filter/project/:project',(req,res)=>{
    const sql='SELECT * FROM tasks WHERE project=?';
    const project=req.params.project;
    console.log(project);
    db.all(sql,[project],(err,rows)=>{
        if(err){
            throw err;
        }
        console.log(rows);
        const courses=rows.map((row)=>({
            id: row.id,
            description: row.description,
            important: row.important,
            private: row.private,
            project: row.project,
            deadline: row.deadline,
            completed: row.completed,

        }));
        res.json(courses);
    });
});
//Activate web server
app.listen(port, ()=>console.log(`Example app listening at http://localhost:${port}`))
