#include "Paddle.h"

Paddle::Paddle()
{
	speed = 5;
	
}

Paddle::~Paddle()
{
}
/// <summary>
/// Updates the position, unless the position is default, then it will get is own
/// psotionas a safety net
/// </summary>
/// <param name="t_x"></param>
/// <param name="t_y"></param>
void Paddle::setPosition(float t_x, float t_y)
{
	position.x = t_x;
	position.y = t_y;
	if (t_x == 0)
	{
		position.x = player.getPosition().x;
	}
	if (t_y == 0)
	{
		position.y = player.getPosition().y;
	}
}
//sets the speed
void Paddle::setSpeed(float t_speed)
{
	speed = t_speed;
}
//sets the size
void Paddle::setSize(float t_x, float t_y)
{
	size.x = t_x;
	size.y = t_y;
}

//returns the position
sf::Vector2f Paddle::getPosition()
{
	return position;
}
//returns the speed
float Paddle::getSpeed()
{
	return speed;
}
//returns the size
sf::Vector2f Paddle::getSize()
{
	return sf::Vector2f();
}
//returns the object itself
sf::RectangleShape Paddle::getRect()
{
	return player;
}
//returns the objects original position
sf::Vector2f Paddle::getOriginalPosition()
{
	return originalPosition;
}
//sets the objects original position
void Paddle::setOriginalPosition(float t_x, float t_y)
{
	originalPosition.x = t_x;
	originalPosition.y = t_y;
}


void Paddle::update()
{//Left movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		position.x = position.x - speed;
	}
	//Right movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		position.x = position.x + speed;
	}
	if (player.getPosition().x < 0)
	{
		position.x = 0;
	}
	if (player.getPosition().x > 700)
	{
		position.x = 700;
	}
	player.setSize(size);
	player.setPosition(position);
}

void Paddle::render(sf::RenderWindow & t_window)
{
	t_window.draw(player);
}
