import React from 'react';
import Spinner from 'react-bootstrap/Spinner';
import Container from 'react-bootstrap/Container';
import Table from 'react-bootstrap/Table';
import Alert from 'react-bootstrap/Alert';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';
import {Link} from 'react-router-dom'
import moment from 'moment';

const BookingItem=function(props){
    let {booking,canDelete,deleteBooking}=props;
    //canDelete e deleteBooking sono elementi definiti solo per i noleggi futuri
    return(<>
                <tr>
                <td>{`${booking.id}`}</td>
                <td>{`${booking.id_auto}`}</td>
                <td>{`${booking.categoria}`}</td>
                <td>{`${booking.marca}`}</td>
                <td>{`${booking.modello}`}</td>
                <td>{`${booking.startDate}`}</td>
                <td>{`${booking.endDate}`}</td>
                <td>{`${booking.nKm}`}</td>
                <td>{`${booking.nDrivers}`}</td>
                <td>{booking.extraInsurance===1 ?<>Sì</>:<>No</>}</td>
                <td>{`${booking.price}€`}</td>
                {canDelete===true && <td><div onClick={()=>deleteBooking(booking.id)}><svg className="bi bi-trash-fill" width="1em" height="1em" viewBox="0 0 16 16" fill="currentColor" xmlns="http://www.w3.org/2000/svg">
                <path fillRule="evenodd" d="M2.5 1a1 1 0 0 0-1 1v1a1 1 0 0 0 1 1H3v9a2 2 0 0 0 2 2h6a2 2 0 0 0 2-2V4h.5a1 1 0 0 0 1-1V2a1 1 0 0 0-1-1H10a1 1 0 0 0-1-1H7a1 1 0 0 0-1 1H2.5zm3 4a.5.5 0 0 1 .5.5v7a.5.5 0 0 1-1 0v-7a.5.5 0 0 1 .5-.5zM8 5a.5.5 0 0 1 .5.5v7a.5.5 0 0 1-1 0v-7A.5.5 0 0 1 8 5zm3 .5a.5.5 0 0 0-1 0v7a.5.5 0 0 0 1 0v-7z"/>
                </svg></div></td>}
                </tr>
    </>)
}

//function per renderizzare noleggi passati
const Bookings=function(props){
    let {bookings,canDelete, deleteBooking}=props;
    //canDelete e deleteBooking sono elementi definiti solo per i noleggi futuri
    return(<>
            {bookings.length===0  ? 
                <><Row className="justify-content-md-center "><Alert variant="primary" >Nessun noleggio da mostrare!</Alert></Row></>:
                <>
                <Table striped borderless hover size="sm" >
                            
                    <thead className="tableHeader">
                        <tr>
                        <th>Id Prenotazione</th>
                        <th>Id Auto</th>
                        <th>Categoria</th>
                        <th>Marca</th>
                        <th>Modello</th>
                        <th>Dal</th>
                        <th>Al</th>
                        <th>Km giornalieri</th>
                        <th>Guidatori Addizionali</th>
                        <th>Assicurazione Extra</th>
                        <th>Prezzo</th>
                        {canDelete===true && <th>Azioni</th>}
                        </tr>
                    </thead>
                    <tbody>
                        {bookings.map((b) => <BookingItem  key = {b.id} booking={b} canDelete={canDelete} deleteBooking={deleteBooking}/>)}
                    </tbody>
                        
                </Table>
                </>
            }</>);
}

class BookingList extends React.Component{

    constructor(props){
        super(props);
        /**
         * apiError: erore generico dal server
         * isLoading : flag per dire che sto caricando i dati
         */
        this.state={isLoading:true,apiError:false};
        this.getBookings=this.getBookings.bind(this);
        this.deleteBooking=this.deleteBooking.bind(this);
    }

    componentDidMount(){
        //chiamata alle api
        this.getBookings();
    }

    
    getBookings(){
        //divide i record in tre vettori da salvare poi in un unico oggetto
                    //composto da:
                    //passati: elenco prenotazioni passate
                    //attivi: elenco prenotazioni attive
                    //futuri: elenco prenotazioni future
                    this.setState({isLoading:true});
        this.props.getUserBookings().then((bookings)=>{
            //console.log(bookings);
            if(bookings.length>0){
            let past=[];
            let active=[];
            let future=[];
            for(let b of bookings){
                switch(b.nKm){
                    case 1:
                        b.nKm="Meno di 50"
                        break;
                    case 2:
                        b.nKm="Tra 50 e 150" 
                        break;
                    default:
                        b.nKm="Più di 150"
                        break;
                }
                if(moment(b.endDate).isBefore(moment())){
                    //noleggio passato
                    past.push(b);
                }else if(moment(b.startDate).isSameOrBefore(moment())&& moment(b.endDate).isSameOrAfter(moment())){
                        //noleggio attivo
                        active.push(b);
                        }
                        else{
                            //noleggio futuro
                            future.push(b);
                        }
                this.setState({pastBookings:past,activeBookings:active,futureBookings:future,isLoading:false,apiError:false});
            }
        }
        else{
            this.setState({pastBookings:[],activeBookings:[],futureBookings:[],isLoading:false,apiError:false});
        }}).catch((err)=>{
            if(err.status===401){
                this.pops.signalTokenIsExpired();
            }
            else{
                this.setState({apiError:true});
            }
        });

    }

    deleteBooking(id){
        this.props.deleteUserReservation(id).then(()=>{
            this.getBookings();
            
        }).catch((err)=>{
            if(err.status===401){
                this.props.signalTokenIsExpired();
            }
            else{
                this.setState({apiError:true});
            }
        });
    }

    render(){
        return(<>
            <Row className="justify-content-md-center below-nav">
                
                <Col>
                <Row className="justify-content-md-center"><h1>Area personale di {`${this.props.loggedUser.nome}`}</h1></Row>
                <br/>
                <Row className="justify-content-md-center"><Link to='/utente/prenota'><Alert variant="warning">Clicca qui per richiedere un nuovo noleggio</Alert></Link></Row>
                </Col>
            </Row>
            {this.state.isLoading ? <Alert variant="success" sm={9}><Spinner animation="border" variant="success"/> Caricamento dati in corso ...</Alert> :
            <>
            {this.state.apiError===true && <><Row className="justify-content-md-center below-nav"><Alert variant="danger" >Errore comunicazione con il server!</Alert></Row></>}
                  <Container fluid >
            <Row className="justify-content-md-center below-nav">
                    <h5>Noleggi attivi</h5>
             </Row>
            <Row className="justify-content-md-center">
                <Col sm={9}>
                    <Bookings bookings={this.state.activeBookings} canDelete={false}/>
                </Col>
            </Row>
            <Row className="justify-content-md-center below-nav">
                    <h5>Noleggi futuri</h5>
             </Row>
            <Row className="justify-content-md-center">
                <Col sm={9}>
                    <Bookings bookings={this.state.futureBookings} canDelete={true} deleteBooking={this.deleteBooking}/>
                </Col>
            </Row>
            <Row className="justify-content-md-center below-nav">
                    <h5>Noleggi passati</h5>
             </Row>
            <Row className="justify-content-md-center">
                <Col sm={9}>
                    <Bookings bookings={this.state.pastBookings} canDelete={false}/>
                 </Col>
            </Row>
            </Container>
            </>}
            </>
        );
    }
}
export default BookingList;