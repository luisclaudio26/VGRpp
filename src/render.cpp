#include "../inc/render.h"
#include "../inc/vector/matrix3.h"
#include <SDL/SDL.h>

#include <iostream>

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

void draw_all(std::vector<Element*>& pool, SDL_Surface* surf, Color bg)
{
	//TODO: ALPHA BLENDING
	Uint32 *pixels = (Uint32*)surf->pixels;

	for(int i = 0; i < surf->h; i++)
		for(int j = 0; j < surf->w; j++)
		{
			Uint32 out = bg;
			for(int k = 0; k < pool.size(); k++)
				pool[k]->sample( j + 0.5, i + 0.5, out);

			//Invert y axis
			int inv_i = surf->h - i - 1;
			
			pixels[inv_i*surf->w + j] = out;
		}
}

//-----------------------------------------------
//----------------- CONSTRUCTORS ----------------
//-----------------------------------------------
Render* Render::render_ptr = 0;

Render::Render() 
{
	this->bg_color = 0x000000;
}

Render::~Render()
{
	for(int i = 0; i < render_pool.size(); i++)
		delete render_pool[i];
}

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
	this->viewport_size = viewport.getRightTop();

	//preprocess all raw elements and store in render pool
	for(int i = 0; i < raw.size(); i++)
		raw[i].preprocess( this->render_pool );

	return 1;
}

void Render::run()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("My Renderer", "My Renderer");

	SDL_Surface* window = SDL_SetVideoMode(viewport_size.x(), viewport_size.y(), 32, SDL_HWSURFACE | SDL_DOUBLEBUF );

	while(true)
	{
		//draw everything inside pool
		draw_all( this->render_pool, window, this->bg_color );

		//get events, skip if user quitted
		if( this->handle_input() ) break;

		//show screen
		SDL_Flip(window);
	}

	//clean everything
	SDL_Quit();
}