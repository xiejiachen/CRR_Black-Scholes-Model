#ifndef Proj01_Options06_h
#define Proj01_Options06_h
#include "TriModel01.h"
#include <vector>
using namespace std;

class EurOption
{
   private:
      int N; //steps to expiry
   public:
      //please implement a constructor for EurOption

      void SetN(int N_){N=N_;}
      int getN(){return N;}

      //Payoff defined to return 0.0
      virtual double Payoff(double z){return 0.0;}

      //pricing European option by a Trinomial Tree model
      // please implement this function to return not only prices but also greeks
      double PriceByCRR(TriModel Model, vector<double>& Greeks);
};

class Call: public EurOption
{
   private:
      double K; //strike price
   public:
      // please implement a constructor for Call option:
    Call(int N_);
      void SetK(double K_){K=K_;}
      double Payoff(double z);
};

class Put: public EurOption
{
   private:
      double K; //strike price
   public:
      // please implement a constructor for Put option:
    Put(int N_);
      void SetK(double K_){K=K_;}
      double Payoff(double z);
};

#endif
