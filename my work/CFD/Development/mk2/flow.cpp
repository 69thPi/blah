#include "res.h"
#include "grid_gen.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;
  grid cell_temp[100][100];

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

 void display(int p,int q)
 {
   for(int j=q-1;j>=0;j--)
   {
     for(int i=0;i<p;i++)
     {
       cout<<cell_temp[i][j].eqn<<"\t";
     }
     cout<<endl;
   }
 }

void grid_read(int m)
{
  grid temp;
  int i=0,j=0;
  ifstream fin("grid.dat",ios::binary);
  while(fin.read((char*)&temp,sizeof(grid)))
  {
    cell_temp[i][j]=temp;
    cout<<cell_temp[i][j].eqn<<endl;
    i++;
    if(i==m)//M
    {
      i=0;
      j++;
    }
  }
  fin.close();
}

void FVM_flow()
{
  int a,b,p,q;
  //DEFINE GRID
 cout<<"enter the grid height=";
 cin>>a;
 cout<<"enter the grid width=";
 cin>>b;

 //DEFINE DISTRIBUTION
 cout<<"enter number of Y divisions(<100):";
 cin>>q;
 cout<<"enter number of X divisions(<100):";
 cin>>p;

  ///DEFINE BOUNDARY CONDIITONS # ALL DIRECHLET
  int n_bound_ch=1,s_bound_ch=1,e_bound_ch=1,w_bound_ch=1;//default set to dirichlet
  cout<<"======NORTH BOUNDARY======"<<endl;
  n_bound_ch=ch_disp();
  system("cls");
  cout<<"======SOUTH BOUNDARY======"<<endl;
  s_bound_ch=ch_disp();
  system("cls");
  cout<<"======EAST BOUNDARY======"<<endl;
  e_bound_ch=ch_disp();
  system("cls");
  cout<<"======WEST BOUNDARY======"<<endl;
  w_bound_ch=ch_disp();
  ///////Generate and initialize grid with the following params # DEFAULT
  init_grid(a,b,p,q,n_bound_ch,s_bound_ch,e_bound_ch,w_bound_ch);

  ////SOLUTION ////
  grid_read(p);
  cout<<"=============read=============="<<endl;
  //SOLVE
  ///////////DISPLAY
  display(p,q);
}
