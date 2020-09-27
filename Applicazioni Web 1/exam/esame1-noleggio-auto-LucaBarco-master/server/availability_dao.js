'use strict';
const moment=require('moment');
const db = require('./db');

//funzione per cercare numero  di auto disponibili e prezzo
exports.getAvailabilities=function(params,user){
    return new Promise((resolve,reject)=>{
        const sql=`
        SELECT COUNT(id) as autoDisponibili
        FROM automobile
        WHERE categoria=? AND id NOT IN( 
        SELECT id_auto
        FROM noleggio
        WHERE categoria=?
        AND ((data_inizio<=datetime(?) AND data_fine>=datetime(?))
        OR (data_inizio>=datetime(?) AND data_fine<=datetime(?))
        OR(data_inizio<=datetime(?) AND data_fine>=datetime(?))
        OR(data_inizio<=datetime(?) AND data_fine>=datetime(?))
))`
        
        db.all(sql,[params.category,params.category,params.startDate,params.startDate,params.startDate,params.endDate,params.startDate,params.endDate,params.endDate,params.endDate],(err,rows)=>{
            if(err){
                reject(err);
            }
            else{
                let carNumber=rows[0].autoDisponibili;
                //calcolo prezzo
                params["carNumber"]=carNumber;
                calculatePrice(params,user).then((price)=>{
                resolve({number:carNumber,price:price});}).catch((err)=>{reject(err);});
            
            }
        })
    })
}


//funzione per il calcolo del prezzo
const calculatePrice=(params,user)=>{
    return new Promise((resolve,reject)=>{
    console.log(params);
    let dailyPrices={"A":80,"B":70,"C":60,"D":50,"E":40};
    let basePrice=dailyPrices[params.category];
    console.log("base: "+basePrice);
    let price=basePrice*moment(params.endDate).diff(moment(params.startDate),'days');
    console.log("prezzo per tutti i giorni: "+price);
    switch(parseInt(params.nKm)){
        //di default si suppone che non si alzi/abbassi il prezzo
        case 1:
            //meno di 50km/giorno
            price=price*(1-0.05);
            console.log("sconto 5% km<50/giorno: "+price);
        break;
        case 3:
            //più di 150km/giorno
            price=price*(1+0.05);
            console.log("aumento 5% km>150/giorno: "+price);
            break;
    }
    switch(parseInt(params.ageDriver)){
        case 1:
            price=price*(1+0.05);
            console.log("aumento 5% età guidatore <25 anni: "+price);
            break;
        case 3:
            price=price*(1+0.1);
            console.log("aumento 10% età guidatore >65 anni: "+price);
            break;
    }
    if(parseInt(params.nDrivers)>0){
        price=price*(1+0.15);
        console.log("aumento 15% numero di guidatori: "+price);
    }
    if(params.extraInsurance==="true"){
        price=price*(1+0.2);
        console.log("aumento 20% assicurazione extra: "+price);
    }
    
    getTotVehicles(params.category).then( (totCarNumber)=>{
        //+10% se meno del 10% dei veicoli rimasti
        console.log(params.carNumber)
        if(params.carNumber<=0.1*totCarNumber){
        price=price*(1+0.1);
        console.log("Aumento 10% per poca disponibilità: "+price);
        }
         //-10% se cliente frequente
        getUserBooks(user).then((nBooks)=>{
        if(nBooks>=3){
            price=price*(1-0.1);
            console.log("sconto 10% per utente frequente: "+price);
        }
        console.log("prezzo totale: "+price);
        resolve(price);
        }).catch((err)=>{reject(err);console.log(err);});
    }).catch((err)=>{
        console.log(err);
        reject(err);
    });  
});
}

//funzione per calcolare il tot numero di auto di una certa categoria
const getTotVehicles=(category)=>{
    return new Promise((resolve,reject)=>{
        const sql=`
        SELECT COUNT(id) as autoDisponibili
        FROM automobile
        WHERE categoria=?`
        
        db.all(sql,[category],(err,rows)=>{
            if(err){
                reject(err);
            }
            else{
                //console.log(rows[0]);
                let carNumber=rows[0].autoDisponibili;
                //console.log(carNumber);
               
                resolve(carNumber);
            }
        })
    })
}

