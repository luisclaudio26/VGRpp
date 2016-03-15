#include <cstdio>
#include <vector>
#include <string>
#include "inc/render.h"
#include "inc/parser/parser.h"

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