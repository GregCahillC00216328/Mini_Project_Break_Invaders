#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SFML\Audio.hpp"


class Bolt
{
public:

	Bolt();		//Default contrusctor
	~Bolt();	//Deconstructor
	void setPosition(float t_x = 0, float t_y = 0);		//Resetting the position of the object
	void setVelocity(float t_x = 0, float t_y = 0, float t_angle = 300); //Updating or reseting the velocity
	void setSpeed(float t_speed = 0);		//Updates the speed variable needed for velocity
	void setSize(float t_x = 0, float t_y = 0);	//Updates the size of the object
	void setAngle(float t_angle = 0);		//Updates the angle needed for velocity 

	sf::Vector2f getPosition();		//Returns the position of the object
	sf::Vector2f getVelocity();		//Returns the velocity of the object
	float getSpeed();				//Returns the speed of the object
	sf::Vector2f getSize();			//Returns the size of the object
	sf::RectangleShape getRect();	//Reuturns the object itself
	float getAngle();				//Returns the angle of the 
	void flipVelocity(int t_x, int t_y);//Used to flip or reflect 
	bool getSpeedBoost();			//returns the speedBoost value
	sf::Vector2f getOriginalPosition();		//Gets the original position, used for resetting
	void setOriginalPosition(float t_x = 0, float t_y = 0);	//Same as above, used for resseting
	void resetSpeedBoost();			//resets the speed boost

	void update(sf::Sound &t_bounceOffWalls,sf::Sound &t_speedBoost);
	void render(sf::RenderWindow &t_window);

private:
	sf::RectangleShape missle;

	sf::Vector2f position;
	sf::Vector2f originalPosition;
	sf::Vector2f velocity;
	sf::Vector2f size;
	float speed;
	float angle;
	float timer = 0;
	bool speedBoost = false;
	int speedBoostTracker = 3;		//max amount of 

	sf::Font fonty;
	sf::Text remainingSpeedBoosts;
};

