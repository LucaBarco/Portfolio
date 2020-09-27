import moment from 'moment';

class Task{    

    constructor(id, description, important, privateTask, deadline, project, completed) {
        if(id)
            this.id = id;
            
        this.description = description;
        this.important = important;
        this.privateTask = privateTask;

        if(deadline)
            this.deadline = moment(deadline);
        if(project)
            this.project = project;

        this.completed = completed || false;

    }

    /**
     * Construct a Task from a plain object
     * @param {{}} json 
     * @return {Task} the newly created Task object
     */
    static from(json) {
        const t =  Object.assign(new Task(), json);
        if(t.deadline)
            t.deadline = moment(t.deadline);
        return t;
    }

}

export default Task;

