#ifndef BASIC_MESH_SHADOW_MAP_WRITER_MAKER_H_
#define BASIC_MESH_SHADOW_MAP_WRITER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BasicMeshShadowMapWriter.h"

namespace tktk
{
	// �uBasicMeshShadowMapWriter�v�����w���p�[�N���X
	class BasicMeshShadowMapWriterMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BasicMeshShadowMapWriterMaker() = default;
		BasicMeshShadowMapWriterMaker(const BasicMeshShadowMapWriterMaker& other) = default;
		BasicMeshShadowMapWriterMaker& operator = (const BasicMeshShadowMapWriterMaker& other) = default;

	public:

		// �쐬�J�n
		static BasicMeshShadowMapWriterMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BasicMeshShadowMapWriter> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		BasicMeshShadowMapWriterMaker& drawPriority(float value);

		// �g�p���郁�b�V��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		BasicMeshShadowMapWriterMaker& meshId(IdType value);

		// �g�p����X�P���g��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		BasicMeshShadowMapWriterMaker& skeletonId(IdType value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		BasicMeshShadowMapWriterMaker& cameraId(IdType value);

	private: /* �e��id�w��n�̊֐��̎��� */

		BasicMeshShadowMapWriterMaker& meshIdImpl(unsigned int value);
		BasicMeshShadowMapWriterMaker& skeletonIdImpl(unsigned int value);
		BasicMeshShadowMapWriterMaker& cameraIdImpl(unsigned int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BasicMeshShadowMapWriterMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr	m_user			{  };
		float			m_drawPriority	{ 0.0f };
		unsigned int	m_meshId		{ 0U };
		unsigned int	m_skeletonId	{ 0U };
		unsigned int	m_cameraId		{ 0U };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BasicMeshShadowMapWriterMaker& meshId(IdType value) { static_assert(false, "MeshId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BasicMeshShadowMapWriterMaker& skeletonId(IdType value) { static_assert(false, "SkeletonId Fraud Type"); }
	
		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BasicMeshShadowMapWriterMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �g�p���郁�b�V��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::meshId(IdType value)
	{
		return meshIdImpl(static_cast<unsigned int>(value));
	}

	// �g�p����X�P���g��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::skeletonId(IdType value)
	{
		return skeletonIdImpl(static_cast<unsigned int>(value));
	}

	// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::cameraId(IdType value)
	{
		return cameraIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !BASIC_MESH_SHADOW_MAP_WRITER_MAKER_H_
