#include "TktkAppendDxlib3DComponent/Graphics/Light/AppendPointLight.h"

#include <stdexcept>
#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <TktkDxlib3DWrapper/Assets/Assets3DManager.h>
#include <DxLib.h>

namespace tktk
{
	AppendPointLight::AppendPointLight(
		int lightId,
		float range,
		const std::array<float, 3>& attenuation,
		const Color & difColor,
		const Color & spcColor,
		const Color & ambColor
	)
		: m_lightId(lightId)
		, m_range(range)
		, m_attenuation(attenuation)
		, m_difColor(difColor)
		, m_spcColor(spcColor)
		, m_ambColor(ambColor)
	{
	}

	void AppendPointLight::start()
	{
		auto transform3D = getComponent<Transform3D>();

		if (transform3D.isNull())
		{
			throw std::runtime_error("AppendPointLight not found Transform3D");
		}

		m_transform3D = transform3D;

		int lightHandle = Assets3DManager::getLightAssets()->getLightHandle(m_lightId);

		DxLib::SetLightRangeAttenHandle(
			lightHandle,
			m_range,
			m_attenuation.at(0),
			m_attenuation.at(1),
			m_attenuation.at(2)
		);

		DxLib::SetLightDifColorHandle(
			lightHandle,
			DXConverter::toCOLOR_F(m_difColor)
		);

		DxLib::SetLightSpcColorHandle(
			lightHandle,
			DXConverter::toCOLOR_F(m_spcColor)
		);

		DxLib::SetLightAmbColorHandle(
			lightHandle,
			DXConverter::toCOLOR_F(m_ambColor)
		);
	}

	void AppendPointLight::onEnable()
	{
		DxLib::SetLightEnableHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			TRUE
		);
	}

	void AppendPointLight::onDisable()
	{
		DxLib::SetLightEnableHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			FALSE
		);
	}

	void AppendPointLight::update()
	{
		DxLib::SetLightPositionHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			DXConverter::toVECTOR(m_transform3D->getWorldPosition())
		);
	}

	float AppendPointLight::getRange() const
	{
		return m_range;
	}

	void AppendPointLight::setRange(float range)
	{
		m_range = range;
		DxLib::SetLightRangeAttenHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			m_range,
			m_attenuation.at(0),
			m_attenuation.at(1),
			m_attenuation.at(2)
		);
	}

	const std::array<float, 3>& AppendPointLight::getAttenuation() const
	{
		return m_attenuation;
	}

	void AppendPointLight::setAttenuation(const std::array<float, 3>& attenuation)
	{
		m_attenuation = attenuation;
		DxLib::SetLightRangeAttenHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			m_range,
			m_attenuation.at(0),
			m_attenuation.at(1),
			m_attenuation.at(2)
		);
	}

	const Color & AppendPointLight::getDifColor() const
	{
		return m_difColor;
	}

	void AppendPointLight::setDifColor(const Color & difColor)
	{
		m_difColor = difColor;
		DxLib::SetLightDifColorHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			DXConverter::toCOLOR_F(m_difColor)
		);
	}

	const Color & AppendPointLight::getSpcColor() const
	{
		return m_spcColor;
	}

	void AppendPointLight::setSpcColor(const Color & spcColor)
	{
		m_spcColor = spcColor;
		DxLib::SetLightSpcColorHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			DXConverter::toCOLOR_F(m_spcColor)
		);
	}

	const Color & AppendPointLight::getAmbColor() const
	{
		return m_ambColor;
	}

	void AppendPointLight::setAmbColor(const Color & ambColor)
	{
		m_ambColor = ambColor;
		DxLib::SetLightAmbColorHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			DXConverter::toCOLOR_F(m_ambColor)
		);
	}
}