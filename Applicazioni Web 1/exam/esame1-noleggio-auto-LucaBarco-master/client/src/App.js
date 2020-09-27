import React from 'react';
import './App.css';
import Header from './components/Header';
import CarList from './components/CarList.js';
import Filters from './components/Filters.js';
import LoginForm from './components/LoginForm.js';
import BookingForm from './components/BookingForm.js';
import BookingList from './components/BookingList.js';
import API from './api/api.js';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';
import Container from 'react-bootstrap/Container';
import Spinner from 'react-bootstrap/Spinner';
import Alert from 'react-bootstrap/Alert';
import {Switch} from 'react-router';
import {withRouter,Redirect, Route} from 'react-router-dom';


class App extends React.Component{

  constructor(props)  {
    super(props);
    /**
     * VARIABILI STATO
     * cars   :   elenco auto da mostrare
     * carProducers :   elenco produttori di auto
     * unfilteredCars : copia di backup contenente tutte le auto
     * checkedCategory: elenco di filtri da applicare alle categorie
     * checkedProducer: elenco di filtri da applicare ai produttori
     * loggedUser     : null se utente non autenticato, 
     * authErr        : null se no ho 401,
     * serverErr      : true se ho errori nel dialogare con il server
     * 
     * 
     * FUNZIONI
     * 
     * TOGGLE 
     *    toggleCategoryFilter : gestiscono aggiunta/rimozione di un filtro 
     *    toggleProducerFilter : gestiscono aggiunta/rimozione di un filtro
     *      -> se il filtro passato come parametro esiste nella lista lo elimino, altrimenti lo aggiungo
     * APPLY
     *  applyCategoryFilter : applica l'elenco di filtri passato come parametro
     *  applyProducerFIlter : applica l'elenco di filtri passato come parametro
     *      -> riescono a gestire i casi particolari di unione tra filtri dello stesso tipo e intersezione tra filtri di tipo diverso 
     * 
     * signalTokenIsExpired :   segnala che utente non è autenticato
     * getUser :  check se utente è autenticato
     * handleErrors : gestione errore se non sono autenticato
     * 
     */ 

    this.state = {cars: [], carProducers:[],unfilteredCars:[],checkedCategory:[],checkedProducer:[],loggedUser:null, authErr:null,serverErr:false};
    this.toggleCategoryFilter=this.toggleCategoryFilter.bind(this);
    this.toggleProducerFilter=this.toggleProducerFilter.bind(this);
    this.signalTokenIsExpired=this.signalTokenIsExpired.bind(this);
    this.login=this.login.bind(this);
    this.login=this.login.bind(this);
    this.getUser=this.getUser.bind(this);
    this.resetCarList=this.resetCarList.bind(this);
  }

  componentDidMount(){
    this.setState({isLoading:true});
    this.getUser();
    API.getAllCars().then((cars)=>{
      //ordinamento dell'elenco per la visualizzazione ordinata per categoria e marca
      cars.sort((e1,e2)=>{
        if(e1.categoria>e2.categoria){
          return true;
        }
        else{
          if(e1.categoria===e2.categoria && e1.marca>e2.marca)
          {return true;}
        return false;
        }
      });
      this.setState({cars:cars,unfilteredCars:cars,isLoading:false,serverErr:false});
      this.getCarProducer();
    }).catch((err)=>{
      this.setState({serverErr:true});
    });
  }
  resetCarList(){
    //funzione per resettare i filtri e la lista di auto una volta usciti dalla hompage (richiamata nel component will unmount del componente Filters)
    this.setState({cars:this.state.unfilteredCars,checkedCategory:[],checkedProducer:[]});
  }
  handleErrors=(err)=> {
    console.log(err.status);
    if (err) {
          this.setState({authErr: err.status});
          this.props.history.push("/login");
    }
  }

  login=(username,password)=>{
    API.userLogin(username,password).then(
      (user)=>{
        this.setState({loggedUser:user,authErr:null});
        
      }
      ).catch((errorObj) => {
        this.handleErrors(errorObj);
    });
  }

  logout = () => {
    API.userLogout().then(() => {
      this.setState({loggedUser: null,authErr: null});
    });
  }

  signalTokenIsExpired(){
    //segnala che il token per l'utente loggato è scaduto
    this.setState({loggedUser:null});
  }

  getUser(){
    //check se utente è autenticato
    API.getUser().then((res)=>{
      this.setState({loggedUser:res,authErr:null});
    }).catch((err)=>{
      if(err.status===401){
        this.setState({loggedUser:null});
      }
    });
  }

  getCarProducer=()=>{
    //estraggo i nomi dei produttori delle auto
    let producers=this.state.cars.map((a)=>a.marca).filter((m,index,array)=>array.indexOf(m)===index);
    producers.sort();
    this.setState({carProducers:producers});
  }

  /*
  Funzioni toggle: gestiscono l'aggiunta o la rimozione di un filtro
  Funzioni apply: applicano l'elenco di filtri
  */ 

