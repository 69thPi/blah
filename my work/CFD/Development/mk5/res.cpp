#include "res.h"
#include "grid_gen.h"
#include "flow.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

grid sol_cell[1000][1000];
grid temp[1000][1000];


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

void grid_read()
{
  grid temp1;
  int i=0,j=0;
  ifstream fin("grid.dat",ios::binary);
  while(fin.read((char*)&temp1,sizeof(grid)))
  {
    sol_cell[i][j]=temp1;
    i++;
    if(i==M)
    {
      i=0;
      j++;
    }
  }
  fin.close();
}

void grid_read_prev()
{
  grid temp1;
  int i=0,j=0;
  ifstream fin("grid1.dat",ios::binary);
  if(!fin.is_open())
    cout<<"No file Found!"<<endl;
  while(fin.read((char*)&temp1,sizeof(grid)))
  {
    sol_cell[i][j]=temp1;
    i++;
    if(i==M-2)
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
  ofstream fout("RESULT.txt",ios::app);
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

int iter_opt()//to get optimal number of iterations
{
  //check current matrix with previous matrix if any value has deviation more than 0.00001% then soltn is  optimal.
  int flag=1;
  int breakout=0;
  for(int j=0;j<N;j++)
    {
      for(int i=0;i<M;i++)
      {
          double n=temp[i][j].data-sol_cell[i][j].data;
          double fin;
          if(n<0)
            fin = -1 * ( (double)n / (double)sol_cell[i][j].data);
          else
            fin = (double)n / (double)temp[i][j].data;

          if(fin > 0.0000001)//can change as per accuracy
            {
              flag=0;
              breakout=1;
              break;
            }
      }
      if(breakout==1)
      break;
    }
 return flag;
}

void write_file()
{
  remove("grid1.dat");//previous existance is removed
  grid temp2;
  ofstream fout("grid1.dat",ios::binary);
  for(int j=0;j<N;j++)
  {
    for(int i=0;i<M;i++)
    {
      temp2=temp[i][j];
      fout.write((char*)&temp2,sizeof(grid));
    }
  }
  fout.close();
}

void consec_iter()
{
  grid_read();//after initialization
  int cnt=0;
  int flag=1,flag2=0;
  while(flag)
  {
      for(int j=0;j<N;j++)
      {
        for(int i=0;i<M;i++)
        {
            solve_cell(i,j,sol_cell[i][j].eqn);
        }
      }
      cnt++;
      if(cnt > 1)
      {
        flag2=iter_opt();
      }
      //copy content of current grid to temp grid; ////CHILD GRID SET
      for(int j=0;j<N;j++)
      {
        for(int i=0;i<M;i++)
        {
            temp[i][j].data=sol_cell[i][j].data;
        }
      }
      if(flag2 == 1)
      flag=0;//end loop after copying the final matrix
  }
  cout<<"iter = "<<cnt<<endl;
  display();//child grid
  notepad();
  grid_read_prev();//PARENT GRID SET
  write_file();//write child as parent for future
  cout<<"======================"<<endl;
}

int compare_data()
{
  int ret=1;
  double parent_sum,child_sum;
  int matched_x,matched_y;
  //PARENT = SOL_CELL
  //CHILD = TEMP
  //locate corresponding location and map data
  //compare data and return true if no value is more than 0.00001% in difference:: i.e. grid independance is REACHED
  //else return false
  //  int j,k;
  //j = (sol_cell[a][b].x_w - temp[a][b].x_w) / temp[a][b].del_x;//only for uniform grids
  if(M>2)
  {
    for(int b=0 ; b < N-2 ; b++ )
    {
      int breakout = 0;
      for(int a=0; a < M-2 ;a++)
      {
        ////////////////FOR X COORD MATCH
              parent_sum=0;
              for(int i=0;i<a;i++)
              parent_sum+=sol_cell[i][b].del_x;//previous cells width
              parent_sum+= sol_cell[a][b].x_w;//current cell west width
              child_sum=0;
              for(int x=0; x<M ; x++)//let flow all through and break when exceeds the parent sum and thats the x index.
              {
                    child_sum+=temp[x][b].del_x;
                    if(child_sum > parent_sum)//coordinates reached
                    {
                      matched_x = x;
                      break;
                    }
              }
         ///////////////////FOR Y COORD MATCH
              parent_sum=0;
              for(int j=0;j<b;j++)
              parent_sum+=sol_cell[a][j].del_y;//previous cells height
              parent_sum+= sol_cell[a][b].y_s;//current cell south height
              child_sum=0;
              for(int y=0; y<N ; y++)//let flow all through and break when exceeds the parent sum and thats the x index.
              {
                child_sum+=temp[a][y].del_y;
                if(child_sum > parent_sum)//coordinates reached
                {
                  matched_y = y;
                  break;
                }
              }
          cout<<"matched_x::"<<matched_x<<"  matched_y"<<matched_y<<endl;
         cout<<"child = "<<temp[matched_x][matched_y].data<<endl;
         cout<<"parent = "<<sol_cell[a][b].data<<endl;
       double n = (double)temp[matched_x][matched_y].data - (double)sol_cell[a][b].data;
       double frn;
       if(n<0)
        frn= (double)(-1 * n) / (double)(sol_cell[a][b].data);
      else
        frn = (double)n / (double)temp[matched_x][matched_y].data;
        cout<<"frn = "<<frn<<endl;
      if(frn > 0.35)//RN<15%> //// 0.1% = 0.001
       {
         ret=0;
         breakout = 1;
         break;
       }
      }
      if(breakout==1)
      break;
    }
  }
  else
    ret=0;
    return ret;
}



//POSSIBLE LOGICAL FLAW THE OPTIMAL ITERATIONS AND THE GRID INDEPENDANT VALUES DONT MATCH HENCE INFINTE LOOP

void iterations()
{
  remove("grid.dat");
  remove("grid1.dat");
  //start counting M and N from 1,3,5,7,9, and so on till we get compare data = true
  int grid_count=1;
  while(1)
  {
    M=grid_count;
    N=grid_count;
    cout<<"++++++++++"<<endl;
    cout<<"M = "<<M<<" N = "<<N<<endl;
    init_grid();
    consec_iter();
    if(compare_data()==1)
      break;
    grid_count+=2;
    if(grid_count>9)
    break;
  }

}





















/*
notepad();
remove("grid.dat");
system("cls");
cout<<"==================RESULT=================="<<endl;
display();
cout<<"=========================================="<<endl;
cout<<"Number of iterations :: "<<cnt<<endl;
cout<<"=========================================="<<endl;

*/
