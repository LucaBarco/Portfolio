import React from 'react';
import Form from 'react-bootstrap/Form'
import Button from 'react-bootstrap/Button'
import Alert from 'react-bootstrap/Alert'
import Row from 'react-bootstrap/Row'
import Col from 'react-bootstrap/Col'
import {Link} from 'react-router-dom'
import moment from 'moment'

class BookingForm extends React.Component{
    constructor(props){
        super(props);
        /**
         * 
         *  mode        :    modalità di visualizzazione  config / payment / confirm
         *  startDate   :   campo per la prenotazione,
         *  endDate     :   campo per la prenotazione,
         *  category    :   campo per la prenotazione,
         *  nDrivers    :   campo per la prenotazione,
         *  nKm         :   campo per la prenotazione,
         *  ageDriver   :   campo per la prenotazione,
        *   extraInsurance:   campo per la prenotazione,,
        *   dateError     : true quando l'intervallo definito dalle date di fine e di inizio non è valido 
        *   startError    : true true quando la data di inizio o di fine precede la data attuale
        *   apiError      : errore generico dal server
        *   number        : campo per la prenotazione/auto disponibili
        *   price         : campo per la prenotazione/prezzo
        *   bookingInfo   : campo contenente il riepilogo della prenotazione che viene ritornato dal server dopo ave cliccato su "prenota",
        *   numberCCErr   :true se campo numero CC errato (16 cifre)
        *   CVVErr        : true se campo CVV errato (3 cifre)
        *   nameErr       : true se campo nomeCC errato (min 4 char)
         */
        this.state={mode:'config',
                    startDate:null,
                    endDate:null,
                    category:"A",
                    nDrivers:"0",
                    nKm:1,
                    ageDriver:1,
                    extraInsurance:false,
                    dateError:true,
                    startError:true,
                    apiError:false,
                    number:0,
                    price:null,
                    bookingInfo:null,
                    numberCCErr:true,
                    CVVErr: true,
                    nameErr:true,
         }
    this.deleteReservation=this.deleteReservation.bind(this);
    this.confirmReservation=this.confirmReservation.bind(this);
    }

    componentDidMount(){
        //check se sono loggato
        this.props.getUser();
    }

    componentDidUpdate(prevProps,prevState){
        if( this.state.dateError===false && this.state.startError===false && this.state.startDate!==null && this.state.endDate!==null && (
            this.state.startDate !== prevState.startDate||
            this.state.endDate !== prevState.endDate ||
            this.state.category !== prevState.category ||
            this.state.nDrivers !== prevState.nDrivers ||
            this.state.ageDriver !== prevState.ageDriver ||
            this.state.nKm !== prevState.nKm ||
            this.state.extraInsurance !== prevState.extraInsurance)

        ){
            this.updateAvailability();
        }
    }
    componentWillUnmount(){
        if(this.state.bookingInfo && this.state.bookingInfo.reservationId && this.state.mode!=='confirm'){
            this.props.deleteReservation(this.state.bookingInfo.reservationId);
        }
    }

    handleSubmit(event){
        //gestisce pressione del tasto "Prenota" del configuratore interattivo
        event.preventDefault();
        //chiamata POST alle API
        this.props.insertReservation({
            category:this.state.category,
            startDate:this.state.startDate,
            endDate:this.state.endDate,
            nDrivers:this.state.nDrivers,
            ageDriver:this.state.ageDriver,
            nKm:this.state.nKm,
            extraInsurance: this.state.extraInsurance
        }).then((res)=>{
            this.setState({mode:'payment',bookingInfo:res,apiError:false});
        }).catch((err)=>{
            if(err.status===401){
                this.props.signalTokenIsExpired();
            }
            else{
            this.setState({apiError:true});
            }
        });
    }

    checkDate(startDate,endDate){
        //check se startDate ed endDate sono coerenti
        if(!moment(startDate).isBefore(moment(endDate))){
            this.setState({dateError:true});
            return true;
        }
        else{
            this.setState({dateError:false});
            return false;
        }  
    }

    checkStartDate(date){
        //check se date è precedente a oggi
        if(moment(date).isBefore(moment())){
            this.setState({startError:true});
            return false;
        }
        else{
            this.setState({startError:false});
            return true;
        }
    }

    updateAvailability(){
        //contatta server per sapere le nuove disponibilità 
        this.props.getAvailability(
            {startDate:this.state.startDate,
                endDate:this.state.endDate,
                category:this.state.category,
                nDrivers:this.state.nDrivers,
                nKm:this.state.nKm,
                ageDriver:this.state.ageDriver,
                extraInsurance:this.state.extraInsurance}).then((resp)=>{
                    this.setState({number:resp.number,price:resp.price,apiError:false});
                }).catch((err)=>{
                    if(err.status===401){
                        this.props.signalTokenIsExpired();
                    }
                    else{
                        if(this.state.apiError===false){
                        this.setState({apiError:true});
                        }
                    }
                });     
    }

