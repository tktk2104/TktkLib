#ifndef APPEND_SPOT_LIGHT_MAKER_H_
#define APPEND_SPOT_LIGHT_MAKER_H_

#include "AppendSpotLight.h"

namespace tktk
{
	class AppendSpotLightMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static AppendSpotLightMaker& makeStart();

	public:

		// �쐬����
		AppendSpotLight* create();

		// ���g�̃��C�gID��ݒ�
		AppendSpotLightMaker& lightId(int value);

		// �X�|�b�g���C�g�̉e���p�x��ݒ�
		AppendSpotLightMaker& outAngleDegree(float value);

		// �X�|�b�g���C�g�̌����J�n�p�x��ݒ�
		AppendSpotLightMaker& inAngleDegree(float value);

		// ���C�g�̓͂�������ݒ�
		AppendSpotLightMaker& range(float value);

		// ���C�g�̉e���͂̋��������Ɏg�p����l��ݒ�
		// d = ���C�g���璸�_�ւ̋���
		// ���C�g�̉e����(��) = 100.0f / (Atten0 + Atten1 * d + Atten2 * d * d)
		AppendSpotLightMaker& attenuation(const std::array<float, 3>& value);

		// ���g�̊g�U���ˌ���ݒ�
		AppendSpotLightMaker& difColor(const Color& value);

		// ���g�̋��ʔ��ˌ���ݒ�
		AppendSpotLightMaker& spcColor(const Color& value);

		// ���g�̊�����ݒ�
		AppendSpotLightMaker& ambColor(const Color& value);

	private:

		// ���g�̃|�C���^
		static AppendSpotLightMaker m_self;

	private:

		int m_lightId{ -1 };
		float m_outAngleDegree{ 90.0f };
		float m_inAngleDegree{ 45.0f };
		float m_range{ 2000.0f };
		std::array<float, 3> m_attenuation{ std::array<float, 3>({ 0.0f, 0.0006f, 0.0f }) };
		Color m_difColor{ Color::white };
		Color m_spcColor{ Color::white };
		Color m_ambColor{ Color::white };
	};
}
#endif // !APPEND_SPOT_LIGHT_MAKER_H_