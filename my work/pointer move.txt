#include <SFML\Graphics.hpp>
#include <iostream>

sf::Text msg;
sf::Font fnt;
sf::RectangleShape bound;
sf::Texture pic;

int main()
{
	if(!fnt.loadFromFile("ARCHRISTY.ttf"))
		return 0;
	if(!pic.loadFromFile("Untitled.jpg"))
		return 0;
	msg.setFont(fnt);
	msg.setColor(sf::Color::Green);
	msg.setCharacterSize(15.f);
	msg.setPosition(sf::Vector2f(0,0));
	sf::Mouse mse;
	pic.setSmooth(true);
	bound.setTexture(&pic);
	bound.setSize(sf::Vector2f(300,300));
	bool speed=false;
	////////////////////////////////////
	sf::RenderWindow window(sf::VideoMode(300,300),"prj 1",sf::Style::None);
	window.setPosition(sf::Vector2i(400,0));
	while(window.isOpen())
	{
		sf::Event event;
		int x=mse.getPosition().x;
	    int y=mse.getPosition().y;
		while(window.pollEvent(event))
		{
			if(event.type==sf::Event::Closed)
				window.close();
			if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Space)
			{
			 if(speed==false)
				 speed=true;
			 else
				 speed=false;
			}
			if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Left)
			{
			if(speed==false)
				mse.setPosition(sf::Vector2i(x-10,y));
			else
				mse.setPosition(sf::Vector2i(x-20,y));
			}			
				
			if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Right)
			{
			if(speed==false)
				mse.setPosition(sf::Vector2i(x+10,y));
			else
				mse.setPosition(sf::Vector2i(x+20,y));
			}		
			if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Up)
			{
			if(speed==false)
				mse.setPosition(sf::Vector2i(x,y-10));
			else
				mse.setPosition(sf::Vector2i(x,y-20));
			}		
			if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Down)
			{
			if(speed==false)
				mse.setPosition(sf::Vector2i(x,y+10));
			else
				mse.setPosition(sf::Vector2i(x,y+20));
			}		
		}
		window.clear(sf::Color::White);
		window.draw(bound);
		window.display();
	}
}