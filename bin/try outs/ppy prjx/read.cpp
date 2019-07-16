#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

int main () {
  ofstream myfile;
  myfile.open ("example.txt",ios::app);
  myfile << "Writing this to a file.\n";
  myfile.close();

  char *name= "example.txt";
  ifstream file;
string line;
  file.open(name);
  if (file.is_open())
  {
    while ( getline (file,line) )
    {
      cout << line << '\n';
    }
    file.close();
  }
  return 0;
}
