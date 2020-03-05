#include "TktkDirectX11Wrapper/Graphics/Material/Asset/MaterialData.h"

namespace tktk
{
	MaterialData::MaterialData(
		int useVertexShaderId,
		int usePixelShaderId,
		const std::vector<int>& useTextureIdArray,
		const Color & ambientColor,
		const Color & diffuseColor,
		const Color & specularColor,
		const Color & emissionColor,
		float shininess
	)
		: m_useVertexShaderId(useVertexShaderId)
		, m_usePixelShaderId(usePixelShaderId)
		, m_materialParameters(
			useTextureIdArray,
			ambientColor,
			diffuseColor,
			specularColor,
			emissionColor,
			shininess
		)
	{
	}

	int MaterialData::getUseVertexShaderId() const
	{
		return m_useVertexShaderId;
	}

	int MaterialData::getUsePixelShaderId() const
	{
		return m_usePixelShaderId;
	}

	MaterialParameters & MaterialData::getParametersRef()
	{
		return m_materialParameters;
	}
}