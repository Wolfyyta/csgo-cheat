#pragma once
#include <cstdint>

/* macro for easier use */
#define REL_TO_ABS utils::RelToAbs

namespace utils
{
	/* call a virtual function located in a class */
	/* credits: cazz/based */
	template <typename Return, typename ... Arguments>
	constexpr Return Call(void* vmt, const std::uint32_t index, Arguments ... args) noexcept
	{
		using Function = Return(__thiscall*)(void*, decltype(args)...);
		return (*static_cast<Function**>(vmt))[index](vmt, args...);
	}

	/* relative to absolute */
	inline std::uintptr_t RelToAbs(std::uintptr_t relAddr) noexcept
	{
		return static_cast<std::uintptr_t>(relAddr + 4 + *reinterpret_cast<std::int32_t*>(relAddr));
	}

	/* get a pointer to a virtual function at the given index */
	constexpr void* Get(void* ptr, const std::uint32_t index) noexcept
	{
		return (*static_cast<void***>(ptr))[index];
	}

	/* simple pattern scanner */
	/* credits: cazz/based */
	std::uint8_t* PatternScan(const char* moduleName, const char* pattern) noexcept;
}