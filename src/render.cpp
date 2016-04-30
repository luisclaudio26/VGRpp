#include "../inc/render.h"
#include "../inc/vector/matrix3.h"
#include <SDL/SDL.h>
#include <iostream>
#include <chrono>

using namespace std::chrono;

//-------------------------------------------
//----------------- INTERNAL ----------------
//-------------------------------------------
Matrix3 viewport_transformation(const Rect& window, const Vec2& viewport)
{
	double x0w = window.getLeftBottom().x(), 	y0w = window.getLeftBottom().y();
	double x1w = window.getRightTop().x(), 		y1w = window.getRightTop().y();
	double x0v = 0.0, 							y0v = 0.0;
	double x1v = viewport.x(), 					y1v = viewport.y();

	Matrix3 t1 = Matrix3::translate( - window.getLeftBottom() );
	Matrix3	scl = Matrix3::scale( (x1v - x0v)/(x1w - x0w) , (y1v - y0v)/(y1w - y0w) );

	//Third translation will always be (0,0), as viewport is at the origin

	return scl * t1 ;
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

int Render::preprocess(std::vector<RawElement>& raw, const Rect& window, const Vec2& viewport, const Matrix3& scene_t)
{
	//Compute window-viewport transformation
	this->viewport_t = viewport_transformation(window, viewport);
	this->viewport_size = viewport;

	//preprocess all raw elements and store in render pool
	for(int i = 0; i < raw.size(); i++)
		raw[i].preprocess( this->render_pool, viewport_t * scene_t );

	return 1;
}

void Render::run()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("My Renderer", "My Renderer");

	SDL_Surface* window = SDL_SetVideoMode(viewport_size.x(), viewport_size.y(), 32, SDL_HWSURFACE | SDL_DOUBLEBUF );

	milliseconds acc_time = milliseconds(0);
	int n_frames = 0;
	while(true)
	{
		high_resolution_clock::time_point t1 = high_resolution_clock::now();

		//draw everything inside pool
		draw_all( this->render_pool, window, this->bg_color );

		//get events, skip if user quitted
		if( this->handle_input() ) break;

		//show screen
		SDL_Flip(window);

		high_resolution_clock::time_point t2 = high_resolution_clock::now();

		//Timing stuff
		acc_time += duration_cast<milliseconds>(t2-t1);
		n_frames++;

		if(acc_time.count() >= 1000)
		{
			//std::cout<<"Time per frame: "<<acc_time.count() / n_frames<<" ms"<<std::endl;
			std::cout<<n_frames<<" fps"<<std::endl;
			acc_time = milliseconds(0);
			n_frames = 0;
		}
	}

	//clean everything
	SDL_Quit();
}