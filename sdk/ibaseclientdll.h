#pragma once
#include "../utils/utils.h"

#include "cclientclass.h"

class IBaseClientDLL
{
public:
	constexpr CClientClass* GetAllClasses() noexcept
	{
		return utils::Call<CClientClass*>(this, 8);
	}
};
