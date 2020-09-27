.data
v1: .double 1.27, 5.26, 6.75, 3.04, 1.73, 8.05, 6.19, 5.52, 6.39, 6.44, 2.54, 3.84, 6.85, 7.62, 3.97, 7.57, 5.26, 2.68, 4.04, 6.50, 7.59, 5.41, 6.83, 8.46, 3.65, 1.12, 4.33, 0.35, 0.49, 5.82
v2: .double 1.63, 5.02, 9.65, 9.85, 2.56, 2.79, 2.57, 2.40, 8.62, 0.46, 7.10, 8.92, 7.31, 2.81, 9.76, 5.84, 2.60, 5.34, 2.50, 2.25, 6.75, 6.71, 2.43, 8.88, 7.47, 0.77, 3.80, 7.41, 3.73, 5.73
v3: .double 9.84, 0.60, 7.72, 4.33, 9.85, 4.37, 0.78, 8.72, 8.16, 7.49, 4.36, 3.31, 3.46, 2.12, 3.06, 5.22, 3.92, 2.61, 2.53, 0.55, 7.66, 0.14, 4.40, 7.87, 9.59, 9.18, 9.22, 7.79, 7.07, 6.16
v4: .double 6.37, 9.92, 4.71, 2.35, 2.41, 2.50, 7.17, 3.93, 5.34, 2.95, 2.23, 3.26, 9.67, 4.76, 4.03, 5.79, 6.68, 2.70, 7.93, 3.46, 4.80, 1.55, 1.99, 0.60, 9.27, 7.92, 4.05, 2.57, 7.64, 8.55
v5: .space 240 ;    30*8 bytes
v6: .space 240 ;    30*8 bytes

.text

daddui R1,R0,0 ;                        FDEMW                                                                 +5
daddui R2,R0,8 ;                         FDEMW                                                                +1
daddui R3,R0,16 ;                         FDEMW                                                               +1
daddui R4,R0,240 ;                         FDEMW                                                              +1
loop: 

      l.d F1, v1(R1) ;1                      FDEMW                                                            +1
      l.d F2, v2(R1) ;1                       FDEMW                                                           +1
      l.d F3, v3(R1) ;1                        FDEMW                                                          +1
      mul.d F8,F1,F2 ;1                         FDEEEEEEEEMW                                                  +8
      l.d F4, v4(R1) ;1                          FDEMW
      l.d F7, v3(R1) ;1                           FDEMW
      mul.d F9,F3,F4 ;1                            FDEEEEEEEEMW                                                +3
      l.d F10, v1(R2) ;2                            FDEMW
      l.d F11, v2(R2) ;2                             FDEMW
      add.d F5,F8,F7 ;1                               FD--EEEEMW                                               +1                                      
      l.d F12, v3(R2) ;2                               FDE-MW
      l.d F13, v4(R2) ;2                                FD-EMW                                        
      l.d F16, v3(R2) ;2                                 F-DE--MW                                              +1
      div.d F6,F9,F5 ;1                                    FD-EEEEEEEEEEEEMW                                   +11
      mul.d F17,F10,F11 ;2                                  FDEEEEEEEEMW
      mul.d F18,F12,F13 ;2                                    FDEEEEEEEEMW
      l.d F19, v1(R3) ;3                                       FDEMW                                      
      l.d F20, v2(R3) ;3                                        FDEMW                                    
      s.d F5,v5(R1) ;1                                           FDEMW
      l.d F21, v3(R3) ;3                                          FDEMW
      l.d F22, v4(R3) ;3                                           FDEMW
      mul.d F26,F19,F20 ;3                                          FDEEEEEEEEMW                                +3
      mul.d F27,F21,F22 ;3                                           FDEEEEEEEEMW                               +1
      l.d F25, v3(R3) ;3                                              FDEMW
      add.d F14,F17,F16 ;2                                             FDEEEEMW
      s.d F6,v6(R1) ;1                                                  FDEMW
      daddui R1,R1,24;1                                                  FD-E---MW                              +1
      div.d F15,F18,F14 ;2                                                FD-EEEEEEEEEEEEMW                     +9
      add.d F23,F26,F25 ;3                                                 F-DEEEEMW
      s.d F14,v5(R2) ;2                                                      FD-EMW
      div.d F24,F27,F23 ;3                                                    F-D--------EEEEEEEEEEEEMW         +12 
      s.d F23,v5(R3) ;3                                                         F--------DEMW
      s.d F15,v6(R2) ;2                                                                  FDEMW
      daddui R2,R2,24;2                                                                   FDEMW
      s.d F24,v6(R3) ;3                                                                    FD--------EMW        +1
      daddui R3,R3,24;3                                                                     F--------DEMW       +1
bne R1,R4,loop ;                                                                                     FDEMW      +1
halt ;                                                                                                          +1

;________________________________________________________________________________________________________________________________________________
;                                                                                                             = 8+(57*10)=578  --> DA EXEC=578