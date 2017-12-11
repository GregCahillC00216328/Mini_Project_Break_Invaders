#include "Bolt.h"


/// <summary>
/// Just basic setting up of the object below
/// sets up the font, speed angle etc
/// </summary>
Bolt::Bolt()
{
	missle.setFillColor(sf::Color::White);
	speed = 5;
	angle = 300;
	velocity = sf::Vector2f(speed * cos(angle * 0.0174533), speed * sin(angle * 0.0174533));

	if (!fonty.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	remainingSpeedBoosts.setFont(fonty);
	
	remainingSpeedBoosts.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	remainingSpeedBoosts.setPosition(0.0f, 550.0f);
	remainingSpeedBoosts.setCharacterSize(24);
	remainingSpeedBoosts.setOutlineColor(sf::Color::Red);
	remainingSpeedBoosts.setFillColor(sf::Color::Black);
	remainingSpeedBoosts.setOutlineThickness(1.0f);
}

Bolt::~Bolt()
{
}


/// <summary>
/// Updates the position, unless the position is default, then it will get is own
/// psotionas a safety net
/// </summary>
/// <param name="t_x"></param>
/// <param name="t_y"></param>
void Bolt::setPosition(float t_x, float t_y)
{
	position.x = t_x;
	position.y = t_y;
	if (t_x == 0)
	{
		position.x = missle.getPosition().x;
	}
	if (t_y == 0)
	{
		position.y = missle.getPosition().y;
	}
}


/// <summary>
/// Updates velocity and recalculates it
/// 0.0174533 is the conversion number to radians. straight number for effeciency
/// the speed boost check doubles the velocity if speed boost is active
/// </summary>
/// <param name="t_x"></param>
/// <param name="t_y"></param>
/// <param name="t_angle"></param>
void Bolt::setVelocity(float t_x, float t_y, float t_angle)
{
	velocity.x = t_x;
	velocity.y = t_y;
	angle = t_angle;
	velocity = sf::Vector2f(speed * cos(angle * 0.0174533), speed * sin(angle * 0.0174533));
	if (speedBoost)
	{
		velocity.x = velocity.x*2;
		velocity.y = velocity.y*2;
	}
}
//update speed
void Bolt::setSpeed(float t_speed)
{
	speed = t_speed; 
}
//update size
void Bolt::setSize(float t_x, float t_y)
{
	size.x = t_x;
	size.y = t_y;
}


//update angle
void Bolt::setAngle(float t_angle)
{
	angle = t_angle;
}
//return position
sf::Vector2f Bolt::getPosition()
{
	return position;
}
//reuturn velocity
sf::Vector2f Bolt::getVelocity()
{
	return velocity;
}
//return speed
float Bolt::getSpeed()
{
	return speed;
}
//return size
sf::Vector2f Bolt::getSize()
{
	return size;
}
//returns the object itseld
sf::RectangleShape Bolt::getRect()
{
	return missle;
}

//returns the angle
float Bolt::getAngle()
{
	return angle;
}
//Flips the velocity if a bounce has occured, reversing its direction appropriately
void Bolt::flipVelocity(int t_x, int t_y)
{
	velocity.x = velocity.x * t_x;
	velocity.y = velocity.y * t_y;
}
//returns the speed boost check
bool Bolt::getSpeedBoost()
{
	return speedBoost;
}
//returns the orignal position
sf::Vector2f Bolt::getOriginalPosition()
{
	return originalPosition;
}
//updates the original position
void Bolt::setOriginalPosition(float t_x, float t_y)
{
	originalPosition.x = t_x;
	originalPosition.y = t_y;
}
//reset the amount of speed boosts used
void Bolt::resetSpeedBoost()
{
	speedBoostTracker = 3;
}



void Bolt::update(sf::Sound &t_bounceOffWalls, sf::Sound &t_speedBoost)
{//Below is what keeps track of the timer
	remainingSpeedBoosts.setString("SpeedBoosts:" + std::to_string(speedBoostTracker));
	if (speedBoost )
	{
		timer++;
		if (timer > 200)
		{
			timer = 0;
			speedBoost = false;
			
		}
	}
	//this is whether you can use another speed boost or not
	if (!speedBoostTracker <= 0)
	{
		//Boosts the speed (doubles the velocity
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !speedBoost || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
			&& !speedBoost)
		{
			velocity.x = velocity.x * 2;
			velocity.y = velocity.y * 2;
			speedBoost = true;
			speedBoostTracker-=1;
			t_speedBoost.play();
		}
		
	}
	//below flips the velocity x or y appropriately for a wall collsiion
	position = position + velocity;
	if (position.x <= 0)
	{
		position.x += 1;
		velocity.x = velocity.x* -1;
		t_bounceOffWalls.play();
	}
	if (position.x >= 795)
	{
		position.x -= 1;
		velocity.x = velocity.x* -1;
		t_bounceOffWalls.play();
	}
	if (position.y <= 0)
	{
		position.y += 1;
		velocity.y = velocity.y* -1;
		t_bounceOffWalls.play();
	}
	if (position.y >= 595)
	{
		position.x -= 1;
		velocity.y = velocity.y* -1;
		t_bounceOffWalls.play();
	}
	

	missle.setPosition(position);
	missle.setSize(size);
}

void Bolt::render(sf::RenderWindow & t_window)
{
	t_window.draw(missle);
	t_window.draw(remainingSpeedBoosts);
}
