#include "Enemy.h"
#include "graphics.h"
#include "config.h"
#include "gameObject.h"
#include <random>
#include "util.h"
#include "game.h";

void Enemy::update()
{
	pos_y += speed * graphics::getDeltaTime();
	
	if (pos_y > CANVAS_HEIGHT)
	{
		active = false;
	}
	
}

void Enemy::draw()
{
	brush.texture = std::string(ASSET_PATH) + "enemy.png";
	graphics::drawRect(pos_x, pos_y, size, size, brush);
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

void Enemy::init()
{
	speed = 0.2f;	
	pos_x = CANVAS_WIDTH * rand0to1();	
	pos_y = -(CANVAS_HEIGHT + 1.1f * size);
	size = 50 + 100 * rand0to1();
	brush.outline_opacity = 0.0f;
}

Enemy::Enemy(const Game& mygame)
	: GameObject(mygame)
{
	init();
}

Enemy::~Enemy()
{
}

Disk Enemy::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size * 0.50f;
	return disk;
}
