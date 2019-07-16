#include <SFML/Graphics.hpp>
#include <math.h>
#include<iostream>
using namespace std;


/* 
  the mai idea is to set the origin at coord 20,446 and the start calculating the values of y wrt x
   in the form  of a loop;
   the but the axis is inverted so to over come that you have to subtract a value of y every change.
*/
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 500), "Graph plotter");
    sf::CircleShape shape(2.f);
	sf::RectangleShape xline(sf::Vector2f(900,2));
	sf::RectangleShape yline(sf::Vector2f(2,450));
	shape.setPointCount(100000);
	int y_cord=455;
	int x_cord=22;
	shape.setPosition(x_cord,y_cord);// set origin
	xline.setPosition(5,450);
	xline.setFillColor(sf::Color::Green);
	yline.setPosition(20,20);
	yline.setFillColor(sf::Color::Green);
	shape.setFillColor(sf::Color::Red);
	int x=0;//calc from user input
	int y=0;//calc from user input
	//cout<<"The eqn for is y=ax^2 + bx + c"<<endl;
	cout<<"the eqn is for y=mx"<<endl;
	cout<<"Enter value for m :";
	//cout<<"Enter value for b :";
	//cout<<"Enter value for c :";

    while (window.isOpen())
    {
		sf::Vector2f pos=shape.getPosition();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();		
        }
		shape.setPosition(pos.x+.1f,(.5*(pos.x)-456)*-1);
		if(pos.x>600)
			shape.setPosition(pos.x,pos.y);

		
		//window.clear(sf::Color::Black);
        window.draw(shape);
		window.draw(xline);
		window.draw(yline);
        window.display();
    }

    return 0;
}



