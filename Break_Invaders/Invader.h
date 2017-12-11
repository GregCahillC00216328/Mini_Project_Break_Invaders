#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Invader
{
public:
	Invader();			//Defualt Contsructor
	~Invader();			//Destructor
	void setPosition(float t_x = 0, float t_y = 0);//Sets the position of the object
	sf::Vector2f getOriginalPosition();		//Gets the original position of the object, used for reseting
	void setOriginalPosition(float t_x = 0, float t_y = 0); //Sets the original position
	void setSpeed(float t_speed = 0);//sets the speed val used for movement
	void setSize(float t_x = 0, float t_y = 0);		//sets size of the object
	void setTexture();//Sets the texture of the invader
	void flipSpeed();//Flips the speed value to swap directions
	void setAlive(bool t_alive);//Sets whether the object has been destroyed or not

	sf::RectangleShape getRect();		//returns the object

	sf::Vector2f getPosition();			//Gets the position of the object
	float getSpeed();					//Gets the speed of the object
	sf::Vector2f getSize();				//Gets the size of the object
	bool Alive();						//sets whether the object is alive or not
		

	void update();
	void render(sf::RenderWindow &t_window);

private:
	sf::RectangleShape invader;

	sf::Vector2f position;
	sf::Vector2f originalPosition;
	sf::Vector2f size;
	sf::Texture invaderTexture;
	float speed;
	bool isAlive = true;
};

