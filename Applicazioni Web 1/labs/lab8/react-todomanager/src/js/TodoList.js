import React from 'react';
import TodoItem from './TodoItem';

function createTodo(task){
    return(
        <TodoItem key={task.id} task={task} deleteTask={deleteTask}/>
    );
}
let deleteTask;
const TodoList= (props)=>{
    let {tasks}=props;
    deleteTask=props.deleteTask;
    return (
        <ul className="list-group list-group-flush">
            {tasks.map(createTodo)}
        </ul>

        );
}
export default TodoList;