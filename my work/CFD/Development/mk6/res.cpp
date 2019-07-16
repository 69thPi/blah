#include "res.h"
#include "grid_gen.h"
#include "flow.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

grid sol_cell[1000][1000];
double temp[1000][1000];
double average=0; //current average


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

int avg_chk() //read previous avg and comapre with parameter and return 1 if in acceptable range
{
  double a=0,f=0;
  ifstream fin("avg.dat",ios::binary);
  fin >> a;
  fin.close();
  double nu = a - average;
  if(nu<0)
   f = (double)(-1 * nu)/(double)average;
  else
   f = (double)nu/(double)a;
  if(f > 0.0000001)
    return 0; //not stable result
  else
    return 1;//stable result
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

void notepad(int cnt)
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
  fout<<cnt<<endl;
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
          double n=temp[i][j]-sol_cell[i][j].data;
          double fin;
          if(n<0)
            fin = -1 * ( (double)n / (double)sol_cell[i][j].data);
          else
            fin = (double)n / (double)temp[i][j];

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
 //display();
 return flag;
}

void write_avg(double a)
{
  ofstream fout("avg.dat",ios::binary);
  fout << a;
  fout.close();
}

void solve_iter()
{
  grid_read();//after initialization
  int cnt=0, flag=1;
  double sum=0;
  while(flag)
  {
    sum=0;
      for(int j=0;j<N;j++)
      {
        for(int i=0;i<M;i++)
        {
            solve_cell(i,j,sol_cell[i][j].eqn);
            sum+=sol_cell[i][j].data;
        }
      }
      cnt++;
      if(cnt > 1)
      {
        flag=(!iter_opt());
      }
      for(int j=0;j<N;j++)
      {
        for(int i=0;i<M;i++)
        {
            temp[i][j]=sol_cell[i][j].data;
        }
      }
  }
  cout<<"Iterations = "<<cnt<<endl;
  display();//display curretn optimal solution
  notepad(cnt);//wrute into notepad
  average = (double)sum/(double)(M*N);
  write_avg(average);
}

int grid_indep_chk()
{
  int ret=1;
  //compare ADJACENT cell data and return true if no value is more than 0.00001% in difference:: i.e. grid independance is REACHED
  if(M=2)
    ret = 0;
  else
  {
    for(int b=0 ; b < N-1 ; b++ )
    {
      int breakout = 0;
      for(int a=0; a < M-1 ;a++)
      {

           double h = sol_cell[a][b].data - sol_cell[a+1][b].data;
           if(h<0)
            h*=-1;
           double v = sol_cell[a][b].data - sol_cell[a][b+1].data;
           if(v<0)
            v*=-1;
                   if(h > 0.00001 || v > 0.00001)
                   {
                     ret=0;
                     breakout = 1;
                     break;
                   }
             if(a==M-2)//check next box vertical distance
             {
                   double v = sol_cell[a+1][b].data - sol_cell[a+1][b+1].data;
                   if(v<0)
                    v*=-1;
                   if(v > 0.00001)
                   {
                     ret=0;
                     breakout = 1;
                     break;
                   }
             }
             if(b==N-2)//check next box horizontal distance
             {
                   double h = sol_cell[a][b+1].data - sol_cell[a+1][b+1].data;
                   if(h<0)
                    h*=-1;
                   if(h > 0.00001)
                   {
                     ret=0;
                     breakout = 1;
                     break;
                   }
             }
      }
      if(breakout==1)
      break;
    }
  }
 return ret;
}



//POSSIBLE LOGICAL FLAW THE OPTIMAL ITERATIONS AND THE GRID INDEPENDANT VALUES DONT MATCH HENCE INFINTE LOOP

void iterations()
{
  remove("RESULT.txt");
 //TO USE ODD OR EVEN NUMBER OF MESH??
 //DOUBLE THE NUMBER AFTER EACH ITERATION AND CHECK THE ADJACENT CELL VLAUES AND COMAPRE THE AVG VALUE OF THE PREV. GRID.
  //start counting M and N from 1,3,5,7,9, and so on till we get compare data = true
  int grid_count=3;//INTIALLY EVEN 1,2,4,8,16....  //3,6,12,24,48...
  while(1)
  {
    M=grid_count;
    N=grid_count;
    //system("cls");
    cout<<"++++++++++"<<endl;
    cout<<"X-GRID = "<<M<<" Y-GRID = "<<N<<endl;
    init_grid();
    solve_iter();
    if(grid_indep_chk() && avg_chk())
      break;
    grid_count*=2;
    if(grid_count>1000)
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
