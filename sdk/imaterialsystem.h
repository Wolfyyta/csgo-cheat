#pragma once
#include "../utils/utils.h"

#include "ckeyvalues.h"

class IMaterial
{
public:
	enum EMaterialVarFlag : std::int32_t
	{
		IGNOREZ = 1 << 15,
		WIREFRAME = 1 << 28
	};

	constexpr void SetMaterialVarFlag(const std::int32_t flag, const bool on) noexcept
	{
		utils::Call<void>(this, 29, flag, on);
	}
};

class IMaterialSystem
{
public:
	constexpr IMaterial* CreateMaterial(const char* name, CKeyValues* kv) noexcept
	{
		return utils::Call<IMaterial*>(this, 83, name, kv);
	}

	constexpr IMaterial* FindMaterial(const char* name) noexcept
	{
		return utils::Call<IMaterial*>(this, 84, name, nullptr, true, nullptr);
	}
};
