"use strict";
const list=["hello","world","spring","easter","fre","r"];
const vect=Array.of(...list);

for(let [i,str] of vect.entries()){
if(str.length>4){
    vect[i]=str.slice(0,2)+str.slice(str.length-2,str.length);
}
else{
    if(str.length<2){
     vect[i]="";
    }
    else{
        vect[i]=str;
    }
}
}
console.log(...list);
console.log(...vect);