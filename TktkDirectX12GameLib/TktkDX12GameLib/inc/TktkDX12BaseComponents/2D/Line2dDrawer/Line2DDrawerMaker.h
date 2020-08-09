#ifndef LINE_2D_DRAWER_MAKER_H_
#define LINE_2D_DRAWER_MAKER_H_
#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "Line2DDrawer.h"

namespace tktk
{
	// �uLine2DDrawerMaker�v�����w���p�[�N���X
	class Line2DDrawerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		Line2DDrawerMaker() = default;
		Line2DDrawerMaker(const Line2DDrawerMaker & other) = default;
		Line2DDrawerMaker& operator = (const Line2DDrawerMaker & other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static Line2DDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<Line2DDrawer> create();
	

	public: /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		Line2DDrawerMaker& drawPriority(float value);

		// �g�p������̃}�e���A��ID��ݒ肷��
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		Line2DDrawerMaker& useLine2DMaterialId(IdType value);

		// �������\�����钸�_���W�̔z���ݒ肷��
		Line2DDrawerMaker& lineVertexArray(const std::vector<tktkMath::Vector2>& value);

		// ���̐F��ݒ肷��
		Line2DDrawerMaker& lineColor(const tktkMath::Color& value);

		// �`���摜�ɕ`�挋�ʂ��ǂꂮ�炢�̔䗦�Ńu�����h���邩��ݒ肷��
		Line2DDrawerMaker& blendRate(const tktkMath::Color& value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�vID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		Line2DDrawerMaker& useRtvDescriptorHeapId(IdType value);
	
	private: /* �e��id�w��n�̊֐��̎��� */

		Line2DDrawerMaker& useLine2DMaterialIdImpl(unsigned int value);
		Line2DDrawerMaker& useRtvDescriptorHeapIdImpl(unsigned int value);

	private:

		// ���g�̃|�C���^
		static Line2DDrawerMaker m_self;
	
	private:

		// �쐬�p�ϐ��B
		GameObjectPtr					m_user{ };
		float							m_drawPriority{ 0.0f };
		unsigned int					m_useLine2DMaterialId{  };
		unsigned int					m_useRtvDescriptorHeapId{  }; // �������p�����[�^�̓o�b�N�o�b�t�@�[
		std::vector<tktkMath::Vector2>	m_lineVertexArray{ };
		tktkMath::Color					m_lineColor{ tktkMath::colorWhite };
		tktkMath::Color					m_blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		Line2DDrawerMaker& useLine2DMaterialId(IdType value) { static_assert(false, "Line2DMaterialId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		Line2DDrawerMaker& useRtvDescriptorHeapId(IdType value) { static_assert(false, "RtvDescriptorHeapId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �g�p������̃}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline Line2DDrawerMaker& Line2DDrawerMaker::useLine2DMaterialId(IdType value)
	{
		return useLine2DMaterialIdImpl(static_cast<unsigned int>(value));
	}

	// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�vID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline Line2DDrawerMaker& Line2DDrawerMaker::useRtvDescriptorHeapId(IdType value)
	{
		return useRtvDescriptorHeapIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !LINE_2D_DRAWER_MAKER_H_