#include "TktkAppendDxlib3DComponent/Graphics/Light/AppendDirectionalLight.h"

#include <stdexcept>
#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <TktkDxlib3DWrapper/Assets/Assets3DManager.h>
#include <DxLib.h>

namespace tktk
{
	AppendDirectionalLight::AppendDirectionalLight(
		int lightId,
		const Color & difColor,
		const Color & spcColor,
		const Color & ambColor
	)
		: m_lightId(lightId)
		, m_difColor(difColor)
		, m_spcColor(spcColor)
		, m_ambColor(ambColor)
	{
	}

	void AppendDirectionalLight::start()
	{
		auto transform3D = getComponent<Transform3D>();

		if (transform3D.isNull())
		{
			throw std::runtime_error("BasicLight not found Transform3D");
		}

		m_transform3D = transform3D;

		int lightHandle = Assets3DManager::getLightAssets()->getLightHandle(m_lightId);

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

	void AppendDirectionalLight::onEnable()
	{
		DxLib::SetLightEnableHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			TRUE
		);
	}

	void AppendDirectionalLight::onDisable()
	{
		DxLib::SetLightEnableHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			FALSE
		);
	}

	void AppendDirectionalLight::update()
	{
		DxLib::SetLightDirectionHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			DXConverter::toVECTOR(m_transform3D->calculateLocalForwardLH())
		);
	}

	const Color & AppendDirectionalLight::getDifColor() const
	{
		return m_difColor;
	}

	void AppendDirectionalLight::setDifColor(const Color & difColor)
	{
		m_difColor = difColor;
		DxLib::SetLightDifColorHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			DXConverter::toCOLOR_F(m_difColor)
		);
	}

	const Color & AppendDirectionalLight::getSpcColor() const
	{
		return m_spcColor;
	}

	void AppendDirectionalLight::setSpcColor(const Color & spcColor)
	{
		m_spcColor = spcColor;
		DxLib::SetLightSpcColorHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			DXConverter::toCOLOR_F(m_spcColor)
		);
	}

	const Color & AppendDirectionalLight::getAmbColor() const
	{
		return m_ambColor;
	}

	void AppendDirectionalLight::setAmbColor(const Color & ambColor)
	{
		m_ambColor = ambColor;
		DxLib::SetLightAmbColorHandle(
			Assets3DManager::getLightAssets()->getLightHandle(m_lightId),
			DXConverter::toCOLOR_F(m_ambColor)
		);
	}
}