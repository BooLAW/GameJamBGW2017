#include "Baffle.h"




void Baffle::Start()
{
	atlas = App->scene->main_scene->GetAtlas(); 

	pos = fPoint(0.0f, 0.0f); 
	baffle_rect = { 0,0,300, 500 }; 
	
}

void Baffle::Update()
{
	App->render->Blit(atlas, pos.x, pos.y, &baffle_rect); 
}

bool Baffle::TouchNote()
{
	return false;
}
