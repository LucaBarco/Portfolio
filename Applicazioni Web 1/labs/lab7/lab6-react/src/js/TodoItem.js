import React from 'react';
import moment from 'moment'

const TodoItem = (props) => {

  let {task} = props;

  return (

    <li className="list-group-item" id = {task.id}>
        <div className="d-flex w-100 justify-content-between">
          <div className="custom-control custom-checkbox">
            <input type="checkbox" className={task.important ? "custom-control-input" : "custom-control-input important"} id={"check-t" +  task.id} defaultChecked = {task.completed} />
            <label className="custom-control-label" htmlFor={"check-t" +  task.id}>{task.description}</label>
            <span className="badge badge-success ml-4">{task.project}</span>
          </div>
          {!task.privateTask && (
                <svg className="bi bi-person-square" width="1.2em" height="1.2em" viewBox="0 0 16 16" fill="currentColor" xmlns="http://www.w3.org/2000/svg">
                  <path fillRule="evenodd" d="M14 1H2a1 1 0 00-1 1v12a1 1 0 001 1h12a1 1 0 001-1V2a1 1 0 00-1-1zM2 0a2 2 0 00-2 2v12a2 2 0 002 2h12a2 2 0 002-2V2a2 2 0 00-2-2H2z" clipRule="evenodd"/>
                  <path fillRule="evenodd" d="M2 15v-1c0-1 1-4 6-4s6 3 6 4v1H2zm6-6a3 3 0 100-6 3 3 0 000 6z" clipRule="evenodd"/>
                </svg>)}

          {task.deadline &&  (
            <small className = {task.deadline.isBefore(moment()) ? "date bg-danger text-white" : "date"}>{task.deadline.format("dddd, MMMM Do YYYY, h:mm:ss a")} </small>
          )}
          
          <div>
            <img width="20" height="20" className="img-button" src="svg/edit.svg" alt =""/>
            <img width="20" height="20" className="img-button" src="svg/delete.svg" alt =""/>
          </div>

        </div>
    </li>
  );
}
export default TodoItem;
