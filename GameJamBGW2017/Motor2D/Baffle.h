#pragma once

#ifndef _BAFFLE_H_
#define _BAFFLE_H_

#include "p2Point.h"
#include "p2Defs.h"
#include "j1Timer.h"
#include "Animation.h"
#include <vector>
#include "j1Render.h"
#include "j1Scene.h"
#include "j1FileSystem.h"
#include "MainScene.h"

class GameObject; 
class Note; 

enum cheer_color
{
	BLUE_CHEER, 
	RED_CHEER, 
	GREEN_CHEER, 
	ALL_CHEER, 
};

enum note_button
{
	A_NOTE,
	B_NOTE,
	X_NOTE,
	Y_NOTE,
};


class Baffle
{
public: 

	Baffle() {}; 
	~Baffle() {};

	void Start(); 
	void Update(float dt, SDL_Texture* atlas); 

private:

	bool TouchNote(note_button button, cheer_color receptor); 


public: 
	fPoint expulse_pos = { 0,0 };
	SDL_Texture* atlas;

private:

	fPoint pos; 
	
	SDL_Rect baffle_rect = NULLRECT; 

	std::list<Note> notes_active; 

	std::vector<iPoint> current_song_array;

	std::vector<iPoint> song1_array;
	std::vector<iPoint> song2_array;

	std::vector<float> song1_timing;
	std::vector<float> song2_timing;

	j1Timer song_time;
	int index = -1; 

	Animator* button_animator;
	Animator* crown_animator;

};

class Note
{

public:
	Note();
	~Note() {};

	void Update();
	void Draw(float dt, SDL_Texture* atlas);

	cheer_color receptor_color;
	note_button button_color;

	GameObject* note = nullptr;
	float velocity = 0;

	//Colider
};


#endif

