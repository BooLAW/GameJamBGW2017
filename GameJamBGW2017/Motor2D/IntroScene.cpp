#include "IntroScene.h"

#include "j1Window.h"
#include "j1Input.h"
#include "j1Filesystem.h"
#include "j1Scene.h"
#include "j1Textures.h"

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}

bool IntroScene::Start()
{

	uint window_w, window_h;

	App->win->GetWindowSize(window_w, window_h);
	window = App->gui->UI_CreateWin(iPoint(0, 0), window_w, window_h); 

	int distance_between_buttons = 100, signpost_w = 400, signpost_h = 200;

	//start_button_rect = SDL_Rect{ 0, 0, signpost_w, signpost_h };
	//options_button_rect = SDL_Rect{ 0, 0, signpost_w, signpost_h };
	//exit_button_rect = SDL_Rect{ 0, 0, signpost_w, signpost_h };

	options_cheer_pos.x = window_w / 2 - (signpost_w / 2);
	start_cheer_pos.x = options_cheer_pos.x - distance_between_buttons - signpost_w;
	exit_cheer_pos.x = options_cheer_pos.x + distance_between_buttons + signpost_w;

	start_cheer_pos.y = options_cheer_pos.y = exit_cheer_pos.y = window_h / 3 ;

	//window->CreateButton(start_cheer_pos, signpost_w, signpost_h, false);
	//window->CreateButton(options_cheer_pos, signpost_w, signpost_h, false);
	//window->CreateButton(exit_cheer_pos, signpost_w, signpost_h, false);

	intro_atlas = App->tex->LoadTexture("textures/Cheerleaders_intro.png"); 

	pugi::xml_document doc;

	char* buf = nullptr;
	int size = App->fs->Load("intro_screen.xml", &buf);
	pugi::xml_parse_result result = doc.load_buffer(buf, size);
	RELEASE(buf);
	int aux = doc.child("file").child("animations").child("anim").attribute("speed").as_int();
	
	start_cheer_animator = new Animator();	
	start_cheer_animator->LoadAnimationsFromXML(doc);
	start_cheer_animator->SetAnimation("cheer_down"); 

	options_cheer_animator = new Animator();
	options_cheer_animator->LoadAnimationsFromXML(doc);
	options_cheer_animator->SetAnimation("cheer_down");

	exit_cheer_animator = new Animator();
	exit_cheer_animator->LoadAnimationsFromXML(doc);
	exit_cheer_animator->SetAnimation("cheer_down");


	return true;
}

bool IntroScene::Update(float dt)
{

	if (App->input->GetControllerButton(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN)
	{
		SwitchState("right");
	}

	if (App->input->GetControllerButton(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN)
	{
		SwitchState("left");
	}

	if (App->input->GetControllerButton(0, SDL_CONTROLLER_BUTTON_A) == KEY_DOWN)
	{
		if (curr_cheerleader == START_CHEERLEADER)
		{
			App->scene->ChangeScene((Scene*)App->scene->main_scene);
			return true; 
		}
			

		else if (curr_cheerleader == OPTIONS_CHEERLEADER)
			App->scene->ChangeScene((Scene*)App->scene->main_scene);

		else
			return false;
	}

	switch (curr_cheerleader)
	{
	case START_CHEERLEADER:
		start_cheer_animator->SetAnimation("cheer_up"); 
		options_cheer_animator->SetAnimation("cheer_down");
		exit_cheer_animator->SetAnimation("cheer_down");
		break; 

	case OPTIONS_CHEERLEADER:
		start_cheer_animator->SetAnimation("cheer_down");
		options_cheer_animator->SetAnimation("cheer_up");
		exit_cheer_animator->SetAnimation("cheer_down");
		break;

	case EXIT_CHEERLEADER:
		start_cheer_animator->SetAnimation("cheer_down");
		options_cheer_animator->SetAnimation("cheer_down");
		exit_cheer_animator->SetAnimation("cheer_up");
		break;
	}

	App->render->Blit(intro_atlas, start_cheer_pos.x, start_cheer_pos.y, &start_cheer_animator->GetCurrentAnimation()->GetAnimationFrame(dt));
	App->render->Blit(intro_atlas, options_cheer_pos.x, options_cheer_pos.y, &options_cheer_animator->GetCurrentAnimation()->GetAnimationFrame(dt));
	App->render->Blit(intro_atlas, exit_cheer_pos.x, exit_cheer_pos.y, &exit_cheer_animator->GetCurrentAnimation()->GetAnimationFrame(dt));

	return true;
}

bool IntroScene::PostUpdate()
{

	return true;

}

bool IntroScene::CleanUp()
{
	delete(exit_cheer_animator); 
	delete(start_cheer_animator);
	delete(options_cheer_animator);

	return true;
}

void IntroScene::SwitchState(const char * direction)
{

	if (direction == "right" && curr_cheerleader != EXIT_CHEERLEADER)
	{
		int curr_cheer = curr_cheerleader; 
		curr_cheer++; 

		curr_cheerleader = (intro_state)curr_cheer; 

	}

	if (direction == "left" && curr_cheerleader != START_CHEERLEADER)
	{
		int curr_cheer = curr_cheerleader;
		curr_cheer--;

		curr_cheerleader = (intro_state)curr_cheer;

	}

}
