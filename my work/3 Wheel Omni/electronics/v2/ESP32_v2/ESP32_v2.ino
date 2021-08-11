#include <math.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define PWM_RANGE 1024
String self="WKi";

#define CHA_1
#define CHB_1
#define PWM_1 21//1
#define VCC_1 19//2
#define GND_1 18//3

#define CHA_2
#define CHB_2
#define PWM_2 5//4
#define VCC_2 16//5
#define GND_2 17//6

#define CHA_3
#define CHB_3
#define PWM_3 15//7
#define VCC_3 2//8
#define GND_3 4//9

//target set values
//path set, direction
int tym[]={1,1};//in seconds // first element def 1;
int dir[]={0,0};//if -1 ACK spin, -2 CK spin; # x axis is flipped

float v1=0,v2=0,v3=0;
float omega1=0,omega2=0,omega3=0;

void set_omega(int theta) //set each wheel desired speed # the PID ftcn will then check and
{
  if(theta<=0){
   if(theta==-1)
   {
    v1=-0.33;
    v2=v1;
    v3=v1;
   }
   else if(theta==-2){
    v1=0.33;
    v2=v1;
    v3=v1;
    }
   else if(theta==0){
    v1=0;
    v2=v1;
    v3=v1;
   }
   }
  else{
     float theta_rad=theta*0.017453f;
     double ct=cos(theta_rad);
     double st=sin(theta_rad);
     v1=(-1*0.33*ct) + (0.58*st);
     v2=(-1*0.33*ct) - (0.58*st);
     v3=1*(0.66*ct);
     }
}

float mult[4]={1.48,1.5,1.7,3.0};
//operating range for pwm values

void pid()
{
  float h_mult=1;
  bool a=false;
  bool b=false;
  bool c=false;
  for(int i=0;i<4;i++)
  {
      if(abs(v1*mult[i])<1)
        a=true;
      if(abs(v2*mult[i])<1)
        b=true;
      if(abs(v3*mult[i])<1)
        c=true;
      if(a==true && b==true && c==true)
        {h_mult=mult[i];
        break;}
      else
      {
        a=false;
        b=false;
        c=false;
      }
  }
  //set omega 1,2,3
  if(v1>-.01 && v1<.01){
    omega1=0;
  }
  else{
  omega1= int(h_mult*abs(int(v1*PWM_RANGE)));
  //ticks
  }
  if(v2>-.01 && v2<.01){
    omega2=0;
  }
  else{
  omega2= int(h_mult*abs(int(v2*PWM_RANGE)));
  //ticks
  }
  if(v3>-.01 && v3<.01){
    omega3=0;
  }
  else{
  omega3= int(h_mult*abs(int(v3*PWM_RANGE)));
  //ticks
  }
  Serial.print("omega1::");
  Serial.println(omega1);
  Serial.print("omega2::");
  Serial.println(omega2);
  Serial.print("omega3::");
  Serial.println(omega3);
  ledcWrite(0,omega1);
  ledcWrite(1,omega2);
  ledcWrite(2,omega3);
}

void pid_scale(float regulator=1.f){
  ledcWrite(0,int(regulator*omega1));
  ledcWrite(1,int(regulator*omega2));
  ledcWrite(2,int(regulator*omega3));
}

void all_move()
{
  if(v1>0.f){
    digitalWrite(VCC_1,1);
    digitalWrite(GND_1,0);
  }
  else if(v1<0.f){
    digitalWrite(GND_1,1);
    digitalWrite(VCC_1,0);
  }
  else{
    digitalWrite(VCC_1,0);
    digitalWrite(GND_1,0);
  }
  if(v2>0.f){
    digitalWrite(VCC_2,1);
    digitalWrite(GND_2,0);
  }
  else if(v2<0.f){
    digitalWrite(GND_2,1);
    digitalWrite(VCC_2,0);
  }
    else{
    digitalWrite(VCC_2,0);
    digitalWrite(GND_2,0);
    }
  if(v3>0.f){
    digitalWrite(VCC_3,1);
    digitalWrite(GND_3,0);
  }
  else if(v3<0.f){
    digitalWrite(GND_3,1);
    digitalWrite(VCC_3,0);
  }
  else{
    digitalWrite(VCC_3,0);
    digitalWrite(GND_3,0);
  }
}

void all_stop()
{
  //hard stop for accuracy
  digitalWrite(VCC_1,1);
  digitalWrite(GND_1,1);
  digitalWrite(VCC_2,1);
  digitalWrite(GND_2,1);
  digitalWrite(VCC_3,1);
  digitalWrite(GND_3,1);
  //current off to save power
 digitalWrite(VCC_1,0);
 digitalWrite(GND_1,0);
 digitalWrite(VCC_2,0);
 digitalWrite(GND_2,0);
 digitalWrite(VCC_3,0);
 digitalWrite(GND_3,0);
}

unsigned long elapsed=0;
unsigned long saved=0;
int freq=400;

void freq_setup(){
  ledcSetup(0,freq,10);
  ledcSetup(1,freq,10);
  ledcSetup(2,freq,10);
  ledcAttachPin(PWM_1,0);
  ledcAttachPin(PWM_2,1);
  ledcAttachPin(PWM_3,2);
}

IPAddress server(0, 0, 0, 0);
// Set your static gateway IP address

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Started");
  freq_setup();
  pinMode(VCC_1,OUTPUT);
  pinMode(GND_1,OUTPUT);
  pinMode(PWM_1,OUTPUT);
  pinMode(VCC_2,OUTPUT);
  pinMode(GND_2,OUTPUT);
  pinMode(PWM_2,OUTPUT);
  pinMode(VCC_3,OUTPUT);
  pinMode(GND_3,OUTPUT);
  pinMode(PWM_3,OUTPUT);
  WiFi.begin("black","pyrad007");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  server=WiFi.localIP();
  server[3]=50;//server IP
  Serial.println("connected");
}

bool motion=false;
int i=0;
int len=sizeof(dir)/sizeof(int);
void loop() {
  elapsed=millis();
    if(!motion && WiFi.status()==WL_CONNECTED && elapsed-saved>1000){ //in not in motion check every second
                  HTTPClient client;
                  client.begin("http://"+String(server[0])+"."+String(server[1])+"."+String(server[2])+"."+String(server[3])+"/"+self);
                  if(client.GET()==200){
                          String payload= client.getString();
                          if (payload.toInt()!=dir[0]){
                               dir[0]=payload.toInt();
                               Serial.println(dir[0]);
                               //create_path();
                               //pos[0]=new_pos; which is the new input value
                               i=0;
                               motion=true;
                          }
                  }
                  client.end();
                  saved=millis();
                  }
    else{
      //run motion routiene//chek every 50ms
      if(elapsed-saved>tym[i]*1000)//check
      {
        //shift register
        all_stop();
        set_omega(dir[i]);
        pid();
        all_move();
        i++;
        if(i==len){
          all_stop();
          motion=false;
        }
        saved=millis();
      }
      if(elapsed-saved<tym[i]*250 || elapsed-saved>tym[i]*750){//slow start
        pid_scale(0.7);
      }
      else if(elapsed-saved<tym[i]*100 || elapsed-saved>tym[i]*900){//slow stop
        pid_scale(0.5);
      }
      else{//in between
        pid_scale(1.0);
      }


    }
}
