#include "IMaterialParameter.h"

#include "mBase/Logger.h"

namespace mGL
{
	IMaterialParameter::~IMaterialParameter()
	{
		Logger::Log("IMaterialParameter", "Destructor called");
	}
}