//funzione per calcolare il tot numero di prenotazioni dell'utente 
const getUserBooks=(user)=>{
    return new Promise((resolve,reject)=>{
        const sql=`
        SELECT COUNT(*) as nPrenotazioni
        FROM noleggio
        WHERE id_utente=? AND data_fine<datetime(?)`
        
        db.all(sql,[user,moment().format("yyyy-MM-DD")],(err,rows)=>{
            if(err){
                reject(err);
            }
            else{
                //console.log(rows[0]);
                let booksNumber=rows[0].nPrenotazioni;
                //console.log(booksNumber);
                resolve(booksNumber);
            }
        })
    })
}

//funzione per selezionare una specifica auto per una prenotazione
exports.getIdAutoForReservation=(params)=>{
    return new Promise((resolve,reject)=>{
        const sql=`
        SELECT id,marca,modello
        FROM automobile
        WHERE categoria=? AND id NOT IN( 
        SELECT id_auto
        FROM noleggio
        WHERE categoria=?
        AND ((data_inizio<=datetime(?) AND data_fine>=datetime(?))
        OR (data_inizio>=datetime(?) AND data_fine<=datetime(?))
        OR(data_inizio<=datetime(?) AND data_fine>=datetime(?))
        OR(data_inizio<=datetime(?) AND data_fine>=datetime(?))
))`
        
        db.all(sql,[params.category,params.category,params.startDate,params.startDate,params.startDate,params.endDate,params.startDate,params.endDate,params.endDate,params.endDate],(err,rows)=>{
            if(err){
                reject(err);
            }
            else{
                if(rows.length>0){
                //console.log(rows);
                let idAuto=rows[0];
                //console.log(idAuto); 
                resolve(idAuto);
                
                }
                else{
                    //id -1 per dire che non esistono auto disponibili
                    resolve(-1);
                }
            }
        });
    });
}

//funzione per inserire una PRENOTAZIONE (richiesta di noleggio, ancora non pagato)
exports.insertReservation=(params,carId,user)=>{
    //insert in tab noleggio with pagato=0 (false)
    return new Promise((resolve,reject)=>{
        let actualDate=new Date();
        let actualTime=actualDate.getTime(); //serve per inserire il timestamp attuale in modo tale che la funzione del setInterval possa cancellare le prenotazioni vecchie e non pagate
        const sql=`
    INSERT INTO noleggio(id_auto,id_utente,data_inizio,data_fine,nGuidatori,etaGuidatori,kmStimati,assicurazioneExtra,prezzo,pagato,timestamp)
    VALUES(?,?,?,?,?,?,?,?,?,0,?)
    `;
    this.getAvailabilities(params,user).then((results)=>{
    let price=results.price.toFixed(2);
    console.log("insert new reservation...");
    console.log(params);
    console.log("car id: "+carId);
    console.log("user: "+user);
    console.log("price: "+price);
    db.run(sql,[carId,user,params.startDate,params.endDate,params.nDrivers,params.ageDriver,params.nKm,params.extraInsurance,price,actualTime],function(err){
        if(err){
            reject(err);
        }
        else {
            //this.lastID è l'id del record appena inserito
            console.log("reservation correctly inserted: "+this.lastID);
            resolve(this.lastID);
        }
    });
    }).catch((err)=>{reject(err);});
});
}


//funzione per rimuovere una prenotazione con uno specifico id
exports.deleteReservation=(id)=>{
    return new Promise((resolve,reject)=>{
    const sql=`
    DELETE FROM noleggio WHERE id=? 
    `;
    db.run(sql,[id],(err)=>{
        if(err){
            reject(err);
        }
        else{
            resolve({result:'deleted'})
        }
    })
});
}

//funzione per confermare una richiesta di noleggio (già presente nel database)
exports.confirmReservation=(id)=>{
    return new Promise((resolve,reject)=>{
    const sql=`
    UPDATE noleggio SET pagato=1 WHERE id=? AND pagato=0 
    `;
    db.run(sql,[id],(err)=>{
        if(err){
            reject(err);
        }
        else{
            resolve({result:'ok'})
        }
    })
});
}

//funzione per eliminare le richieste di noleggio non pagate più vecchie di 10 minuti
exports.deletePendentReservations=function(){
    return new Promise((resolve,reject)=>{
        const interval=600000; //millisecondi per cui il timestamp non è più valido
        let actualDate=new Date();
        let actualTime=actualDate.getTime();
        const sql=`DELETE FROM noleggio WHERE pagato=0 AND timestamp<=?`;
        db.run(sql,[actualTime-interval],(err)=>{
            if(err){
                console.log(err);
                reject(err);
            }
            else{
                resolve({result:'ok'});
            }
        });
    });
}