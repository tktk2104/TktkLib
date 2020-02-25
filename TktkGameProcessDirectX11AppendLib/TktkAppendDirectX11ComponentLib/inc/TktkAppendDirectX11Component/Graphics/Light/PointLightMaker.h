#ifndef POINT_LIGHT_MAKER_H_
#define POINT_LIGHT_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "PointLight.h"

namespace tktk
{
	class PointLightMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static PointLightMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<PointLight> create();

		PointLightMaker& lightId(int value);

		PointLightMaker& ambientColor(const Color& value);

		PointLightMaker& diffuseColor(const Color& value);

		PointLightMaker& specularColor(const Color& value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static PointLightMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		int m_lightId{ 0 };
		Color m_ambientColor{ Color(0.3f, 0.3f, 0.3f, 1.0f) };
		Color m_diffuseColor{ Color::white };
		Color m_specularColor{ Color::white };
	};
}
#endif // !POINT_LIGHT_MAKER_H_