#include "TktkDirectX11Wrapper/Graphics/Light/Asset/LightData.h"

namespace tktk
{
	LightData::LightData(
		const Color & ambientColor,
		const Color & diffuseColor,
		const Color & specularColor,
		const Vector3 & position
	)
		: m_ambientColor(ambientColor)
		, m_diffuseColor(diffuseColor)
		, m_specularColor(specularColor)
		, m_position(position)
	{
	}

	LightData::~LightData()
	{
	}

	const Color & LightData::getAmbientColor() const
	{
		return m_ambientColor;
	}

	void LightData::setAmbientColor(const Color & ambient)
	{
		m_ambientColor = ambient;
	}

	const Color & LightData::getDiffuseColor() const
	{
		return m_diffuseColor;
	}

	void LightData::setDiffuseColor(const Color & diffuse)
	{
		m_diffuseColor = diffuse;
	}

	const Color & LightData::getSpecularColor() const
	{
		return m_specularColor;
	}

	void LightData::setSpecularColor(const Color & specular)
	{
		m_specularColor = specular;
	}

	const Vector3 & LightData::getPosition() const
	{
		return m_position;
	}

	void LightData::setPosition(const Vector3 & pos)
	{
		m_position = pos;
	}
}