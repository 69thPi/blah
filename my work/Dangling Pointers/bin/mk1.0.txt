#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


int main1()
{

    char* enc = (char *)malloc(32);
    enc="ABCDEFGH";
    char* data=enc;
    char ** p_dat=&data;
    char ** p_enc=&enc;
    cout<<"addr Data:"<<p_dat<<endl;
    cout<<"addr Enc:"<<p_enc<<endl;
    cout<<"data buffer at enc::";
    puts(data);
    puts(enc);
    char * input= enc;
    char ** p_inp=&input;
    cout<<"addr inp:"<<p_inp<<endl;
    free(enc); ///the data buffer could be accidentially freed.
    cout<<"addr Enc:"<<p_enc<<endl;
     puts(input);
    enc = (char *)malloc(32);
    cout<<"input buffer at address::";
    puts(enc);
    cout<<"addr Enc:"<<p_enc<<endl;

    cin>>enc;

    return 0;
}

int main()
{
    char* data = (char *)malloc(32);

    char **p_d=&data;
    cout<<p_d<<endl;
    cout<<"data buffer at address"<<data<<endl;
     free(data);

    char* input = (char *)malloc(32);
    char **p_inp=&input;
    cout<<p_inp<<endl;
    cout<<"input buffer at address"<<input<<endl;
    cin>>input;
    return 0;
}
