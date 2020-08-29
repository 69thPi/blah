#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;



//vars
///design vars
CircleShape dots[32];
Sprite pc[32];
string from="",to="";
bool selected=false;//selected location to move
int white_plays=1; // whose turn
bool valid=true;
int takeout=0;
int fromSprite=-1;
int toSprite=-1;



float width=56;//square width
float size=56; //image size for pieces
float l_offset=1.5*width+2-4; //width+border(2)+ width/2 - correction
float t_offset=l_offset;
float r_offset= 1.5*width+452; //width+totalboardWidth (8*width+2*border)+ width /2
float b_offset= 1.5*width+454;

int pos[10][10]=
	{ 0,-1,-2,-3,-4,-5,-3,-2,-1, 0,
     -6, 0, 0, 0, 0, 0, 0, 0, 0, 6,
	 -6, 0, 0, 0, 0, 0, 0, 0, 0, 6,
	 -6, 0, 0, 0, 0, 0, 0, 0, 0, 6,
     -6, 0, 0, 0, 0, 0, 0, 0, 0, 6,
     -6, 0, 0, 0, 0, 0, 0, 0, 0, 6,
     -6, 0, 0, 0, 0, 0, 0, 0, 0, 6,
     -6, 0, 0, 0, 0, 0, 0, 0, 0, 6,
     -6, 0, 0, 0, 0, 0, 0, 0, 0, 6,
      0, 1, 2, 3, 4, 5, 3, 2, 1, 0};

int parade_r[8]=
		{0,
		 0,
		 0,
		 0,
		 0,
		 0,
		 0,
		 0};
int parade_l[8]=
		{0,
		 0,
		 0,
		 0,
		 0,
		 0,
		 0,
		 0};

///methods

//supporting characters

string box(Vector2f p) //return chess box string
{
	float off[2]={59,59}; //top and left margin (incl. border)
	string s="";
	s += char(int((p.x-off[0])/width)+97);
	s += char((7-int((p.y-off[1])/width))+49);
	return s;// include logic to return only if valid move
}

int get_sprite_id(Vector2i v)
{
  int ret=-1;
  for (int i=0;i<32;i++)
	  if(pc[i].getGlobalBounds().contains(v.x,v.y))
		{
			  ret= i;
			  break;
		}
	return ret;
}

//matrix manip
void bring_in()
{
	for (int i=1;i<9;i++)
	{
		pos[1][i]=pos[0][i]; //move ahead
		pos[2][i]=6*pos[1][1]; //move pawns
		pos[0][i]*=-1; //set new home pos
		pos[8][i]=pos[9][i];
		pos[7][i]=6*pos[8][1];
		pos[9][i]*=-1;
		if(abs(pos[0][i])==4)
				pos[0][i]=(pos[0][i]/4)*5;
		else if(abs(pos[0][i])==5)
				pos[0][i]=(pos[0][i]/5)*4;
	}
	for( int i=0;i<10;i++){//sidelines set to 0
		pos[i][0]=0;
		pos[i][9]=0;}
	for (int i=0;i<10;i++){
		for(int j=0;j<10;j++)
			cout<<pos[i][j]<<" ";
		cout<<endl;}
}


//initial setup
void setHomingDots(){
	for (int i=0;i<32;i++)  //black
	{
		dots[i].setRadius(3.f);
		if (i<8)
		{
			dots[i].setFillColor(Color::Blue);
			dots[i].setPosition(Vector2f(l_offset+width*i,width/2)); //56+2 +(56/2)
		}
		else if(i>7 && i<16){
			dots[i].setFillColor(Color::Red);
			dots[i].setPosition(Vector2f(l_offset+width*(i-8),b_offset));
		}
		else if(i>15 && i<24){
			dots[i].setFillColor(Color::White);
			dots[i].setPosition(Vector2f(width/2,t_offset+width*(i-16)));
		}
		else{
			dots[i].setFillColor(Color::White);
			dots[i].setPosition(Vector2f(r_offset,t_offset+width*(i-24)));
		}
	}
}

void assign_pcs()
{
	int k=0;
    for(int i=1;i<9;i++)
    for(int j=1;j<9;j++)
     {
       int n = pos[i][j];
       if (!n) continue;
       int x = abs(n)-1;
       int y = n>0?1:0;
       pc[k].setTextureRect( IntRect(size*x,size*y,size,size) ); //select texture area for each piece upon value
       pc[k].setPosition(size*j,size*i);
       k++;
     }
}

void disp_pcs()
{
	int k=0;
    for(int i=0;i<10;i++)
    for(int j=0;j<10;j++)
     {
       int n = pos[i][j];
       if (!n) continue;
       int x = abs(n)-1;
       int y = n>0?1:0;
       pc[k].setTextureRect( IntRect(size*x,size*y,size,size) ); //select texture area for each piece upon value
       pc[k].setPosition(size*j,size*i);
       k++;
     }
}

