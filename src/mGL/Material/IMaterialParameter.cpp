#include "IMaterialParameter.h"

#include "Logger.h"

namespace mGL
{
	IMaterialParameter::~IMaterialParameter()
	{
		Logger::Log("IMaterialParameter", "Destructor called");
	}
}