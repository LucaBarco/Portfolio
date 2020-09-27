import React from 'react';


class Filters extends React.Component{
    createProject=(project)=>{
        return (
            <a href="/#" key={project} className="list-group-item list-group-item-action" onClick={()=>this.props.handleFilterProject(project)}>{project}</a>
        );
    }
    constructor(props){
        super(props);
        this.state={projects:props.projects}
    }
    render() {
    return (
    <div>
        <div className="list-group list-group-flush">
            <a href="/#" id="filter-all" className="list-group-item list-group-item-action active" onClick={this.props.handleFilterAll}>All</a>
            <a href="/#" id="filter-important" className="list-group-item list-group-item-action"  onClick={this.props.handleFilterImportant}>Important</a>
            <a href="/#" id="filter-today" className="list-group-item list-group-item-action"  onClick={this.props.handleFilterToday}>Today</a>
            <a href="/#" id="filter-week" className="list-group-item list-group-item-action"  onClick={this.props.handleFilterWeek}>Next 7 Days</a>
            <a href="/#" id="filter-private" className="list-group-item list-group-item-action"  onClick={this.props.handleFilterPrivate}>Private</a>
            <a href="/#" id="filter-shared" className="list-group-item list-group-item-action"  onClick={this.props.handleFilterShared}>Shared With...</a>
        </div>

        <div className="my-5">
            <h6 className="border-bottom border-gray p-3 mb-0">Projects</h6>
            <div className="list-group list-group-flush" id="projects">
                {this.state.projects.map(this.createProject) }
            </div>
        </div>
        </div>
    );
}
}


export default Filters;
