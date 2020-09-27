//
// Created by Luca Barco on 08/01/2018.
//

#ifndef E03_EDGE_H
#define E03_EDGE_H
typedef struct edge_s{
    int v;
    int w;
    int wt;
}Edge;

Edge EDGEcreate(int v,int w,int wt);
#endif //E03_EDGE_H
