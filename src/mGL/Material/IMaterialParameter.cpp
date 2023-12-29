#include "IMaterialParameter.h"
#include <iostream>

namespace mGL
{
	IMaterialParameter::~IMaterialParameter()
	{
		std::cout << "~IMaterialParameter called" << std::endl;
	}
}