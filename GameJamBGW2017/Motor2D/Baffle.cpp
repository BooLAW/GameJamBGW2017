#include "Baffle.h"
#include "p2Log.h"
#include "GameObject.h"

void Baffle::Start()
{
	atlas = App->tex->LoadTexture("textures/main_scene_spritesheet.png");

	pos = fPoint(50.0f, 375.0f);
	expulse_pos = fPoint(pos.x + 150, pos.y + 150); 
	
	baffle_rect = { 0, 0, 297, 607}; 

	song1_array.push_back(iPoint(B_NOTE, BLUE_CHEER));
	song1_array.push_back(iPoint(1, 4));
	song1_array.push_back(iPoint(3, 2));
	song1_array.push_back(iPoint(0, 1));
	song1_array.push_back(iPoint(0, 0));
	song1_array.push_back(iPoint(2, 1));

	song1_timing.push_back(1500);
	song1_timing.push_back(1700);
	song1_timing.push_back(1900);
	song1_timing.push_back(2100);
	song1_timing.push_back(7500);
	song1_timing.push_back(9000);

	pugi::xml_document doc; 

	char* buf = nullptr;
	int size = App->fs->Load("main_scene.xml", &buf);
	pugi::xml_parse_result result = doc.load_buffer(buf, size);
	RELEASE(buf);

	song_time.Start(); 
	index = 0; 
	
}

void Baffle::Update(float dt, SDL_Texture* atlas)
{
	
		if (song_time.Read() >= song1_timing[index] && (song_time.Read() <= song1_timing[index + 1] || index == song1_array.size() - 1))
		{
			TouchNote((note_button)song1_array[index].x, (cheer_color)song1_array[index].y);
			index++;
		}

		App->render->Blit(atlas, pos.x, pos.y, &baffle_rect);

		for (std::list<Note>::iterator it = notes_active.begin(); it != notes_active.end(); it++)
		{
			it->Update();
			it->Draw(dt, atlas);
		}	
}


bool Baffle::TouchNote(note_button button, cheer_color receptor)
{
	Note* new_note = new Note(); 
	
	switch (button)
	{
	case A_NOTE:
		new_note->note->SetAnimation("button_a"); 
		break; 

	case B_NOTE:
		new_note->note->SetAnimation("button_b");
		break;

	case X_NOTE:
		new_note->note->SetAnimation("button_x");
		break;

	case Y_NOTE:
		new_note->note->SetAnimation("button_y");
		break;
	}

	notes_active.push_back(*new_note); 

	return true;
}




Note::Note()
{
	note = new GameObject(iPoint(App->scene->main_scene->GetBaffle()->expulse_pos.x, App->scene->main_scene->GetBaffle()->expulse_pos.y), App->cf->CATEGORY_SCENERY, App->cf->MASK_SCENERY, pbody_type::p_t_note, 0);

	pugi::xml_document doc;

	char* buf = nullptr;
	int size = App->fs->Load("main_scene.xml", &buf);
	pugi::xml_parse_result result = doc.load_buffer(buf, size);
	RELEASE(buf);

	note->animator->LoadAnimationsFromXML(doc); 
	note->SetPos({ App->scene->main_scene->GetBaffle()->expulse_pos.x, App->scene->main_scene->GetBaffle()->expulse_pos.y });


	velocity = 1.0f; 

}

void Note::Update()
{
	note->SetPos(fPoint(note->GetPos().x + velocity, note->GetPos().y));
}

void Note::Draw(float dt, SDL_Texture* atlas)
{
	App->render->Blit(atlas, note->GetPos().x, note->GetPos().y, &note->animator->GetCurrentAnimation()->GetAnimationFrame(dt));
}
