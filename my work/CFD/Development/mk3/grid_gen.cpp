#include "res.h"
#include "flow.h"
#include <fstream>
#include <iostream>

using namespace std;

/////////GLOBAL VARS/////////
  grid cell[100][100];//no of divisions
/////////////////////////////////////INITIAL CELL SETUP/////////////////////////////////////
void assign_dim(grid &temp)
{
  temp.del_y=(double)height/(double)N;
  temp.del_x=(double)width/(double)M;
}

void assign_params(grid &temp)//set distance of cell edges from CG; ###for rectangular cells ONLY
{
  temp.x_e = temp.del_x/((double)2);
  temp.x_w = temp.del_x/((double)2);
  temp.y_n = temp.del_y/((double)2);
  temp.y_s = temp.del_y/((double)2);
}

void assign_coeffs(int i,int j)//called while solving for each cell
{
  double xw,xe,yn,ys;
  //mid cells
  if(i>0 && i<M-1 && j>0 && j<N-1)
    {
      xw=cell[i-1][j].x_e + cell[i][j].x_w;
      yn=cell[i][j].y_n + cell[i][j+1].y_s;
      ys=cell[i][j-1].y_n + cell[i][j].y_s;
      xe=cell[i][j].x_e + cell[i+1][j].x_w;
    }
  else//boundary cells
  {
    if(i==0 && j==0)
    {
      yn=cell[i][j].y_n + cell[i][j+1].y_s;
      ys= 2 * cell[i][j].y_s;
      xe=cell[i][j].x_e + cell[i+1][j].x_w;
      xw= 2 * cell[i][j].x_w;
    }
    else if(i==0 && j==N-1)
    {
      yn= 2 * cell[i][j].y_n;
      ys=cell[i][j-1].y_n + cell[i][j].y_s;
      xe=cell[i][j].x_e + cell[i+1][j].x_w;
      xw= 2 * cell[i][j].x_w;
    }
    else if(i==M-1 && j==0)
    {
      yn=cell[i][j].y_n + cell[i][j+1].y_s;
      ys= 2 * cell[i][j].y_s;
      xe= 2 * cell[i][j].x_e;
      xw=cell[i-1][j].x_e + cell[i][j].x_w;
    }
    else if(i==M-1 && j==N-1)
    {
      yn= 2 * cell[i][j].y_n;
      ys=cell[i][j-1].y_n + cell[i][j].y_s;
      xe= 2 * cell[i][j].x_e;
      xw=cell[i-1][j].x_e + cell[i][j].x_w;
    }
  }

  cell[i][j].aw=cell[i][j].del_y/xw;
  cell[i][j].an=cell[i][j].del_x/yn;
  cell[i][j].ae=cell[i][j].del_y/xe;
  cell[i][j].as=cell[i][j].del_x/ys;
  cell[i][j].ap = 1 * (cell[i][j].an + cell[i][j].as + cell[i][j].ae + cell[i][j].aw);// -1 is compensated by taking terms to RHS.
}

