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
		*m_lightDataPtr->getPositionPtr() = m_transform->getWorldPosition();
	}

	void PointLight::enable()
	{
		Light::enableLight(m_lightId);
	}

	void PointLight::disable()
	{
		Light::disableLight(m_lightId);
	}

	Color * PointLight::getAmbientColor()
	{
		return m_lightDataPtr->getAmbientColorPtr();
	}

	Color * PointLight::getDiffuseColor()
	{
		return m_lightDataPtr->getDiffuseColorPtr();
	}

	Color * PointLight::getSpecularColor()
	{
		return m_lightDataPtr->getSpecularColorPtr();
	}
}