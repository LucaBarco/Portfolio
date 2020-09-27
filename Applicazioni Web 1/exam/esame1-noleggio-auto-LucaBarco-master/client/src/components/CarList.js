import React from 'react';
import Spinner from 'react-bootstrap/Spinner';
import Table from 'react-bootstrap/Table';
import Alert from 'react-bootstrap/Alert';   //per mostrare messaggio errore risultati 
import Container from 'react-bootstrap/Container'; //necessario per poter inserire alert condizionale

//funzione per renderizzare riga della tabella
const CarItem=(props)=>{
    let {auto}=props;
   return(
        <tr>
            <td>{auto.categoria}</td>
            <td>{auto.marca}</td>
            <td>{auto.modello}</td>
            <td>{auto.quantita}</td>
        </tr>);
      
}

//funzione per renderizzare la tabella delle auto
const CarList=(props)=>{
let{cars}=props;
    return(<Container fluid>
                <Table striped borderless hover size="sm" >
                    <thead className="tableHeader">
                        <tr>
                        <th>Categoria</th>
                        <th>Marca</th>
                        <th>Modello</th>
                        <th>Numero veicoli</th>
                        </tr>
                    </thead>
                    <tbody>
                        {cars.map((auto) => <CarItem  key = {auto.id} auto={auto} />)}
                    </tbody>
                </Table>
         { cars.length===0 && props.isLoading && <Alert variant="primary"><Spinner animation="border" variant="primary"/> Caricamento in corso ...</Alert> } 
         {cars.length===0 && !props.isLoading && <Alert variant="primary"> Nessun risultato trovato</Alert>  }
        </Container>);
}

export default CarList;