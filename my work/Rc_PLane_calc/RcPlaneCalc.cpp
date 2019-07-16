#include <iostream>
#include <stdlib.h>

using namespace std;




void exit()
{
	cout<<"Do you wish to exit?(Y/N)"<<endl;
	  char ch2;
	  cout<<">>";
	  cin>>ch2;
	  if(ch2 =='Y' || ch2 =='y')
		  exit(0);
}

void print(int a,int b,double c)
{
  cout<<"------------------------------------"<<endl;
  cout<<"---AR---+---Span-------+-------Chord"<<endl;
  for(int i=a;i<=b;i++)
  {
   float len=sqrt(c/i);
   float chord=c/len;
   cout<<"    "<<i<<"      "<<chord<<"          "<<len<<endl;
    cout<<"--------+--------------+------------"<<endl;
  }
}



void wing_params()
{
	double weight=0,vel=0,area=1;
	float Cl=1.0f;
  system("cls");
  cout<<"   *       *  ***  *   *    ***        ***    *   *      ***       "<<endl;
  cout<<"   *       *   *   * * *  *          *       * *  *     *          "<<endl;
  cout<<"    *  *  *    *   *  **  *  **      *      ***** *     *          "<<endl;
  cout<<"     *   *    ***  *   *    * *        ***  *   * ****   *** *     "<<endl;
  cout<<"Enter weight of plane(in grams)::";
  cin>>weight;
  cout<<"Enter velocity of plane(m/s)::";
  cin>>vel;
  area = 1.90116*(weight/vel);
  int st=1,end=1;
  cout<<"Enter range for Aspect Ratio"<<endl;
  cout<<"Start value:";
  cin>>st;
  cout<<"End value:";
  cin>>end;

  while(1)
  {
	  system("cls");
	  cout<<"The Area is "<<area<<" cm^2 \nwith Cl="<<Cl<<"\nTemperature =30 Deg Cel\nDensity=1.032kg/m^3 \nViscosity=1.88e-5 kg/m-s\nElevation=1km above MSL"<<endl;
	  print(st,end,area);
	  exit();
	  cout<<"Do you wish to change Cl (Y/N)?"<<endl;
	  cout<<">>";
	  char ch1;
	  cin>>ch1;
	  if(ch1 =='Y' || ch1 =='y')
	  {
		  area = 1.90116*(weight/vel);
		  cout<<"Enter Cl::";
		  cin>>Cl;
		  area /= Cl;// update Cl
	  }
	  else
		break;
  }

}

int main()
{
 while(1)
 {
	 wing_params();
	 system("cls");
	 exit();
 }
}