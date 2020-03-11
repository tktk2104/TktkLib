#ifndef SIMPLE_CAMERA_MAKER_H_
#define SIMPLE_CAMERA_MAKER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "SimpleCamera.h"

namespace tktk
{
	class SimpleCameraMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static SimpleCameraMaker& makeStart(GameObjectPtr user);

	private:

		// ���g�̃|�C���^
		static SimpleCameraMaker m_self;

	private:

		// �v���C�x�[�g�R���X�g���N�^�B
		SimpleCameraMaker() = default;
		SimpleCameraMaker(const SimpleCameraMaker& other) = default;
		SimpleCameraMaker& operator = (const SimpleCameraMaker& other) = default;

	public:

		// �쐬����
		CfpPtr<SimpleCamera> create();

		// �쐬����J������ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SimpleCameraMaker& cameraId(IdType value)
		{
			return cameraIdImpl(static_cast<int>(value));
		}
		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SimpleCameraMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		// �J�����̎ˊp��ݒ肷��
		SimpleCameraMaker& cameraFov(float value);

		// �J�����̃j�A�N���b�v��ݒ肷��
		SimpleCameraMaker& cameraNear(float value);

		// �J�����̃t�@�[�N���b�v��ݒ肷��
		SimpleCameraMaker& cameraFar(float value);

	private:

		// �e��id�w��n�̊֐��̎���
		SimpleCameraMaker& cameraIdImpl(int value);

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		int m_cameraId{ 0 };
		float m_cameraFov{ 45.0f };
		float m_cameraNear{ 0.01f };
		float m_cameraFar{ 1000.0f };
	};
}
#endif // !SIMPLE_CAMERA_MAKER_H_