#include "Baffle.h"
#include "p2Log.h"
#include "GameObject.h"

void Baffle::Start()
{
	atlas = App->scene->main_scene->GetAtlas(); 

	pos = fPoint(0.0f, 150.0f); 
	baffle_rect = { 0, 0, 389, 796}; 

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

void Baffle::Update(float dt)
{
	
		if (song_time.Read() >= song1_timing[index] && (song_time.Read() <= song1_timing[index + 1] || index == song1_array.size() - 1))
		{
			TouchNote((note_button)song1_array[index].x, (cheer_color)song1_array[index].y);
			index++;
		}

		App->render->Blit(atlas, pos.x, pos.y, &baffle_rect);

		for (std::list<Note>::iterator it = notes_active.begin(); it != notes_active.end(); it++)
		{
			it->Draw(dt);
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

fPoint Baffle::GetPos()
{
	return pos;
}

Note::Note()
{
	note = new GameObject(iPoint(0, 0), App->cf->CATEGORY_SCENERY, App->cf->MASK_SCENERY, pbody_type::p_t_note); 

	pugi::xml_document doc;

	char* buf = nullptr;
	int size = App->fs->Load("main_scene.xml", &buf);
	pugi::xml_parse_result result = doc.load_buffer(buf, size);
	RELEASE(buf);

	note->animator->LoadAnimationsFromXML(doc); 

}

void Note::Update()
{

}

void Note::Draw(float dt)
{
	App->render->Blit(App->scene->main_scene->GetAtlas(), note->GetPos().x, note->GetPos().y, &note->animator->GetCurrentAnimation()->GetAnimationFrame(dt));
}
