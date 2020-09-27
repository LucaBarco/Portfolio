import React from 'react';
import ListGroup from 'react-bootstrap/ListGroup';
import {Link} from 'react-router-dom'
class Filters extends React.Component {
    createProject = (project) => {
        return (
            <ListGroup.Item  key={project}> <Link to={`/${project}`}> {project} </Link></ListGroup.Item>
        );
    }

    render() {
        return (
            <React.Fragment>
                <ListGroup defaultActiveKey="#all" variant="flush">
                    <ListGroup.Item id = "filter-all"> <Link to='/'>All</Link> </ListGroup.Item>
                    <ListGroup.Item id = "filter-important"> <Link to='/important'>Important</Link> </ListGroup.Item>
                    <ListGroup.Item  id = "filter-today"> <Link to='/today'>Today</Link> </ListGroup.Item>
                    <ListGroup.Item  id = "filter-week"> <Link to='/week'>Next 7 Days </Link> </ListGroup.Item>
                    <ListGroup.Item  id = "filter-private"><Link to='/private'>Private</Link></ListGroup.Item>
                    <ListGroup.Item  id = "filter-shared"><Link to='/shared'>Shared With...</Link></ListGroup.Item>
                    <ListGroup.Item className="p-3 mt-5 list-title">Projects</ListGroup.Item>
                    {this.props.projects.map(this.createProject) }
                </ListGroup>
            </React.Fragment>
        );
    }
}

export default Filters;
