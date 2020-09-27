'use strict';
/**
 *      Check: 
 *          Numero carta: value.trim().match(/\b\d{16}\b/g)
 *          Numero CVV: value.trim().match(/\b\d{3}\b/g)
 */
exports.pay=function(params){
    return new Promise((resolve,reject)=>{
        //check parametri --> verifico che esistano i campi di pagamento e che siano del formato corretto
    if(!params.name || !params.number.trim().match(/\b\d{16}\b/g)||!params.CVV.trim().match(/\b\d{3}\b/g)){
        //error
        reject({error:'invalid parameters'});
    }
    else{
        resolve({payment:'ok'});
    }
    });
}
