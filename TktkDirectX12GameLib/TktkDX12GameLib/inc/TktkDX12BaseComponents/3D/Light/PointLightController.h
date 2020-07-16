#ifndef POINT_LIGHT_CONTROLLER_H_
#define POINT_LIGHT_CONTROLLER_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// �|�C���g���C�g����R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform3D�z
	class PointLightController
		: public ComponentBase
	{
	public:

		PointLightController(
			unsigned int lightId,
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular
		);

	public:

		void start();
		void afterCollide();

	public:

		// ������ݒ肷��
		void setAmbient(const tktkMath::Color& ambient);

		// �g�U���ˌ���ݒ肷��
		void setDiffuse(const tktkMath::Color& diffuse);

		// ���ʔ��ˌ���ݒ肷��
		void setSpeqular(const tktkMath::Color& speqular);

	private:

		// ���C�g�������g�̈����ƁuTransform3D�v���g���čX�V����
		void updateLight();

	private:

		unsigned int				m_lightId;
		tktkMath::Color				m_ambient;
		tktkMath::Color				m_diffuse;
		tktkMath::Color				m_speqular;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !POINT_LIGHT_CONTROLLER_H_