#pragma once
#include "gameObject.h"
#include "config.h"
#include "graphics.h"
#include "player.h"

class EnemyFire : public GameObject, public Collidable
{
	float pos_x , pos_y;
	float speed;
	float size;
	float rotation;
	float height = 1.0f;
	graphics::Brush brush1;
	bool active = true;

public:
	EnemyFire(const class Game& mygame);
	~EnemyFire();
	void update() override;
	void draw() override;
	void init() override;
	void init(float pos_x, float pos_y, float speed);
	bool isActive() { return active; }
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	Disk getCollisionHull() const override;

};
