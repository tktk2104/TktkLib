#include "TktkDxlib3DWrapper/Assets/LightAssets/LightAssets.h"

#include <algorithm>
#include <DxLib.h>
#include <TktkDxlib2DWrapper/Utility/DXConverter.h>

namespace tktk
{
	void LightAssets::onDestroy() const
	{
		DxLib::DeleteLightHandleAll();
	}

	void LightAssets::createDirectionalLight(
		int id,
		const Vector3 & direction,
		const Color & diffuse,
		const Color & specular,
		const Color & ambient
	)
	{
		eraseLight(id);

		int createLightHandle = DxLib::CreateDirLightHandle(
			DXConverter::toVECTOR(direction)
		);

		SetLightDifColorHandle(createLightHandle, DXConverter::toCOLOR_F(diffuse));
		SetLightSpcColorHandle(createLightHandle, DXConverter::toCOLOR_F(specular));
		SetLightAmbColorHandle(createLightHandle, DXConverter::toCOLOR_F(ambient));

		m_lightAssetsMap.insert(std::make_pair(id, createLightHandle));
	}

	void LightAssets::createPointLight(
		int id,
		const Vector3 & position,
		float range,
		const std::array<float, 3>& attenuation,
		const Color & diffuse,
		const Color & specular,
		const Color & ambient
	)
	{
		eraseLight(id);

		int createLightHandle = CreatePointLightHandle(
			DXConverter::toVECTOR(position),
			range,
			attenuation.at(0),
			attenuation.at(1),
			attenuation.at(2)
		);

		SetLightDifColorHandle(createLightHandle, DXConverter::toCOLOR_F(diffuse));
		SetLightSpcColorHandle(createLightHandle, DXConverter::toCOLOR_F(specular));
		SetLightAmbColorHandle(createLightHandle, DXConverter::toCOLOR_F(ambient));

		m_lightAssetsMap.insert(std::make_pair(id, createLightHandle));
	}

	void LightAssets::createSpotLight(
		int id,
		const Vector3 & position,
		const Vector3 & direction,
		float outAngleDegree,
		float inAngleDegree,
		float range,
		const std::array<float, 3>& attenuation,
		const Color & diffuse,
		const Color & specular,
		const Color & ambient
	)
	{
		eraseLight(id);

		int createLightHandle = CreatePointLightHandle(
			DXConverter::toVECTOR(position),
			range,
			attenuation.at(0),
			attenuation.at(1),
			attenuation.at(2)
		);

		SetLightDifColorHandle(createLightHandle, DXConverter::toCOLOR_F(diffuse));
		SetLightSpcColorHandle(createLightHandle, DXConverter::toCOLOR_F(specular));
		SetLightAmbColorHandle(createLightHandle, DXConverter::toCOLOR_F(ambient));

		m_lightAssetsMap.insert(std::make_pair(id, createLightHandle));
	}

	void LightAssets::eraseLight(int id)
	{
		auto eraseNode = m_lightAssetsMap.find(id);
		if (eraseNode == std::end(m_lightAssetsMap)) return;

		DxLib::DeleteLightHandle((*eraseNode).second);
		m_lightAssetsMap.erase(id);
	}

	void LightAssets::eraseLightAll()
	{
		DxLib::DeleteLightHandleAll();
		m_lightAssetsMap.clear();
	}

	int LightAssets::getLightHandle(int id) const
	{
		return m_lightAssetsMap.at(id);
	}
}