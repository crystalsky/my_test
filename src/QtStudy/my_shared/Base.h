
#ifndef Base_h__
#define Base_h__

#include <Reflected_Object.h>
#include <iostream>

namespace my_kit
{
	class base : public UtilityKit::Reflected_Object
	{
	public:
		base(){}
		virtual ~base(){}

		virtual void run()
		{
			std::cout << "base nothing to run!!!" << std::endl;
		}
	};
}



#endif // Base_h__
