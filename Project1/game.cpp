#include "game.h"
#include "graphics.h"
#include "config.h"

bool g_check{};

void Game::spawnMeteorite()
{
	 if (!meteorite) 
	{
		meteorite = new Enemy(*this);
	}
}

void Game::startFire()
{
	fire = new Fire(*this);	
}

void Game::startEnemyFire()
{
	enemyFire = new EnemyFire(*this);
}

void Game::checkEnemyFire()
{
	if (enemyFire && !enemyFire->isActive())
	{
		delete enemyFire;
		enemyFire = nullptr;
		g_check = false;
	}
}

 void Game::checkMeteorite()
 {
	 if (meteorite && !meteorite->isActive())
	 {
		 player->drainLife(0.02f);

		 delete meteorite;
		 meteorite = nullptr;
	 }
 }

 void Game::checkFire()
 {
	 if (fire && !fire->isActive())
	 {
		 delete fire;
		 fire = nullptr;
	 }
 }

 bool Game::checkCollision()
 {
	 if (!player || !meteorite)
	 {
		 return false;
	 }
	 Disk d1 = player->getCollisionHull();
	 Disk d2 = meteorite->getCollisionHull();

	 float dx = d1.cx - d2.cx;
	 float dy = d1.cy - d2.cy;

	 if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		 player->drainLife(0.02f);
		 return true;
	 }
	 else {
		 return false;
	 }
 }

 bool Game::checkFireCollision()
 {
	 if (!fire || !meteorite)
	 {
		 return false;
	 }
	 Disk d1 = fire->getCollisionHull();
	 Disk d2 = meteorite->getCollisionHull();

	 float dx = d1.cx - d2.cx;
	 float dy = d1.cy - d2.cy;

	 if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		 return true;
	 }
	 else {
		 return false;
	 }
 }

 bool Game::checkEnemyFireCollision()
 {
	 if (!player || !enemyFire)
	 {
		 return false;
	 }
	 Disk d1 = player->getCollisionHull();
	 Disk d2 = enemyFire->getCollisionHull();

	 float dx = d1.cx - d2.cx;
	 float dy = d1.cy - d2.cy;

	 if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		 player->drainLife(0.02f);
		 return true;
	 }
	 else {
		 return false;
	 }
 }

 void Game::updateStartScreen()
 {
	 graphics::playMusic(std::string(ASSET_PATH) + "Star Wars Theme.mp3", 1.0f, true, 0);

	 if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	 {
		 status = STATUS_PLAYING;
	 }
 }

 void Game::updateLevelScreen()
 {
	 graphics::playMusic("Star Wars Theme.mp3", 1.0f, true, 0);
	 
	 if (!player_initialized && graphics::getGlobalTime() > 1000)
	 {
		 player = new Player(*this);
		 player_initialized = true;
	 }

	 float start_time = graphics::getGlobalTime();
	 
	 if (player)
		 player->update();	 

	 
	 checkFire();

	 float pos_x = player->getPosX();
	 float pos_y = player->getPosY();
	 

	 if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	 {	
		 startFire();	
		 fire->init(pos_x, pos_y+100);
		 fire->update();
	 }

	 if (fire) {
		 fire->update();
	 }
	 	 
	 checkMeteorite();

	 spawnMeteorite();

	 if (meteorite) {
		 meteorite->update();

	 }
	 
	 checkEnemyFire();	 

	 float speed = meteorite->getSpeed();

	 float en_pos_x = meteorite->getPosX();
	 float en_pos_y = meteorite->getPosY();
	 
	 if ((int)graphics::getGlobalTime() %2 == 0 && !g_check)
	 {		 
			 startEnemyFire();
			 enemyFire->init(en_pos_x, en_pos_y, speed * 3);
			 enemyFire->update();
			 g_check = true;
	 }

	 if (enemyFire) {
		 enemyFire->update();
	 }

	 if (checkCollision())
	 {
		 delete meteorite;
		 meteorite = nullptr;
	 }

	 if (checkFireCollision())
	 {
		 delete fire;
		 fire = nullptr;

		 delete meteorite;
		 meteorite = nullptr;
	 }

	 if (checkEnemyFireCollision())
	 {
		 delete enemyFire;
		 enemyFire = nullptr;
		 g_check = false;

	 }

	 if (player->getRemainingLife() < 0.2f) {
		 setLowLifeMode(true);
	 }
 
	if (player->getRemainingLife() == 0.0f) {
		delete player;
		player = nullptr;

		status = STATUS_END;
	}
	
	if (graphics::getGlobalTime() > 150000) {

		delete player;
		player = nullptr;

		status = STATUS_WIN;
		
	}
	 
 }

 void Game::updateEndScreen()
 { 
	 
	 if (graphics::getKeyState(graphics::SCANCODE_ESCAPE))
	 {
		 exit(0);
	 }

 }

 void Game::updateWinScreen()
 {
	 if (graphics::getKeyState(graphics::SCANCODE_ESCAPE))
	 {
		 exit(0);
	 }
 }

 void Game::drawStartScreen()
 {	
	 graphics::playMusic(std::string(ASSET_PATH) + "Star Wars Theme.mp3", 1.0f, true, 0);

	 graphics::Brush br;
	 br.texture = std::string(ASSET_PATH) + "star-wars-backgrounds-2.png";
	 br.outline_opacity = 0.0f;	

	 //draw background
	 graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);
	  
 }

 void Game::drawLevelScreen()
 {
	 graphics::Brush br;
	 br.texture = std::string(ASSET_PATH) + "star-wars-backgrounds-25.png";
	 br.outline_opacity = 0.0f;

	 //draw background
	 graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);
	 
	 //draw player
	 if (player)
		 player->draw();

	 //draw fire
	 if (fire)
	 {		 
		 fire->draw();
	 }

	 //draw enemy
	 if (meteorite)
		 meteorite->draw();
		
	 //draw enemy's fire
	 if (enemyFire)
		 enemyFire->draw();
	 
	 if (player && debug_mode)
	 {
		 char info[40];
		 sprintf_s(info, "(%f)", player->getRemainingLife());
		 graphics::drawText(50, 50, 40, info, br);
	 }
	 
	char info[40];
	sprintf_s(info, "%d", 150-(int)graphics::getGlobalTime()/1000);
	graphics::drawText(50, 50, 40, info, br);

	 float player_life = player ? player->getRemainingLife() : 0.0f;	 

	 br.outline_opacity = 0.0f;
	 br.fill_color[0] = 1.0f;
	 br.fill_color[1] = 0.2f;
	 br.fill_color[2] = 0.2f;
	 br.texture = "";
	 br.fill_secondary_color[0] = 1.0f * (1.0f - player_life) + player_life * 0.2f;
	 br.fill_secondary_color[1] = 0.2f;
	 br.fill_secondary_color[2] = 0.2f * (1.0f - player_life) + player_life * 1.0f;
	 br.gradient = true;
	 br.gradient_dir_u = 1.0f;
	 br.gradient_dir_v = 0.0f;
	 graphics::drawRect(CANVAS_WIDTH - 100 - ((1.0f - player_life) * 120 / 2), 20, player_life * 120, 10, br);

	 br.outline_opacity = 1.0f;
	 br.gradient = false;
	 br.fill_opacity = 0.0f;
	 graphics::drawRect(CANVAS_WIDTH - 100, 20, 120, 10, br); 
	 
 }

 void Game::drawEndScreen()
 {
	 graphics::Brush br;
	 br.texture = std::string(ASSET_PATH) + "game_over.png";
	 br.outline_opacity = 0.0f;

	 //draw background
	 graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);
 }

 void Game::drawWinScreen()
 {
	 graphics::Brush br;
	 br.texture = std::string(ASSET_PATH) + "game_win_2.png";
	 br.outline_opacity = 0.0f;

	 //draw background
	 graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);
 }

void Game::update()
{
	if (status == STATUS_START) 
	{
		updateStartScreen();
	}
	else if (status == STATUS_WIN)
	{
		updateWinScreen();
	}
	else if (status == STATUS_END)
	{
		updateEndScreen();
	}
	else
	{
		updateLevelScreen();
	}
	
	
}

void Game::draw()
{
	if (status == STATUS_START)
	{
		drawStartScreen();
	}	
	else if (status == STATUS_WIN)
	{
		drawWinScreen();
	}
	else if (status == STATUS_END)
	{
		drawEndScreen();
	}	
	else 
	{
		drawLevelScreen();
	}
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "Salty Ocean.ttf");
}

float Game::window2canvasX(float x)
{
	return x * CANVAS_WIDTH / (float)window_width;
}

float Game::window2canvasY(float y)
{
	return y * CANVAS_HEIGHT / (float)window_height;
}

Game::Game()
{
}

Game::~Game()
{
	if (player)
	{
		delete player;
	}
}
