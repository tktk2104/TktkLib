#include "TktkAppendDxlib3DComponent/Graphics/Light/BasicDirectionalLight.h"

#include <stdexcept>
#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <DxLib.h>

namespace tktk
{
	BasicDirectionalLight::BasicDirectionalLight(
		const Color & difColor,
		const Color & spcColor,
		const Color & ambColor
	)
		: m_difColor(difColor)
		, m_spcColor(spcColor)
		, m_ambColor(ambColor)
	{
	}

	void BasicDirectionalLight::start()
	{
		auto transform3D = getComponent<Transform3D>();

		if (transform3D.isNull())
		{
			throw std::runtime_error("BasicLight not found Transform3D");
		}

		m_transform3D = transform3D;

		DxLib::ChangeLightTypeDir(DXConverter::toVECTOR(m_transform3D->calculateLocalForwardLH()));
	
		DxLib::SetLightDifColor(DXConverter::toCOLOR_F(m_difColor));
		DxLib::SetLightSpcColor(DXConverter::toCOLOR_F(m_spcColor));
		DxLib::SetLightAmbColor(DXConverter::toCOLOR_F(m_ambColor));
	}

	void BasicDirectionalLight::onEnable()
	{
		DxLib::SetLightEnable(TRUE);
	}

	void BasicDirectionalLight::onDisable()
	{
		DxLib::SetLightEnable(FALSE);
	}

	void BasicDirectionalLight::update()
	{
		DxLib::SetLightDirection(DXConverter::toVECTOR(m_transform3D->calculateLocalForwardLH()));
	}

	const Color & BasicDirectionalLight::getDifColor() const
	{
		return m_difColor;
	}

	void BasicDirectionalLight::setDifColor(const Color & difColor)
	{
		m_difColor = difColor;
		DxLib::SetLightDifColor(DXConverter::toCOLOR_F(m_difColor));
	}

	const Color & BasicDirectionalLight::getSpcColor() const
	{
		return m_spcColor;
	}

	void BasicDirectionalLight::setSpcColor(const Color & spcColor)
	{
		m_spcColor = spcColor;
		DxLib::SetLightSpcColor(DXConverter::toCOLOR_F(m_spcColor));
	}

	const Color & BasicDirectionalLight::getAmbColor() const
	{
		return m_ambColor;
	}

	void BasicDirectionalLight::setAmbColor(const Color & ambColor)
	{
		m_ambColor = ambColor;
		DxLib::SetLightAmbColor(DXConverter::toCOLOR_F(m_ambColor));
	}
}