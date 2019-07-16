#include <iostream>

using namespace std;

int main()
{
    int a=5;
    int * ptr=NULL;
    ptr=&a;
    cout<<"value= "<<*ptr<<endl;
    cout<<"Address="<<ptr<<endl;
    cin>>a;
    return 0;
}
