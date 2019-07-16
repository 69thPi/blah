#include <iostream>
#include <fstream>

using namespace std;


struct grid{
  double data;
  double del_x;
  double del_y;
};

grid cell[5][5];
grid new_cell[5][5];

int M=2,N=3;

void grid_write()
{
  ofstream fout("grid.dat",ios::binary);
  for(int j=0;j<N;j++)
  {
    for(int i=0;i<M;i++)
    {
      fout.write((char*)&cell[i][j],sizeof(grid));
    }
  }
  fout.close();
}
void grid_read()
{
  grid temp;
  int i=0,j=0;
  ifstream fin("grid.dat",ios::binary);
  cout<<"####"<<endl;
  while(fin.read((char*)&temp,sizeof(grid)))
  {
    new_cell[i][j]=temp;
    cout<<temp.data<<endl;
    cout<<new_cell[i][j].data<<endl;
    i++;
    if(i==M)
    {
      cout<<"in"<<endl;
      i=0;
      j++;
    }

  }
  cout<<"+++++"<<endl;
  fin.close();
}

int main()
{
  double cnt=1;
  for(int j=0;j<N;j++)
  {
    for(int i=0;i<M;i++)
    {
      cell[i][j].data=cnt++;
      cell[i][j].del_x=0.5;
      cell[i][j].del_y=0.3;
    }
  }
  grid_write();
  grid_read();
  for(int j=N-1;j>=0;j--)
  {
    for(int i=0;i<M;i++)
    {
      cout<<cell[i][j].data<<"\t";
    }
    cout<<endl;
  }
  cout<<"=================================="<<endl;
  for(int j=N-1;j>=0;j--)
  {
    for(int i=0;i<M;i++)
    {
      cout<<new_cell[i][j].data<<"\t";
    }
    cout<<endl;
  }
}
