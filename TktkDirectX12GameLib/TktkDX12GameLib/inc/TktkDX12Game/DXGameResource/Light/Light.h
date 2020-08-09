#ifndef LIGHT_H_
#define LIGHT_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "LightData.h"

namespace tktk
{
	// �uLightData�v���Ǘ�����N���X
	class Light
	{
	public:

		explicit Light(unsigned int lightNum);
		~Light() = default;

	public:

		// �uLightData�v�̃C���X�^���X�����
		void create(
			unsigned int id,
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ���C�g���̒萔�o�b�t�@���X�V����
		void updateLightCBuffer(unsigned int id) const;

		// �w��̃��C�g�̊�����ݒ肷��
		void setAmbient(unsigned int id, const tktkMath::Color& ambient);

		// �w��̃��C�g�̊g�U���ˌ���ݒ肷��
		void setDiffuse(unsigned int id, const tktkMath::Color& diffuse);

		// �w��̃��C�g�̋��ʔ��ˌ���ݒ肷��
		void setSpeqular(unsigned int id, const tktkMath::Color& speqular);

		// �w��̃��C�g�̍��W��ݒ肷��
		void setPosition(unsigned int id, const tktkMath::Vector3& position);

	private:

		HeapArray<LightData> m_lightArray;
	};
}
#endif // !LIGHT_H_