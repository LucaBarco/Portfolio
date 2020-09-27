import moment from 'moment';
class Task{

    constructor(id, description, important, privateTask, deadline, project, completed){
        if(id){
            this.id=id;
        }
        if(project){
            this.project=project;
        }
        if(deadline){
        this.deadline= moment(deadline);
        }
        this.description=description;
        this.privateTask=privateTask;
        this.important=important;
        this.completed=completed || false;
    }
    static from(json){
        const o=Object.assign(new Task(),json);
        if(o.deadline){
            o.deadline=moment(o.deadline);
        }
        return o;
    }
}
export default Task;