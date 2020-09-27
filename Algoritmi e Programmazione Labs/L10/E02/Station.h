//
// Created by Luca Barco on 13/01/2018.
//

#ifndef E02_STATION_H
#define E02_STATION_H
typedef struct casella_s *casella;

casella readStation(char *id,int posti,int bici);
casella NewStation(casella x,casella y);
casella voidStation();
int EqStation(casella a,casella b);
char *GetId(casella x);
int GetPosti(casella x);
int GetBici(casella x);
void PrintStation(casella x);
void diminuisciPosti(casella x);
void diminuisciBici(casella x);
void aumentaPosti(casella x);
void aumentaBici(casella x);
#endif //E02_STATION_H
