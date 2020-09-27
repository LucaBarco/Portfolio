'use strict';

const User = require('./user');
const db = require('./db');
const bcrypt = require('bcrypt');

/**
 * Function to create a User object from a row of the users table
 * @param {*} row a row of the users table
 */

const createUser = function (row) {
    const id = row.id;
    const nome = row.nome;
    const username = row.username;
    const hash = row.password;
   
    return new User(id, nome, username, hash);
}

//getUser by username
exports.getUser = function (username) {
    return new Promise((resolve, reject) => {
        const sql = "SELECT * FROM utente WHERE username = ?"
        db.all(sql, [username], (err, rows) => {
            if (err) 
                reject(err);
            else if (rows.length === 0)
                resolve(undefined);
            else{
                const user = createUser(rows[0]);
                resolve(user);
            }
        });
    });
  };

//getUser by id
exports.getUserById = function (id) {
    return new Promise((resolve, reject) => {
        const sql = "SELECT * FROM utente WHERE id = ?"
        db.all(sql, [id], (err, rows) => {
            if (err) 
                reject(err);
            else if (rows.length === 0)
                resolve(undefined);
            else{
                const user = createUser(rows[0]);
                resolve(user);
            }
        });
    });
  };

//check password (check degli hash)
exports.checkPassword = function(user, password){
    console.log("hash of: " + password);
    let hash = bcrypt.hashSync(password, 10);
    console.log(hash);
    console.log("DONE");

    return bcrypt.compareSync(password, user.hash);
}

//get dell'elenco delle prenotazioni dell'utente
exports.getUserBookings=function(user){
    return new Promise((resolve,reject)=>{
        const sql=`
        SELECT noleggio.id as id,
            noleggio.id_auto as id_auto,
            noleggio.id_utente as id_utente,
            noleggio.nGuidatori as nDrivers,
            noleggio.kmStimati as nKm,
            noleggio.assicurazioneExtra as extraInsurance,
            noleggio.data_inizio as startDate,
            noleggio.data_fine as endDate,
            noleggio.prezzo as price,
            automobile.marca as marca,
            automobile.modello as modello,
            automobile.categoria as categoria
            FROM noleggio,automobile 
            WHERE noleggio.id_auto=automobile.id AND id_utente=? AND pagato=1
        `
        db.all(sql,[user],(err,rows)=>{
            if (err) {
                reject(err);
            }
            else{
                resolve(rows);
            }
        });
    });
}