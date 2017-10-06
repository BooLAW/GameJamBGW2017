#pragma once

#ifndef _BAFFLE_H_
#define _BAFFLE_H_

#include "p2Point.h"
#include "p2Defs.h"
#include "j1Timer.h"
#include "Animation.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "MainScene.h"

enum note_color
{
	BLUE_NOTE, 
	RED_NOTE, 
	GREEN_NOTE, 
	GREY_NOTE, 
};

enum note_button
{
	A_NOTE,
	B_NOTE,
	X_NOTE,
	Y_NOTE,
};

class Note
{

public: 
	Note() {};
	~Note() {};

	note_color color;
	note_button button; 

	iPoint pos; 
	uint velocity; 

	Animator* note_animator; 

	//Colider
};

class Baffle
{
public: 

	Baffle() {}; 
	~Baffle() {};

	void Start(); 
	void Update(); 

private:

	bool TouchNote(); 

private:

	fPoint pos; 
	SDL_Rect baffle_rect = NULLRECT; 
	std::list<Note> notes_active; 
	uint* current_song = nullptr; 
	j1Timer song_time; 

	SDL_Texture* atlas = nullptr; 

};


#endif

