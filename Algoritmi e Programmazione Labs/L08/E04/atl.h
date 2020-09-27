//
// Created by Luca Barco on 10/12/2017.
//

#ifndef E04_ATL_H
#define E04_ATL_H
typedef struct atleta_s{
    char *codice;
    char *nome;
    char *cognome;
    char *categoria;
    char *data;
    int n_nome,n_cognome,n_categoria,ore;
}atleta;

atleta atletaScan(FILE *fp);
void atletaPrint(atleta item,FILE *fp);
atleta atletaVoid();
int atletaEq(atleta a,atleta b);

#endif //E04_ATL_H
