#include "../../inc/parser/parser.h"

#include <fstream>
#include <iostream>
using namespace std;

//Initialize Parser object as NULL
Parser* Parser::parser_ptr = 0;

//------------------------------------------------
//------------------- INTERNAL -------------------
//------------------------------------------------
static void load_rect(fstream& f, Rect& w)
{
	double x, y;
	Vec2 v;
	
	f>>x; f>>y; v.set(x, y);
	w.setLeftBottom( v );

	f>>x; f>>y; v.set(x, y);
	w.setRightTop( v );
}


//-----------------------------------------------------
//------------------- FROM PARSER.H -------------------
//-----------------------------------------------------
Parser::Parser()
{
	
}

int Parser::loadScene(std::string filepath, std::vector<RawElement>& raw, Rect& window, Rect& viewport)
{
	string buffer;
	fstream file;
	file.open(filepath.c_str(), ios_base::in);

	if( !file.is_open() ) return -1;

	//window data
	file>>buffer;
	if( buffer.compare("WINDOW") ) return -1;
	load_rect(file, window);

	//viewport data
	file>>buffer;
	if( buffer.compare("VIEWPORT") ) return -1;
	load_rect(file, viewport);

	file.close();

	return 0;
}
