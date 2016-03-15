#ifndef _RENDER_H_
#define _RENDER_H_

#include <vector>
#include "RawElement/RawElement.h"
#include "vector/rect.h"

class Render
{
private:
	//1) container of drawable objects

	//handle window and keyboard input. Return TRUE if we must quit.
	bool handle_input();

	//Render class is a Singleton
	static Render* render_ptr;
	Render();

public:
	//1) Push object to the drawing pool
	//2) Draw all objects in the pool
	
	//take raw objects, preprocess and store in pool
	int preprocess(std::vector<RawElement>& raw, Rect& window, Rect& viewport);

	//creates window, draw everything inside pool until we quit
	void run();

	//returns the only instance of Render class
	static Render* instance() {
		if(!Render::render_ptr)
			Render::render_ptr = new Render();
		return Render::render_ptr;
	}
};

#endif