//@author_Greg_Cahill
#ifndef GAME
#define GAME

#include "Brick.h"
#include "Bolt.h"
#include "Invader.h"
#include "Paddle.h"
#include "SFML\Audio.hpp"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void renderGameOver();
	
	void setupFontAndText();
	void setupSprite();
	void loadSounds();


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_timeRemaining; // text used for message on screen
	sf::Text m_gameOverText;
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	bool checker0 = false;
	bool checker1 = false;
	bool gameOver = false;



	Brick bricks[2][6];			//This is the green bricks in game in a 2Darray
	Invader invader[2][6];		//This is the spaceInvaders in game in a 2Darray
	Bolt bolt;					//This is the little ball in game
	Paddle paddle;				//This is the player movable paddle
	float deflectionAmount;		//needed for the angle of bouncing off (ball) of the paddle
	float boltAngle;			//The deflection angle of the bolt off the paddle
	float timeRemaining =40;	//Time to play game
	int timeChecker = 0;		//If time hits this number, game is over


	//Below are the sound effects and music for the game
	sf::SoundBuffer ballDestroyedbuffer;
	sf::Sound ballDestroyedsound;

	sf::SoundBuffer bounceOffWallsbuffer;
	sf::Sound bounceOffWallssound;

	sf::SoundBuffer breakBlockbuffer;
	sf::Sound breakBlocksound;

	sf::SoundBuffer gameOverbuffer;
	sf::Sound gameOversound;

	sf::SoundBuffer invaderDestroyedbuffer;
	sf::Sound invaderDestroyedsound;

	sf::SoundBuffer speedBoostbuffer;
	sf::Sound speedBoostsound;
	
	sf::Music music;

};

#endif // !GAME

