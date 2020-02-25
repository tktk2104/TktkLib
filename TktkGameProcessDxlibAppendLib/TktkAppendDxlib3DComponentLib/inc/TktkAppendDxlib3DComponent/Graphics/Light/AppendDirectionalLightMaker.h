#ifndef APPEND_DIRECTIONAL_LIGHT_MAKER_H_
#define APPEND_DIRECTIONAL_LIGHT_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "AppendDirectionalLight.h"

namespace tktk
{
	class AppendDirectionalLightMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static AppendDirectionalLightMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<AppendDirectionalLight> create();

		// ���g�̃��C�gID��ݒ�
		AppendDirectionalLightMaker& lightId(int value);

		// ���g�̊g�U���ˌ���ݒ�
		AppendDirectionalLightMaker& difColor(const Color& value);

		// ���g�̋��ʔ��ˌ���ݒ�
		AppendDirectionalLightMaker& spcColor(const Color& value);

		// ���g�̊�����ݒ�
		AppendDirectionalLightMaker& ambColor(const Color& value);

	private:

		// ���g�̃|�C���^
		static AppendDirectionalLightMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		int m_lightId{ -1 };
		Color m_difColor{ Color::white };
		Color m_spcColor{ Color::white };
		Color m_ambColor{ Color::white };
	};
}
#endif // !APPEND_DIRECTIONAL_LIGHT_MAKER_H_