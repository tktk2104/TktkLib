#include "TktkAppendDirectX11Component/Graphics/Light/PointLight.h"

#include "TktkDirectX11Wrapper/Graphics/Light/Light.h"

namespace tktk
{
	PointLight::PointLight(int lightId, const Color & ambient, const Color & diffuse, const Color & specular)
		: m_lightId(lightId)
	{
		Light::create(lightId, ambient, diffuse, specular, Vector3::zero);
		m_lightDataPtr = Light::getLightDataPtr(lightId);
	}

	PointLight::~PointLight()
	{
	}

	void PointLight::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.isNull())
		{
			throw std::runtime_error("SimpleCamera Transform3D not found");
		}

		Light::enableLight(m_lightId);
	}

	void PointLight::afterCollide()
	{
		m_lightDataPtr->setPosition(m_transform->getWorldPosition());
	}

	void PointLight::enable()
	{
		Light::enableLight(m_lightId);
	}

	void PointLight::disable()
	{
		Light::disableLight(m_lightId);
	}

	Color PointLight::getAmbientColor() const
	{
		return m_lightDataPtr->getAmbientColor();
	}

	void PointLight::setAmbientColor(const Color & ambient)
	{
		m_lightDataPtr->setAmbientColor(ambient);
	}

	Color PointLight::getDiffuseColor() const
	{
		return m_lightDataPtr->getDiffuseColor();
	}

	void PointLight::setDiffuseColor(const Color & diffuse)
	{
		m_lightDataPtr->setDiffuseColor(diffuse);
	}

	Color PointLight::getSpecularColor() const
	{
		return m_lightDataPtr->getSpecularColor();
	}

	void PointLight::setSpecularColor(const Color & specular)
	{
		m_lightDataPtr->setSpecularColor(specular);
	}
}