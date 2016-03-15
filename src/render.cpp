#include "../inc/render.h"
#include <SDL/SDL.h>

//-------------------------------------------
//----------------- INTERNAL ----------------
//-------------------------------------------

//-----------------------------------------------
//----------------- CONSTRUCTORS ----------------
//-----------------------------------------------
Render* Render::render_ptr = 0;

Render::Render() { }

//------------------------------------------------
//----------------- FROM RENDER.H ----------------
//------------------------------------------------
bool Render::handle_input()
{
	SDL_Event event;
	bool quit = false;

	if (SDL_PollEvent(&event))
		switch (event.type)
		{
			//close button clicked
			case SDL_QUIT: 
				quit = true; 
				break; 

			//handle the keyboard 
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) 
				{
					case SDLK_ESCAPE:
						quit = true; 
						break;
				}
				break;
	}

	return quit;	
}

void Render::run()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("My Renderer", "My Renderer");

	SDL_Surface* window = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );

	while(true)
	{
		//Clean screen
		SDL_FillRect(window, 0, SDL_MapRGB(window->format, 0, 0, 0) );

		//get events, skip if user quitted
		if( this->handle_input() ) break;

		//show screen
		SDL_Flip(window);
	}

	//clean everything
	SDL_Quit();
}