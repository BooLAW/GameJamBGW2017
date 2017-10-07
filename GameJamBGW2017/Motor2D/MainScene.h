#ifndef _MAINSCENE_H_
#define _MAINSCENE_H_

#include "Scene.h"
#include "j1Render.h"

#define MAX_SCORE 5000
class Animator;
class GameObject;
class b2Fixture;
class Parallax;
class Player;
class Player2;
class Baffle; 

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
	SDL_Texture* GetAtlas();

	Baffle* GetBaffle(); 

	GameObject* go = nullptr;
	//Sensors 
	SDL_Rect* good = nullptr;
	SDL_Rect* great = nullptr;
	SDL_Rect* perfect = nullptr;

	Parallax* p1 = nullptr;

	fPoint pos;

private:
	SDL_Rect win_rect;
	uint score = 0;
	Baffle* baffle; 

	Animator* score_bar;

	SDL_Texture* main_atlas = nullptr; 
	SDL_Rect field = NULLRECT; 

	Player* player1 = nullptr;
	Player* player2 = nullptr;
	Player* player3 = nullptr;

};


#endif // !_MAINSCENE_H_