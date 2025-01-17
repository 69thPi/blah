//#include<iostream>
//#include<SFML\Graphics.hpp>
//
//using namespace std;
//
//int main()
//{
//  return 0;
//}

/*till now this program justs shows the understanding of the movement of shapes and their construstions
  what more is left is:-
  1>collisoins with pad
  2>moving ball with pad properly & when toucing the pad
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdio.h>
using namespace std;

int main()
{
    const float pi=3.14159265f;
	float ball_angle=0.f;
	const float ballspeed=400.f;
	const float height=800.f;
	const float width=1280.f;
	const float brad=10.f;
	sf::RenderWindow playscreen(sf::VideoMode(600,400),"DX BALL",sf::Style::Fullscreen);
	playscreen.setPosition(sf::Vector2i(0,0));
	playscreen.setVerticalSyncEnabled(true);//?
	sf::CircleShape ball;
	sf::RectangleShape pad;
	sf::RectangleShape boundl;//left boundary
	sf::RectangleShape boundr;//right boundary
	sf::RectangleShape boundt;//top boundary
	sf::RectangleShape boundb;//bottom boundary
	sf::Texture pic_mm;
	sf::RectangleShape m_m(sf::Vector2f(810,375));//main message
	if(!pic_mm.loadFromFile("resource/main.png"))
		cout<<"error"<<endl;
	pic_mm.setSmooth(true);
	m_m.setPosition(sf::Vector2f(250,200));
	m_m.setTexture(&pic_mm);
	//pause = p
	sf::Texture pic_P;
	sf::RectangleShape P(sf::Vector2f(105,40));
	if(!pic_P.loadFromFile("resource/pause.png"))
		cout<<"pause error"<<endl;
	pic_P.setSmooth(true);
	P.setPosition(sf::Vector2f(1150,0));
	P.setTexture(&pic_P);
	//dxball head
	sf::Texture dxball;
	sf::RectangleShape dx(sf::Vector2f(105,40));
	if(!dxball.loadFromFile("resource/dx.png"))
		cout<<"pause error"<<endl;
	dxball.setSmooth(true);
	dx.setPosition(sf::Vector2f(595,0));
	dx.setTexture(&dxball);
	//continue = c 
	sf::Texture cont;
	sf::RectangleShape ct(sf::Vector2f(250,40));
	if(!cont.loadFromFile("resource/ct.png"))
		cout<<"continue error"<<endl;
	cont.setSmooth(true);
	ct.setPosition(sf::Vector2f(470,400));
	ct.setTexture(&cont);
	//exit=esc 
	sf::Texture ext;
	sf::RectangleShape xt(sf::Vector2f(110,40));
	if(!ext.loadFromFile("resource/xit.png"))
		cout<<"continue error"<<endl;
	ext.setSmooth(true);
	xt.setPosition(sf::Vector2f(0,0));
	xt.setTexture(&ext);
	//click to start
	sf::Texture str;
	sf::RectangleShape st(sf::Vector2f(170,40));
	if(!str.loadFromFile("resource/cts.png"))
		cout<<"start error"<<endl;
	str.setSmooth(true);
	st.setPosition(sf::Vector2f(550,400));
	st.setTexture(&str);
	//*****************************************
	//BASE LINE(ins screen)=(15,770)(1258,770)
	//BASE LINE(desktop)=(1280,796);
	//*****************************************
	//for bounds
	//left bound(0,0)#default
	boundl.setFillColor(sf::Color::Blue);
	boundl.setSize(sf::Vector2f(10,722));
	boundl.setPosition(sf::Vector2f(5,50));
	//right bound(1253,0)#right end
	boundr.setFillColor(sf::Color::Blue);
	boundr.setSize(sf::Vector2f(10,722));
	boundr.setPosition(sf::Vector2f(1258,50));
	//top bound(0,0)#default
	boundt.setFillColor(sf::Color::Blue);
	boundt.setSize(sf::Vector2f(1263,10));
	boundt.setPosition(sf::Vector2f(5,40));
	//bottom bound(0,722)#bottom
	boundb.setFillColor(sf::Color::Blue);
	boundb.setSize(sf::Vector2f(1263,10));
	boundb.setPosition(sf::Vector2f(5,770));
	//for pad
	pad.setSize(sf::Vector2f(100,10));
	pad.setFillColor(sf::Color::Green);
	pad.setPosition(sf::Vector2f(586,760));//y fixed
	//BASE LINE(PAD)=(15,760)-(1158,760);
	//for ball
	ball.setRadius(brad);
	ball.setPosition(sf::Vector2f(626,740));
	ball.setFillColor(sf::Color::Red);
	//scrlength=(1280,796);
	sf::Clock clock;
	bool isPlaying=false;
	bool istouchingpad=false;
	bool toplay=false;
	bool check=true;//check for pause break
	//if 'P' is pressed then check will be false and ball and pad will stay  in place.
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
			if(((event.type==sf::Event::KeyPressed)&&(event.key.code==sf::Keyboard::P)) || (event.type==sf::Event::LostFocus)) //pause
			{
				if(toplay==true){
				isPlaying=false;
				check=false;
				cout<<"check=false"<<endl;
				cout<<"game paused:"<<endl;}
			}
			if(((event.type==sf::Event::KeyPressed)&&(event.key.code==sf::Keyboard::C))||(event.type==sf::Event::GainedFocus))//continue
			{
				if(toplay==true){
				isPlaying=true;
				check=true;
				cout<<"check=true"<<endl;
				cout<<"game continued:"<<endl;}
			}
			if((event.type==sf::Event::KeyPressed) && (event.key.code==sf::Keyboard::Space))//PRESS SPACE TO EXIT
			{
				if(!toplay)
				{
					cout<<"toplay=true"<<endl;
					cout<<"isplaying=false"<<endl;
					isPlaying=false;
					toplay=true;//to break main pause or (re)start
					clock.restart();
					pad.setPosition(sf::Vector2f(586,760));
					ball.setPosition(sf::Vector2f(626,740));
					do
                    {
                        // Make sure the ball initial angle is not too much vertical
                        ball_angle = (rand() % 360) * pi / 360;
                    }
                    while (abs(cos(ball_angle)) < 0.7f);
				}
			}
			if((event.type==sf::Event::KeyPressed)&& event.key.code==sf::Keyboard::O)//user looses
			{
			  cout<<"out"<<endl;
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
				 pad.setPosition(sf::Vector2f(mpos.x-50.f,760.f));
				 if(!isPlaying)
				 {
					 //for ball to stay with pad
					 ball.setPosition(sf::Vector2f(mpos.x-10.f,740.f));
					 if(ball.getPosition().x>1198.f)
					{
						ball_angle=-ball_angle;
						ball.setPosition(1198.f,ball.getPosition().y);
					}
					 if(ball.getPosition().x<55.f)
					{
						ball_angle=-ball_angle;
						ball.setPosition(55.f,ball.getPosition().y);
					}
				 }
			}
			if(event.type==sf::Event::MouseButtonPressed && toplay==true)//start game
			{
			 cout<<"isplaying=true"<<endl;
			 isPlaying=true;
			}
		}
			//*****************END OF USER EVENTS****************
			//check	GAME EVENTS	
			
			float pad_l=pad.getPosition().x;
			float pad_r=pad.getPosition().x+100;
			//to check if ball touches pad
			if((ball.getPosition().y>770)&&(pad_l<ball.getPosition().x && pad_r>ball.getPosition().x))
				{
					istouchingpad=true;
				}
			//handling ball
			 if(ball.getPosition().x>1258.f)
				{
					ball_angle=-ball_angle;
					ball.setPosition(1258.f,ball.getPosition().y);
				}
			if(ball.getPosition().x<15.f)
				 {
					ball_angle=-ball_angle;
					ball.setPosition(15.f,ball.getPosition().y);
				 }
			if(ball.getPosition().y<50.f)
				{
					ball_angle=-ball_angle;
					ball.setPosition(ball.getPosition().x,50.f);
				}
			//handling touch/loss::case
			if(istouchingpad=true)//make sure the ball hits the pad
				{
							/*ball_angle=-ball_angle;
							ball.setPosition(ball.getPosition().x,50.f);*/
							if (ball.getPosition().x > pad.getPosition().x+50.f)
								ball_angle = pi - ball_angle + (rand() % 20) * pi / 180;
							else
								ball_angle = pi - ball_angle - (rand() % 20) * pi / 180;
							/*for(int i=0;i<100;i++)
							{
								if(ball.getPosition().x==i)
								{
								 ball_angle=pi - ball_angle+((rand()%i)*pi/180);
								 break;
								}
							}*/
				}
			else
				{
							isPlaying=false;
							cout<<"you loose!"<<endl;//pop up
							toplay=false;
				}
		
			//to HANDLE PAD
			sf::Vector2f pad_cord=pad.getPosition();
			if(pad_cord.x <15)
				pad.setPosition(15,760);
			if(pad_cord.x >1158)//base length- [pad length] all distances are measured from origin of pad L (1258-1158);
				pad.setPosition(1158,760);
		
		if(isPlaying)
			{
				//ball move
				srand(time(NULL));
				float deltaTime = clock.restart().asMilliseconds();//for ball speed to inc as time passes
				float factor =1.f;
				int dir=1;
				float sign=pow(-1,rand()%2);//to start the ball in left or right dirs.
				dir*=sign;
					//ballspeed * deltaTime;
				ball.move(dir*cos(ball_angle) * factor,-1*sin(ball_angle) * factor);
			}
		
		playscreen.clear(sf::Color::Black);
		playscreen.draw(boundl);
		playscreen.draw(boundb);
		playscreen.draw(boundt);
		playscreen.draw(boundr);
		playscreen.draw(ball);
		playscreen.draw(pad);
		playscreen.draw(P);
		playscreen.draw(xt);
		playscreen.draw(dx);
		if(toplay==true &&	isPlaying==false && check==false)
			playscreen.draw(ct);
		if(toplay==true &&	isPlaying==false && check==true)
			playscreen.draw(st);
		if(isPlaying==false && toplay==false)
			playscreen.draw(m_m);
		playscreen.display();
	}

	return 0;
}