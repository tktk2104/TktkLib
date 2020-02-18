#ifndef APPEND_SPOT_LIGHT_H_
#define APPEND_SPOT_LIGHT_H_

#include <memory>
#include <array>
#include <TktkMath/Color.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>

namespace tktk
{
	class AppendSpotLight
		: public ComponentBase
	{
	public:

		AppendSpotLight(
			int lightId,
			float outAngleDegree,
			float inAngleDegree,
			float range,
			const std::array<float, 3>& attenuation,
			const Color& difColor,
			const Color& spcColor,
			const Color& ambColor
		);

	public:

		void start();
		void onEnable();
		void onDisable();
		void update();

	public:

		// �X�|�b�g���C�g�̉e���p�x���擾
		float getOutAngleDegree() const;
		// �X�|�b�g���C�g�̉e���p�x���Đݒ�
		void setOutAngleDegree(float outAngleDegree);

		// �X�|�b�g���C�g�̌����J�n�p�x���擾
		float getInAngleDegree() const;
		// �X�|�b�g���C�g�̌����J�n�p�x���Đݒ�
		void setInAngleDegree(float inAngleDegree);

		// ���̓͂��������擾
		float getRange() const;
		// ���̓͂��������Đݒ�
		void setRange(float range);

		// ���C�g�̉e���͂̋��������Ɏg�p����l���擾
		// d = ���C�g���璸�_�ւ̋���
		// ���C�g�̉e����(��) = 100.0f / (Atten0 + Atten1 * d + Atten2 * d * d)
		const std::array<float, 3>& getAttenuation() const;
		// ���C�g�̉e���͂̋��������Ɏg�p����l���Đݒ�
		// d = ���C�g���璸�_�ւ̋���
		// ���C�g�̉e����(��) = 100.0f / (Atten0 + Atten1 * d + Atten2 * d * d)
		void setAttenuation(const std::array<float, 3>& attenuation);

		// ���g�̊g�U���ˌ����擾
		const Color& getDifColor() const;
		// ���g�̊g�U���ˌ����Đݒ�
		void setDifColor(const Color& difColor);

		// ���g�̋��ʔ��ˌ����擾
		const Color& getSpcColor() const;
		// ���g�̋��ʔ��ˌ����Đݒ�
		void setSpcColor(const Color& spcColor);

		// ���g�̊������擾
		const Color& getAmbColor() const;
		// ���g�̊������Đݒ�
		void setAmbColor(const Color& ambColor);

	private:

		std::weak_ptr<Transform3D> m_transform3D;

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
#endif // !APPEND_SPOT_LIGHT_H_