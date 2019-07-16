#include<fstream>
  #include<iostream>
  #include<sstream>
  #include<string>
  #include<stdio.h>
  #include<stdlib.h>
  #include<string.h>

using namespace std;

class student{
   char name[200];
   char branch[2];
   int roll,P,T,yr;
 public:
   student()
   {
     roll=0;
     P=0;
     T=0;
     yr=17;
   }
   student(student &s)
   {
     strcpy(name,s.name);
     strcpy(branch,s.branch);
     roll=s.roll;
     P=s.P;
     T=s.T;
     yr=s.yr;
   }
   void input_roll();
   int ret_p()
   {
     return P;
   }
   int ret_t()
   {
     return T;
   }
   void ret_roll()
   {
     cout<<branch<<roll<<":=";
   }
   void P_incre(int val=1)
   {
     P=P+val;
   }
   void T_incre(int val=1)
   {
     T=T+val;
   }
   int cmp_roll(int r)
   {
     if(roll==r)
      return 1;
     else
      return 0;
   }
   int cmp_yr(int r)
   {
     if(yr==r)
      return 1;
     else
      return 0;
   }
   int cmp_branch(char b[2])
   {
     return strcmp(branch,b);
   }
   void inp_name()
   {
     cout<<"Name:";
     fgets(name,200,stdin);
   }

   void disp()
   {
     cout<<name<<endl;
     cout<<"\t\t  "<<branch<<"  |  "<<roll<<"  |  "<<P<<"  |  "<<T<<endl;
     cout<<"------------------------------------------"<<endl;
   }
   void write(ofstream &f)
   {
     f<<name<<endl;
     f<<"\t\t  "<<branch<<"  |  "<<roll<<"  |  "<<P<<"  |  "<<T<<endl;
     f<<"------------------------------------------"<<endl;
   }
};

student stu[200];
int no_of_stu=0;
string file_name = "data/stu_list.bin";

void student::input_roll()//used for handling roll number
{
 string inp;
 cout<<"Enter roll [11AB000]::";
 getline(cin,inp);
 for(int i=0;i<2;i++)
 branch[i]=inp[i+2];
 branch[2]='\0';
 string num=inp.substr(4,6); //select number part for conversion
 string y=inp.substr(0,2);
 stringstream(num)>>roll; //assign roll form input
 stringstream(y)>>yr; //assign roll form input
 cout<<yr<<branch<<roll<<endl;
}

void present()//update present status of students
{
  string inp;
  char b[2],ig[2];
  int r;
  while(1)
  {
  cout<<"Enter roll [AB000]::";
  getline(cin,inp);
  if(inp.length()>3)
  break;
  }
  string num=inp.substr(2); //select number part for conversion
  stringstream(num)>>r; //assign roll form input
  for(int i=0;i<2;i++)
  b[i]=inp[i];
  b[2]='\0';
  int cnt=0;
  for(int i=0;i<no_of_stu;i++)
  {
    if(stu[i].cmp_roll(r)==1)
    {
      if(stu[i].cmp_branch(b)==0)
      cnt++;
    }
  }
  if(cnt==1)
     {
        //-----------------------------roll number of the required form---------------[
        for(int i=0;i<no_of_stu;i++){
          if(stu[i].cmp_roll(r)==1){
            if(stu[i].cmp_branch(b)==0)
              {
                stu[i].P_incre();
                cout<<"UPDATED"<<endl;
            }}}
       //-----------------------------------------------------------------------------[
     }
  else if(cnt==0)
    cout<<"no record found"<<endl;
  else
    {
      cout<<"Multiple records found, please enter year::";
      int yr;
      cin>>yr;
      gets(ig);
      //-----------------------------roll number of the required form---------------[
      for(int i=0;i<no_of_stu;i++){
        if(stu[i].cmp_roll(r)==1){
          if(stu[i].cmp_branch(b)==0){
            if(stu[i].cmp_yr(yr)==1)
              {
                stu[i].P_incre();
                cout<<"UPDATED"<<endl;
              }
          }}}
     //-----------------------------------------------------------------------------[
    }
}

void inp_details()//Add or start over woth data
{
   student stu;
   ofstream fout;
   fout.open(file_name.c_str(),ios::app | ios::binary);//ios::app |
   while(!0)
     {
       system("cls");
       cout<<"        Database Entry!"<<endl;
       cout<<"=============================="<<endl;
       //input
       stu.inp_name();
       stu.input_roll();
       //write data
       fout.write((char*)(&stu),sizeof(student));
       //ask continue
       cout<<"Do you wish to add more?";
       char ig;
       cin>>ig;
       char ign[2];
       gets(ign);
       //break;
       if(ig=='N' || ig=='n')
        break;
     }
   fout.close();
}

void read()//load data only
{
  ifstream fin;
  fin.open(file_name.c_str(),ios::in | ios::binary);
  student temp;
     while(fin.read((char*)&temp,sizeof(student)))
            {
              stu[no_of_stu]=temp;
              no_of_stu++;
            }
  //number of students in data base
  cout<<"number of students::"<<no_of_stu<<endl;
  fin.close();
}

