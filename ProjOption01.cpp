//
//  ProjOption01.cpp
//  shiyishi
//
//  Created by Jiachen Xie on 03/04/2016.
//  Copyright © 2016 Jiachen Xie. All rights reserved.
//

#include "TriModel01.h"
#include "Proj01_Options.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;



double EurOption::PriceByCRR(TriModel Model, vector<double>& Greeks)
{
    double pu=Model.RiskNeutProb_up();// the probability of up
    double pd=Model.RiskNeutProb_down();//the probability of down
    double pm=1-pu-pd;                 //the probability of mid
    int N= getN();                     // get N

//Memory Management, dynamic memory
    int row = 2*N+1;
    int coulum = 2*N+1;
    double **Price;
    Price = new double *[row];
    for (int i =0; i < row;i++)
        Price[i] = new double[coulum];


    for (int i=-N; i<=N; i++)
    {
        Price[N][i+N]= Payoff(Model.S(N,i));
    }
    for (int n=N-1;n>=0;n--)//i is node number, n is step number
    {
        for (int i=-n;i<=n;i++){
            Price[n][i+n]=(pu*Price[n+1][i+2+n]+pm*Price[n+1][i+n+1]+pd*Price[n+1][ i+n])*exp(-Model.Getr()*Model.Getdt());
        }
    }
    //Calculate Greeks delta=0, gamma=1, theta=2
    Greeks[0]=(Price[1][2]-Price[1][0])/(Model.S(1,1)-Model.S(1,-1)) ;
    Greeks[1]=(((Price[1][2]-Price[1][1])/(Model.S(1,1)-Model.S(1,0)))-((Price[1][1]-Price[1][0])/(Model.S(1,0)-Model.S(1,-1))))/(0.5*(Model.S(1,1)-Model.S(1,-1))) ;
    Greeks[2]=(Price[1][1]-Price[0][0])/Model.Getdt();

    //Memory Management, delete useless data space.
    /*for(int i=0; i< row; i++)
        delete[]Price[i];
        delete[]Price;*/

    return Price[0][0];



}

 Call::Call(int N_){
     //cout << "Enter call option data:" << endl;

     //cout << "Enter steps to expiry N: "; cin >> N;
     SetN(N_);
     //cout << "Enter strike price K:"; cin>>K;
     //cout << endl;
    }
double Call::Payoff(double z)
{
    if(z>K) return z-K;
    return 0.0;
}


Put::Put(int N_){
    //cout << "Enter Put option data:" << endl;
    SetN(N_);
    //cout << "Enter strike price K:"; cin>>K;
   //cout << endl;
}

double Put::Payoff(double z)
{
    if(z<K) return K-z;
    return 0.0;
}