void assign_eqn(int No,int S,int E,int W)//arguments store the equation type applied to their respective boundaries
{
  for (int y=0;y<N;y++)
  {
    for(int x=0;x<M;x++)
    {
      if(x>0 && x<M-1 && y>0 && y<N-1)
        cell[x][y].eqn=0;
      else
      {
        if(x>0 && x<M-1 && y==0) //south mid boundary
            {
              switch(S)
              {
                case 1:cell[x][y].eqn=2; //direchlet south
                       break;
                case 2:cell[x][y].eqn=10;
                       break;
                case 3:
                       break;
              }
            }
        else if(x>0 && x<M-1 && y==N-1) //north mid boundary
            {
              switch(No)
              {
                case 1:cell[x][y].eqn=1; //direchlet north
                       break;
                case 2:cell[x][y].eqn=9;
                       break;
                case 3:
                       break;
              }
            }
        else if(y>0 && y<N-1 && x==0) //west mid boundary
            {
              switch(W)
              {
                case 1:cell[x][y].eqn=4; //direchlet west
                       break;
                case 2:cell[x][y].eqn=12;
                       break;
                case 3:
                       break;
              }
            }
        else if(y>0 && y<N-1 && x==M-1) //east mid boundary
            {
              switch(E)
              {
                case 1:cell[x][y].eqn=3;// direchlet east
                       break;
                case 2:cell[x][y].eqn=11;
                       break;
                case 3:
                       break;
              }
            }
        else if(x==0 && y==0)  //south west cell
            {
                if(S==1)
                    {
                      if(W==1)
                       cell[x][y].eqn=8;
                      else if(W==2)
                      cell[x][y].eqn=23;
                      else if(W==3);
                    }
                else if(S==2)
                    {
                      if(W==1)
                      cell[x][y].eqn=45;
                      else if(W==2)
                      cell[x][y].eqn=16;
                      else if(W==3);
                    }
                else if(S==3)
                    {
                      if(W==1);
                      else if(W==2);
                      else if(W==3);
                    }
            }
        else if(x==0 && y==N-1) //north west cell
            {
               if(No==1)
                   {
                     if(W==1)
                      cell[x][y].eqn=6;
                     else if(W==2)
                      cell[x][y].eqn=31;
                     else if(W==3);
                   }
               else if(No==2)
                   {
                     if(W==1)
                     cell[x][y].eqn=33;
                     else if(W==2)
                     cell[x][y].eqn=14;
                     else if(W==3);
                   }
               else if(No==3)
                   {
                     if(W==1);
                     else if(W==2);
                     else if(W==3);
                   }
             }
        else if(x==M-1 && y==0) //south east cell
            {
              if(S==1)
                  {
                    if(E==1)
                    cell[x][y].eqn=7;
                    else if(E==2)
                    cell[x][y].eqn=37;
                    else if(E==3);
                  }
              else if(S==2)
                  {
                    if(E==1)
                    cell[x][y].eqn=39;
                    else if(E==2)
                    cell[x][y].eqn=15;
                    else if(E==3);
                  }
              else if(S==3)
                  {
                    if(E==1);
                    else if(E==2);
                    else if(E==3);
                  }
        }
        else if(x==M-1 && y==N-1) //north east cell
          {
            if(No==1)
                {
                  if(E==1)
                  cell[x][y].eqn=5;
                  else if(E==2)
                  cell[x][y].eqn=25;
                  else if(E==3);
                }
            else if(No==2)
                {
                  if(E==1)
                  cell[x][y].eqn=27;
                  else if(E==2)
                  cell[x][y].eqn=13;
                  else if(E==3);
                }
            else if(No==3)
                {
                  if(E==1);
                  else if(E==2);
                  else if(E==3);
                }
           }
      }
    }
  }

}

void grid_write()
{
  grid temp;
  ofstream fout("grid.dat",ios::binary);
  for(int j=0;j<N;j++)
  {
    for(int i=0;i<M;i++)
    {
      temp=cell[i][j];
      fout.write((char*)&temp,sizeof(grid));
    }
  }
  fout.close();
}

////////////////////////////////////////////USER FUNCTIONS////////////////////////////////////////////
void init_grid()
{
  ///DEFINE GEOMETRICAL PARAMS
  for(int j=0;j<N;j++)
  {
    for(int i=0;i<M;i++)
    {
      cell[i][j].data=0;
      assign_dim(cell[i][j]);//assign del_x and del_y;
      assign_params(cell[i][j]);//assign values of x_w,x_e,y_n,y_s;
    }
  }
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<M;j++)
    {
      assign_coeffs(i,j);//assign coefficients for each block
    }
  }
  ///DEFINE EQUATION FOR EACH CELL
  assign_eqn(n_typ,s_typ,e_typ,w_typ);

  //DEVELOPER MODE FEATURE SEE THE EQNS ON CELLS
  // for(int j=N-1;j>=0;j--)
  // {
  //   for(int i=0;i<M;i++)
  //   cout<<cell[i][j].eqn<<"\t";
  //   cout<<endl;
  // }
  grid_write();
}
