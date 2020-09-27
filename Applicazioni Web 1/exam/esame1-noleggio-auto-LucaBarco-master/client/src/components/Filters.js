import React from 'react';
import Container from 'react-bootstrap/Container';
import Row from 'react-bootstrap/Row';
import Form from 'react-bootstrap/Form';

class Filters extends React.Component{

    
    //no constructor per via del warning no-useless-constructor
   
    createProducer=(p)=>{
        return (<Form.Check 
            type="switch"
            key={`switch-${p}`}
            id={`switch-${p}`}
            label={`${p}`}
            onChange={()=>this.props.toggleProducerFilter(p)}
            
        />);
    }
    componentWillUnmount(){
        this.props.resetCarList();
    }
    render(){
        return(
            <Container fluid>
            <Row >
            <h3>Categorie</h3>
            </Row>
            <Form>
                <Form.Check 
                    type="switch"
                    key="switch-A"
                    id="switch-A"
                    label="A"
                    onChange={()=>this.props.toggleCategoryFilter('A')}
                />
                <Form.Check 
                    type="switch"
                    key="switch-B"
                    id="switch-B"
                    label="B"
                    onChange={()=>this.props.toggleCategoryFilter('B')}
                />
                <Form.Check 
                    type="switch"
                    key="switch-C"
                    id="switch-C"
                    label="C"
                    onChange={()=>this.props.toggleCategoryFilter('C')}
                />
                <Form.Check 
                    type="switch"
                    key="switch-D"
                    id="switch-D"
                    label="D"
                    onChange={()=>this.props.toggleCategoryFilter('D')}
                />
                <Form.Check 
                    type="switch"
                    key="switch-E"
                    id="switch-E"
                    label="E"
                    onChange={()=>this.props.toggleCategoryFilter('E')}
                />
            </Form>
            <Row>
            <h3><br/>Marche</h3>
            </Row>
            {
                this.props.carProducers.map(this.createProducer)
            }
            </Container>
        );
    }
}
export default Filters;