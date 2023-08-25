#pragma once
#include "gameObject.h"
#include "graphics.h"
#include "config.h"


class Enemy : public GameObject, public Collidable
{
	float pos_x, pos_y;
	float speed;
	float size;
	float rotation;
	graphics::Brush brush;
	bool active = true;

public:
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	float getSpeed() { return speed; }
	Enemy(const Game& mygame);
	~Enemy();
	Disk getCollisionHull() const override;
};