//game start

//gameplay

int push(int pc_val){  //pc_val =+6/-6 //fill up corresponding array and set 
	int i=0;
	if(pc_val==-6)//black on left //bottom up
	{
		for(i=0;i<8;i++)
		{
			if(parade_l[i]==0)
			{
				parade_l[i]=pc_val;
				break;
			}}
		//transfer array
	}
	else if(pc_val ==6)//white or right //top bottom
	{
		for(i=0;i<8;i++)
		{
			if(parade_r[i]==0)
			{
				parade_r[i]=pc_val;
				break;
			}}
	}
	for(int j=0;j<8;j++)
	{
		pos[j+1][0]=parade_l[j];
		pos[j+1][9]=parade_r[7-j];
	}

	return (i+1)*pc_val/6; //-/+ coord  - black + white
}

void prt()
{
	cout<<endl<<endl;
		for(int k=0;k<10;k++){
		for (int l=0;l<10;l++)
			cout<<pos[k][l]<<" ";
		cout<<endl;
		}}
//game end

/////////////////////////////////////////////////



void animate(int a,int b,int x,int y,int id)
{
	float x_pos=a*width,y_pos=b*width;
	if(b<0)//means its a pawn
	{
		if(a<0) //means black pawn
			pc[id].setPosition(Vector2f(0,(9-abs(a))*width));
		else
			pc[id].setPosition(Vector2f(504.f,(a*width)));
	}
	//abxy used for animation loop;
	else
	pc[id].setPosition(Vector2f(x_pos,y_pos));
}

void transfer(int id) //compare value with outsider chart and transfer main piece.
{
	
}

int string_coord(string coord,int axis,int val=0)
{
	if(val==0){
		if(axis==0) //horizontal
			return (int(coord[0])-97)+1;
		else if(axis==1) //vertical
			return (7-(int(coord[1])-49))+1;
	}
	else
		return pos[(7-(int(coord[1])-49))+1][(int(coord[0])-97)+1];
}

 void move()
 {
	 int fin_j=string_coord(to,0),fin_i=string_coord(to,1);
	 int from_j=(int(from[0])-97)+1,from_i=(7-(int(from[1])-49))+1;
	 
	 takeout=pos[fin_i][fin_j];

	 if(takeout*pos[from_i][from_j]<=0) //cannot kill own pieces #casling
	 {
		 if(takeout!=0)
		 {
			if(abs(takeout)==6){ //if pawn then add to sidelines
				int toPos=push(takeout);
				animate(toPos,-1,0,0,toSprite); //for now send that to 0,0;
			}
			else
			{
				//else if other pieces then do that.
				animate(1,0,0,0,toSprite);
			}
		 } 
		 pos[fin_i][fin_j]=pos[from_i][from_j];
		 pos[from_i][from_j]=0;
		 animate(fin_j,fin_i,0,0,fromSprite);
		 fromSprite=-1;
		 toSprite=-1;
		 prt();
	 }
 }
int main()
{
    RenderWindow window(VideoMode(564, 564), "Board Imager");
	Texture t1,t2;
	t1.loadFromFile("board1.png", IntRect(0,0,564,564)); //board image size
	t2.loadFromFile("figures.png");
	Sprite sboard(t1);
	for (int i=0;i<32;i++) pc[i].setTexture(t2);
	setHomingDots();
	disp_pcs();
		
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
			if (event.type == Event::KeyPressed)
				if(event.key.code == Keyboard::Return)
				{
					bring_in();
					assign_pcs();
				}
			if (event.type == Event::MouseButtonPressed)
				if(event.key.code == sf::Mouse::Left)
				{
					Vector2i v= Mouse::getPosition(window);
					if (v.x>59 && v.x<505 && v.y>59 && v.y<508)  // 59,59  505,508 //check click within board
					{
						if (valid==true) //valid selection and move valid1(c range of motion selected) and valid 2(casling witin the path no obstacle)
						{
							if(selected == false){ //nothing selected
								fromSprite=get_sprite_id(v);
								if (fromSprite>=0){ //handling clicks on empty places
									if( ( string_coord(box(Vector2f(v.x,v.y)),2,1) * white_plays)>0)//checks whose turn it is
									{
										from = box(Vector2f(v.x,v.y));
										selected = true;
										cout<<from;
									}
								}
							}
							else{
								if(from!=box(Vector2f(v.x,v.y))){
									toSprite=get_sprite_id(v);
									to = box(Vector2f(v.x,v.y));
									move();//if anyhting present then throw that away and move whatever was there to new location
									cout<<to<<endl;
									}
								selected = false;
								white_plays*=-1;
								from="",to="";
							}
						}
					}
				}
        }

        window.clear();
        window.draw(sboard);
		for (int i=0;i<32;i++){
			window.draw(dots[i]);
			window.draw(pc[i]);
		}
        window.display();
    }

    return 0;
}