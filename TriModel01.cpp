//
//  TriModel01.cpp
//  shiyishi
//
//  Created by Jiachen Xie on 03/04/2016.
//  Copyright © 2016 Jiachen Xie. All rights reserved.
//

#include "TriModel01.h"
#include <cmath>

void TriModel::Setdt(double T, int N){
    double N1=N;
    dt=T/N1;
    dx=sigma*sqrt(3*dt);
    v=r-q-0.5*sigma*sigma;
};

double TriModel::RiskNeutProb_up(){

    return 0.5*((sigma*sigma*dt+v*v*dt*dt)/pow(dx, 2)+v*dt/dx);
};

// calculate the risk neutral probability of going down
double TriModel::RiskNeutProb_down(){
    
    return 0.5*((pow(sigma, 2)*dt+pow(v*dt,2))/pow(dx, 2)-v*dt/dx);
};

double TriModel::S(int n, int i){

    
    return S0*exp(i*dx);
};
double  TriModel::Getr(){
    return r;
};

// return time interval dt
double TriModel::Getdt(){
    return dt;
};
