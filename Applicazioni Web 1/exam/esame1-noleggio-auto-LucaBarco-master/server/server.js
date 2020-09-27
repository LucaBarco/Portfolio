const express = require('express');
const autoDao = require('./auto_dao.js');
const userDao = require('./user_dao.js');
const paymentDao = require('./payment_dao.js');
const availabilityDao = require('./availability_dao.js');
const morgan = require('morgan');
const jwt = require('express-jwt');
const moment=require('moment');
const jsonwebtoken = require('jsonwebtoken');
const cookieParser = require('cookie-parser');

const jwtSecret = '6xvL4xkAAbG49hcXf5GIYSvkDICiUAR6EdR5dLdwW7hMzUjjMUe9t6M5kSAYxsvX';
const expireTime = 600; //seconds
// Authorization error
const authErrorObj = { errors: [{  'param': 'Server', 'msg': 'Authorization error' }] };

const PORT = 3001;

app = new express();


//set-up logging
app.use(morgan('tiny'));

//process body content
app.use(express.json());

//ogni minuto pulisce il database dalle prenotazioni pendenti
function intervalFunc() {
    console.log('Deleting pending reservations...');
    availabilityDao.deletePendentReservations().then((resp)=>{console.log(resp);}).catch((err)=>{console.log(err)});
  }
setInterval(intervalFunc, 60000);



//GET /api/auto?marca=..&categoria=...
//parametri marca e categoria sono opzionali --> una GET api/auto mostra tutte le auto

app.get('/api/auto',(req,res)=>{
    console.log(req.query);
    autoDao.getAuto(req.query).then((autos)=>{
        res.json(autos);
    })
    .catch((err)=>{
        res.status(500).json({
            errors:[{'msg':err}],
        });
    });
})

// Authentication endpoint

/**
 * POST /api/login
 * body: deve contenere username e password
 */

app.post('/api/login', (req, res) => {
    const username = req.body.username;
    const password = req.body.password;

    userDao.getUser(username)
      .then((user) => {
        console.log(user);
        if(user === undefined) {
            res.status(404).send({
                errors: [{ 'param': 'Server', 'msg': 'Invalid e-mail' }] 
              });
        } else {
            if(!userDao.checkPassword(user, password)){
                res.status(401).send({
                    errors: [{ 'param': 'Server', 'msg': 'Wrong password' }] 
                  });
            } else {
                //AUTHENTICATION SUCCESS
                const token = jsonwebtoken.sign({ user: user.id}, jwtSecret, {expiresIn: expireTime});
                res.cookie('token', token, { httpOnly: true, sameSite: true, maxAge: 1000*expireTime });
                res.json({id: user.id, nome: user.nome});
            }
        } 
      }).catch(
        // Delay response when wrong user/pass is sent to avoid fast guessing attempts
        (err) => {
            new Promise((resolve) => {setTimeout(resolve, 1000)}).then(() => res.status(401).json(authErrorObj))
        }
      );
  });

app.use(cookieParser());

app.post('/api/logout', (req, res) => {
    res.clearCookie('token').end();
});

// For the rest of the code, all APIs require authentication
app.use(
    jwt({
      secret: jwtSecret,
      getToken: req => req.cookies.token
    })
  );
  
// To return a better object in case of errors
app.use(function (err, req, res, next) {
    if (err.name === 'UnauthorizedError') {
      res.status(401).json(authErrorObj);
    }
  });
  
// AUTHENTICATED REST API endpoints

/*
*   GET /api/utente
*   check se l'utente è autenticato
*/

app.get('/api/utente', (req,res) => {
    const user = req.user && req.user.user;
    userDao.getUserById(user)
        .then((result) => {
            if(result){
            res.json({id: result.id, nome: result.nome});
            }
            else{
                res.status(401).json(authErrorObj);
            }
        }).catch(
        (err) => {
         res.status(401).json(authErrorObj);
        }
      );
});

/*
*   GET /api/utente/cercaAutoDisponibili?startDate=..&endDate=...&category=..&ageDriver&..nDrivers=..&nKm=..&extraInsurance=..
*  
*   Get delle disponibilità di auto per una richiesta di noleggio, con query
*/

app.get('/api/utente/cercaAutoDisponibili', (req,res) => {
    const user = req.user && req.user.user;
    errorList=checkQueryParams(req.query);
    if(errorList){
        console.log(errorList.errors[0].msg);
        //errore nei parametri -> ritorna bad request
        return res.status(400).json(errorList)
    }
    else{
        availabilityDao.getAvailabilities(req.query,user)
        .then((availability) => {
            console.log("number: "+availability.number+" price: "+availability.price);
            res.json({number: availability.number, price: availability.price});
        }).catch(
        (err) => {
            console.log(err);
         res.status(401).json(authErrorObj);
        }
      );
    }
});


/*
*   POST /api/utente/prenota
*   post per effettuare una prenotazione (blocco dell'auto ma ancora non pagata)
*/