    updateField(name,value){
        //gestisce cambiamento di un campo del configuratore interattivo
        this.setState({[name]:value});
        if(name==="startDate"){
            //check startDate
            if(this.checkStartDate(value)){
            //check interval
            this.checkDate(value,this.state.endDate);
            }
        }else{
            if(name==="endDate"){
                    //check endDate
                this.checkDate(this.state.startDate,value)
                    
            }
        }
        
    }

    toggleInsurance(){
        //gestisce cambiamento del flag extraInsurance
        this.setState((previous)=>{return {extraInsurance:!previous.extraInsurance};});
    }

    updatePaymentField(name,value){
        //gestisce cambiamento campo del form di pagamento
        switch(name){
            case "numberCC":
            if(value.trim().match(/\b\d{16}\b/g)){
                this.setState({numberCC:value,numberCCErr:false});
            }
            else{
                this.setState({numberCCErr:true});
            }
                break;
            case "CVV":
                if(value.trim().match(/\b\d{3}\b/g)){
                    this.setState({CVV:value,CVVErr:false});
                }
                else{
                    this.setState({CVVErr:true});
                }
                break;
            case "nameCC":
                if(value.length>=4){
                this.setState({nameCC:value,nameErr:false});
                }
                else{
                    this.setState({nameErr:true});
                }
                break;
                default:
                    break;
        }
        
    }

    handlePaymentSubmit(event){
        //gestisce pressione del tasto "PAGA"
        event.preventDefault();
        //gestire pagamento
        this.confirmReservation();
    }

    deleteReservation(){
        this.props.deleteReservation(this.state.bookingInfo.reservationId).then(()=>{
            //reset delle variabili di stato per poter resettare il configuratore interattivo
            this.setState({mode:'config',
            startDate:null,
            endDate:null,
            category:"A",
            nDrivers:"0",
            nKm:1,
            ageDriver:1,
            extraInsurance:false,
            dateError:true,
            startError:true,
            apiError:false,
            number:0,
            price:null,
            bookingInfo:null,
            numberCCErr:true,
            CVVErr: true,
            nameErr:true,});
        }).catch((err)=>{
            if(err.status===401){
                this.props.signalTokenIsExpired();
            }
            else{
            this.setState({mode:'config',apiError:true});
            }
        });
    }

