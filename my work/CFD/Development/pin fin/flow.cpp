#include "res.h"
#include "grid_gen.h"
#include "flow.h"
#include <iostream>
#include <stdlib.h>

using namespace std;
  grid cell_temp[100];
  int width;
  int M,e_typ,w_typ;

int ch_disp()
{
  cout<<"  PRESS        OPTION"<<endl;
  cout<<"    1         DIRECHLET"<<endl;
  cout<<"    2          NEUMANN"<<endl;
  cout<<"    3         LAST  ONE"<<endl;
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

void Fin_flow()
{
  system("cls");
  cout<<"\tWELCOME TO 2D FIN SOLVER!"<<endl<<endl;
 //DEFINE GRID
 cout<<"PLEASE ENTER THE FOLLOWING FIN PARAMETERS.."<<endl<<endl;
 cout<<"Enter the Fin Length=";
 //cin>>width;
 width=1;
 //DEFINE DISTRIBUTION
 cout<<"\nPLEASE ENTER THE CELL DISTRIBUTION.."<<endl;
 cout<<"Enter Number of Horizontal Divisions(<100):";
// cin>>M;
M=30;
 system("cls");
 cout<<"======WEST BOUNDARY======"<<endl;
 w_typ=ch_disp();
  system("cls");
  cout<<"======EAST BOUNDARY======"<<endl;
  e_typ=ch_disp();
  ///////Generate and initialize grid with the following params # DEFAULT
  init_grid();
  /////////////SOLVE//////////
  iterations();
}
