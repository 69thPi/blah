#include <iostream>
#include <math.h>

using namespace std;
float R= 287.05; //sp. gas constt air
double g=9.80665; //acceleration due to gravity
double r0,t0=288.15,p0=101325;

void calc_r() //density
{
  r0=p0/(R*t0);
}

void calc_TaP(double a,double h_in,double h_min) //take t0 from global
{
  h_min*=1000;
     if(a!=0) //non iso-thermal layer
       {
         double t=t0+a*(h_in-h_min);
         p0*=pow((t/t0),(-1* g/ (R*a)));
         t0=t;
       }
     else //iso-thermal layer
     {
       p0*=exp((-1 * g * (h_in-h_min))/(R*t0));
     }

  }



void ISA_model()
{
  double height=84001;//to take an input
  cout<<"Enter Height of evaluation:(in meters from MSL)::\n";
 while(1)
 {
   cout<<">>";
   cin>>height;
   if(height>84000)
   cout<<"please enter height less than 84 kms\n";
   else
    break;
 }

      while(1)
      {
          ///--------------------0 to 11km-------------------------
            if(height>11000)
              calc_TaP(-0.0065,11000,0); //calc at 11km
            else
              {
                  calc_TaP(-0.0065,height,0);
                  break;
              }
          ///--------------------11 to 20km-------------------------
          if(height>20000)
            calc_TaP(0,20000,11);
          else
            {
              calc_TaP(0,height,11);
              break;
            }
          ///--------------------20 to 32km-------------------------
          if(height>32000)
            calc_TaP(0.001,32000,20);
          else
          {
              calc_TaP(0.001,height,20);
              break;
          }
         ///--------------------32 to 47km-------------------------
          if(height>47000)
            calc_TaP(0.0028,47000,32);
          else //47km a=2.8
          {
              calc_TaP(0.0028,height,32);
              break;
          }
          ///--------------------47 to 51km-------------------------
           if(height>51000)
             calc_TaP(0,51000,47);
           else //47km a=2.8
           {
               calc_TaP(0,height,47);
               break;
           }
           ///--------------------51 to 71km-------------------------
            if(height>71000)
              calc_TaP(-0.0028,71000,51);
            else //47km a=2.8
            {
                calc_TaP(-0.0028,height,51);
                break;
            }
            ///--------------------71 to 84km-------------------------
                calc_TaP(-0.0020,height,71);
                break;
        }
        calc_r();
        cout<<endl<<endl;
        cout<<"---------------------------------"<<endl;
        cout<<"--   ------ at "<<height<<" -------  --\n";
        cout<<"---------------------------------"<<endl;
        cout<<" Temperature = "<<t0<<" K."<<endl;
        cout<<" Pressure    = "<<p0<<" Pa."<<endl;
        cout<<" Density     = "<<r0<<" Kg/m^3."<<endl;
}

int main()
{
  ISA_model();
}
