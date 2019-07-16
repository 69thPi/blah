#include<bits/stdc++.h>

using namespace std;

/// //////////////GLOBAL VARS///////////////////////
int nOfPe=0;
int nOfSub=0;
int ttbl[10];/// for reading subjects
char subjects[20][30];/// subjects for each day
char temp[20][30];
int ext[52];///extract
char ig[2];
int weekdayInit=0;

class attn
{
    char subName[30];
    int P;
    int A;
    int T;
    bool bunk;
    int dd;
    int mm;
    int yyyy;
    char day_val;
public:
    attn()
    {
        P=0;
        A=0;
        T=0;
        bunk=false;
        dd=0;
        mm=0;
        yyyy=0;
        day_val=' ';
    }
    void copyfn(attn &a)
    {
        strcpy(subName,a.subName);
        P=a.P;
        A=a.A;
        T=a.T;
        dd=a.dd;
        mm=a.mm;
    }
    void disp()
    {
        cout<<"----"<<subName<<"----"<<endl;
        cout<<"present :"<<P<<endl;
        cout<<"absent :"<<A<<endl;
        cout<<"total :"<<T<<endl;
        cout<<"bunk :"<<bunk<<endl;
        cout<<dd<<"-"<<mm<<"-"<<yyyy<<endl;
    }
    void getName(char n[30])
    {
        strcpy(subName,n);
    }
    int srch(char name[30])
    {
        return strcmpi(name,subName);
    }
    int match(int d,int m,int y,char name[30])
    {
        if((srch(name)==0)&& dd==d && mm==m && yyyy==y)
            return 1;
        else
            return 0;
    }
    int datenottoday();
    void askInp();
    void opn2();
    void edit();
};
tm* get_node()/// TO GET SYSTEM TIME
{
  time_t tym;
  tm *node;
  time(&tym);
  node=localtime(&tym);
  return node;
}
/// INDEPENDANT FUNCTIONS
void DispDay(int n)
{
    switch(n)
        {
        case 0:cout<<"Sunday"<<endl;
                break;
        case 1:cout<<"Monday"<<endl;
                break;
        case 2:cout<<"Tuesday"<<endl;
                break;
        case 3:cout<<"Wednesday"<<endl;
                break;
        case 4:cout<<"Thursday"<<endl;
                break;
        case 5:cout<<"Friday"<<endl;
                break;
        }
}
/// ////////////////INITIAL SETUP/////////////////////
void write_ttbl()
{
    int timeTbl[5][10];///store the periods
    cout<<"========INITIAL SETUP========"<<endl;
    cout<<"Choose your working days?"<<endl;
    cout<<"   PRESS 1 for:      PRESS 2 for"<<endl;
    cout<<"     SUNDAY              MONDAY"<<endl;
    cout<<"     MONDAY              TUESDAY"<<endl;
    cout<<"     TUESDAY             WEDNESDAY"<<endl;
    cout<<"     WEDNESDAY           THURSDAY"<<endl;
    cout<<"     THHURSDAY           FRIDAY"<<endl;
    cout<<"enter you option:";
    int in;
    cin>>in;
    in--;///0 for sunday //1 for friday
    weekdayInit=in;
    system("cls");
    cout<<"enter number of subjects:";
    cin>>nOfSub;
    if(nOfSub==0)
    {
        cout<<"ERROR! not possible"<<endl;
        exit(0);
    }
    gets(ig);///to handle enter button
    system("pause");
    system("cls");
    cout<<"PLEASE ENTER SUBJECT NAMES"<<endl;
    for(int i=0;i<nOfSub;i++)
    {
        cout<<"enter subject "<<i+1<<" :";
        gets(subjects[i]); ///enter subject names
    }
    system("cls");
    cout<<"enter max. number of periods per day:";
    cin>>nOfPe; ///enter number of periods max.
    if(nOfPe==0)
    {
        cout<<"ERROR! not possible"<<endl;
        exit(0);
    }
    for(int j=0;j<5;j++)
    {
        system("cls");
        cout<<"IF YOU HAVE TWO CONSECUTIVE PERIODS THEN PLEASE ENTER THEM AS ONE"<<endl;
        for(int k=0;k<nOfSub;k++)
           cout<<"-> "<<k+1<<" for "<<subjects[k]<<endl;
        DispDay(j+weekdayInit);
     for(int i=0;i<nOfPe;i++)
     {
        do{
        cout<<"enter subject "<<i+1<<" :";
        cin>>timeTbl[j][i];
        timeTbl[j][i]-=1;
        }while(timeTbl[j][i]>=nOfSub || timeTbl[j][i]<0);
     }
    }
    ofstream subname("subjects.txt");
    ofstream ttbl("timetable.txt");
    for(int i=0;i<nOfSub;i++)///write subjects into file
        subname<<subjects[i]<<endl;
    for(int i=0;i<5;i++)
        for(int j=0;j<nOfPe;j++)
          ttbl<<timeTbl[i][j]<<endl;
    ttbl<<weekdayInit<<endl;///second last element
    ttbl<<nOfPe<<endl;/// last element of ttbl.txt
    subname.close();
    ttbl.close();
}
/// ///////////////RUN///////////////////
void getSub()
{
    char t[30];
    int k=0;
     ifstream fin1("subjects.txt");
    while(fin1.getline(t,30,'\n'))
    {
        strcpy(temp[k],t);
        k++;
    }
    nOfSub=k;///global var set
    fin1.close();
}
void getOrder()
{
    ifstream fin("timetable.txt");
    int n,c=0;
    while(fin>>n) ///read data
    {
        ext[c]=n;
        c++;
    }
    nOfPe=ext[--c];/// global var set to last element stored in extract
    weekdayInit=ext[--c];
    fin.close();
}
void getPrd()///get subjects for each day
{
    getOrder();
    int day=get_node()->tm_wday-weekdayInit;
    int init=day*nOfPe,j=0;
    for(int i=init,j=0;i<init+nOfPe;i++,j++)
    {
      ttbl[j]=ext[i];/// ext global
    }
    getSub();/// set temp array
    for(int i=0;i<nOfPe;i++)
    {
        strcpy(subjects[i],temp[ttbl[i]]);/// temp global
    }
}
void dispAllSubs()
{
        getSub();///set temp to all subs
        cout<<"----CHOOSE SUBJECT----"<<endl;
        for(int i=0;i<nOfSub;i++)
        {
            cout<<"  "<<i+1<<"     "<<temp[i]<<endl;
        }
        cout<<"your choice:";
}
void readAttn(int &cnt,int flag=0)
{
    cnt=0;
    attn node;
    ifstream reAtn("attendance.dat",ios::binary);
     while(reAtn.read((char*)&node,sizeof(attn)))
     {
         if(flag==1)///call by display fn
           node.disp();
        cnt++;
     }
    reAtn.close();
}
void initNode(char name[30],attn &node)
{
    attn T;
    int cnt;
    readAttn(cnt);
    if(cnt!=0)
      cnt--;

    ifstream init("attendance.dat",ios::binary);
    if(!init)
        node.getName(name);///if file isnt made for first time
    else
    {
        int found=0;
            for(int i=cnt;i>=0;i--)
            {
                init.seekg(i*sizeof(attn));
                init.read((char*)&T,sizeof(attn));
                if(T.srch(name)==0)///if match then initialize
                {
                    node.copyfn(T);///copy function
                    found=1;
                    break;
                }
            }
            if(found==0)///no match found
                    node.getName(name);
    }
    init.close();
}
void inp_daily()
{
    getPrd();
    int day=get_node()->tm_wday;
    if(day>=weekdayInit && day<=(weekdayInit+4))
    {
        for(int i=0;i<nOfPe;i++)
        {
            attn node;
            initNode(subjects[i],node);///initialize data//along with subject name acc. to tym table
            if(node.datenottoday()==1)///true
            {
                node.askInp();/// update record
                ofstream wrAtn("attendance.dat",ios::binary|ios::app);
                wrAtn.write((char*)&node,sizeof(attn));///save data
                wrAtn.close();
            }
            else
            {
                cout<<"\tDONE FOR TODAY!!\nYou have already filled the attendance."<<endl;
                break;
            }
        }

    }
    else
        cout<<"No Classes Today"<<endl;

}

