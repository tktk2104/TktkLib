#include "TktkDirectX11Wrapper/Graphics/Material/Asset/MaterialAssets.h"

namespace tktk
{
	MaterialAssets::~MaterialAssets()
	{
		clear();
	}

	void MaterialAssets::create(
		int id,
		int indexBufferStartPos,
		int indexBufferUseCount,
		int useVertexShaderId,
		int usePixelShaderId,
		const std::unordered_map<unsigned int, int>& useTextureIdMap,
		const Color & ambientColor,
		const Color & diffuseColor,
		const Color & specularColor,
		const Color & emissionColor,
		float shiniess
	)
	{
		erase(id);

		m_assets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(
				indexBufferStartPos,
				indexBufferUseCount,
				useVertexShaderId,
				usePixelShaderId,
				useTextureIdMap,
				ambientColor,
				diffuseColor,
				specularColor,
				emissionColor,
				shiniess
			)
		);
	}

	void MaterialAssets::duplicate(int id, int originalId)
	{
		MaterialData * originalDataPtr = getDataPtr(originalId);

		create(
			id,
			originalDataPtr->getIndexBufferStartPos(),
			originalDataPtr->getIndexBufferUseCount(),
			originalDataPtr->getUseVertexShaderId(),
			originalDataPtr->getUseVertexShaderId(),
			originalDataPtr->getUseTextureIdMap(),
			*originalDataPtr->getAmbientColorPtr(),
			*originalDataPtr->getDiffuseColorPtr(),
			*originalDataPtr->getSpecularColorPtr(),
			*originalDataPtr->getEmissionColorPtr(),
			*originalDataPtr->getShininessPtr()
		);
	}

	void MaterialAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void MaterialAssets::clear()
	{
		m_assets.clear();
	}

	MaterialData * MaterialAssets::getDataPtr(int id)
	{
		return &(m_assets.at(id));
	}
}