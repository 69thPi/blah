#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <fstream>
using namespace std;

void write(int i,float f)
{
	ofstream fout("data.txt",ios::app);
	fout<<i<<":"<<f<<endl;
	fout.close();
}
int main()
{ 
	//defining stuff
	const float pi=3.14159265f;
	float ball_angle=120.f;
	const float height=800;
	const float width=1280;
	const float brad=10.f;//ball radius
	const float bdia=20.f;//ball diameter
	int dir=1;
	float sign=pow(-1,rand()%2);//to start the ball in left or right dirs.
	dir*=sign;
	sf::RenderWindow playscreen(sf::VideoMode(1100,650),"DX BALL-DEVELOPED BY TANMAY SARIYA",sf::Style::Default);
	playscreen.setPosition(sf::Vector2i(80.f,40.f));
	playscreen.setVerticalSyncEnabled(true);//?
	sf::CircleShape ball;
	sf::RectangleShape pad;
	sf::RectangleShape boundl;//left boundary
	sf::RectangleShape boundr;//right boundary
	sf::RectangleShape boundt;//top boundary
	sf::RectangleShape boundb;//bottom boundary
	//bricks
	sf::RectangleShape cover[13][8];
	for(int i=0;i<13;i++)
	{
		for (int j=0;j<8;j++)
		{
			cover[i][j].setSize(sf::Vector2f(80,30));
			cover[i][j].setFillColor(sf::Color::Black);
			cover[i][j].setOutlineThickness(-1.f);
			cover[i][j].setOutlineColor(sf::Color::Red);
			cover[i][j].setPosition(15+i*80.f,50+j*30.f);
		}
	}
	/////////////
	sf::Texture pic_mm;
	sf::Font fnt;
	if(!fnt.loadFromFile("resource/sansation.ttf"))
		return 0;
	sf::RectangleShape m_m(sf::Vector2f(810,375));//main message
	if(!pic_mm.loadFromFile("resource/main.png"))
		cout<<"error"<<endl;
	pic_mm.setSmooth(true);
	m_m.setPosition(sf::Vector2f(150,130));
	m_m.setTexture(&pic_mm);
	//pause = p
	sf::Text pause;
	pause.setFont(fnt);
	pause.setString("PAUSE=P");
	pause.setColor(sf::Color::Black);
	pause.setPosition(sf::Vector2f(970,0));
	//dxball head

	sf::Text dxhead;
	dxhead.setFont(fnt);
	dxhead.setString("DX_BALL");
	dxhead.setColor(sf::Color::Red);
	dxhead.setPosition(sf::Vector2f(440,0));
	//continue = c 

	sf::Text cont;
	cont.setFont(fnt);
	cont.setString("Press 'C' to continue..");
	cont.setColor(sf::Color::Red);
	cont.setPosition(sf::Vector2f(370,300));
	//exit=esc 

	sf::Text ext;
	ext.setFont(fnt);
	ext.setString("EXIT=Esc");	
	ext.setColor(sf::Color::Red);
	ext.setPosition(sf::Vector2f(0,0));

	//click to start
	sf::Text cts;
	cts.setFont(fnt);
	cts.setColor(sf::Color::Red);
	cts.setString("CLICK TO START");
	cts.setPosition(sf::Vector2f(400,300));
	

	//*****************************************
	//BASE LINE(ins screen)=(15,770)(1258,770)
	//BASE LINE(desktop)=(1280,796);
	//*****************************************
	//for bounds
	sf::RectangleShape check1;
	check1.setFillColor(sf::Color::Green);
	check1.setSize(sf::Vector2f(80,30));
	//starts at x==15
	//ends at x==1178.5
	check1.setPosition(16.f,50.f);
	check1.setOutlineThickness(-5.f);
	check1.setOutlineColor(sf::Color::Red);
	//left bound(0,0)#default
	boundl.setFillColor(sf::Color::Black);
	boundl.setSize(sf::Vector2f(10,590));////////// ||  |
	boundl.setPosition(sf::Vector2f(5,50));
	//right bound(1253,0)#right end
	boundr.setFillColor(sf::Color::Black);
	boundr.setSize(sf::Vector2f(10,590));/////////  |  ||
	boundr.setPosition(sf::Vector2f(1080,50));
	//top bound(0,0)#default
	boundt.setFillColor(sf::Color::Black);
	boundt.setSize(sf::Vector2f(1085,10));
	boundt.setPosition(sf::Vector2f(5,40));
	//bottom bound(0,722)#bottom
	boundb.setFillColor(sf::Color::Black);
	boundb.setSize(sf::Vector2f(1085,10));
	boundb.setPosition(sf::Vector2f(5,630));
	//for pad
	pad.setSize(sf::Vector2f(100,10));
	pad.setFillColor(sf::Color::Blue);
	pad.setOutlineThickness(-2.f);
	pad.setOutlineColor(sf::Color::Black);
	pad.setPosition(sf::Vector2f(486,620));//y fixed
	//BASE LINE(PAD)=(15,630)-(1080,630);
	//for ball
	ball.setRadius(brad);
	ball.setPosition(sf::Vector2f(526,600));
	ball.setFillColor(sf::Color::Red);
	//scrlength=(1280,796);
	//declaring display stuff over

	sf::Clock clock;
	bool isPlaying=false;
	bool istouchingpad=false;
	bool toplay=false;
	bool check=true;//check for pause break
	//if 'P' is pressed then check will be false and ball and pad will stay  in place.
	float ball_speed =2.f;//ball speed
	int factor=0;
	int col_ball=1;
	while(playscreen.isOpen())
	{
		sf::Event event;
		while(playscreen.pollEvent(event))
		{
			//EVENTS::
			if((event.type==sf::Event::Closed)||((event.type==sf::Event::KeyPressed)&&(event.key.code==sf::Keyboard::Escape)))
			{
				playscreen.close();
				toplay=false;
				break;
			}
			if((event.type==sf::Event::KeyPressed)&&(event.key.code==sf::Keyboard::BackSpace)) //pause
			{
				check1.setPosition(check1.getPosition().x-.1f,check1.getPosition().y);			
			}
			if(((event.type==sf::Event::KeyPressed)&&(event.key.code==sf::Keyboard::P)) || (event.type==sf::Event::LostFocus)) //pause
			{
				if(toplay==true){
				isPlaying=false;
				check=false;
				}
			}
			if(((event.type==sf::Event::KeyPressed)&&(event.key.code==sf::Keyboard::C))||(event.type==sf::Event::GainedFocus))//continue
			{
				if(toplay==true){
				isPlaying=true;
				check=true;
				}
			}
			if((event.type==sf::Event::KeyPressed) && (event.key.code==sf::Keyboard::Space))//PRESS SPACE TO EXIT
			{
				if(!toplay)
				{
					isPlaying=false;
					toplay=true;//to break main pause or (re)start
					clock.restart();
					ball_speed=15.f;
					ball.setFillColor(sf::Color::Red);					
					ball_angle=0.7f;                    
				}
			}
			if((event.type==sf::Event::KeyPressed)&& event.key.code==sf::Keyboard::O)//user looses
			{
				toplay=false;
			  isPlaying=false;
			}
			if((event.type==sf::Event::KeyPressed)&& event.key.code==sf::Keyboard::I)
			{
				cout<<"x:"<<sf::Mouse::getPosition().x<<endl;
				cout<<"y:"<<sf::Mouse::getPosition().y<<endl;
			}
			if((event.type==sf::Event::MouseMoved)&&check==true)
			{
				 sf::Vector2i mpos=sf::Mouse::getPosition();
				 pad.setPosition(sf::Vector2f(mpos.x-140.f,620.f));
				 if(!isPlaying)
				 {
					 //for ball to stay with pad
					 ball.setPosition(sf::Vector2f(mpos.x-brad-90,600.f));
					 if(ball.getPosition().x>1020.f)
					{
						ball.setPosition(1020.f,ball.getPosition().y);
					}
					 if(ball.getPosition().x<55.f)
					{
						ball.setPosition(55.f,ball.getPosition().y);
					}
				 }
			}
			if(event.type==sf::Event::MouseButtonPressed && toplay==true)//start game
			{
			 isPlaying=true;
			 col_ball++;       //# changing color of ball;
			 if(col_ball>3)
				 col_ball=1;

			 if(col_ball==2)
				 ball.setFillColor(sf::Color::Red);
			 else if(col_ball==1)
				 ball.setFillColor(sf::Color(104,21,196));
			 else if(col_ball==3)
				 ball.setFillColor(sf::Color::Blue);
			}
		}
			//*****************END OF USER EVENTS====POLL EVENTS***************
			//check	GAME EVENTS	
		//srand(time(NULL));
		if(isPlaying)
			{
				//ball move
				float deltaTime = clock.restart().asSeconds();//for ball speed to inc as time passes
									
				ball.move(dir*cos(ball_angle) * ball_speed,-1*sin(ball_angle) * ball_speed);
          
				float pad_l=pad.getPosition().x;
	            float pad_r=pad.getPosition().x+100.f;
			//handling ball
			 if(ball.getPosition().x+bdia>1080.f)
				{
					ball_angle=pi-ball_angle;
					ball.setPosition(1080.f-bdia,ball.getPosition().y);
				}
			if(ball.getPosition().x<15.f)
				 {
					ball_angle=pi-ball_angle;
					ball.setPosition(15.f,ball.getPosition().y);
				 }
			if(ball.getPosition().y<50.f)
				{
					ball_angle=-ball_angle;
					ball.setPosition(ball.getPosition().x,50.f);
				}
			//handling touch/loss::case
			//to check if ball touches pad
			if(ball.getPosition().y>600.f)
				{
					if(ball.getPosition().x+brad>pad.getPosition().x && ball.getPosition().x+brad<pad.getPosition().x+100)
					ball_angle=2*pi-ball_angle;
					factor++;
					if(factor>=3)
					{
					 factor=0;
					 if(ball_speed<5)
					 ball_speed+=0.5f;
					}
					write(factor,ball_speed);
				}
			if(ball.getPosition().y>620.f)
			{
				ball.setFillColor(sf::Color::Transparent);
				        isPlaying=false;
						toplay=false;
			}
			
			}

			//to HANDLE PAD
			sf::Vector2f pad_cord=pad.getPosition();
			if(pad_cord.x <15)
				pad.setPosition(15,620);
			if(pad_cord.x>980)//base length- [pad length] all distances are measured from origin of pad L (1258-1158);
				pad.setPosition(980,620);
		 
			playscreen.clear(sf::Color::White);//0,25,5
		/*for(int i=0;i<13;i++)
	{
		for (int j=0;j<8;j++)
		{
			playscreen.draw(cover[i][j]);
		}
	}*/
		playscreen.draw(boundl);
		playscreen.draw(boundt);
		playscreen.draw(boundr);
		playscreen.draw(ball);
		playscreen.draw(boundb);
		playscreen.draw(pad);
		playscreen.draw(pause);
		playscreen.draw(ext);
		playscreen.draw(dxhead);
		
		if(toplay==true &&	isPlaying==false && check==false)
			playscreen.draw(cont);
		if(toplay==true &&	isPlaying==false && check==true)
			playscreen.draw(cts);
		if(isPlaying==false && toplay==false)
			playscreen.draw(m_m);
		playscreen.display();
	}

	return 0;
}