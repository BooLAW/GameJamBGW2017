#include "Player.h"
#include "GameObject.h"
#include "Scene.h"
#include "j1App.h"
#include "j1Input.h"
#include "CollisionFilters.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "Functions.h"
#include "j1Textures.h"
#include "p2Log.h"
#include "j1Viewports.h"


Player::Player()
{
}

Player::~Player()
{
}

bool Player::LoadEntity()
{
	bool ret = true;

	player_go = new GameObject(iPoint(curr_coord.x,curr_coord.y), App->cf->CATEGORY_PLAYER, App->cf->MASK_PLAYER, pbody_type::p_t_player, 0);
	if (top_pos == true)
	{
		curr_coord = top_coord;
	}else if (middle_pos == true)
	{
		curr_coord = mid_coord;

	}else if (bot_pos == true)
	{
		curr_coord = bot_coord;
	}
	player_go->CreateCollision(iPoint(0, 0), 45, 70, fixture_type::f_t_null);
	player_go->SetListener((j1Module*)App->entity);
	player_go->SetFixedRotation(true);

	player_go->SetTexture(App->tex->LoadTexture("spritesheet.png"));

	pugi::xml_document doc;
	App->LoadXML("player.xml", doc);
	player_go->LoadAnimationsFromXML(doc);

	player_go->SetAnimation("idle_down");


	return ret;
}

bool Player::Start()
{
	bool ret = true;



	return ret;
}

bool Player::PreUpdate()
{
	bool ret = true;



	return ret;
}

bool Player::Update(float dt)
{
	bool ret = true;

	float speed = (200 * dt);
	//---dance movements interaction
	if (App->input->GetControllerButton(gamepad_num, SDL_CONTROLLER_BUTTON_A) == KEY_REPEAT)
	{
		//A interaction with balls
		//
		//score interaction,check(good,great,perfect)
	}
	else if (App->input->GetControllerButton(gamepad_num, SDL_CONTROLLER_BUTTON_B) == KEY_REPEAT)
	{
		//B interaction with balls
		//
		//score interaction,check(good,great,perfect)
	}
	else if (App->input->GetControllerButton(gamepad_num, SDL_CONTROLLER_BUTTON_X) == KEY_REPEAT)
	{
		//X interaction with balls
		//
		//score interaction,check(good,great,perfect)
	}
	else if (App->input->GetControllerButton(gamepad_num, SDL_CONTROLLER_BUTTON_Y) == KEY_REPEAT)
	{
		//Y interaction with balls
		//
		//score interaction,check(good,great,perfect)
	}
	//transition
	if (App->input->GetControllerButton(gamepad_num, SDL_CONTROLLER_BUTTON_LEFTSHOULDER) == KEY_REPEAT)
	{
		//Change position - Transition??
		//play animation of transition
		//player_go->SetAnimation("transition");
		//change position
		dance_pos = transition;
		//change bools
		if (top_pos == true)
		{
			top_pos = false;
			middle_pos = false;
			bot_pos = true;
			player_go->SetPos(bot_coord);

		}
		else if (middle_pos == true)
		{
			top_pos == true;
			middle_pos = false;
			bot_pos = false;
			player_go->SetPos(top_coord);
		}
		else if (bot_pos == true)
		{
			top_pos == false;
			middle_pos = true;
			bot_pos = false;
			player_go->SetPos(mid_coord);
		}

	}
	else if (App->input->GetControllerButton(gamepad_num, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) == KEY_REPEAT)
	{
		player_go->SetPos({ player_go->fGetPos().x + speed, player_go->fGetPos().y });

	}
	else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT || App->input->GetControllerButton(gamepad_num, SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_REPEAT || App->input->GetControllerJoystickMove(gamepad_num, LEFTJOY_UP) > 12000)
	{
		player_go->SetPos({ player_go->fGetPos().x, player_go->fGetPos().y - speed });

	}
	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT || App->input->GetControllerButton(gamepad_num, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_REPEAT || App->input->GetControllerJoystickMove(gamepad_num, LEFTJOY_DOWN) > 12000)
	{
		player_go->SetPos({ player_go->fGetPos().x, player_go->fGetPos().y + speed });

	}
	return ret;
}

bool Player::Draw(float dt)
{
	bool ret = true;
	player_go->SetAnimation("idle");

	//Movement
	if (top_pos == true)
	{
		//iddle anim 
		player_go->SetAnimation("idle");
	}
	else if (middle_pos == true)
	{
		if (App->input->GetControllerButton(gamepad_num, SDL_CONTROLLER_BUTTON_A) == KEY_REPEAT)
		{
			//A anim
			player_go->SetAnimation("A_anim");
		}
		else if (App->input->GetControllerButton(gamepad_num, SDL_CONTROLLER_BUTTON_X) == KEY_REPEAT)
		{
			//X anim
			player_go->SetAnimation("X_anim");
		}
		else if (App->input->GetControllerButton(gamepad_num, SDL_CONTROLLER_BUTTON_Y) == KEY_REPEAT)
		{
			//Y anim
			player_go->SetAnimation("Y_anim");
		}
		else if (App->input->GetControllerButton(gamepad_num, SDL_CONTROLLER_BUTTON_B) == KEY_REPEAT)
		{
			//B anim
			player_go->SetAnimation("B_anim");
		}

	}
	else if (bot_pos == true)
	{
		//iddle anim 
		player_go->SetAnimation("idle");
	}
	
	return ret;
}

bool Player::PostUpdate()
{
	bool ret = true;



	return ret;
}

bool Player::CleanUp()
{
	bool ret = true;

	return ret;
}

void Player::OnColl(PhysBody* bodyA, PhysBody * bodyB, b2Fixture * fixtureA, b2Fixture * fixtureB)
{
	switch (bodyA->type)
	{
	case pbody_type::p_t_player:
		if (bodyB->type == pbody_type::p_t_world)
		{
		}
		break;

	}
}

void Player::SetGamePad(int id)
{
	gamepad_num = id-1;
}

void Player::SetCamera(int id)
{
	if (id > 0 && id < 5)
	{
		camera = id;
	}
}
