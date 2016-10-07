#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// TODO 5: Move all creation of bodies on 1,2,3 key press here in the scene
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		Stalker circleT1Flamer = App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25);
		App->physics->bodies.add(circleT1Flamer);
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		// TODO 1: When pressing 2, create a box on the mouse position
		App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY());
	}
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		App->physics->CreateChains();
	}
	// TODO 7: Draw all the circles using "circle" texture
	if (App->physics->bodies.getFirst() != nullptr)
	{
		float x, y;
		for (p2List_item<Stalker>* i = App->physics->bodies.getFirst(); i != nullptr; i = i->next)
		{
			i->data.getPositionBody(x, y);
			x = METERS_TO_PIXELS(x) - 25;
			y = METERS_TO_PIXELS(y) - 25;
			App->renderer->Blit(circle, x, y);
		}
	}
	

	return UPDATE_CONTINUE;
}
