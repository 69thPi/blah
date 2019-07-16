#include "res.h"
#include "grid_gen.h"
#include "flow.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

grid sol_cell[70][100];//steps * grid
double matA[100][100];
double matB[100];
double EAST,WEST;
double alph_0=1,B=0,del_t,T_inf=0;//Default conditions set to isotropic Alpha =1;


//DATA MANIPULATION FUNCTIONS
void assign_coeffs(int i,int t)//called while solving for each cell
{
  double P,E,W,L;
  if(i==0)
  {
    W= -1 * alph_0;
    // (A_0)
    E =-1 * alph_0 * (1 + B * sol_cell[0][i].del_x * 0.5f);
    // (A_0 (1 + B * del_x (p +0.5))
  }
  else if(i==M-1)
  {
    W=-1 * alph_0 * (1 + B * sol_cell[0][i].del_x * (M - 2.5f));
    // (A_0* (1 + B * del_t (p -1.5))
    E = -1 * alph_0;
    // (A_0)
  }
  else
  {
      W= -1 * alph_0 * (1 + B * sol_cell[0][i].del_x * ((double)i - 1.5f));
    // A_0 * (1 + B * del_t (p -1.5))
    E =-1 * alph_0 * (1 + B * sol_cell[0][i].del_x * ((double)i + 0.5f));
    // A_0 * (1 + B * del_t (p +0.5))
  }
     L= sol_cell[t-1][i].data;
     double theta=0;
     theta = del_t / (double)pow(sol_cell[0][i].del_x,2) ;
     E *= theta;
     W *= theta;
     P = (double)1 - (E + W);
  if(i==0)
  {
    if(w_typ==1)//direchlet
    {
      sol_cell[t][i].aw = 0;
      sol_cell[t][i].ap = P-W;
      sol_cell[t][i].ae = E;
      sol_cell[t][i].lhs = sol_cell[t-1][i].data -(double)2*W*WEST;
    }
    else if(w_typ==2)//neumann
    {
      sol_cell[t][i].aw = 0;
      sol_cell[t][i].ap = W + P;
      sol_cell[t][i].ae = E;
      sol_cell[t][i].lhs = sol_cell[t-1][i].data - W*WEST*sol_cell[0][i].del_x;
    }
    else if(w_typ==3)//robins
    {
      theta = 2 / sol_cell[0][i].del_x * WEST;
      sol_cell[t][i].aw = 0;
      sol_cell[t][i].ap = (W * (theta - 1 / theta + 1)) + P;
      sol_cell[t][i].ae = E;
      sol_cell[t][i].lhs = sol_cell[t-1][i].data - (((double)2 / theta + 1) * T_inf  * W);
    }
  }
  else if(i==M-1) ///last box
  {
    if(e_typ==1)//direchlet
    {
      sol_cell[t][i].aw = W;
      sol_cell[t][i].ap = P-E;
      sol_cell[t][i].ae = 0;
      sol_cell[t][i].lhs = sol_cell[t-1][i].data  -(double)2*E*EAST;
    }
    else if(e_typ==2)//neumann
    {
      sol_cell[t][i].aw = W;
      sol_cell[t][i].ap = P+E;
      sol_cell[t][i].ae = 0;
      sol_cell[t][i].lhs = sol_cell[t-1][i].data + E*EAST*sol_cell[0][i].del_x;
    }
    else if(e_typ==3)//robins
    {
      theta = 2 / sol_cell[0][i].del_x * EAST;
      sol_cell[t][i].aw = W;
      sol_cell[t][i].ap = ((theta - 1 / theta + 1) * E) + P;
      sol_cell[t][i].ae = 0;
      sol_cell[t][i].lhs =  sol_cell[t-1][i].data - (((double)2 / theta + 1) * T_inf * E);
    }
  }
  else
  {
    sol_cell[t][i].aw = W;
    sol_cell[t][i].ap = P;
    sol_cell[t][i].ae = E;
    sol_cell[t][i].lhs = sol_cell[t-1][i].data;
  }
}

void gen_TDMA(int t)
{
  for(int i=0;i<M;i++)
  {
    if(i!=0)
    matA[i][i-1]=sol_cell[t][i].aw;
    matA[i][i]=sol_cell[t][i].ap;
    if(i!=M-1)
    matA[i][i+1]=sol_cell[t][i].ae;
    //setting up matB too!
    matB[i]=sol_cell[t][i].lhs;
  }
}

