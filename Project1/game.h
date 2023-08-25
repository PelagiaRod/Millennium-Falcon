#pragma once

#include "player.h"
#include "Enemy.h"
#include "Fire.h"
#include "EnemyFire.h"

class Game 
{
	typedef enum { STATUS_START, STATUS_PLAYING, STATUS_END, STATUS_WIN } status_t;
	Player * player = nullptr;
	bool player_initialized = false;
	bool debug_mode = false;
	bool low_life = false;
	Enemy * meteorite = nullptr;
	void startFire();
	void checkFire();
	void startEnemyFire();
	void checkEnemyFire();
	void spawnMeteorite();
	void checkMeteorite();
	bool checkCollision();
	bool checkFireCollision();
	bool checkEnemyFireCollision();
	Fire * fire = nullptr;
	EnemyFire* enemyFire = nullptr;
	status_t status = STATUS_START;

	unsigned int window_width = WINDOW_WIDTH;
	unsigned int window_height = WINDOW_HEIGHT;

	void updateStartScreen();
	void updateLevelScreen();
	void updateEndScreen();
	void updateWinScreen();

	void drawStartScreen();
	void drawLevelScreen();
	void drawEndScreen();
	void drawWinScreen();

public:
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode; }
	void setLowLifeMode(bool d) { low_life = d; }
	bool getLowLifeMode() const { return low_life; }
	void update();
	void draw();
	void init();

	unsigned int getWindowWidth() { return window_width; }
	unsigned int getWindowHeight() { return window_height; }
	float window2canvasX(float x);
	float window2canvasY(float y);
	void setWindowDimensions(unsigned int w, unsigned int h) { window_width = w; window_height = h;  }

	Game();
	~Game();
};
