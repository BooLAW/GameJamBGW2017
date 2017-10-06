#pragma once

#ifndef  _INTROSCENE_H_
#define _INTROSCENE_H_

enum intro_state
{
	START_CHEERLEADER, 
	OPTIONS_CHEERLEADER,
	EXIT_CHEERLEADER,

};

#include "Scene.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "Animation.h"

class IntroScene : public Scene
{
public:
	IntroScene();
	~IntroScene();

	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

private:

	void SwitchState(const char* direction); 

private:

	UI_Window* window = nullptr; 

	iPoint start_cheer_pos = NULLPOINT; 
	iPoint options_cheer_pos = NULLPOINT;
	iPoint exit_cheer_pos = NULLPOINT;

	intro_state curr_cheerleader = START_CHEERLEADER; 

	SDL_Texture* intro_atlas = nullptr; 

	Animator* start_cheer_animator = nullptr; 
	Animator* options_cheer_animator = nullptr;
	Animator* exit_cheer_animator = nullptr;

};


#endif // ! _INTROSCENE_H_