/// CLASS FUNCTIONS
int attn::datenottoday()
    {
        if(dd==get_node()->tm_mday && mm==get_node()->tm_mon)
            return 0;///false
        else
            return 1;///date is not todays///true
    }
void attn::askInp()/// asks for input of subjects acc. to time table //v1.01
{
    int flag=0;
        cout<<"-----enter for "<<subName<<"-----"<<endl;
        cout<<"enter P=present A=absent B=bunk"<<endl;
            char inp;
                cin>>inp;

                switch(inp)
                {
                    case 'p':
                    case 'P':P++;
                            day_val='P';
                            T++;
                        break;
                    case 'a':
                    case 'A':A++;
                             day_val='A';
                            T++;
                        break;
                    case 'b':
                    case 'B':A++;
                             day_val='A';
                            T++;
                            bunk=true;
                        break;
                  default:flag=1;
                        break;
                }
                 dd=get_node()->tm_mday;
                 mm=get_node()->tm_mon;
                 yyyy=get_node()->tm_year+1900;
                if(flag==1)
                    askInp();

}
void attn::opn2()/// error:function does not work for more than one record
{
        char src[30];
        int ch;
        system("cls");
        cout<<"---------VIEW---------"<<endl;
        dispAllSubs();
        cin>>ch;
        ch--;
        strcpy(src,temp[ch]);/// temp value of that ch it has to display subjects
        attn media;
        ifstream a("attendance.dat",ios::binary);
        remove("display.txt");///to clear any prev record;
        ofstream disp("display.txt");
        int cnt=0;
        float perc=0;
        disp<<"  ATTENDANCE   |          TOTAL             |   BUNK   |   DATE"<<endl;
        disp<<"------------------------------------------------------------------"<<endl;
        disp<<"               |PRESENT | ABSENT  | CLASSES |          |       "<<endl;
        disp<<"=================================================================="<<endl;
        while(a.read((char*)&media,sizeof(attn)))///assuming data is in ascending order of date(dd+mm)
        {
            char bnk[]="NO ";
            if(media.srch(src)==0)///match found
            {
                if(media.bunk==1)
                    strcpy(bnk,"YES");
               disp<<"      "<<media.day_val<<"        |   "<<media.P<<"    |    "<<media.A<<"    |    "<<media.T<<"    |   "<<bnk<<"    | "<<media.dd<<"-"<<media.mm<<"-"<<media.yyyy<<endl;
               perc=((float)media.P/media.T)*100;
               cnt++;
            }
        }
        if(cnt!=0)
             disp<<"Attendance Percentage::"<<perc<<"%"<<endl;
        else
            disp<<"              ***NO DATA***"<<endl;
        disp.close();
        a.close();
        system("display.txt");///opens file
        remove("display.txt");///delete file display file.txt
}
void attn::edit()
{
    system("cls");
    int ttla,ttlp;
    dispAllSubs();
    int ch;
    cin>>ch;
    ch--;
    gets(ig);
    char dat[10];
    while(strlen(dat)!=10)
    {
    cout<<"enter the date of attendance:(dd-mm-yyyy)\n>>";
    gets(dat);
    }
    int d=(dat[0]-48)*10+(dat[1]-48);
    int m=(dat[3]-48)*10+(dat[4]-48);
    int y=(dat[6]-48)*1000+(dat[7]-48)*100+(dat[8]-48)*10+(dat[9]-48);
    ifstream rd("attendance.dat",ios::binary);
    ofstream tp("temp.dat",ios::binary);
    attn t;
    int found=0;
    while(rd.read((char*)&t,sizeof(attn)))
    {
        if(found==0)/// not found yet
        {
            if(t.match(d,m,y,temp[ch])==0) ///before found
           {
               tp.write((char*)&t,sizeof(attn));
           }
        else if(t.match(d,m,y,temp[ch])==1)/// if match found
           {
              /// DISP OLD INP
              cout<<"you were";
              switch(t.day_val)
              {
                  case 'P':cout<<" Present"<<endl;
                            t.P--;
                  break;
                  case 'A':cout<<" Absent"<<endl;
                            t.A--;
                  break;
              }
              t.bunk=false;
              cout<<">>what is your new input?"<<endl;
              cout<<"enter P=present A=absent B=bunk"<<endl;
              char inp;
              int flag=0;
              while(flag==0)
              {
                cin>>inp;
                switch(inp)
                {
                    case 'p':
                    case 'P':t.P++;
                            t.day_val='P';
                            flag=1;
                        break;
                    case 'a':
                    case 'A':t.A++;
                             t.day_val='A';
                             flag=1;
                        break;
                    case 'b':
                    case 'B':t.A++;
                             t.day_val='A';
                            bunk=true;
                            flag=1;
                        break;
                }
              }
                tp.write((char*)&t,sizeof(attn));
                found=1;
                ttla=t.A;
                ttlp=t.P;
           }
        }
        else if(found==1)///after found
        {
            if(t.day_val=='A')
                {
                    ttla++;
                    t.A=ttla;
                }
            else if(t.day_val=='P')
                {
                    ttlp++;
                    t.P=ttlp;
                }
                t.disp();
            tp.write((char*)&t,sizeof(attn));
        }
    }
    rd.close();
    tp.close();
    remove("attendance.dat");
    rename("temp.dat","attendance.dat");
    if(found==0)
        cout<<"no record found"<<endl;
}

