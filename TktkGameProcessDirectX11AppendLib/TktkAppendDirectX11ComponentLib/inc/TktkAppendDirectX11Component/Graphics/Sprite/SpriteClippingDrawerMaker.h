#ifndef SPRITE_CLIPPING_DRAWER_MAKER_H_
#define SPRITE_CLIPPING_DRAWER_MAKER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "TktkDirectX11Wrapper/Graphics/BlendState/Asset/SystemBlendStateId.h"
#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/Asset/SystemDepthStencilStateId.h"
#include "TktkDirectX11Wrapper/Graphics/RasterizerState/Asset/SystemRasterizerStateId.h"
#include "SpriteClippingDrawer.h"

namespace tktk
{
	class SpriteClippingDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static SpriteClippingDrawerMaker& makeStart(GameObjectPtr user);

	private:

		// ���g�̃|�C���^
		static SpriteClippingDrawerMaker m_self;

	private:

		// �v���C�x�[�g�R���X�g���N�^�B
		SpriteClippingDrawerMaker() = default;
		SpriteClippingDrawerMaker(const SpriteClippingDrawerMaker& other) = default;
		SpriteClippingDrawerMaker& operator = (const SpriteClippingDrawerMaker& other) = default;
	
	public:

		// �쐬����
		CfpPtr<SpriteClippingDrawer> create();
	
		// �`��D��x��ݒ肷��
		SpriteClippingDrawerMaker& drawPriority(float value);

		// �e�N�X�`�����\�[�X�̕`�悷��͈͂̍�����W��ݒ肷��i�e�N�X�`�����W�j
		SpriteClippingDrawerMaker& textureClippingLeftTopPos(const Vector2& value);

		// �e�N�X�`�����\�[�X�̕`�悷��͈͂�ݒ肷��i�e�N�X�`�����W�j
		SpriteClippingDrawerMaker& textureClippingSize(const Vector2& value);

		// �e�N�X�`�����W�ɂ�����l��ݒ肷��
		SpriteClippingDrawerMaker& textureUvMulRate(const Vector2& value);

		// �`���摜�ɕ`�挋�ʂ��ǂꂮ�炢�̔䗦�Ńu�����h���邩��ݒ肷��
		SpriteClippingDrawerMaker& blendRate(const Color& value);

		// �X�v���C�g�̒��S�ʒu��ݒ肷��
		SpriteClippingDrawerMaker& spriteCenterRate(const Vector2& value);

		// �e�N�X�`��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& textureId(IdType value)
		{
			return textureIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& textureId(IdType value) { static_assert(false, "TextureId Fraud Type"); }

		// �u�����h�X�e�[�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& blendStateId(IdType value)
		{
			return blendStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& blendStateId(IdType value) { static_assert(false, "BlendStateId Fraud Type"); }

		// �[�x�X�e���V���X�e�[�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& depthStencilStateId(IdType value)
		{
			return depthStencilStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& depthStencilStateId(IdType value) { static_assert(false, "DepthStencilStateId Fraud Type"); }

		// ���X�^���C�U�X�e�[�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& rasterizerStateId(IdType id)
		{
			return rasterizerStateIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& rasterizerStateId(IdType id) { static_assert(false, "RasterizerStateId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		SpriteClippingDrawerMaker& textureIdImpl(int value);
		SpriteClippingDrawerMaker& blendStateIdImpl(int value);
		SpriteClippingDrawerMaker& depthStencilStateIdImpl(int value);
		SpriteClippingDrawerMaker& rasterizerStateIdImpl(int value);

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		float m_drawPriority{ 0.0f };
		int m_textureId{ 0 };
		int m_blendStateId{ static_cast<int>(SystemBlendStateId::Alpha) };
		int m_depthStencilStateId{ static_cast<int>(SystemDepthStencilStateId::NotUseDepth) };
		int m_rasterizerStateId{ static_cast<int>(SystemRasterizerStateId::Basic) };
		Vector2 m_textureClippingLeftTopPos{ 0.0f, 0.0f };
		Vector2 m_textureClippingSize{ 1.0f, 1.0f };
		Vector2 m_textureUvMulRate{ 1.0f, 1.0f };
		Color m_blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };
		Vector2 m_spriteCenterRate{ 0.5f, 0.5f };
	};
}
#endif // !SPRITE_CLIPPING_DRAWER_MAKER_H_