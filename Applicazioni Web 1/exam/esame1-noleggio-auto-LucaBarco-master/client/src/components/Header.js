import React from 'react';
import Navbar from 'react-bootstrap/Navbar'
import Nav from 'react-bootstrap/Nav'
import {Link} from 'react-router-dom'

//funzione per renderizzare header -> se sono loggato mostro link per storico e nuova prenotazione
//viene passato il path corrente per poter visualizzare correttamente l'opzione di nuova prenotazione o di accesso allo storico senza renderle ridondanti
const Header=(props)=>{
    return(
      <Navbar bg="primary" variant="dark"  expand="sm" fixed="top" >
          <Navbar.Brand >
              <Link to='/home' className="headerLinks ">
                  <img src="../svg/car2.png" alt=""  width="42" className="d-inline-block align-top"/>
                  AutoNoleggio
              </Link>  
          </Navbar.Brand>
          
          <Navbar.Toggle aria-controls="basic-navbar-nav" />
  
          <Navbar.Collapse id="basic-navbar-nav">
              <Nav className="ml-md-auto">   
                {props.loggedUser===null && 
                    <>
                      <Link to='/login' className="headerLinks">Login</Link>
                    </>
                }
                {props.loggedUser!==null &&
                    <>  
                      <Link to='/home' className="headerLinks " onClick={props.logout}>Logout </Link>
                      {props.path!=='/utente/storico' && <Link to='/utente/storico' className="headerLinks ">Area personale</Link>}
                      {props.path!=='/utente/prenota' && <Link to='/utente/prenota' className="headerLinks ">Nuovo Noleggio</Link>}
                      <span  className="headerUsername ">{`Ciao, ${props.loggedUser.nome}!`} </span>
                    </>}
              </Nav>
        </Navbar.Collapse>
      </Navbar>
);}

export default Header;