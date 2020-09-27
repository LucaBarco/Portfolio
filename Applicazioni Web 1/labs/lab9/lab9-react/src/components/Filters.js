import React from 'react';
import ListGroup from 'react-bootstrap/ListGroup';

class Filters extends React.Component {
    createProject = (project) => {
        return (
            <ListGroup.Item action href={`#${project}`} key={project} onClick = {() => {this.props.filterTasks('filter-project', project);}}>{project}</ListGroup.Item>
        );
    }

    render() {
        return (
            <React.Fragment>
                <ListGroup defaultActiveKey="#all" variant="flush">
                    <ListGroup.Item action href="#all" id = "filter-all" onClick = {() => {this.props.filterTasks('filter-all');}}>All</ListGroup.Item>
                    <ListGroup.Item action href="#important" id = "filter-important" onClick = {() => {this.props.filterTasks('filter-important');}}>Important</ListGroup.Item>
                    <ListGroup.Item action href="#today" id = "filter-today" onClick = {() => {this.props.filterTasks('filter-today');}}>Today</ListGroup.Item>
                    <ListGroup.Item action href="#week" id = "filter-week" onClick = {() => {this.props.filterTasks('filter-week');}}>Next 7 Days</ListGroup.Item>
                    <ListGroup.Item action href="#private" id = "filter-private" onClick = {() => {this.props.filterTasks('filter-private');}}>Private</ListGroup.Item>
                    <ListGroup.Item action href="#shared" id = "filter-shared" onClick = {() => {this.props.filterTasks('filter-shared');}}>Shared With...</ListGroup.Item>
                    <ListGroup.Item className="p-3 mt-5 list-title">Projects</ListGroup.Item>
                    {this.props.projects.map(this.createProject) }
                </ListGroup>
            </React.Fragment>
        );
    }
}

export default Filters;
