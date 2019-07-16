#include <iostream>
#include <math.h>

using namespace std;

int choice()
{
  int ch1=0;
  cout<<" PRESS    OPTION"<<endl;
  cout<<"   1      to find Re."<<endl;
  cout<<"   2      to find u0 for a Re."<<endl;
  cout<<"   3      to see variation in Re with length"<<endl;
  cout<<" Please enter your choice:"<<endl;
  while(1)
  {
    cout<<">>";
    cin>>ch1;
    if(ch1 ==1 || ch1==2 || ch1==3)
      break;
    else
      cout<<"Please enter a valid option!"<<endl;
  }
 return ch1;
}

void calc(int a)
{
   //temp,rho=ISA_model(); import from ISA model
   float temp=288.15,rho=1.225;
   float maxL,R,u0;
   double mu=17.89 * (486.88/(temp+198.72)) * pow((temp/288.16),1.5); // 10^-6 Pa-s
   double v=mu/rho;  //m^2/s;
   switch(a)
   {
     case 1:cout<<"Enter velocity(m/s) :: ";
              cin>>u0;
              cout<<"Enter Length(m) :: ";
              cin>>maxL;
              cout<<"++++++++++++++++++++++++++++++"<<endl;
              cout<<"  Re = "<<u0*maxL*1000000/v<<endl;
              break;
      case 2:cout<<"Enter Reynolds No. :: ";
              cin>>R;
              cout<<"Enter Length(m) :: ";
              cin>>maxL;
              cout<<"++++++++++++++++++++++++++++++"<<endl;
              cout<<"  u0 = "<<R*v/(maxL*1000000)<<" m/s."<<endl;
              break;
      case 3:cout<<"Enter velocity(m/s) :: ";
              cin>>u0;
              cout<<"Enter Max. Length(m) :: ";
              cin>>maxL; //in meters.
              int res=10;
              cout<<"Evaluate Re at every ....\n>>(cms)::";
              cin>>res;
              cout<<"++++++++++++++++++++++++++++++"<<endl;
              int L=0; //L in centimeters.
              while(L <= (maxL*100))
              {
                cout<<"++++++++++++++++++++++++++++++"<<endl<<endl;
                cout<<"  Re @"<<L<<" cms :: "<<u0*L*1000000/v<<endl<<endl;
                L+=res;
              }
              break;
   }

}



int main()
{
 calc(choice());
}