/// END OF CLASS FUNCTIONS
/// CONTROL FUNCTIONS

void flow()
{
    attn ign;
        system("cls");
        ifstream chk("timetable.txt");
        if(!chk)
        {
            write_ttbl(); ///for initial setup
        }
        else
        {
            cout<<"------MENU------"<<endl;
            cout<<"   1      enter todays data"<<endl;
            cout<<"   2       view attendance"<<endl;
            cout<<"   3       edit attendance"<<endl;
            cout<<" YOUR CHOICE:";
            char ch;
            cin>>ch;
            switch(ch)
            {
                case '1':inp_daily();
                    break;
                case '2':ign.opn2();
                    break;
                case '3':ign.edit();
                default:
                    break;

            }
        }
}
int main()
{
    while(1)
    {
        flow();
        int flag=0,crt=0;
        while(1)
            {
                cout<<"Do You Wish To Exit?(y/n) \n>>";
                char ch;
                cin>>ch;
                switch(ch)
                {
                case 'y':
                case 'Y':flag=1;
                         crt=1;
                    break;
                case 'n':
                case 'N':crt=1;
                    break;
                default:
                    break;
                }
                if(crt==1)
                    break;
            }
            if(flag==1)
                break;
    }
    return 0;
}

/// END OF CONTROL FUNCTIONS

