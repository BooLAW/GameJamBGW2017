#ifndef _PLAYER_
#define _PLAYER_

#include "Entity.h"
const fPoint top_coord = { 10.f,10.f };
const fPoint mid_coord = { 500.f,250.f };
const fPoint bot_coord = { 10.f,500.f };

enum id_color {
	red = 1,
	green,
	yellow,
	null_color
};
enum pos {
	top = 1,
	mid,
	bot,
	transition,
	null_pos
};

class GameObject;
class Player : public Entity
{
public:
	Player();
	~Player();

	// Load animations
	bool LoadEntity();

	// Start variables
	bool Start();

	// PreUpdate
	bool PreUpdate();

	// Update
	bool Update(float dt);

	// Draw and change animations
	bool Draw(float dt);

	// Post Update
	bool PostUpdate();

	// CleanUp
	bool CleanUp();

	// On Collision
	void OnColl(PhysBody* bodyA, PhysBody* bodyB, b2Fixture* fixtureA, b2Fixture* fixtureB);

	//Set Gamepad number to this player. id>0
	void SetGamePad(int id);

	//Set Camera to this player. 1<=id<=4
	void SetCamera(int id);

public:
	GameObject* player_go = nullptr;

	id_color id = null_color;
	pos dance_pos = null_pos;
	//3 positions of the cheerleaders
	bool top_pos = false;
	bool middle_pos = false;
	bool bot_pos = false;
	fPoint curr_coord = { 0.f,0.f };

private:
	uint gamepad_num = 0;
	int camera = 1;
};

#endif