#ifndef LIGHT_DATA_H_
#define LIGHT_DATA_H_

#include "LightCBuffer.h"

namespace tktk
{
	// ���C�g�����Ǘ�����N���X
	class LightData
	{
	public:

		LightData(
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);
		~LightData() = default;

	public:

		// ���C�g���̒萔�o�b�t�@���X�V����
		void updateLightCBuffer() const;

		// ������ݒ肷��
		void setAmbient(const tktkMath::Color& ambient);

		// �g�U���ˌ���ݒ肷��
		void setDiffuse(const tktkMath::Color& diffuse);

		// ���ʔ��ˌ���ݒ肷��
		void setSpeqular(const tktkMath::Color& speqular);

		// ���W��ݒ肷��
		void setPosition(const tktkMath::Vector3& position);

	private:

		LightCBuffer		m_lightCBuffer;
	};
}
#endif // !LIGHT_DATA_H_