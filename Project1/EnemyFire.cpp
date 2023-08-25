#include "game.h"
#include "graphics.h"
#include "config.h"
#include "EnemyFire.h"


EnemyFire::EnemyFire(const Game& mygame)
	: GameObject(mygame)
{
}

EnemyFire::~EnemyFire()
{
}

void EnemyFire::update()
{
	graphics::playSound(std::string(ASSET_PATH) + "bcfire01.wav", 0.5f, false);
	pos_y += speed * graphics::getDeltaTime();
	
	if (pos_y > CANVAS_HEIGHT)
	{
		active = false;
	}

}



void EnemyFire::draw() {
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 10);

	brush1.texture = "";

	brush1.fill_color[0] = 0.0f;
	brush1.fill_color[1] = 0.5f;
	brush1.fill_color[2] = 0.5f;

	brush1.fill_opacity = 1.0f;
	brush1.fill_secondary_opacity = 0.0f;

	brush1.gradient = true;

	brush1.outline_opacity = 0.0f;

	graphics::setScale(30, 30);

	graphics::drawRect(pos_x, pos_y, 0.1, 1.5, brush1);

	graphics::resetPose();

	if (game.getDebugMode()) 
	{
		graphics::Brush br;
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.3f;
		br.fill_color[0] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
	}
}

void EnemyFire::init()
{
	pos_x;
	pos_y;
}

void EnemyFire::init(float pos_x, float pos_y, float speed)
{
	this->speed = speed;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}



Disk EnemyFire::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 20.0f;
	return disk;
}
