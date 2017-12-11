#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class Paddle
{
public:
	Paddle();		//Default contructor
	~Paddle();		//Destructor

	void setPosition(float t_x = 0, float t_y = 0);			//Sets the posiition of the object
	void setSpeed(float t_speed = 0);			//Sets the spped of the object used for movement
	void setSize(float t_x = 0, float t_y = 0 );		//Sets the size of the object

	sf::Vector2f getPosition();		//returns the position of the object
	float getSpeed();			//returns the speed of the object
	sf::Vector2f getSize();		//Returns the size of the object
	sf::RectangleShape getRect();	//returns the object itself
	sf::Vector2f getOriginalPosition();	//Returns original position, used for reseting
	void setOriginalPosition(float t_x = 0, float t_y = 0); // sets the original position

	void update();
	void render(sf::RenderWindow &t_window);

private:
	sf::RectangleShape player;
	sf::Vector2f originalPosition;
	sf::Vector2f position;
	sf::Vector2f size;
	float speed;
	
};

