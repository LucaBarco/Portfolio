import React from 'react';
import TodoItem from './TodoItem';
import ListGroup from 'react-bootstrap/ListGroup';

const TodoList = (props) => {

  let {tasks, editTask, deleteTask} = props;

  return (
    <React.Fragment>
      {tasks && 
      <ListGroup as="ul" variant="flush">
        {tasks.map((task) => <TodoItem key={task.id} task={task} editTask={editTask} deleteTask={deleteTask} />) }
      </ListGroup>}
    </React.Fragment>
  );
}

export default TodoList;
