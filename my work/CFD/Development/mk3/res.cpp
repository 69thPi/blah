#include "res.h"
#include "grid_gen.h"
#include "flow.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

grid sol_cell[100][100];
double NORTH,SOUTH,EAST,WEST;

void solve_cell(int i,int j,int n)//solves eqn for respective sol_cells/
{
  switch(n)
  {
    //MID CELLS
    case 0:sol_cell[i][j].data = ((sol_cell[i][j].an*sol_cell[i][j+1].data)+(sol_cell[i][j].as*sol_cell[i][j-1].data)+(sol_cell[i][j].ae*sol_cell[i+1][j].data)+(sol_cell[i][j].aw*sol_cell[i-1][j].data))/(sol_cell[i][j].ap);
          break;
    //DIRECHLET MID EDGE
    case 1:sol_cell[i][j].data = ((sol_cell[i][j].an*NORTH)+(sol_cell[i][j].as*sol_cell[i][j-1].data)+(sol_cell[i][j].ae*sol_cell[i+1][j].data)+(sol_cell[i][j].aw*sol_cell[i-1][j].data))/(sol_cell[i][j].ap);
          break;
    case 2:sol_cell[i][j].data = ((sol_cell[i][j].an*sol_cell[i][j+1].data)+(sol_cell[i][j].as*SOUTH)+(sol_cell[i][j].ae*sol_cell[i+1][j].data)+(sol_cell[i][j].aw*sol_cell[i-1][j].data))/(sol_cell[i][j].ap);
          break;
    case 3:sol_cell[i][j].data = ((sol_cell[i][j].an*sol_cell[i][j+1].data)+(sol_cell[i][j].as*sol_cell[i][j-1].data)+(sol_cell[i][j].ae*EAST)+(sol_cell[i][j].aw*sol_cell[i-1][j].data))/(sol_cell[i][j].ap);
          break;
    case 4:sol_cell[i][j].data = ((sol_cell[i][j].an*sol_cell[i][j+1].data)+(sol_cell[i][j].as*sol_cell[i][j-1].data)+(sol_cell[i][j].ae*sol_cell[i+1][j].data)+(sol_cell[i][j].aw*WEST))/(sol_cell[i][j].ap);
          break;
    //DIRECHLET-DIRECHLET CORNERS
    case 5:sol_cell[i][j].data = ((sol_cell[i][j].an*NORTH)+(sol_cell[i][j].as*sol_cell[i][j-1].data)+(sol_cell[i][j].ae*EAST)+(sol_cell[i][j].aw*sol_cell[i-1][j].data))/(sol_cell[i][j].ap);
          break;
    case 6:sol_cell[i][j].data = ((sol_cell[i][j].an*NORTH)+(sol_cell[i][j].as*sol_cell[i][j-1].data)+(sol_cell[i][j].ae*sol_cell[i+1][j].data)+(sol_cell[i][j].aw*WEST))/(sol_cell[i][j].ap);
          break;
    case 7:sol_cell[i][j].data = ((sol_cell[i][j].an*sol_cell[i][j+1].data)+(sol_cell[i][j].as*SOUTH)+(sol_cell[i][j].ae*EAST)+(sol_cell[i][j].aw*sol_cell[i-1][j].data))/(sol_cell[i][j].ap);
          break;
    case 8:sol_cell[i][j].data = ((sol_cell[i][j].an*sol_cell[i][j+1].data)+(sol_cell[i][j].as*SOUTH)+(sol_cell[i][j].ae*sol_cell[i+1][j].data)+(sol_cell[i][j].aw*WEST))/(sol_cell[i][j].ap);
          break;
    //NEUMANN MID EDGE
    case 9:sol_cell[i][j].data = ((sol_cell[i][j].an* NORTH * sol_cell[i][j].y_n * (double)2) + (sol_cell[i][j].as * sol_cell[i][j-1].data) + (sol_cell[i][j].ae * sol_cell[i+1][j].data) + (sol_cell[i][j].aw * sol_cell[i-1][j].data))/(sol_cell[i][j].ap + sol_cell[i][j].an);
          break;
    case 10:sol_cell[i][j].data = ((sol_cell[i][j].an*sol_cell[i][j+1].data)+(sol_cell[i][j].as * SOUTH * sol_cell[i][j].y_s * 2)+(sol_cell[i][j].ae*sol_cell[i+1][j].data)+(sol_cell[i][j].aw*sol_cell[i-1][j].data))/(sol_cell[i][j].ap + sol_cell[i][j].as);
          break;
    case 11:sol_cell[i][j].data = ((sol_cell[i][j].an*sol_cell[i][j+1].data)+(sol_cell[i][j].as*sol_cell[i][j-1].data)+(sol_cell[i][j].ae * EAST * sol_cell[i][j].x_e * 2)+(sol_cell[i][j].aw*sol_cell[i-1][j].data))/(sol_cell[i][j].ap + sol_cell[i][j].ae);
          break;
    case 12:sol_cell[i][j].data = ((sol_cell[i][j].an*sol_cell[i][j+1].data)+(sol_cell[i][j].as*sol_cell[i][j-1].data)+(sol_cell[i][j].ae*sol_cell[i+1][j].data)+(sol_cell[i][j].aw * WEST * sol_cell[i][j].x_w * 2))/(sol_cell[i][j].ap + sol_cell[i][j].aw);
          break;
    //NEWMANN-NEUMANN CORNERS
    case 13:sol_cell[i][j].data = ((sol_cell[i][j].an* NORTH * sol_cell[i][j].y_n * 2)+(sol_cell[i][j].as*sol_cell[i][j-1].data)+(sol_cell[i][j].ae * EAST * sol_cell[i][j].x_e * 2)+(sol_cell[i][j].aw*sol_cell[i-1][j].data))/(sol_cell[i][j].ap + sol_cell[i][j].an + sol_cell[i][j].ae);
          break;
    case 14:sol_cell[i][j].data = ((sol_cell[i][j].an* NORTH * sol_cell[i][j].y_n * 2)+(sol_cell[i][j].as*sol_cell[i][j-1].data)+(sol_cell[i][j].ae*sol_cell[i+1][j].data)+(sol_cell[i][j].aw * WEST * sol_cell[i][j].x_w * 2))/(sol_cell[i][j].ap + sol_cell[i][j].an + sol_cell[i][j].aw);
          break;
    case 15:sol_cell[i][j].data = ((sol_cell[i][j].an*sol_cell[i][j+1].data)+(sol_cell[i][j].as * SOUTH * sol_cell[i][j].y_s * 2)+(sol_cell[i][j].ae * EAST * sol_cell[i][j].x_e * 2)+(sol_cell[i][j].aw*sol_cell[i-1][j].data))/(sol_cell[i][j].ap + sol_cell[i][j].as+ sol_cell[i][j].ae);
          break;
    case 16:sol_cell[i][j].data = ((sol_cell[i][j].an*sol_cell[i][j+1].data)+(sol_cell[i][j].as * SOUTH * sol_cell[i][j].y_s * 2)+(sol_cell[i][j].ae*sol_cell[i+1][j].data)+(sol_cell[i][j].aw * WEST * sol_cell[i][j].x_w * 2))/(sol_cell[i][j].ap + sol_cell[i][j].as + sol_cell[i][j].aw);
          break;
    //3rd MID EDGES
    case 17://north
            break;
    case 18://south
            break;
    case 19://east
            break;
    case 20://west
            break;
    //3RD-3RD CORNERS
    case 21://north east
            break;
    case 22://north west
            break;
    case 23://south east
            break;
    case 24://south west
            break;
     ////////////////////////////////////////////////////MIXTURE CORNERS/////////////////////////////////////////
      /////////////NORTH EAST
      //DIRECHLET-NEUMANN
    case 25:sol_cell[i][j].data = ((sol_cell[i][j].an*NORTH)+(sol_cell[i][j].as*sol_cell[i][j-1].data)+(sol_cell[i][j].ae * EAST * sol_cell[i][j].x_e * 2)+(sol_cell[i][j].aw*sol_cell[i-1][j].data))/(sol_cell[i][j].ap + sol_cell[i][j].ae);
            break;
      //DIRECHLET-3RD
    case 26:
            break;
      //NEWMANN-DIRECHLET
    case 27:sol_cell[i][j].data = ((sol_cell[i][j].an* NORTH * sol_cell[i][j].y_n * 2) + (sol_cell[i][j].as * sol_cell[i][j-1].data) + (sol_cell[i][j].ae*EAST) + (sol_cell[i][j].aw * sol_cell[i-1][j].data))/(sol_cell[i][j].ap + sol_cell[i][j].an);
            break;
      //NEUMANN-3RD
    case 28:
            break;
      //3RD-DIRECHLET
    case 29:
            break;
      //3RD-NEUMANN
    case 30:
            break;
      /////////////NORTH WEST
      //DIRECHLET-NEUMANN
    case 31:sol_cell[i][j].data = ((sol_cell[i][j].an*NORTH)+(sol_cell[i][j].as*sol_cell[i][j-1].data)+(sol_cell[i][j].ae*sol_cell[i-1][j].data)+(sol_cell[i][j].aw * WEST * sol_cell[i][j].x_w * 2))/(sol_cell[i][j].ap + sol_cell[i][j].aw);
            break;
      //DIRECHLET-3RD
    case 32:
            break;
      //NEWMANN-DIRECHLET
    case 33:sol_cell[i][j].data = ((sol_cell[i][j].an* NORTH * sol_cell[i][j].y_n * 2) + (sol_cell[i][j].as * sol_cell[i][j-1].data) + (sol_cell[i][j].ae * sol_cell[i+1][j].data) + (sol_cell[i][j].aw*WEST))/(sol_cell[i][j].ap + sol_cell[i][j].an);
            break;
      //NEUMANN-3RD
    case 34:
            break;
      //3RD-DIRECHLET
    case 35:
            break;
      //3RD-NEUMANN
    case 36:
            break;
      /////////////SOUTH EAST
      //DIRECHLET-NEUMANN
    case 37:sol_cell[i][j].data = ((sol_cell[i][j].an*sol_cell[i][j+1].data)+(sol_cell[i][j].as*SOUTH)+(sol_cell[i][j].ae * EAST * sol_cell[i][j].x_e * 2)+(sol_cell[i][j].aw*sol_cell[i-1][j].data))/(sol_cell[i][j].ap + sol_cell[i][j].ae);
            break;
      //DIRECHLET-3RD
    case 38:
            break;
      //NEWMANN-DIRECHLET
    case 39:sol_cell[i][j].data = ((sol_cell[i][j].an*sol_cell[i][j+1].data)+(sol_cell[i][j].as * SOUTH * sol_cell[i][j].y_s * 2)+ (sol_cell[i][j].ae*EAST) +(sol_cell[i][j].aw*sol_cell[i-1][j].data))/(sol_cell[i][j].ap + sol_cell[i][j].as);
            break;
      //NEUMANN-3RD
    case 40:
            break;
      //3RD-DIRECHLET
    case 41:
            break;
      //3RD-NEUMANN
    case 42:
            break;
      /////////////SOUTH WEST
      //DIRECHLET-NEUMANN
    case 43:sol_cell[i][j].data = ((sol_cell[i][j].an*sol_cell[i][j+1].data)+(sol_cell[i][j].as*SOUTH)+(sol_cell[i][j].ae*sol_cell[i-1][j].data)+(sol_cell[i][j].aw * WEST * sol_cell[i][j].x_w * 2))/(sol_cell[i][j].ap + sol_cell[i][j].aw);
            break;
      //DIRECHLET-3RD
    case 44:
            break;
      //NEWMANN-DIRECHLET
    case 45:sol_cell[i][j].data = ((sol_cell[i][j].an*sol_cell[i][j+1].data)+(sol_cell[i][j].as * SOUTH * sol_cell[i][j].y_s * 2)+(sol_cell[i][j].ae*sol_cell[i+1][j].data)+(sol_cell[i][j].aw*WEST))/(sol_cell[i][j].ap + sol_cell[i][j].as);
            break;
      //NEUMANN-3RD
    case 46:
            break;
      //3RD-DIRECHLET
    case 47:
            break;
    //3RD-NEUMANN
    case 48:
            break;
  }
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

void solve_setup()
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

void grid_read()
{
  grid temp;
  int i=0,j=0;
  ifstream fin("grid.dat",ios::binary);
  while(fin.read((char*)&temp,sizeof(grid)))
  {
    sol_cell[i][j]=temp;
    i++;
    if(i==M)
    {
      i=0;
      j++;
    }
  }
  fin.close();
}

void display()
{
 for(int j=N-1;j>=0;j--)
 {
   for(int i=0;i<M;i++)
   {
     cout<<sol_cell[i][j].data<<"\t";
   }
   cout<<endl;
 }
}

void notepad()
{
  ofstream fout("RESULT.txt");
  for(int j=N-1;j>=0;j--)
  {
    for(int i=0;i<M;i++)
    {
      fout<<sol_cell[i][j].data<<"\t";
    }
    fout<<endl;
  }
  fout.close();
}
void iterations()
{
  grid_read();
  solve_setup();
  int cnt=1;
  int iter=2;
  cout<<"enter number of iterations::";
  cin>>iter;
  while(cnt<=iter)
  {
      for(int j=0;j<N;j++)
      {
        for(int i=0;i<M;i++)
        {
            solve_cell(i,j,sol_cell[i][j].eqn);
        }
      }
      cnt++;
  }
  grid_write();//notepad
  notepad();
  remove("grid.dat");
  system("cls");
  cout<<"==================RESULT=================="<<endl;
  display();
}
