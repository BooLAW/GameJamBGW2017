#ifndef _MAINSCENE_H_
#define _MAINSCENE_H_

#include "Scene.h"
#include "j1Render.h"

class GameObject;
class b2Fixture;
class Parallax;
class Player;
class Player2;

class MainScene : public Scene 
{
public:
	MainScene();
	~MainScene();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void OnColl(PhysBody* bodyA, PhysBody* bodyB, b2Fixture* fixtureA, b2Fixture* fixtureB);
	void OnCommand(std::list<std::string>& tokens);

	GameObject* go = nullptr;
	Parallax* p1 = nullptr;

	fPoint pos;

private:

	SDL_Texture* background = nullptr;

	Player* player1 = nullptr;
	Player* player2 = nullptr;
	Player* player3 = nullptr;

};


#endif // !_MAINSCENE_H_