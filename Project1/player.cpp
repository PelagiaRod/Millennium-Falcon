#include "player.h"
#include "graphics.h"
#include "game.h"
#include "gameObject.h"


Player::Player(const Game& mygame)
	: GameObject(mygame)
{
}

void Player::update()
{
	
	if (graphics::getKeyState(graphics::SCANCODE_A))
	{
		pos_x -= speed * graphics::getDeltaTime() / 20.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D))
	{
		pos_x += speed * graphics::getDeltaTime() / 20.0f;
	}
	
	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
	if (pos_y < 0) pos_y = 0;
	if (pos_y > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT;

}

void Player::draw()
{
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime()/10);

	graphics::Brush br;
	br.outline_opacity = 0.0f;

	graphics::setScale(height, height);

	
	br.texture = std::string(ASSET_PATH) + "millennium-falcon.png";
	graphics::drawRect(pos_x, pos_y + 150, 100, 100, br);

	graphics::resetPose();

	if (game.getLowLifeMode())
	{
		graphics::Brush br1;
		br1.outline_opacity = 0.0f;
		br1.texture = "";
		br1.fill_color[0] = 1.0f;
		br1.fill_color[1] = 0.2f;
		br1.fill_color[2] = 0.2f;
		br1.fill_opacity = 0.3f;
		br1.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br1);

	}

	if (game.getDebugMode())
	{
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);

	}

}

void Player::init()
{
}

Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y+150;
	disk.radius = 55.0f;
	return disk;
}
