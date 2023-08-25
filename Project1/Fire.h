#pragma once
#include "gameObject.h"
#include "config.h"
#include "graphics.h"
#include "player.h"

class Fire : public GameObject, public Collidable
{
	float pos_x = CANVAS_WIDTH / 2, pos_y = CANVAS_HEIGHT / 2;
	float speed = 0.8f;
	float size;
	float rotation;
	float height = 1.0f;
	graphics::Brush brush1;
	bool active = true;

public:
	Fire(const class Game& mygame);
	~Fire();
	void update() override;	
	void draw() override;
	void init() override;
	void init(float pos_x, float pos_y);
	bool isActive() { return active; }
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	Disk getCollisionHull() const override;

};
