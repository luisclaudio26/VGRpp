#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>
#include "../vector/rect.h"
#include "../RawElement/RawElement.h"

class Parser
{
private:	
	static Parser* parser_ptr;
	Parser();
public:

	int loadScene(std::string filepath, std::vector<RawElement>& raw, Rect& window, Rect& viewport);


	static Parser* instance() {
		if(!Parser::parser_ptr)	
			Parser::parser_ptr = new Parser();
		return Parser::parser_ptr;
	}
};

#endif