void solve_TDMA(int t)//for time step t
{
  system("cls");
  for(int i=1;i<M;i++)//leave 0th row
  {
    double frac = (double)matA[i][i-1] / (double)matA[i-1][i-1];
    matA[i][i-1] = matA[i][i-1] - frac * matA[i-1][i-1];
    matA[i][i] = matA[i][i] - frac * matA[i-1][i];
    matB[i] = matB[i] - frac * matB[i-1];
  }
  //calc values
  sol_cell[t][M-1].data = (double)matB[M-1] / (double)matA[M-1][M-1];
  for(int i=M-2;i>=0;i--)
     sol_cell[t][i].data = (double)((double)matB[i] - (double)matA[i][i+1] * sol_cell[t][i+1].data ) / (double)matA[i][i] ;
}

////DATA OUTPUT FUNCTIONS
void grid_read()//read grid and init matA and matB
{
  grid temp;
  int i=0;
  ifstream fin("grid0.dat",ios::binary);
  while(fin.read((char*)&temp,sizeof(grid)))
  {
    sol_cell[0][i]=temp;
    i++;
  }
  fin.close();
  for(int j=0;j<i;j++)
  {
    for(int k=0;k<i;k++)
    matA[j][k] = 0;
    matB[j]=0;
  }
}
void display(int x)
{
  for(int i=0;i<M;i++)
   {
     cout<<sol_cell[x][i].data<<"  ";
     if(i!=M-1)
     cout<<"|  ";
   }
   cout<<endl;
}
void notepad(int x)//writes final grid RESULT
{
  ofstream fout("RESULT1.txt");
  for(int i=0;i<M;i++)
    {
      fout<<sol_cell[x][i].data<<endl;//(i*sol_cell[0][0].del_x)+(sol_cell[0][0].del_x/2)<<"\t"<<
    }
  fout.close();
}

////SET UP THE USER PREFERENCES
double ret_bound_val(int x)
{
  double inp;
  if(x==1)
  cout<<"ENTER DIRECHLET BOUNDARY VALUE::";
  else if(x==2)
  cout<<"ENTER NEUMANN BOUNDARY VALUE::";
  else
  cout<<"ENTER ROBIN'S BOUNDARY VALUE::k(T-To)/nEnter k::";
  cin>>inp;
  return inp;
}
void solve_setup()
{
  //ask input values for all boundaries as per conditions
  system("cls");
  cout<<"=====ENTER BOUNDARY CONDITION====="<<endl;
  cout<<"\n==========FOR WEST WALL==========="<<endl;
  WEST=ret_bound_val(w_typ);
  cout<<"\n==========FOR EAST WALL==========="<<endl<<endl;
  EAST=ret_bound_val(e_typ);
}

/// ITERATE THE GRID
void iterations()
{
  grid_read();//read the grid from the saved file.
  solve_setup();//ask for solving input values
  int ttl_count,x=1;//ttl_count keeps track of the total number of iterations to be performed
  double Time=0.2f,D_t=0.2f;//user input #time= time wanted #D_t =time step required
  system("cls");
  // cout<<"     ::INPUT PARAMETERS::"<<endl;
  // cout<<"============================="<<endl;
  // cout<<"<::For A=A_o(1+Bx)::>"<<endl;
  // cout<<"Enter A_o::";
  // cin>>alph_0;
  cout<<"Enter B::";
  cin>>B;
  cout<<"Enter time instant::";
  cin>>Time;
  // cout<<"Enter time step::";
  // cin>>D_t;
  ttl_count=(double)Time/D_t+2;
  while(x<ttl_count)
  {
    del_t=D_t*x;
    cout<<"del_t::"<<del_t<<endl;//comment for final
    for(int i=0;i<M;i++)
      assign_coeffs(i,x);
      gen_TDMA(x);
      solve_TDMA(x++);
  }
  notepad(--x);
  remove("grid0.dat");
  system("cls");
  cout<<"==================RESULT=================="<<endl;
  display(x);
  cout<<"=========================================="<<endl;
  cout<<"Number of iterations :: "<<x<<endl;
  cout<<"=========================================="<<endl;
  for(int i=0;i<x;i++)
  {
    cout<<"del_t= "<<i*D_t<<endl;
    cout<<"------------------------------------------"<<endl;
    display(i);
    cout<<"=========================================="<<endl;
  }
}