    confirmReservation(){
        //metodo che conferma la prenotazione
        this.props.confirmReservation(this.state.bookingInfo.reservationId,{
            number:this.state.numberCC,
            name:this.state.numberCC,
            CVV:this.state.CVV,
        }).then(()=>{
            this.setState({mode:'confirm',apiError:false});
        }).catch((err)=>{
            if(err.status===401){
                this.props.signalTokenIsExpired();
            }
            else{
            this.setState({mode:'confirm',apiError:true});
            }
        }
        );
    }

    
    render(){
        return(<>
        
        { this.state.mode==='config' && <>
            
        <Row className="justify-content-md-center below-nav">
            <Form  method="POST" onSubmit={(event) => this.handleSubmit(event)}>
            <Col>
             <Row>
                 <Col >
              <Form.Group >
                <Form.Label>Data di inizio</Form.Label>
                <Form.Control type="date" name="startDate"  onChange={(ev) => this.updateField(ev.target.name, ev.target.value)} required autoFocus/>
              </Form.Group>
              </Col>
              <Col >
              <Form.Group >
                <Form.Label>Data di fine</Form.Label>
                <Form.Control type="date" name="endDate"  onChange={(ev) => this.updateField(ev.target.name, ev.target.value)} required />
              </Form.Group>
              </Col>
              <Col>
              <Form.Group >
                <Form.Label>Categoria Auto</Form.Label>
                    <Form.Control as="select" className="mr-sm-2"  id="inlineFormCustomSelectPref" name="category" custom onChange={(ev) => this.updateField(ev.target.name, ev.target.value)} >
                            <option default value="A">A</option>
                            <option value="B">B</option>
                            <option value="C">C</option>
                            <option value="D">D</option>
                            <option value="E">E</option>
                    </Form.Control>
                </Form.Group>
                </Col>
              </Row>
              <Row>
                <Col>
                <Form.Group >
                    <Form.Label>Eta' Guidatore</Form.Label>
                         <Form.Control as="select" className="mr-sm-2"  id="inlineFormCustomSelectPref" name="ageDriver" custom onChange={(ev) => this.updateField(ev.target.name, ev.target.value)}>
                            <option default value="1">Meno di 25 anni</option>
                            <option value="2">Tra 25 e 65 anni</option>
                            <option value="3">Più di 65 anni</option>
                        </Form.Control>
                    </Form.Group>
                </Col>
                <Col>
                  <Form.Group >
                    <Form.Label>Numero Guidatori Addizionali</Form.Label>
                         <Form.Control as="select" className="mr-sm-2"  id="inlineFormCustomSelectPref" name="nDrivers" custom onChange={(ev) => this.updateField(ev.target.name, ev.target.value)}>
                            <option default value="0">0</option>
                            <option value="1">1</option>
                            <option value="2">2</option>
                            <option value="3">3</option>
                            <option value="4">4</option>
                        </Form.Control>
                 </Form.Group>
                </Col>
              </Row>
              <Row>
                <Col>
                  <Form.Group >
                     <Form.Label>Stima km giornalieri</Form.Label>
                          <Form.Control  as="select" className="mr-sm-2"  id="inlineFormCustomSelectPref" name="nKm" custom onChange={(ev) => this.updateField(ev.target.name, ev.target.value)} >
                            <option default value="1">Meno di 50 km</option>
                            <option value="2">Tra 50 km e 150 km</option>
                            <option value="3">Più di 150km</option>
                        </Form.Control>
                    </Form.Group>
                  </Col>
                  <Col>
                    <Form.Check 
                        type="switch"
                        id="extra-insurance"
                        label="Assicurazione Extra"
                        name="extraInsurance"
                        onChange={(ev) => this.toggleInsurance()}
                        />
                  </Col>
              </Row>
          <Col>
          
          {this.state.dateError===true && this.state.startDate!==null && this.state.endDate!==null && <Alert variant="danger">Intervallo date non valido!</Alert>}
          {this.state.dateError===true && this.state.startDate===null && <Alert variant="danger">Inserire data di inizio!</Alert>}
          {this.state.startError===true && this.state.startDate!==null && <Alert variant="danger">Inserire una data successiva a oggi!</Alert>}
          {this.state.dateError===true && this.state.endDate===null && <Alert variant="danger">Inserire data di fine!</Alert>}
          {this.state.apiError===true && <Alert variant="danger">Errore comunicazione con server!</Alert>}
          {this.state.startDate && this.state.endDate && this.state.category && this.state.number===0 && !this.state.startError && !this.state.dateError && <Alert variant="danger">{`Nessuna auto disponibile dal ${this.state.startDate} al ${this.state.endDate} per la categoria ${this.state.category}`} !</Alert>}
          {this.state.number>0 && this.state.apiError===false && this.state.dateError===false && this.state.startError===false && this.state.price!==null &&
            <Alert variant="primary"><Row>{`Totale auto disponibili: ${this.state.number}`}</Row><Row>{`Prezzo: ${this.state.price.toFixed(2)}€`}</Row></Alert>}
            
            <Row>
                <Col>
                <Link to = "/home">
                    <Button variant="secondary">Torna alla Home</Button>
                </Link>
                </Col>
            {this.state.apiError===false && this.state.dateError===false && this.state.startError===false && this.state.number>0 && <><Col><Button variant="primary" type="submit">Prenota</Button></Col></>}
            </Row>  
        </Col>
    </Col>
    </Form>
    </Row></> }

    {this.state.mode==='payment' &&<>
    
    <Row md="auto" className="justify-content-md-center below-nav">
    <Col md="auto" >
        <Row>
            <h2>Riepilogo</h2>
        </Row>
        <Row>
            <Alert variant="info">
                Id prenotazione: <span className="summaryBooking">{`${this.state.bookingInfo.reservationId}`}<br/><br/></span>
                Auto:<span className="summaryBooking">{` ${this.state.bookingInfo.carId}`}</span><br/> Categoria:<span className="summaryBooking">{` ${this.state.category}`}<br/></span>
                Marca:<span className="summaryBooking">{` ${this.state.bookingInfo.marca}`}</span><br/> Modello: <span className="summaryBooking">{` ${this.state.bookingInfo.modello}`}<br/><br/></span>
                Dal:<span className="summaryBooking">{`  ${this.state.startDate}`}</span><br/> Al: <span className="summaryBooking">{` ${this.state.endDate}`}<br/><br/></span>
                Guidatori aggiuntivi:<span className="summaryBooking">{` ${this.state.nDrivers}`}<br/></span>
                {this.state.extraInsurance===true && <>Assicurazione Extra: <span className="summaryBooking">Sì</span></>}
            </Alert>
        </Row>
        <Row>
            <Alert variant="primary">          
            Prezzo:<span className="summaryBooking price">{` ${this.state.price.toFixed(2)}€`}<br/></span>
            </Alert>
        </Row>
    </Col>
    <Col sm={1}/>
    <Col md="auto" >
        <Form  method="POST" onSubmit={(event) => this.handlePaymentSubmit(event)}>
    <Col>
    <h2>Pagamento</h2>
            <Form.Group>
                <Form.Control  type="text" name="nameCC"   placeholder="Nome intestatario carta" onChange={(ev) => this.updatePaymentField(ev.target.name, ev.target.value)}/>
                <br />
                    {this.state.nameCC &&  this.state.nameErr && <><Alert variant="danger">Inserire un nome valido</Alert><br/></>}
                <Form.Control  type="text" name="numberCC" placeholder="Numero carta di credito" onChange={(ev) => this.updatePaymentField(ev.target.name, ev.target.value)}/>
                <br />
                    {this.state.numberCC &&  this.state.numberCCErr && <><Alert variant="danger">Inserire un numero carta valido</Alert><br/></>}
                <Form.Control  type="text" name="CVV"      placeholder="CVV" onChange={(ev) => this.updatePaymentField(ev.target.name, ev.target.value)}/>
                    {this.state.CVV  && this.state.CVVErr && <><Alert variant="danger">Inserire CVV valido</Alert><br/></>}
            </Form.Group>
            {(this.state.nameErr || this.state.numberCCErr || this.state.CVVErr) &&<><Alert variant="danger">Completare i dati di pagamento</Alert></>}
        
            <Row>
                <Col><Button variant="secondary" onClick={this.deleteReservation}>Annulla</Button></Col>
                {(!this.state.nameErr && !this.state.numberCCErr && !this.state.CVVErr) &&<><Col><Button variant="primary" type="submit">Paga</Button></Col></>}
            </Row>
    </Col>
    </Form>
    </Col>
    </Row>
    </>}

    { this.state.mode==='confirm' && this.state.apiError===false &&
        <>
        <Row md="auto" className="justify-content-md-center below-nav">
            <Alert variant="success" className="justify-content-md-center"><h1>Complimenti!</h1><br/>Prenotazione Completata!</Alert>
        </Row>      
        <Row md="auto" className="justify-content-md-center ">
            <h2>Riepilogo</h2><br/>
        </Row>   
        <Row md="auto" className="justify-content-md-center ">
            <Alert variant="info">
                Id prenotazione: <span className="summaryBooking">{`${this.state.bookingInfo.reservationId}`}<br/><br/></span>
                Auto:<span className="summaryBooking">{` ${this.state.bookingInfo.carId}`}</span><br/> Categoria:<span className="summaryBooking">{` ${this.state.category}`}<br/></span>
                Marca:<span className="summaryBooking">{` ${this.state.bookingInfo.marca}`}</span><br/> Modello: <span className="summaryBooking">{` ${this.state.bookingInfo.modello}`}<br/><br/></span>
                Dal:<span className="summaryBooking">{`  ${this.state.startDate}`}</span><br/> Al: <span className="summaryBooking">{` ${this.state.endDate}`}<br/><br/></span>
                Guidatori aggiuntivi:<span className="summaryBooking">{` ${this.state.nDrivers}`}<br/></span>
                {this.state.extraInsurance===true && <>Assicurazione Extra: <span className="summaryBooking">Sì</span></>}
            </Alert>
        </Row>
        <Row md="auto" className="justify-content-md-center ">
            <Alert variant="primary">          
            Prezzo:<span className="summaryBooking price">{` ${this.state.price.toFixed(2)}€`}<br/></span>
            </Alert>
        </Row>
        <Row md="auto" className="justify-content-md-center ">
            <Col  md="auto">
                <Link to='/home'><Alert variant="primary">Clicca qui per tornare alla home</Alert></Link>
            </Col>
            <Col md="auto">
                <Link to='/utente/storico'><Alert variant="primary">Clicca qui per accedere alle tue prenotazioni</Alert></Link>
            </Col>
        </Row> 
    </> }

    {this.state.mode==='confirm' && this.state.apiError===true &&
        <>
        <Row md="auto" className="justify-content-md-center below-nav">
            <Alert variant="danger" className="justify-content-md-center"><h1>Prenotazione annullata!</h1></Alert>
        </Row>      
        <Row md="auto" className="justify-content-md-center ">
            <Link to='/home'><Alert variant="primary">Clicca qui per tornare alla home</Alert></Link>
        </Row> 
    </> }
    </>);
    }
}

export default BookingForm;