app.post('/api/utente/prenota', (req, res) => {
    const user = req.user && req.user.user;
    let idBook=0;
    const params=req.body;
    //console.log(params);
    errorList=checkQueryParams(params);
    if(errorList){
        console.log(errorList.errors[0].msg);
        //errore nei parametri -> ritorna bad request
        return res.status(400).json(errorList)
    }
    else{
    
    //per bloccare la prenotazione bisogna risevare un'auto
    availabilityDao.getIdAutoForReservation(params).then((resp)=>{
        if(resp===-1){
            //non ci sono auto disponibili
            res.status(404).send({errors:[{'param':'Server','msg':'No cars available'}]});
        }
        else{
            if(resp===undefined){
                console.log('Invalid search for cars');
                res.status(404).send({
                    errors: [{ 'param': 'Server', 'msg': 'Invalid search for cars' }] 
                  });
            }
            else{
                //ho ottenuto un'auto --> inserisco la prenotazione
                auto=resp;
                availabilityDao.insertReservation(params,auto.id,user).then((result)=>{
                    
                    if(result===undefined){
                        console.log('Invalid booking insert');
                        res.status(404).send({
                            errors: [{ 'param': 'Server', 'msg': 'Invalid booking insert' }] 
                          });
                    }
                    else{
                        idBook=result;
                        res.json({carId:auto.id,reservationId:idBook,marca:auto.marca,modello:auto.modello});
                    }
                }).catch((err)=>{
                    console.log(err);
                    res.status(500).send({
                        errors: [{ 'param': 'Server', 'msg': 'error' }] 
                      });
                })
            }
        }
    }).catch((err)=>{
        console.log(err); 
        res.status(500).send({
            errors: [{ 'param': 'Server', 'msg': 'error' }] 
          });}
    );} });

/*
*   DELETE /api/utente/prenota/:id
*   rimuove una prenotazione
*/ 

app.delete('/api/utente/prenota/:id',(req,res)=>{
    availabilityDao.deleteReservation(req.params.id).then((resp)=>{
        res.json(resp);
    }).catch((err)=>{
        console.log(err);
        res.status(500).send({
            errors: [{ 'param': 'Server', 'msg': 'error' }] 
          });
    });
});

/*
*   PUT /api/utente/prenota/:id
*   effettua il pagamento e conferma il noleggio
*/

app.put('/api/utente/prenota/:id',(req,res)=>{
    const params=req.body;
    paymentDao.pay(params).then((result)=>{
       if(result.payment==='ok'){
           console.log(result);
        availabilityDao.confirmReservation(req.params.id).then((resp)=>{
            res.json(resp);
        }).catch((err)=>{
            console.log(err);
            res.status(500).send({
                errors: [{ 'param': 'Server', 'msg': 'error' }] 
              });
        });
       }
    }).catch((err)=>{
        console.log(err);
        res.status(400).send({
            errors: [{ 'param': 'Server', 'msg': 'Invalid credit card data' }] 
          });
    })
});

/*  GET api/utente/storico
*   restituisce le prenotazioni per quell'utente
*/

app.get('/api/utente/storico', (req,res) => {
    const user = req.user && req.user.user;
    userDao.getUserBookings(user)
        .then((bookings) => {
            res.json(bookings);
        }).catch(
        (err) => {
            console.log(err);
         res.status(500).send({errors: [{ 'param': 'Server', 'msg': 'error' }] });
        }
      );
});

/*
*   funzione per validazione campi della query lato server
*/

checkQueryParams=(params)=>{
    let errorList=[];
    let categories=['A','B','C','D','E'];
    //check se sono definiti tutti i campi indispensabili per cercare disponibilità di noleggio
    if(params.startDate && params.endDate && params.category && params.nKm && params.nDrivers && params.extraInsurance!==undefined && params.ageDriver){
        if(moment(params.startDate).isBefore(moment())){
            errorList.push("Incorrect start date field: it cannot precede the current day");
        }
        if(moment(params.endDate).isBefore(moment(params.startDate))){
            errorList.push("Incorrect date interval");
        }
        if(!categories.includes(params.category)){
            errorList.push("Incorrect category field");
        }
        if((parseInt(params.nKm)<1 || parseInt(params.nKm)>=4)){
            //check se nKm è 1(meno di 50/day),2(tra 50/day e 150/day),3(più di 150/day)
            errorList.push("Incorrect kilometers");
        }
        if((parseInt(params.nDrivers)<0||parseInt(params.nDrivers)>=5)){
            //il numero di extra driver non può essere negativo o maggiore di 4
            errorList.push("Incorrect number of drivers field");
        }
        if(!(params.extraInsurance || !params.extraInsurance)){
            errorList.push("Incorrect extra insurance field");
        }
        if((parseInt(params.ageDriver)<1 || parseInt(params.ageDriver)>3)){
            //check se ageDriver è 1 (meno di 25) ,2 (tra 25 e 65 anni) e 3 (più di 65 anni) 
            errorList.push("Incorrect ageDriver field");
        }
    }
    else{
        console.log("parameters missing");
        errorList.push("parameters missing");
    }
    if(errorList.length>0){
        return {
            errors: [{ 'param': 'Server', 'msg': errorList }] 
          };
    }
    else{
        return null;
    }
}

//activate server
app.listen(PORT, ()=>console.log(`Server running on http://localhost:${PORT}/`));


