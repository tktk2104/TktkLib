#include "TktkDirectX11Wrapper/Graphics/Material/Asset/MaterialData.h"

namespace tktk
{
	MaterialData::MaterialData(
		int indexBufferStartPos,
		int indexBufferUseCount,
		int useVertexShaderId,
		int usePixelShaderId,
		const std::unordered_map<unsigned int, int>& useTextureIdMap,
		const Color & ambientColor,
		const Color & diffuseColor,
		const Color & specularColor,
		const Color & emissionColor,
		float shininess
	)
		: m_indexBufferStartPos(indexBufferStartPos)
		, m_indexBufferUseCount(indexBufferUseCount)
		, m_useVertexShaderId(useVertexShaderId)
		, m_usePixelShaderId(usePixelShaderId)
		, m_useTextureIdMap(useTextureIdMap)
		, m_ambientColor(ambientColor)
		, m_diffuseColor(diffuseColor)
		, m_specularColor(specularColor)
		, m_emissionColor(emissionColor)
		, m_shininess(shininess)
	{
	}

	MaterialData::~MaterialData()
	{
	}

	int MaterialData::getIndexBufferStartPos() const
	{
		return m_indexBufferStartPos;
	}

	int MaterialData::getIndexBufferUseCount() const
	{
		return m_indexBufferUseCount;
	}

	int MaterialData::getUseVertexShaderId() const
	{
		return m_useVertexShaderId;
	}

	void MaterialData::setUseVertexShaderId(int id)
	{
		m_useVertexShaderId = id;
	}

	int MaterialData::getUsePixelShaderId() const
	{
		return m_usePixelShaderId;
	}

	void MaterialData::setUsePixelShaderId(int id)
	{
		m_usePixelShaderId = id;
	}

	const std::unordered_map<unsigned int, int>& MaterialData::getUseTextureIdMap() const
	{
		return m_useTextureIdMap;
	}

	void MaterialData::addUseTextureId(unsigned int stage, int id)
	{
		m_useTextureIdMap.insert(std::make_pair(stage, id));
	}

	void MaterialData::clearUseTextureId()
	{
		m_useTextureIdMap.clear();
	}

	Color * MaterialData::getAmbientColorPtr()
	{
		return &m_ambientColor;
	}

	Color * MaterialData::getDiffuseColorPtr()
	{
		return &m_diffuseColor;
	}

	Color * MaterialData::getSpecularColorPtr()
	{
		return &m_specularColor;
	}

	Color * MaterialData::getEmissionColorPtr()
	{
		return &m_emissionColor;
	}

	float * MaterialData::getShininessPtr()
	{
		return &m_shininess;
	}

	const std::unordered_map<int, SafetyVoidPtr>& MaterialData::getSetVSConstantBufferParamMap() const
	{
		return m_setVSConstantBufferParamMap;
	}

	const std::unordered_map<int, SafetyVoidPtr>& MaterialData::getSetPSConstantBufferParamMap() const
	{
		return m_setPSConstantBufferParamMap;
	}
}