import React from 'react';
import TodoItem from './TodoItem';

function createTodo(task) {
  return (
    <TodoItem key = {task.id} task = {task}/>
  );
}

const TodoList = (props) => {

  let {tasks} = props;

  return (
    <div>
      
      {tasks && 
      <ul className ="list-group list-group-flush">
        {tasks.map(createTodo) }
      </ul>}
    </div>
  );
}

export default TodoList;
