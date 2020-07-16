#ifndef POINT_LIGHT_CONTROLLER_MAKER_H_
#define POINT_LIGHT_CONTROLLER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "PointLightController.h"

namespace tktk
{
	// �uPointLightController�v�����w���p�[�N���X
	class PointLightControllerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		PointLightControllerMaker() = default;
		PointLightControllerMaker(const PointLightControllerMaker& other) = default;
		PointLightControllerMaker& operator = (const PointLightControllerMaker& other) = default;

	public:

		// �쐬�J�n
		static PointLightControllerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<PointLightController> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �g�p���鏉�����C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		PointLightControllerMaker& initLightId(IdType value);

		// ����������ݒ肷��
		PointLightControllerMaker& initAmbient(const tktkMath::Color& value);

		// �����g�U���ˌ���ݒ肷��
		PointLightControllerMaker& initDiffuse(const tktkMath::Color& value);

		// �������ʔ��ˌ���ݒ肷��
		PointLightControllerMaker& initSpeqular(const tktkMath::Color& value);

	private: /* �e��id�w��n�̊֐��̎��� */

		PointLightControllerMaker& initLightIdImpl(unsigned int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static PointLightControllerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr	m_user			{  };
		unsigned int	m_initLightId	{ 0U };
		tktkMath::Color	m_initAmbient	{ 0.25f, 1.0f };
		tktkMath::Color	m_initDiffuse	{ 0.25f, 1.0f };
		tktkMath::Color	m_initSpeqular	{ 0.25f, 1.0f };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		PointLightControllerMaker& initLightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �g�p���鏉�����C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline PointLightControllerMaker& PointLightControllerMaker::initLightId(IdType value)
	{
		return initLightIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !POINT_LIGHT_CONTROLLER_MAKER_H_