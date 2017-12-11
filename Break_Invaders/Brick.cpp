#include "Brick.h"

//Setup the block colour
Brick::Brick()
{
	block.setFillColor(sf::Color::Green);
}

Brick::~Brick()
{
}
/// <summary>
/// Updates the position, unless the position is default, then it will get is own
/// psotionas a safety net
/// </summary>
/// <param name="t_x"></param>
/// <param name="t_y"></param>
void Brick::setPosition(float t_x, float t_y)
{
	position.x = t_x;
	position.y = t_y;
	if (t_x == 0)
	{
		position.x = block.getPosition().x;
	}
	if (t_y == 0)
	{
		position.y = block.getPosition().y;
	}
}
//Updates the zise
void Brick::setSize(float t_x, float t_y)
{
	size.x = t_x;
	size.y = t_y;
}



//returns the position
sf::Vector2f Brick::getPosition()
{
	return position;
}
//returns the size
sf::Vector2f Brick::getSize()
{
	return size;
}
//returns the object itself
sf::RectangleShape Brick::getRect()
{
	return block;
}
//returns the check for destroyed or not
bool Brick::Alive()
{
	return isAlive;
}
//returns original position
sf::Vector2f Brick::getOriginalPosition()
{
	return originalPosition;
}
//updates the original postion
void Brick::setOriginalPosition(float t_x, float t_y)
{
	originalPosition.x = t_x;
	originalPosition.y = t_y;
}



//updates whether the object has been destroyed or not 
void Brick::setAlive(bool t_alive)
{
	isAlive = t_alive;
}
//Updates the position and size
void Brick::update()
{
	block.setPosition(position);
	block.setSize(size);
}
//draws the block on screen
void Brick::render(sf::RenderWindow & t_window)
{
	if (isAlive)
	{
		t_window.draw(block);
	}
	
}
