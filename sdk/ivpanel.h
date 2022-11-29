#pragma once
#include "../utils/utils.h"
#include <cstdint>

class IVPanel
{
public:
	constexpr const char* GetName(std::uint32_t panel) noexcept
	{
		return utils::Call<const char*>(this, 36, panel);
	}
};
