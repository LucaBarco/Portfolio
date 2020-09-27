'use strict';
const db=require('./db');
const createNewAuto= function(row){
    return ({id:row.id,modello:row.modello,marca:row.marca,categoria:row.categoria,quantita:row.quantita});
}

/*
GET tutte le auto disponibili 
 se sono definiti i parametri marca e modello, le auto vengono filtrate
*/
exports.getAuto=function(params){
    return new Promise((resolve,reject)=>{
       // const sql="SELECT * FROM automobile";
       const sql="SELECT DISTINCT modello,marca,categoria,COUNT(*) as quantita FROM automobile GROUP BY modello,marca,categoria";
        db.all(sql,[],(err,rows)=>{
            if(err){
                reject(err);
            }
            else{
                let autoList=rows.map((row)=>createNewAuto(row));
               // console.log(autoList);
                if(params.marca){
                    autoList=autoList.filter((auto)=>auto.marca===params.marca);
                }
                if(params.categoria){
                    autoList=autoList.filter((auto)=>auto.categoria===params.categoria);
                }
                resolve(autoList);
            }
        });
    })
}
