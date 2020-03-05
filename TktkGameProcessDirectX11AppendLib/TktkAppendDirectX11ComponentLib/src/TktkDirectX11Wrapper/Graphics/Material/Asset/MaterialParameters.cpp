#include "TktkDirectX11Wrapper/Graphics/Material/Asset/MaterialParameters.h"

namespace tktk
{
	MaterialParameters::MaterialParameters(const std::vector<int>& useTextureIdArray, const Color & ambientColor, const Color & diffuseColor, const Color & specularColor, const Color & emissionColor, float shininess)
		: m_useTextureIdArray(useTextureIdArray)
		, m_ambientColor(ambientColor)
		, m_diffuseColor(diffuseColor)
		, m_specularColor(specularColor)
		, m_emissionColor(emissionColor)
		, m_shininess(shininess)
	{
	}

	const std::unordered_map<int, SafetyVoidPtr>& MaterialParameters::getConstantBufferSetData() const
	{
		return m_constantBufferSetData;
	}

	const std::vector<int>& MaterialParameters::getUseTextureIdArray() const
	{
		return m_useTextureIdArray;
	}

	const Color & MaterialParameters::getAmbientColor() const
	{
		return m_ambientColor;
	}

	void MaterialParameters::setAmbientColor(Color && value)
	{
		m_ambientColor = std::move(value);
	}

	const Color & MaterialParameters::getDiffuseColor() const
	{
		return m_diffuseColor;
	}

	void MaterialParameters::setDiffuseColor(Color && value)
	{
		m_diffuseColor = std::move(value);
	}

	const Color & MaterialParameters::getSpecularColor() const
	{
		return m_specularColor;
	}

	void MaterialParameters::setSpecularColor(Color && value)
	{
		m_specularColor = std::move(value);
	}

	const Color & MaterialParameters::getEmissionColor() const
	{
		return m_emissionColor;
	}

	void MaterialParameters::setEmissionColor(Color && value)
	{
		m_emissionColor = std::move(value);
	}

	float MaterialParameters::getShininess() const
	{
		return m_shininess;
	}

	void MaterialParameters::setShininess(float value)
	{
		m_shininess = value;
	}

	void MaterialParameters::setUseTextureIdImpl(std::vector<int>&& textureIdArray)
	{
		m_useTextureIdArray = std::move(textureIdArray);
	}

	void MaterialParameters::addUseTextureIdImpl(int textureId)
	{
		m_useTextureIdArray.push_back(textureId);
	}
}