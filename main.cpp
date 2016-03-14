#include <stdio.h>
#include "inc/render.h"

int main(int argc, char** args)
{
	Render::instance()->run();
	return 0;
}