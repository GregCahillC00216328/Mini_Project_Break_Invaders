//@author_Greg_Cahill

#include "Game.h"
#include <iostream>

/// <summary>
/// Sets up the text/fonts, sprites and sounds
/// the for loop initialies the invaders and bricks as they are a 2D array, it needs to be a nested for loop
/// After that, just basic setup for the others
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	loadSounds();
	for (int row = 0; row < 2; row++)
	{
		for (int col = 0; col < 6; col++)
		{
			invader[row][col].setSize(50, 50);
			invader[row][col].setTexture();
			invader[row][col].setPosition(100 * col + 100, 140 * row + 80);
			invader[row][col].setOriginalPosition(100 * col + 100, 100 * row + 100);
			bricks[row][col].setSize(130, 50);
			bricks[row][col].setPosition(133 * col, 150 * row);
			bricks[row][col].setOriginalPosition(133 * col, 150 * row);
		}
	}
	bolt.setSize(5, 5);
	bolt.setPosition(200, 500);
	bolt.setOriginalPosition(200, 500);
	paddle.setSize(100, 5);
	paddle.setPosition(350, 550);
	paddle.setOriginalPosition(350, 550);
	music.play();
	music.setVolume(30);
	music.setLoop(true);
}


Game::~Game()
{
}


