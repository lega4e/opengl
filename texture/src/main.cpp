#include <stdio.h>
#include <stdlib.h>

#include <glob.hpp>




int main( int argc, char *argv[] )
{
	try
	{
		init_application();
		main_loop();
		free_application();
	}
	catch(std::string const &e)
	{
		fprintf(stderr, "%s\n", e.c_str());
	}
	return 0;
}





// END
