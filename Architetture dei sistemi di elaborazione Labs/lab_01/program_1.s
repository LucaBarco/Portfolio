.data
a: .byte 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50
b: .byte 51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100
c: .space 50
max: .space 1
min: .space 1
.text

daddui r1,r0,0                  ;   indice per a,b,c
daddui r8,r0,50                 ;   valore di confronto per fine del ciclo
daddui r6,r0,255                ;   registro per min
daddui r7,r0,0                  ;   registro per max
cic: lbu r2,a(r1)               ;   carico nei registri i valori di a e b
      lbu r3,b(r1)
      dadd r4,r2,r3             ;   li sommo
      sb r4,c(r1)               ;   salvo in c
      sltu r5,r4,r6             ;   controllo per il max 
      beq r5,r0,verificamax
      nop                       ; NOP aggiunta per garantire risultato corretto nell'esecuzione con delay slot attivato
      dadd r6,r0,r4
verificamax: sltu r5,r7,r4      ;   controllo per il min
      beq r5,r0,next
      dadd r7,r0,r4
next: daddui r1,r1,1
      bne r1,r8,cic             ;   condizione per il ciclo
sb r6,min(r0)
sb r7,max(r0)
block: j block

    