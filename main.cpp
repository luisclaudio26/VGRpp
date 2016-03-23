#include <cstdio>
#include <vector>
#include <string>
#include "inc/render.h"
#include "inc/parser/parser.h"
#include "inc/vector/rect.h"

/*  Transformations in .2d file maps a point in
	object space to scene space! For example:
	if we have a circle with associated transformation, we need
	to apply the inverse of this transformation to bring a point
	in scene space to the circle space, and then verify if the point
	is inside it!
*/

int main(int argc, char** args)
{
	std::string filepath("scenes/blueTriangle.2d"); //Not to type everything in terminal

	std::vector<RawElement> raw;
	Rect window, viewport;

	Parser::instance()->loadScene(filepath, raw, window, viewport);

	Render::instance()->preprocess(raw, window, viewport);

	Render::instance()->run();
	return 0;
}