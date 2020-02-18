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

	Color * LightData::getAmbientColorPtr()
	{
		return &m_ambientColor;
	}

	Color * LightData::getDiffuseColorPtr()
	{
		return &m_diffuseColor;
	}

	Color * LightData::getSpecularColorPtr()
	{
		return &m_specularColor;
	}

	Vector3 * LightData::getPositionPtr()
	{
		return &m_position;
	}
}