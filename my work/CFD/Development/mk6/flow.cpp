#include "res.h"
#include "grid_gen.h"
#include "flow.h"
#include <iostream>
#include <stdlib.h>

using namespace std;
  grid cell_temp[1000][1000];
  int height,width;
  int N=5,M=5,n_typ,s_typ,e_typ,w_typ;
  double NORTH,SOUTH,EAST,WEST;

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

void def_bound_typ()
{
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
}

double ret_bound_val(int x)
{
  double inp;
  if(x==1)
  cout<<"ENTER DIRECHLET BOUNDARY VALUE::";
  else if(x==2)
  cout<<"ENTER NEUMANN BOUNDARY VALUE::";
  else
  cout<<"ENTER ROBIN'S BOUNDARY VALUE::";
  cin>>inp;
  return inp;
}

void bound_val_setup()
{
  //ask input values for all boundaries as per conditions
  system("cls");
  cout<<"=====ENTER BOUNDARY CONDITION====="<<endl;
  cout<<"\n==========FOR NORTH WALL=========="<<endl<<endl;
  NORTH=ret_bound_val(n_typ);
  cout<<"\n==========FOR SOUTH WALL=========="<<endl<<endl;
  SOUTH=ret_bound_val(s_typ);
  cout<<"\n==========FOR EAST WALL==========="<<endl<<endl;
  EAST=ret_bound_val(e_typ);
  cout<<"\n==========FOR WEST WALL==========="<<endl;
  WEST=ret_bound_val(w_typ);

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
 ///DEFINE BOUNDARY CONDIITON TYPE # DEF == ALL DIRECHLET
  def_bound_typ();
  ////////input boundary values
  bound_val_setup();

  ////CALC GRID TILL GRID INDEPENDANT SOLUTION IS REACHED
  ///////Generate and initialize grid with the following params # DEFAULT
  // init_grid();
  /////////////SOLVE
  iterations();
}
