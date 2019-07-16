#include "res.h"
#include "grid_gen.h"
#include "flow.h"
#include <iostream>
#include <stdlib.h>

using namespace std;
  grid cell_temp[1000][1000];
  int height,width;
  int N,M,n_typ,s_typ,e_typ,w_typ;

int ch_disp()
{
  cout<<"  PRESS        OPTION"<<endl;
  cout<<"    1         DIRECHLET"<<endl;
  cout<<"    2          NEUMANN"<<endl;
  cout<<"    3         LAST  ONE"<<endl;
  cout<<"Your choice::";
  int ch,flag=1;
  while(flag)
  {
    cout<<"Your choice::";
    cin>>ch;
    if(ch>0 &&  ch<4)
      flag=0;
    else
      cout<<"Invalid! Please enter again.."<<endl;
  }
  return ch;
}

void FVM_flow()
{
  system("cls");
  cout<<"\tWELCOME TO FINITE VOLUME METHOD SOLVER!"<<endl<<endl;
 //DEFINE GRID
 cout<<"PLEASE ENTER THE FOLLOWING GRID PARAMETERS.."<<endl<<endl;
 cout<<"Enter the Grid Height=";
 cin>>height;
 cout<<"Enter the Grid Width=";
 cin>>width;
 //DEFINE DISTRIBUTION
 cout<<"\nPLEASE ENTER THE CELL DISTRIBUTION.."<<endl;
 cout<<"Enter Number of Vertical Divisions(<100):";
 cin>>N;
 cout<<"Enter Number of Horizontal Divisions(<100):";
 cin>>M;

  ///DEFINE BOUNDARY CONDIITONS # ALL DIRECHLET
  system("cls");
  cout<<"======NORTH BOUNDARY======"<<endl;
  n_typ=ch_disp();
  system("cls");
  cout<<"======SOUTH BOUNDARY======"<<endl;
  s_typ=ch_disp();
  system("cls");
  cout<<"======EAST BOUNDARY======"<<endl;
  e_typ=ch_disp();
  system("cls");
  cout<<"======WEST BOUNDARY======"<<endl;
  w_typ=ch_disp();
  ///////Generate and initialize grid with the following params # DEFAULT
  init_grid();
  /////////////SOLVE
  iterations();
}