void read_disp()//load and display ## Standby
{
  ifstream fin;
  fin.open(file_name.c_str(),ios::in | ios::binary);
  student temp;
  //list of students to be manipulated
  cout<<"Name\t\tBranch\tRoll\tP     T"<<endl;
  cout<<"------------------------------------------"<<endl;
     while(fin.read((char*)&temp,sizeof(student)))
            {
              stu[no_of_stu]=temp;
              temp.disp();
              no_of_stu++;
              if(no_of_stu % 70 == 0 )
                system("pause");
            }
  //number of students in data base
  cout<<"number of students::"<<no_of_stu<<endl;
  fin.close();
}

void data_restore_pt()//function for random things
{
  student temp;
  ofstream fout("data/last_save.bin",ios::binary);
  ifstream fin("data/stu_list.bin",ios::binary);
  while(fin.read((char*)&temp,sizeof(student)))
    {
      student copy(temp);
      fout.write((char*)&copy,sizeof(student));
    }
  fout.close();
  fin.close();
}

void enter_attn()//enter day's Attendance
{
  read();
  //===enter roll
  cout<<"Enter number of students present::";
  int num=0;
  cin>>num;
  if(num>no_of_stu)
   exit(0);
  char ig[2];
  gets(ig);
  cout<<"=============================="<<endl;
  for(int i=1;i<=num;i++)
  present();
  //backup point
     data_restore_pt();//creates a copy of last classes attendance
  //write all data
 ofstream fout;
  fout.open(file_name.c_str(), ios::binary);
  //loop over all
  //all T++ and write
    for(int i=0;i<no_of_stu;i++)
    {
      stu[i].T_incre();
      fout.write((char*)(&stu[i]),sizeof(student));
    }
  fout.close();
}

void fill_register()//print in order of Register
{
  read();
  student temp[200],save;
  int i=0;
  ifstream fold("data/last_save.bin",ios::binary);
  while(fold.read((char*)&save,sizeof(student)))
  {
    temp[i++]=save;
  }
  fold.close();
  cout<<"        STUDENTS LAST PRESENT"<<endl;
  cout<<"======================================"<<endl;
  int cnt=1;
  for(int j=0;j<no_of_stu;j++)
    {
      if(stu[j].ret_p()-temp[j].ret_p()==1)
          {
            stu[j].disp();
            cnt++;
          }
      if(cnt % 70 == 0)
          system("pause");
    }
}

void print_notepad(float perc)
{
  read();
  ofstream fout("Attendance_List.txt");
  fout<<"Name\t\tBranch\tRoll\tP     T"<<endl;
  fout<<"------------------------------------------"<<endl;
  for(int i=0;i<no_of_stu;i++)
  {
    if(((float)stu[i].ret_p()/(float)stu[i].ret_t())*100 < perc)
    stu[i].write(fout);
  }
  fout<<"Total Number of Students="<<no_of_stu<<endl;
  fout.close();
  system("Attendance_List.txt");
}

void fast_enter()// enter Attendance samultanetously
{
  read();
  cout<<"Enter total no. of classes conducted=";
  int ttl=0;
  cin>>ttl;
  for(int i=0;i<no_of_stu;i++)
  {
    stu[i].T_incre(ttl);//Increase Total No. of Classes
    stu[i].ret_roll();//to print student roll no.
    int sta_p;
    cin>>sta_p;
    cout<<"==========================="<<endl;
    if(sta_p!=0)// press "0" to skip
     {
       stu[i].P_incre(sta_p);
     }
  }
  ofstream fout;
   fout.open(file_name.c_str(), ios::binary);
     for(int i=0;i<no_of_stu;i++)
       fout.write((char*)(&stu[i]),sizeof(student));
   fout.close();
}

int main()
{
  system("cls");
  cout<<"========SVSAT_Attendance helper.========"<<endl;
  cout<<"      CHOICE                       PRESS"<<endl;
  cout<<" Display All Data                    1"<<endl;
  cout<<" Enter Today's Attendance            2"<<endl;
  cout<<" Fill Register                       3"<<endl;
  cout<<" Add Data                            4"<<endl;
  cout<<" Percentage View                     5"<<endl;
  int ch1;
  cout<<"Your choice::";
  cin>>ch1;
  char ig[2];
  gets(ig);
  switch(ch1)
  {
    case 1:system("cls");
          print_notepad(101);
          break;
    case 2:system("cls");
          enter_attn();
          break;
    case 3:system("cls");
          fill_register();//compares todays data with last class to get current present
          break;
    case 4:system("cls");
          inp_details();
          break;
   case 5:system("cls");
          float z;
          cout<<"Enter Threshold Percentage::";
          cin>>z;
          print_notepad(z);
          break;
    case 0:system("cls");
          fast_enter();
          break;
    default:cout<<"Wrong input! Please Select again."<<endl;
  }

}
