//
//  main.cpp
//  shiyishi
//
//  Created by Jiachen Xie on 03/04/2016.
//  Copyright © 2016 Jiachen Xie. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "TriModel01.h"
#include "Proj01_Options.h"
#include <vector>
#include <fstream>
using namespace std;

int main() {

    double S0,r,q,sigma,T,CALLK,PUTK;
    int N;

    //S0 =100; r =0.05; q =0.03; sigma =0.2;T=1.0;N=500; K =100;


    cout<<"Hello, welcome to Option Price Calculator, Please enter some basic information firstly"<<endl;
    cout<<"Please enter Underlying Price S0:  "; cin>>S0;
    cout<<"Please enter Free-Risk Interest Rates r:  "; cin>>r;
    cout<<"Please enter Dividend Yield q:  "; cin>>q;
    cout<<"Please enter Volatility sigma:  "; cin>>sigma;
    cout<<"Please enter Years Until Expiration:  "; cin>>T;
    cout<<"Please enter steps to expiry N:  "; cin>>N;
    cout<<"Good Job. TriNOMIAL Trees Model has been build.  "<<endl;
    cout<<"Now, Please also enter some Options information  "<<endl;
    cout<<"Please enter call option exercise Price:  "; cin>>CALLK;
    cout<<"Please enter put option exercise Price:  "; cin>>PUTK;






    //Order is S0,r,q,sigma
    TriModel Mod(S0,r,q,sigma);
    Mod.Setdt(T, N);


    Call Calloption(N);
    Calloption.SetK(CALLK);
    vector<double> CallGreek(3);
    cout<<"The results about Call Option :"<<endl;
    cout<<"Call Option Price is "<<Calloption.PriceByCRR(Mod,CallGreek)<<endl;

    cout<<"Call Delta = "<<CallGreek[0]<<endl;
    cout<<"Call Gamma = :"<<CallGreek[1]<<endl;
    cout<<"Call Theta = :"<<CallGreek[2]<<endl;

    Put Putoption(N);
    Putoption.SetK(PUTK);
    vector<double> PutGreek(3);
    cout<<"The results about Put Option :"<<endl;
    cout<<"Put Option Price is "<<Putoption.PriceByCRR(Mod,PutGreek)<<endl;

    cout<<"Put Delta = "<<PutGreek[0]<<endl;
    cout<<"Put Gamma = :"<<PutGreek[1]<<endl;
    cout<<"Put Theta = :"<<PutGreek[2]<<endl;
    cout<<"All This results has also been saved in Excel Files EurPrices.xls and EurGreeks.xls"<<"\n"<<endl;

    ofstream eurprice;
    eurprice.open("European.xls");
    ofstream eurgreek;
    eurgreek.open("EurGreeks.xls");
    eurprice<<"Parameters"<<"\t"<<"Value"<<"\n";
    eurprice<<"Underlying Price"<<"\t"<<S0<<"\n";
    eurprice<<"Interest Rates"<<"\t"<<r<<"\n";
    eurprice<<"Dividend Yield"<<"\t"<<q<<"\n";
    eurprice<<"Volatility"<<"\t"<<sigma<<"\n";
    eurprice<<"Time(Year)"<<"\t"<<T<<"\n";
    eurprice<<"steps to expiry"<<"\t"<<N<<"\n";
    eurprice<<"CallOption Price"<<"\t"<<Calloption.PriceByCRR(Mod,CallGreek)<<"\n";
    eurprice<<"Put Option Price"<<"\t"<<Putoption.PriceByCRR(Mod,PutGreek)<<"\n";
    eurprice<<"n"<<"\t"<<"Call Option"<<"\t"<<"Put Option"<<"\n";

    eurgreek << "N"<<"\t"<<"CallDelta" << "\t" <<"CallGamma" << "\t" << "CallTheta" << "\t";
    eurgreek << "PutDelta" << "\t" << "PutGamma"  << "\t" << "PutTheta" << "\n";

    CallGreek.clear(); PutGreek.clear();


    for(int N =100; N<=2000; N += 100){

        Mod.Setdt(T, N);
        Call Calloption(N);
        Calloption.SetK(CALLK);
        Put Putoption(N);
        Putoption.SetK(PUTK);
        eurprice << N <<"\t"<<Calloption.PriceByCRR(Mod,CallGreek)<<"\t";
        eurprice << Putoption.PriceByCRR(Mod,PutGreek)<<"\n";
        eurgreek << N<<"\t"<<CallGreek[0] << "\t" << CallGreek[1] << "\t" << CallGreek[2] << "\t";
        eurgreek << PutGreek[0] << "\t" << PutGreek[1] << "\t" << PutGreek[2] << "\n";
        CallGreek.clear(); PutGreek.clear();



    }


















    return 0;
}
