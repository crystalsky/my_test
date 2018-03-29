#include "vector_erease.h"
#include "inc_stl.h"

IMPLEMENT_REFLECTED_CLASS(vector_erease)
vector_erease::vector_erease()
{
	
}

vector_erease::~vector_erease()
{
	
}

void vector_erease::run()
{
	int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
	std::vector<int> vecIA(ia, ia + sizeof(ia) / sizeof(int));

	for (std::vector<int>::iterator it = vecIA.begin();
		it != vecIA.end();)
	{
		if (*it % 2 != 0)
		{
			it = vecIA.erase(it);
		}
		else
		{
			++it;
		}
	}
}
