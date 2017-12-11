#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Brick
{
public:
	Brick();		//Default Contructor
	~Brick();		//Destructor
	void setPosition(float t_x = 0, float t_y = 0);		//Updates the position
	void setSize(float t_x = 0, float t_y = 0);			//Updates the size

	sf::Vector2f getPosition();					//Gets the position of the object
	sf::Vector2f getSize();						//Returns the size of the object
	sf::RectangleShape getRect();				//Returns the shape itself
	bool Alive();								//Returns whether the object has been destroyed or not
	sf::Vector2f getOriginalPosition();			//Gets the original position, used for reseting
	void setOriginalPosition(float t_x = 0, float t_y = 0); //Sets the original Position

	void setAlive(bool t_alive);			//Set alive status
	void update();							//Updates this object
	void render(sf::RenderWindow &t_window);		//Render fucntion, accepts the window form the game via reference

private:
	sf::RectangleShape block;

	sf::Vector2f position;
	sf::Vector2f originalPosition;
	sf::Vector2f size;
	

	bool isAlive = true;
};
