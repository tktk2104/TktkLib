#include "TktkAppendDxlib3DComponent/Graphics/Light/AppendSpotLight.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <TktkDxlib3DWrapper/Assets/Assets3DManager.h>
#include <DxLib.h>

namespace tktk
{
	AppendSpotLight::AppendSpotLight(
		int lightId,
		float outAngleDegree,
		float inAngleDegree,
		float range,
		const std::array<float, 3>& attenuation,
		const Color & difColor,
		const Color & spcColor,
		const Color & ambColor
	)
		: m_lightId(lightId)
		, m_outAngleDegree(outAngleDegree)
		, m_inAngleDegree(inAngleDegree)
		, m_range(range)
		, m_attenuation(attenuation)
		, m_difColor(difColor)
		, m_spcColor(spcColor)
		, m_ambColor(ambColor)
	{
	}

	void AppendSpotLight::start()
	{
		auto transform3D = getComponent<Transform3D>();

		if (transform3D.isNull())
		{
			throw std::runtime_error("AppendPointLight not found Transform3D");
		}

		m_transform3D = transform3D;

		int lightHandle = Assets3DManager::getLightAssets()->getLightHandle(m_lightId);

		DxLib::SetLightAngleHandle(
			lightHandle,
			MathHelper::toRadians(m_outAngleDegree),
			MathHelper::toRadians(m_inAngleDegree)
		);

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

	void AppendSpotLight::onEnable()
	{
		DxLib::SetLightEnableHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			TRUE
		);
	}

	void AppendSpotLight::onDisable()
	{
		DxLib::SetLightEnableHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			FALSE
		);
	}

	void AppendSpotLight::update()
	{
		int lightHandle = Assets3DManager::getLightAssets()->getLightHandle(m_lightId);

		DxLib::SetLightPositionHandle(
			lightHandle,
			DXConverter::toVECTOR(m_transform3D->getWorldPosition())
		);

		DxLib::SetLightDirectionHandle(
			lightHandle,
			DXConverter::toVECTOR(m_transform3D->calculateLocalForwardLH())
		);
	}

	float AppendSpotLight::getOutAngleDegree() const
	{
		return m_outAngleDegree;
	}

	void AppendSpotLight::setOutAngleDegree(float outAngleDegree)
	{
		m_outAngleDegree = outAngleDegree;
		DxLib::SetLightAngleHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			MathHelper::toRadians(m_outAngleDegree),
			MathHelper::toRadians(m_inAngleDegree)
		);
	}

	float AppendSpotLight::getInAngleDegree() const
	{
		return m_inAngleDegree;
	}

	void AppendSpotLight::setInAngleDegree(float inAngleDegree)
	{
		m_inAngleDegree = inAngleDegree;
		DxLib::SetLightAngleHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			MathHelper::toRadians(m_outAngleDegree),
			MathHelper::toRadians(m_inAngleDegree)
		);
	}

	float AppendSpotLight::getRange() const
	{
		return m_range;
	}

	void AppendSpotLight::setRange(float range)
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

	const std::array<float, 3>& AppendSpotLight::getAttenuation() const
	{
		return m_attenuation;
	}

	void AppendSpotLight::setAttenuation(const std::array<float, 3>& attenuation)
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

	const Color & AppendSpotLight::getDifColor() const
	{
		return m_difColor;
	}

	void AppendSpotLight::setDifColor(const Color & difColor)
	{
		m_difColor = difColor;
		DxLib::SetLightDifColorHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			DXConverter::toCOLOR_F(m_difColor)
		);
	}

	const Color & AppendSpotLight::getSpcColor() const
	{
		return m_spcColor;
	}

	void AppendSpotLight::setSpcColor(const Color & spcColor)
	{
		m_spcColor = spcColor;
		DxLib::SetLightSpcColorHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			DXConverter::toCOLOR_F(m_spcColor)
		);
	}

	const Color & AppendSpotLight::getAmbColor() const
	{
		return m_ambColor;
	}

	void AppendSpotLight::setAmbColor(const Color & ambColor)
	{
		m_ambColor = ambColor;
		DxLib::SetLightAmbColorHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			DXConverter::toCOLOR_F(m_ambColor)
		);
	}
}