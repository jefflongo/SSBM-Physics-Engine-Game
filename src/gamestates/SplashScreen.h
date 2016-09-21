#ifndef SPLASH_SCREEN_H_
#define SPLASH_SCREEN_H_

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "../GameState.h"

class Game;

class SplashScreen : public GameState
{
public:
	SplashScreen(){}
	void init();
	void update(Game& game);
	void render(sf::RenderWindow& window);
	void destroy();
private:
	unsigned int getConnectedDevices();
	void moveText();
	void pollForStart(Game& game);

	unsigned int connectedDevices_ = 0;

	sf::Font font_;
	sf::Text pressStartText_;
	sf::Music theme_; // YouTube: Rebaz - Super Smash Bros. Melee Theme (Remix) - SUPER FOX BROS.
};

#endif // SPLASH_SCREEN_H_