//
// Created by Luca Barco on 17/01/2018.
//

#ifndef E01_EDGE_H
#define E01_EDGE_H
typedef struct edge_s{
    int v;
    int w;
    int wt;
}Edge;

Edge EDGEcreate(int v,int w,int wt);
#endif //E01_EDGE_H
