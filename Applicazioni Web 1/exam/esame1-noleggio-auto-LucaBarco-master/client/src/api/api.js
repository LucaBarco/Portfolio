import Auto from './auto.js'
const baseURL="/api";


async function getAllCars(){
    let url="/auto";
    let i=0;
    const response=await fetch(baseURL+url);
    const carsJson=await response.json();
    if(response.ok){
        return carsJson.map((a)=>{i++;  return new Auto(i,a.modello,a.marca,a.categoria,a.quantita)});
    }
    else{
        let err={status:response.status, errObj:carsJson};
        throw err;
    }
}

async function getUser(){
    let url="/utente";
    const response=await fetch(baseURL+url);
    const userJson=await response.json();
    if(response.ok){
        return ({id:userJson.id,nome:userJson.nome});
    }
    else{
        let err={status:response.status, errObj:userJson};
        throw err;
    }
}

async function getAvailability(params){
    
    let url="/utente/cercaAutoDisponibili";
    let query="?";
    for(let key in params){
        query+=encodeURIComponent(key)+"="+encodeURIComponent(params[key])+"&";
    }
    const response=await fetch(baseURL+url+query);
    const resJson=await response.json();
    if(response.ok){
        //console.log(resJson);
        return {number:resJson.number,price:resJson.price};
    }
    else{
        let err={status:response.status, errObj:resJson};
        throw err;
    }
}
async function deleteUserReservation(id){
    let url=`/utente/prenota/${id}`;
    return new Promise((resolve,reject)=>{
        fetch(baseURL+url,{
            method:'DELETE',
        }).then((response)=>{
            if(response.ok){
                response.json().then((info)=>{
                    resolve(info);
                })
            }
            else {
                // analyze the cause of error
                response.json()
                    .then((obj) => { obj["status"]=response.status;reject(obj); }) // error msg in the response body
                    .catch((err) => { reject({ errors: [{ param: "Application", msg: "Cannot parse server response" }] }) }); // something else
            }
        }).catch((err) => { reject({ errors: [{ param: "Server", msg: "Cannot communicate" }] }) }); // connection errors
    });
}
async function confirmUserReservation(id,params){
    
        let url=`/utente/prenota/${id}`;
        return new Promise((resolve,reject)=>{
            fetch(baseURL+url,{
                method:'PUT',
                headers:{
                    'Content-Type':'application/json',
                },
                body: JSON.stringify(params),
            }).then((response)=>{
                if(response.ok){
                    response.json().then((info)=>{
                        resolve(info);
                    })
                }
                else {
                    // analyze the cause of error
                    response.json()
                        .then((obj) => { obj["status"]=response.status;reject(obj); }) // error msg in the response body
                        .catch((err) => { reject({ errors: [{ param: "Application", msg: "Cannot parse server response" }] }) }); // something else
                }
            }).catch((err) => { reject({ errors: [{ param: "Server", msg: "Cannot communicate" }] }) }); // connection errors
        });
    
}

async function userReservation(params){
    let url="/utente/prenota";
    return new Promise((resolve,reject)=>{
        fetch(baseURL+url,{
            method:'POST',
            headers:{
                'Content-Type':'application/json',
            },
            body: JSON.stringify(params),
        }).then((response)=>{
            if(response.ok){
                response.json().then((reservationInfo)=>{
                    resolve(reservationInfo);
                })
            }
            else {
                // analyze the cause of error
                response.json()
                    .then((obj) => { obj["status"]=response.status;reject(obj); }) // error msg in the response body
                    .catch((err) => { reject({ errors: [{ param: "Application", msg: "Cannot parse server response" }] }) }); // something else
            }
        }).catch((err) => { reject({ errors: [{ param: "Server", msg: "Cannot communicate" }] }) }); // connection errors
    });

}

async function userLogin(username, password) {
    return new Promise((resolve, reject) => {
        fetch(baseURL + '/login', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({username: username, password: password}),
        }).then((response) => {
            if (response.ok) {
                response.json().then((user) => {
                    resolve(user);
                });
            } else {
                // analyze the cause of error
                response.json()
                    .then((obj) => { obj["status"]=response.status;reject(obj); }) // error msg in the response body
                    .catch((err) => { reject({ errors: [{ param: "Application", msg: "Cannot parse server response" }] }) }); // something else
            }
        }).catch((err) => { reject({ errors: [{ param: "Server", msg: "Cannot communicate" }] }) }); // connection errors
    });
}

async function userLogout() {
    return new Promise((resolve, reject) => {
        fetch(baseURL + '/logout', {
            method: 'POST',
        }).then((response) => {
            if (response.ok) {
                resolve(null);
            } else {
                // analyze the cause of error
                response.json()
                    .then((obj) => { reject(obj); }) // error msg in the response body
                    .catch((err) => { reject({ errors: [{ param: "Application", msg: "Cannot parse server response" }] }) }); // something else
            }
        });
    });
}
async function getUserBookings(){
    return new Promise((resolve,reject)=>{
        fetch(baseURL+'/utente/storico').then((response)=>{
            if(response.ok){
                response.json().then((records)=>{
                    resolve(records);
                })
            }
            else {
                // analyze the cause of error
                response.json()
                .then((obj) => { reject(obj); }) // error msg in the response body
                .catch((err) => { reject({ errors: [{ param: "Application", msg: "Cannot parse server response" }] }) }); // something else
            }
        })
    })
}

const API = { getUser,getAllCars, getAvailability,getUserBookings,userReservation,confirmUserReservation,deleteUserReservation,userLogin, userLogout} ;
export default API;