#ifndef BASIC_DIRECTIONAL_LIGHT_MAKER_H_
#define BASIC_DIRECTIONAL_LIGHT_MAKER_H_

#include "BasicDirectionalLight.h"

namespace tktk
{
	class BasicDirectionalLightMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static BasicDirectionalLightMaker& makeStart();

	public:

		// �쐬����
		BasicDirectionalLight* create();

		// ���g�̊g�U���ˌ���ݒ�
		BasicDirectionalLightMaker& difColor(const Color& value);

		// ���g�̋��ʔ��ˌ���ݒ�
		BasicDirectionalLightMaker& spcColor(const Color& value);

		// ���g�̊�����ݒ�
		BasicDirectionalLightMaker& ambColor(const Color& value);

	private:

		// ���g�̃|�C���^
		static BasicDirectionalLightMaker m_self;

	private:

		Color m_difColor{ Color::white };
		Color m_spcColor{ Color::white };
		Color m_ambColor{ Color::white };
	};
}
#endif // !BASIC_DIRECTIONAL_LIGHT_MAKER_H_