void Game::run()
{
	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	//This will loop while the game isnt over, the core game loop
	while (m_window.isOpen() && !gameOver)
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame&&!gameOver)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible

	}
	//this plays the game over sound effect
	if (gameOver)
	{
		gameOversound.play();
	}
	//this is the game over loop, until the player
	//hits reset, they will see this screen
	//on reset, it calls game.run again and resets the objects
	while(gameOver)
	{
		renderGameOver();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			paddle.setPosition(paddle.getOriginalPosition().x, paddle.getOriginalPosition().y);
			bolt.setPosition(bolt.getOriginalPosition().x, paddle.getOriginalPosition().y);
			bolt.resetSpeedBoost();
			for (int row = 0; row < 2; row++)
			{
				for (int col = 0; col < 6; col++)
				{
					invader[row][col].setPosition(invader[row][col].getOriginalPosition().x, invader[row][col].getOriginalPosition().y);
					invader[row][col].setAlive(true);
					bricks[row][col].setPosition(bricks[row][col].getOriginalPosition().x, bricks[row][col].getOriginalPosition().y);
					bricks[row][col].setAlive(true);
					
				}
			}
			gameOver = false;
		}
		if (!gameOver)
		{
			run();
		}
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if ( sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	timeChecker += 1;
	if (timeChecker >= 60)
	{
		timeChecker = 0;
		timeRemaining -= 1;
	}
	if (timeRemaining <= 0)
	{
		gameOver = true;
		timeRemaining = 40;
	}
	//Updates the time remaining string utilising static cast to read time remaining
	m_timeRemaining.setString("Time: " + std::to_string(static_cast<int>(timeRemaining)));
	//calls the paddle update method
	paddle.update();
	// enters this check if the ball collides with the paddle
	//Plays a sound effect and deflects off at the appropriate angle

	if (bolt.getRect().getGlobalBounds().intersects(paddle.getRect().getGlobalBounds()))
	{
		bounceOffWallssound.play();
		deflectionAmount = (((bolt.getPosition().x+5) - (paddle.getPosition().x))
			/ 100 - 0.5);
		boltAngle = 90 - (90*abs(deflectionAmount));


		if (!bolt.getSpeedBoost())
		{
			bolt.setVelocity(bolt.getVelocity().x, bolt.getVelocity().y, boltAngle);
		}
		if (bolt.getSpeedBoost())
		{
			bolt.setVelocity(bolt.getVelocity().x, bolt.getVelocity().y, boltAngle);
		}
		if ((bolt.getPosition().x + 5) <= (paddle.getPosition().x) + 50)
		{
			bolt.flipVelocity(-1, -1);
		}
		if ((bolt.getPosition().x + 5) >= (paddle.getPosition().x) + 50)
		{
			bolt.flipVelocity(1, -1);
		}
		
	}
	//Penalty for the ball going below the paddle, decrementing the time variable
	if (bolt.getPosition().y > paddle.getPosition().y + 5)
	{
		timeRemaining -= 2;
		bolt.setPosition(400, 300);
		ballDestroyedsound.play();
	}
	//calls the bolt update, and passes two sound effects used for the speed boost and wall deflection
	bolt.update(bounceOffWallssound, speedBoostsound);
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	for (int col = 0; col < 6; col++)
	{
		//the 4 ifs below check if any of the invaders have touched the left or right window boundries
		//if they have, they enter the 5th if check, flipping ALL their directions
		//This ensures that an invader isnt skipped when bouncing and 
		//makes sure that they all stay in a uniform pattern
		if (invader[0][col].getPosition().x <= 0 && invader[0][col].Alive())
		{
			checker0 = true;
		}
		if (invader[0][col].getPosition().x >= 750 && invader[0][col].Alive())
		{
			checker0 = true;
		}
		

		if (invader[1][col].getPosition().x <= 0 && invader[1][col].Alive())
		{
			checker1 = true;
		}
		if (invader[1][col].getPosition().x >= 750 && invader[1][col].Alive())
		{
			checker1 = true;
		}
		
	}
	if (checker0 == true || checker1 == true)
	{
		invader[0][0].flipSpeed();
		invader[0][1].flipSpeed();
		invader[0][2].flipSpeed();
		invader[0][3].flipSpeed();
		invader[0][4].flipSpeed();
		invader[0][5].flipSpeed();
		invader[1][0].flipSpeed();
		invader[1][1].flipSpeed();
		invader[1][2].flipSpeed();
		invader[1][3].flipSpeed();
		invader[1][4].flipSpeed();
		invader[1][5].flipSpeed();

	}
	
	for (int row = 0; row < 2; row++)
	{
		for (int col = 0; col < 6; col++)
		{
			bricks[row][col].update();
			bricks[row][col].render(m_window);
			//Checks if any of the bricks have collided with the bolt
			//if yes, it destroys that specific one, flips the bolt velocity
			//the internal if check checks if the collsion was on the side of the brick
			//if it was, only the x value will be flipped, retaining its y velocity
			if (bricks[row][col].getRect().getGlobalBounds().intersects(bolt.getRect().getGlobalBounds()) && bricks[row][col].Alive())
			{
				bolt.flipVelocity(1, -1);
				bricks[row][col].setAlive(false);
				breakBlocksound.play();
				if (bolt.getPosition().y + 5 > bricks[row][col].getRect().getPosition().y + 5
					&& bolt.getPosition().y + 5 < bricks[row][col].getRect().getPosition().y + 45)
				{
					bolt.flipVelocity(-1, -1);
				}
			}
			invader[row][col].update();
			invader[row][col].render(m_window);
			//same as above, just repeated for the invader
			if (invader[row][col].getRect().getGlobalBounds().intersects(bolt.getRect().getGlobalBounds()) && invader[row][col].Alive())
			{
				bolt.flipVelocity(1, -1);
				invader[row][col].setAlive(false);
				invaderDestroyedsound.play();
				if (bolt.getPosition().y+5 > invader[row][col].getRect().getPosition().y + 5
					&& bolt.getPosition().y+5 < invader[row][col].getRect().getPosition().y + 45)
				{
					bolt.flipVelocity(-1, -1);
				}
			}

			
		}
	}
	//resets the invader boundry checks
		checker0 = false;
		checker1 = false;
		//calls the renders
	bolt.render(m_window);
	paddle.render(m_window);
	m_window.draw(m_timeRemaining);
	m_window.display();
}
//the game over screen render
void Game::renderGameOver()
{
	m_window.clear(sf::Color::Cyan);
	m_window.draw(m_gameOverText);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_timeRemaining.setFont(m_ArialBlackfont);
	
	m_timeRemaining.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_timeRemaining.setPosition(650.0f, 550.0f);
	m_timeRemaining.setCharacterSize(25);
	m_timeRemaining.setOutlineColor(sf::Color::Red);
	m_timeRemaining.setFillColor(sf::Color::Black);
	m_timeRemaining.setOutlineThickness(1.0f);

	m_gameOverText.setFont(m_ArialBlackfont);
	m_gameOverText.setString("   Game Over!      \nPress R key to restart");
	m_gameOverText.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_gameOverText.setPosition(150.0f, 200.0f);
	m_gameOverText.setCharacterSize(45);
	m_gameOverText.setOutlineColor(sf::Color::Red);
	m_gameOverText.setFillColor(sf::Color::Black);
	m_gameOverText.setOutlineThickness(1.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);
}
/// <summary>
/// Loads the sound effects and music
/// </summary>
void Game::loadSounds()
{
	if (!ballDestroyedbuffer.loadFromFile("ASSETS/SOUNDEFFECTS/BallDestroyed.wav"))
	{
		std::cout << "bad file" << std::endl;
	}
	if (!bounceOffWallsbuffer.loadFromFile("ASSETS/SOUNDEFFECTS/BounceOffWalls.wav"))
	{
		std::cout << "bad file" << std::endl;
	}
	if (!breakBlockbuffer.loadFromFile("ASSETS/SOUNDEFFECTS/BreakBlock.wav"))
	{
		std::cout << "bad file" << std::endl;
	}
	if (!gameOverbuffer.loadFromFile("ASSETS/SOUNDEFFECTS/GameOver.wav"))
	{
		std::cout << "bad file" << std::endl;
	}
	if (!invaderDestroyedbuffer.loadFromFile("ASSETS/SOUNDEFFECTS/InvaderDestroyed.wav"))
	{
		std::cout << "bad file" << std::endl;
	}
	if (!speedBoostbuffer.loadFromFile("ASSETS/SOUNDEFFECTS/SpeedBoost.wav"))
	{
		std::cout << "bad file" << std::endl;
	}
	if (!music.openFromFile("ASSETS/SOUNDEFFECTS/Music.wav"))
	{
		std::cout << "bad file" << std::endl;
	}
	
	ballDestroyedsound.setBuffer(ballDestroyedbuffer);
	bounceOffWallssound.setBuffer(bounceOffWallsbuffer);
	breakBlocksound.setBuffer(breakBlockbuffer);
	gameOversound.setBuffer(gameOverbuffer);
	invaderDestroyedsound.setBuffer(invaderDestroyedbuffer);
	speedBoostsound.setBuffer(speedBoostbuffer);

	ballDestroyedsound.setVolume(50);
	bounceOffWallssound.setVolume(50);
	breakBlocksound.setVolume(50);
	gameOversound.setVolume(50);
	invaderDestroyedsound.setVolume(50);
	speedBoostsound.setVolume(50);
	
}
