#include "Invader.h"
//sets the speed
Invader::Invader()
{
	speed = 0.1;
}

Invader::~Invader()
{
}
/// <summary>
/// Updates the position, unless the position is default, then it will get is own
/// psotionas a safety net
/// </summary>
/// <param name="t_x"></param>
/// <param name="t_y"></param>
void Invader::setPosition(float t_x, float t_y)
{
	position.x = t_x;
	position.y = t_y;
	if (t_x == 0)
	{
		position.x = invader.getPosition().x;
	}
	if (t_y == 0)
	{
		position.y = invader.getPosition().y;
	}
}
//returns the original position
sf::Vector2f Invader::getOriginalPosition()
{
	return originalPosition;
}
//updates the original position
void Invader::setOriginalPosition(float t_x, float t_y)
{
	originalPosition.x = t_x;
	originalPosition.y = t_y;
}
//sets the speed 
void Invader::setSpeed(float t_speed)
{
	speed = t_speed;
}
//sets the size
void Invader::setSize(float t_x, float t_y)
{
	size.x = t_x;
	size.y = t_y;
}
//sets the texture passed by reference
void Invader::setTexture()
{
	if (!invaderTexture.loadFromFile("ASSETS\\IMAGES\\spaceInavder.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	
	invader.setTexture(&invaderTexture);
}
//flips the spped, effectively flipping directions for moving
void Invader::flipSpeed()
{
	speed =speed * -1;
}
//sets whether the object has been destroyed or not
void Invader::setAlive(bool t_alive)
{
	isAlive = t_alive;
}
//returns the object itself
sf::RectangleShape Invader::getRect()
{
	return invader;
}



sf::Vector2f Invader::getPosition()
{
	return position;
}

float Invader::getSpeed()
{
	return speed;
}

sf::Vector2f Invader::getSize()
{
	return size;
}

bool Invader::Alive()
{
	return isAlive;
}



void Invader::update()
{
	position.x = position.x + speed;
	invader.setPosition(position);
	invader.setSize(size);

	/*if (position.x <= 0 && isAlive)
	{
		flipSpeed();
	}
	if (position.x >= 650 && isAlive)
	{
		flipSpeed();
	}*/
}

void Invader::render(sf::RenderWindow & t_window)
{
	if (isAlive)
	{
		t_window.draw(invader);
	}
	
}
