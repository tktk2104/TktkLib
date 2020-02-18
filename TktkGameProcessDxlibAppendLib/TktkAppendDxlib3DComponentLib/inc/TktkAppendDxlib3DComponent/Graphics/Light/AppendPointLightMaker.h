#ifndef APPEND_POINT_LIGHT_MAKER_H_
#define APPEND_POINT_LIGHT_MAKER_H_

#include <memory>
#include "AppendPointLight.h"

namespace tktk
{
	class AppendPointLightMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static AppendPointLightMaker& makeStart();

	public:

		// �쐬����
		std::shared_ptr<AppendPointLight> create();

		// ���g�̃��C�gID��ݒ�
		AppendPointLightMaker& lightId(int value);

		// ���C�g�̓͂�������ݒ�
		AppendPointLightMaker& range(float value);

		// ���C�g�̉e���͂̋��������Ɏg�p����l��ݒ�
		// d = ���C�g���璸�_�ւ̋���
		// ���C�g�̉e����(��) = 100.0f / (Atten0 + Atten1 * d + Atten2 * d * d)
		AppendPointLightMaker& attenuation(const std::array<float, 3>& value);

		// ���g�̊g�U���ˌ���ݒ�
		AppendPointLightMaker& difColor(const Color& value);

		// ���g�̋��ʔ��ˌ���ݒ�
		AppendPointLightMaker& spcColor(const Color& value);

		// ���g�̊�����ݒ�
		AppendPointLightMaker& ambColor(const Color& value);

	private:

		// ���g�̃|�C���^
		static AppendPointLightMaker m_self;

	private:

		int m_lightId{ -1 };
		float m_range{ 2000.0f };
		std::array<float, 3> m_attenuation{ std::array<float, 3>({ 0.0f, 0.0006f, 0.0f }) };
		Color m_difColor{ Color::white };
		Color m_spcColor{ Color::white };
		Color m_ambColor{ Color::white };
	};
}
#endif // !APPEND_POINT_LIGHT_MAKER_H_