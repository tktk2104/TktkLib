#ifndef SPRITE_DRAWER_MAKER_H_
#define SPRITE_DRAWER_MAKER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "TktkDirectX11Wrapper/Graphics/BlendState/Asset/SystemBlendStateId.h"
#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/Asset/SystemDepthStencilStateId.h"
#include "SpriteDrawer.h"

namespace tktk
{
	class SpriteDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static SpriteDrawerMaker& makeStart(GameObjectPtr user);

	private:

		// ���g�̃|�C���^
		static SpriteDrawerMaker m_self;

	private:

		// �v���C�x�[�g�R���X�g���N�^�B
		SpriteDrawerMaker() = default;
		SpriteDrawerMaker(const SpriteDrawerMaker& other) = default;
		SpriteDrawerMaker& operator = (const SpriteDrawerMaker& other) = default;

	public:

		// �쐬����
		CfpPtr<SpriteDrawer> create();

		// �`��D��x��ݒ肷��
		SpriteDrawerMaker& drawPriority(float value);

		// �`���摜�ɕ`�挋�ʂ��ǂꂮ�炢�̔䗦�Ńu�����h���邩��ݒ肷��
		SpriteDrawerMaker& blendRate(const Color& value);

		// �e�N�X�`��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SpriteDrawerMaker& textureId(IdType value)
		{
			return textureIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteDrawerMaker& textureId(IdType value) { static_assert(false, "TextureId Fraud Type"); }

		// �u�����h�X�e�[�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SpriteDrawerMaker& blendStateId(IdType value)
		{
			return blendStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteDrawerMaker& blendStateId(IdType value) { static_assert(false, "BlendStateId Fraud Type"); }

		// �[�x�X�e���V���X�e�[�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SpriteDrawerMaker& depthStencilStateId(IdType value)
		{
			return depthStencilStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteDrawerMaker& depthStencilStateId(IdType value) { static_assert(false, "DepthStencilStateId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		SpriteDrawerMaker& textureIdImpl(int value);
		SpriteDrawerMaker& blendStateIdImpl(int value);
		SpriteDrawerMaker& depthStencilStateIdImpl(int value);

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		float m_drawPriority{ 0.0f };
		int m_textureId{ 0 };
		int m_blendStateId{ static_cast<int>(SystemBlendStateId::Alpha) };
		Color m_blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };
		int m_depthStencilStateId{ static_cast<int>(SystemDepthStencilStateId::NotUseDepth) };
	};
}
#endif // !SPRITE_DRAWER_MAKER_H_