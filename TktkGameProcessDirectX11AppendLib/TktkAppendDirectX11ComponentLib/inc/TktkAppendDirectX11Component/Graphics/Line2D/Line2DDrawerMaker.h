#ifndef LINE_2D_DRAWER_MAKER_H_
#define LINE_2D_DRAWER_MAKER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "TktkDirectX11Wrapper/Graphics/BlendState/Asset/SystemBlendStateId.h"
#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/Asset/SystemDepthStencilStateId.h"
#include "Line2DDrawer.h"

namespace tktk
{
	class Line2DDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static Line2DDrawerMaker& makeStart(GameObjectPtr user);

	private:

		// ���g�̃|�C���^
		static Line2DDrawerMaker m_self;

	private:

		// �v���C�x�[�g�R���X�g���N�^�B
		Line2DDrawerMaker() = default;
		Line2DDrawerMaker(const Line2DDrawerMaker& other) = default;
		Line2DDrawerMaker& operator = (const Line2DDrawerMaker& other) = default;

	public:

		// �쐬����
		CfpPtr<Line2DDrawer> create();

		// �`��D��x��ݒ肷��
		Line2DDrawerMaker& drawPriority(float value);

		// �������\�����钸�_���W�̔z���ݒ肷��
		Line2DDrawerMaker& lineVertexArray(const std::vector<Vector2>& value);

		// ���̐F��ݒ肷��
		Line2DDrawerMaker& lineColor(const Color& value);

		// �`���摜�ɕ`�挋�ʂ��ǂꂮ�炢�̔䗦�Ńu�����h���邩��ݒ肷��
		Line2DDrawerMaker& blendRate(const Color& value);

		// �u�����h�X�e�[�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		Line2DDrawerMaker& blendStateId(IdType value)
		{
			return blendStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		Line2DDrawerMaker& blendStateId(IdType value) { static_assert(false, "BlendStateId Fraud Type"); }

		// �[�x�X�e���V���X�e�[�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		Line2DDrawerMaker& depthStencilStateId(IdType value)
		{
			return depthStencilStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		Line2DDrawerMaker& depthStencilStateId(IdType value) { static_assert(false, "DepthStencilStateId Fraud Type"); }
	
	private:

		// �e��id�w��n�̊֐��̎���
		Line2DDrawerMaker& blendStateIdImpl(int value);
		Line2DDrawerMaker& depthStencilStateIdImpl(int value);
	
	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		float m_drawPriority{ 0.0f };
		std::vector<Vector2> m_lineVertexArray{ };
		Color m_lineColor{ Color::white };
		int m_blendStateId{ static_cast<int>(SystemBlendStateId::Alpha) };
		int m_depthStencilStateId{ static_cast<int>(SystemDepthStencilStateId::NotUseDepth) };
		Color m_blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };
	};
}
#endif // !LINE_2D_DRAWER_MAKER_H_