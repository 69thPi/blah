#include <iostream>
#include <stdlib.h>

using namespace std;

struct grid{
  double data;
  double del_x;
  double del_y;
  double x_e;
  double x_w;
  double y_n;
  double y_s;
  double ap;
  double an;
  double as;
  double ae;
  double aw;
};
/////////GLOBAL VARS/////////
  int width=1,height=1,N=5,M=5;
  grid cell[10][10];//no of divisions
  double dir_E=-1,dir_W=1,dir_N=0,dir_S=0;

void display()
{
  for(int j=N-1;j>=0;j--)
  {
    for(int i=0;i<M;i++)
    {
      cout<<cell[i][j].data<<"\t"; //<<","<<cell[i][j].an<<","<<cell[i][j].as<<","<<cell[i][j].ae<<","<<cell[i][j].aw<<","<<cell[i][j].ap<<"\t";//
    }
    cout<<"\n";
  }
}
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

void init_cells()
{
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<M;j++)
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

}

/////////////////////////////////////CELL SETUP OVER/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////FNS FOR EQUATIONS////////////////////////////////////

//ap(Tij)+an(Ti,j+1)+as(Ti,j-1)+ae(Ti+1,j)+aw(Ti-1,j)=0
void dir_solve_cell(int i,int j,int n)//solves eqn for respective cells/
{
  switch(n)
  {

    case 1:cell[i][j].data = ((cell[i][j].an*cell[i][j+1].data)+(cell[i][j].as*dir_S)+(cell[i][j].ae*cell[i+1][j].data)+(cell[i][j].aw*cell[i-1][j].data))/(cell[i][j].ap);
          break;
    case 2:cell[i][j].data = ((cell[i][j].an*dir_N)+(cell[i][j].as*cell[i][j-1].data)+(cell[i][j].ae*cell[i+1][j].data)+(cell[i][j].aw*cell[i-1][j].data))/(cell[i][j].ap);
          break;
    case 3:cell[i][j].data = ((cell[i][j].an*cell[i][j+1].data)+(cell[i][j].as*cell[i][j-1].data)+(cell[i][j].ae*cell[i+1][j].data)+(cell[i][j].aw*dir_W))/(cell[i][j].ap);
          break;
    case 4:cell[i][j].data = ((cell[i][j].an*cell[i][j+1].data)+(cell[i][j].as*cell[i][j-1].data)+(cell[i][j].ae*dir_E)+(cell[i][j].aw*cell[i-1][j].data))/(cell[i][j].ap);
          break;
    case 5:cell[i][j].data = ((cell[i][j].an*cell[i][j+1].data)+(cell[i][j].as*dir_S)+(cell[i][j].ae*cell[i+1][j].data)+(cell[i][j].aw*dir_W))/(cell[i][j].ap);
          break;
    case 6:cell[i][j].data = ((cell[i][j].an*cell[i][j+1].data)+(cell[i][j].as*dir_S)+(cell[i][j].ae*dir_E)+(cell[i][j].aw*cell[i-1][j].data))/(cell[i][j].ap);
          break;
    case 7:cell[i][j].data = ((cell[i][j].an*dir_N)+(cell[i][j].as*cell[i][j-1].data)+(cell[i][j].ae*cell[i+1][j].data)+(cell[i][j].aw*dir_W))/(cell[i][j].ap);
          break;
    case 8:cell[i][j].data = ((cell[i][j].an*dir_N)+(cell[i][j].as*cell[i][j-1].data)+(cell[i][j].ae*dir_E)+(cell[i][j].aw*cell[i-1][j].data))/(cell[i][j].ap);
          break;
    case 9:cell[i][j].data = ((cell[i][j].an*cell[i][j+1].data)+(cell[i][j].as*cell[i][j-1].data)+(cell[i][j].ae*cell[i+1][j].data)+(cell[i][j].aw*cell[i-1][j].data))/(cell[i][j].ap);
          break;
  }
}

void solve_del_sq_t_dir()
{
  for (int y=0;y<N;y++)
  {
    for(int x=0;x<M;x++)
    {
      if(x>0 && x<M-1 && y>0 && y<N-1)
        dir_solve_cell(x,y,9);
      else
      {
        if(x>0 && x<M-1 && y==0)
          dir_solve_cell(x,y,1);
        else if(x>0 && x<M-1 && y==N-1)
          dir_solve_cell(x,y,2);
        else if(y>0 && y<N-1 && x==0)
          dir_solve_cell(x,y,3);
        else if(y>0 && y<N-1 && x==M-1)
          dir_solve_cell(x,y,4);
        else if(x==0 && y==0)
          dir_solve_cell(x,y,5);
        else if(x==0 && y==N-1)
          dir_solve_cell(x,y,7);
        else if(x==M-1 && y==0)
          dir_solve_cell(x,y,6);
        else if(x==M-1 && y==N-1)
          dir_solve_cell(x,y,8);
      }
    }
  }

}
/////////////////////////////////////FLOW FUNCTIONS/////////////////////////////////////
void iterations()
{
  int cnt_stp=1;
  while(cnt_stp<=50)
  {
    //cout<<"============================"<<"\t"<<cnt_stp<<"\t"<<"============================"<<endl;
    solve_del_sq_t_dir();
    //display();
    cnt_stp++;
  }
  display();
}

int main()
{
  //DEFINE GRID
 cout<<"enter the grid height=";
 cin>>height;
 cout<<"enter the grid width=";
 cin>>width;
 //DEFINE DISTRIBUTION
 cout<<"enter number of Y divisions(<100):";
 cin>>N;
 cout<<"enter number of X divisions(<100):";
 cin>>M;
  //INITIALIZE GRID CELLS
  init_cells();
  ///INITIALIZATION OVER
  ///DEFINE BOUNDARY CONDIITONS # ALL DIRECHLET
  cout<<"-----------For DIRECHLET conditions-----------"<<endl;
  cout<<"Enter North boundary Temp::";
  cin>>dir_N;
  cout<<"Enter South boundary Temp::";
  cin>>dir_S;
  cout<<"Enter East boundary Temp::";
  cin>>dir_E;
  cout<<"Enter West boundary Temp::";
  cin>>dir_W;
  //system("cls");
  ///USER INTERFACE OVER
  ///SOLVE GRID
  iterations();
  ///PUBLISH RESULTS TO .txt
}
