#include "res.h"
#include "flow.h"
#include <fstream>
#include <iostream>

using namespace std;

/////////GLOBAL VARS/////////
  grid cell[100];//no of divisions
/////////////////////////////////////INITIAL CELL SETUP/////////////////////////////////////
void assign_dim(grid &temp)
{
  temp.del_x=(double)width/(double)M;
}

void assign_params(grid &temp)//set distance of cell edges from CG; ###for rectangular cells ONLY
{
  temp.x_e = temp.del_x/((double)2);
  temp.x_w = temp.del_x/((double)2);
}

void grid_write()
{
  remove("grid0.dat");
  ofstream fout("grid0.dat",ios::binary);
  for(int i=0;i<M;i++)
      fout.write((char*)&cell[i],sizeof(grid));
  fout.close();
}

////////////////////////////////////////////USER FUNCTIONS////////////////////////////////////////////
void init_grid()
{
  cout<<"-------------------------------"<<endl;
  cout<<"Enter the ambient temperature::";
  cin>>T_inf;
  ///DEFINE GEOMETRICAL PARAMS
  for(int i=0;i<M;i++)
    {
      cell[i].data=T_inf;// eequals T_inf
      assign_dim(cell[i]);//assign del_x;
      assign_params(cell[i]);//assign values of x_w,x_e;
      cell[i].ap=0;
      cell[i].ae=0;
      cell[i].aw=0;
      cell[i].lhs=0;
    }
 /// save the intitial matrix
  grid_write();
}
