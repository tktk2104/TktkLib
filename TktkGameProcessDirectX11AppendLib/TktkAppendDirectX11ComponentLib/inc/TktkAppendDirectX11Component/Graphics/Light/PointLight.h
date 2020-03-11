#ifndef POINT_LIGHT_H_
#define POINT_LIGHT_H_

#include <TktkMath/Color.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include "TktkDirectX11Wrapper/Graphics/Light/Asset/LightData.h"

namespace tktk
{
	class PointLight
		: public ComponentBase
	{
	public:

		PointLight(int lightId, const Color& ambient, const Color& diffuse, const Color& specular);
		~PointLight();

	public:

		void start();

		void afterCollide();

	public:

		void enable();

		void disable();

		// �����̐F���擾����
		Color getAmbientColor() const;

		// �����̐F��ݒ肷��
		void setAmbientColor(const Color& ambient);

		// �g�U���ˌ��̐F���擾����
		Color getDiffuseColor() const;

		// �g�U���ˌ��̐F��ݒ肷��
		void setDiffuseColor(const Color& diffuse);

		// ���ʔ��ˌ��̐F���擾����
		Color getSpecularColor() const;

		// ���ʔ��ˌ��̐F��ݒ肷��
		void setSpecularColor(const Color& specular);

	private:

		CfpPtr<Transform3D> m_transform;

		int m_lightId;
		LightData* m_lightDataPtr;
	};
}
#endif // !POINT_LIGHT_H_