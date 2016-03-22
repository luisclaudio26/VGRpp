#include "../inc/render.h"
#include "../inc/vector/matrix3.h"
#include <SDL/SDL.h>

//-------------------------------------------
//----------------- INTERNAL ----------------
//-------------------------------------------
Matrix3 viewport_transformation(Rect& window, Rect& viewport)
{
	double x0w = window.getLeftBottom().x(), 	y0w = window.getLeftBottom().y();
	double x1w = window.getRightTop().x(), 		y1w = window.getRightTop().y();
	double x0v = viewport.getLeftBottom().x(), 	y0v = viewport.getLeftBottom().x();
	double x1v = viewport.getRightTop().x(), 	y1v = viewport.getRightTop().x();

	Matrix3 t1 = Matrix3::translate( -window.getLeftBottom() );
	Matrix3	scl = Matrix3::scale( (x1v - x0v)/(x1w - x0w) , (y1v - y0v) / (y1w - y0w) );
	Matrix3 t3 = Matrix3::translate( viewport.getLeftBottom() );

	return t3 * scl * t1;
}

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

int Render::preprocess(std::vector<RawElement>& raw, Rect& window, Rect& viewport)
{
	//Compute window-viewport transformation
	this->t_viewport = viewport_transformation(window, viewport);

	//preprocess all raw elements and store in render pool
	for(int i = 0; i < raw.size(); i++)
		render_pool.push_back( raw[i].preprocess() );

	return 1;
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