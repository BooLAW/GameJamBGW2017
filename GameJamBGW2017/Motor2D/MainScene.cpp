#include "MainScene.h"
#include "j1Scene.h"
#include "p2Log.h"
#include "j1Input.h"
#include "Functions.h"
#include "j1Physics.h"
#include "GameObject.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Console.h"
#include "Parallax.h"
#include "j1Entity.h"
#include "CollisionFilters.h"
#include "Player.h"
#include "Baffle.h"
#include "j1Map.h"
#include "j1Window.h"


MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

bool MainScene::Start()
{
	bool ret = true;

	LOG("Start MainScene");
	win_rect = { 0,0,1920,1080 };
	//Load Background

	//Load Spritesheet
	main_atlas = App->tex->LoadTexture("textures/main_scene_spritesheet.png");

	//Load Players
	player1 = new Player();
	player1->middle_pos = true;
	//player2 = new Player();
	//player2->top_pos = true;
	//player3 = new Player();
	//player3->bot_pos = true;

	player1->LoadEntity();
	//player2->LoadEntity();
	//player3->LoadEntity();

//	main_atlas = (SDL_Texture*)App->tex->LoadTexture("textures/placeholder.png"); 

	baffle = new Baffle();
	baffle->Start();

	field = SDL_Rect{ 0, 627, 1915, 1009 }; 

	return ret;
}

bool MainScene::PreUpdate()
{
	bool ret = true;

	return ret;
}

bool MainScene::Update(float dt)
{
	bool ret = true;	
	player1->Update(dt);

	App->render->Blit(main_atlas, 0, 75, &field);
	baffle->Update(dt, main_atlas);

	player1->Draw(dt);
	

	//App->render->Blit(background, 0, 0,&win_rect, 0.7);
	//App->render->Blit(main_atlas, int(player1->curr_coord.x), int(player1->curr_coord.y), &player1->player_go->animator->GetCurrentAnimation()->GetAnimationFrame(dt));
	//App->render->Blit(main_atlas, int(player2->curr_coord.x), int(player1->curr_coord.y), &player1->player_go->animator->GetCurrentAnimation()->GetAnimationFrame(dt));
	//App->render->Blit(main_atlas, int(player3->curr_coord.x), int(player1->curr_coord.y), &player1->player_go->animator->GetCurrentAnimation()->GetAnimationFrame(dt));

	return ret;
}

bool MainScene::PostUpdate()
{
	bool ret = true;


	return ret;
}

bool MainScene::CleanUp()
{
	bool ret = true;


	return ret;
}

void MainScene::OnColl(PhysBody * bodyA, PhysBody * bodyB, b2Fixture * fixtureA, b2Fixture * fixtureB)
{

}

void MainScene::OnCommand(std::list<std::string>& tokens)
{
	/*switch (tokens.size())
	{
	case 3:
		if (tokens.front() == "scene.set_player_gamepad") {
			int player, gamepad;
			player = atoi((++tokens.begin())->c_str());
			gamepad = atoi(tokens.back().c_str());
			if (player > 0 && player <= 4 && gamepad > 0 && gamepad <= 4)
			{
				switch (player)
				{
				case 1:
					test_player->SetGamePad(gamepad);
					break;
				case 2:
					test_player2->SetGamePad(gamepad);
					break;
				}
			}
			else
			{
				LOG("Invalid player or gamepad number");
			}
		}
		else if (tokens.front() == "scene.set_player_camera") {
			int player, camera;
			player = atoi((++tokens.begin())->c_str());
			camera = atoi(tokens.back().c_str());
			if (player > 0 && player <= 4 && camera > 0 && camera <= 4)
			{
				switch (player)
				{
				case 1:
					test_player->SetCamera(camera);
					break;
				case 2:
					test_player2->SetCamera(camera);
					break;
				}
			}
			else
			{
				LOG("Invalid player or camera number");
			}
		}
		break;
	default:
		break;
	}*/
}

SDL_Texture * MainScene::GetAtlas()
{
	return main_atlas;
}

Baffle * MainScene::GetBaffle()
{
	return baffle;
}