  toggleCategoryFilter=(filter)=>{
    let filters=this.state.checkedCategory;
    //if filtro non presente -> lo inserisco nella lista dei filtri
    if(!filters.includes(filter)){
        filters.push(filter);
    }
    else{
      //lo rimuovo
        filters.splice(filters.indexOf(filter),1);
    }
    //se nuovo elenco di filtri è vuoto:
    // se anche l'altro è vuoto: resetto cars alla versione integrale con tutte le auto, altrimenti applico alto filtro
    //se invece il nuovo elenco di filtri non è vuoto, applico la funzione di applicazione dei filtri
    if(filters.length===0){
      if(this.state.checkedProducer.length===0){
        this.setState({cars:this.state.unfilteredCars});
      }
      else{
      this.applyProducerFilter(this.state.checkedProducer);
      }
    }
    else{
    this.applyCategoryFilter(filters);
    }
  }

  toggleProducerFilter=(filter)=>{
    let filters=this.state.checkedProducer;
    //if filtro non presente -> lo inserisco nella lista dei filtri
    if(!filters.includes(filter)){
        filters.push(filter);
    }
    else{
        filters.splice(filters.indexOf(filter),1);
    }
    //se nuovo elenco di filtri è vuoto:
    // se anche l'altro è vuoto: resetto cars alla versione integrale con tutte le auto, altrimenti applico altro filtro
    //se invece il nuovo elenco di filtri non è vuoto, applico la funzione di applicazione dei filtri
    if(filters.length===0){
      if(this.state.checkedCategory.length===0){
        this.setState({cars:this.state.unfilteredCars});
      }
      else{
      this.applyCategoryFilter(this.state.checkedCategory);
      }
    }
    else{
    this.applyProducerFilter(filters);
    }
    
  }

  applyCategoryFilter=(filters)=>{
    let filtered=this.state.unfilteredCars;
    if(this.state.checkedProducer.length!==0){
      filtered=filtered.filter((e)=>{
        if(this.state.checkedProducer.includes(e.marca)){
          return true;
        }
        return false;
      });
    }
    this.setState({checkedCategory:filters,cars:filtered.filter((e)=>{
      if(filters.includes(e.categoria)){
        return true;
      }
      return false;
    })});
  }

  applyProducerFilter=(filters)=>{
    let filtered=this.state.unfilteredCars;
    if(this.state.checkedCategory.length!==0){
      filtered=filtered.filter((e)=>{
        if(this.state.checkedCategory.includes(e.categoria)){
          return true;
        }
        return false;
      });
    }
    this.setState({checkedProducer:filters,cars:filtered.filter((e)=>{
      if(filters.includes(e.marca)){
        return true;
      }
      return false;
    })});
  }




  render(){
    return (
    <>
      <Header loggedUser={this.state.loggedUser} logout={this.logout} path={this.props.location.pathname}/>
      
        
      <Container fluid >
      <Switch>
        <Route exact path='/home'>
            <Row className="vheight-100">
              <Col sm={3} className="below-nav ustify-content-md-center">
              <Filters carProducers={this.state.carProducers}  toggleCategoryFilter={this.toggleCategoryFilter} toggleProducerFilter={this.toggleProducerFilter} resetCarList={this.resetCarList}/>
              </Col>
            <Col sm={9} className="below-nav ustify-content-md-center ">
          <CarList cars={this.state.cars} isLoading={this.state.isLoading}/>
          </Col>
          </Row>
      </Route>
      <Route exact path='/login'>
      {this.state.loggedUser!==null && <Redirect to='/utente/storico'/>}
      <LoginForm  loginMethod={this.login} authErr={this.state.authErr} />
      </Route>
      <Route exact path='/utente/prenota'>
      {this.state.loggedUser===null && <Redirect to='/login'/>}
      <BookingForm getUser={this.getUser} getAvailability={API.getAvailability} insertReservation={API.userReservation} deleteReservation={API.deleteUserReservation} confirmReservation={API.confirmUserReservation} signalTokenIsExpired={this.signalTokenIsExpired}/>
      </Route>
      <Route exact path='/utente/storico'>
        {(!this.state.isLoading===undefined || this.state.isLoading===true) &&  <Alert variant="primary" className="below-nav"><Spinner animation="border" variant="primary"/> Caricamento in corso ...</Alert>}
      { this.state.isLoading===false && this.state.loggedUser===null && <Redirect to='/login'/>}
      {this.state.loggedUser!==null &&
      <BookingList loggedUser={this.state.loggedUser} getUserBookings={API.getUserBookings} signalTokenIsExpired={this.signalTokenIsExpired} deleteUserReservation={API.deleteUserReservation}/>}
       </Route>

      <Route><Redirect to='/home'/></Route>
      </Switch>
      </Container>
      
     </> 
    )
  }
}

export default withRouter(App);