#include "std_transform.h"
#include "inc_stl.h"

IMPLEMENT_REFLECTED_CLASS(std_transform)
std_transform::std_transform()
{
	
}

std_transform::~std_transform()
{
	
}

void std_transform::run()
{
	std::string str2 = "abcdefghijklmnopqrstuvwxyz";
	std::string str3(str2); 
	std::string::iterator it = std::transform(str2.begin(), str2.end(), str3.begin(), toupper);

	std::transform(str2.begin(), str2.end(), std::ostream_iterator<char>(std::cout, " "), toupper);
	std::cout << std::endl;
}
