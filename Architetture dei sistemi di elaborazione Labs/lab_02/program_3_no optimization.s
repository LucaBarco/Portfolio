.data
v: .byte 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
even_counter: .space 1
odd_counter: .space 1

.text
daddi R1,R0,0 ;                           FDEMW +5
daddi R2,R0,30 ;                           FDEMW +1
daddi R7,R0,0 ;ones counter                 FDEMW +1
daddi R8,R0,0 ;even counter                  FDEMW +1
daddi R9,R0,0 ;odd_counter                    FDEMW +1 =9+
loop: lb R3,v(R1) ;                            FDEMW (+1
      daddi R1,R1,1 ;                           FDEMW +1
      lb R4,v(R1) ;                              FDEMW +1
      daddi R7,R0,0 ;                             FDEMW +1
      and R5,R3,R4 ;                               FDEMW +1
      daddi R10,R0,8 ;                              FDEMW +1=6+
      cic: andi R6,R5,1 ;                            FDEMW (+1
           beqz R6,next ;                             FDSEMW +2 STALLO RAW
           daddi R7,R7,1 ;                              FDEMW +1 +1 *
           next: daddi R10,R10,-1 ;                      FDEMW +1
                 dsrl R5,R5,1 ;                           FDEMW +1
                 bnez R10,cic ;                            FDEMW +1 +1*)=9*8=72+
      andi R6,R7,1 ;                                        FDEMW +1
      bnez R6,odd ;                                          FDSEMW +2 STALLO RAW
      daddi R8,R8,1 ;                                          FDEMW +1 +1 *
      j ctrl ;                                                  FDEMW +1
      odd: daddi R9,R9,1 ;                                       FDEMW +1 +1 *
      ctrl: bne R1,R2,loop ;                                      FDEMW +1 +1*)=10+
sb R8, even_counter(R0) ;                                          FDEMW +1
sb R9, odd_counter(R0) ;                                            FDEMW +1
halt ;                                                               FDEMW +1 =3)=9+(6+72+10)*30+3=2652 --> DA EXEC 2561

;shift a dx --> faccio AND con 1 per vedere se ottengo un numero pari o dispari--> se ottengo 0 salto, altrimenti incremento contatore

;* : (IL +1 EXTRA E' DOVUTO AL FETCH IN PIU' PER LA VALUTAZIONE DEL BRANCH SENZA ATTIVAZIONE DEL BRANCH DELAY SLOT)