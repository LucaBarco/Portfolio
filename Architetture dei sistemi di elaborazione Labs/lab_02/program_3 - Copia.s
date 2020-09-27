.data
v: .byte 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3
even_counter: .space 1
odd_counter: .space 1

.text
daddi R1,R0,0 ;                           FDEMW +5                                  indice vettore
daddi R2,R0,30 ;                           FDEMW +1                                 per ciclo
daddi R7,R0,0 ;ones counter                 FDEMW +1                                ones counter
daddi R9,R0,0 ;odd_counter                    FDEMW +1 =9+                          odd counter
loop: lb R3,v(R1) ;                            FDEMW (+1                            load di v(i)
      daddi R1,R1,1 ;                           FDEMW +1                            incremento indice i
      lb R4,v(R1) ;                              FDEMW +1                           load di v(i+1)
      daddi R7,R0,0 ;                             FDEMW +1                          inizializzo contatore di 1
      and R5,R3,R4 ;                               FDEMW +1 =5                      and tra v(i) e v(i+1)    
      cic: andi R6,R5,1 ;                           FDEMW (+1                       and del risultato con 1 --> se 1 ho un uno, altrimenti no
           dadd R7,R7,R6 ;                           FDEMW +1                       sommo il risultato della and al contatore di 1 (no condizioni)
           dsrl R5,R5,1 ;                              FDEMW +1                     salto a dx di un bit del risultato della prima and
           bnez R5,cic ;                                FDEMW +1 +1*)=5*8=40+       cond. per ciclo sul byte (R5==0 significa che ho finito di testare i bit a 1)
      andi R6,R7,1 ;                                     FDEMW +1                   and tra contatore di 1 e 1 per capire se pari o dispari
      dadd R9,R9,R6 ;                                     FDEMW +1                  sommo il risultato della and al contatore odd (no condizioni)
     bne R1,R2,loop ;                                      FDEMW +1 +1*)=4 +        cond. per ciclo esterno
     daddi R2,R2,-1 ;                                       FDEMW +1
     dsub R8,R2,R9 ;                                         FDEMW +1               calcolo contatore even come differenza tra il numero di valori e il numero di odd
sb R9, odd_counter(R0) ;                                      FDEMW +1              salvo nelle variabili
sb R8, even_counter(R0) ;                                      FDEMW +1
halt ;                                                          FDEMW +1 =5)=9+(5+40+4)*30+5=1484 --> DA EXEC 510

;shift a dx --> faccio AND con 1 per vedere se ottengo un numero pari o dispari--> se ottengo 0 salto, altrimenti incremento contatore
; in pratica testo sempre l'ultimo bit del byte per 8 volte facendolo shiftare 
;* : (IL +1 EXTRA E' DOVUTO AL FETCH IN PIU' PER LA VALUTAZIONE DEL BRANCH SENZA ATTIVAZIONE DEL BRANCH DELAY SLOT)