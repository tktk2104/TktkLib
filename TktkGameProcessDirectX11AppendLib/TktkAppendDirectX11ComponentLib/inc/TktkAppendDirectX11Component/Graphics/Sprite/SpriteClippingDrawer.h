#ifndef SPRITE_CLIPPING_DRAWER_H_
#define SPRITE_CLIPPING_DRAWER_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>

namespace tktk
{
	// �X�v���C�g�N���b�s���O�`��R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform2D�z
	class SpriteClippingDrawer
		: public ComponentBase
	{
	public:

		SpriteClippingDrawer(
			float drawPriority,
			int textureId,
			int blendStateId,
			int depthStencilStateId,
			const Vector2& textureClippingLeftTopPos,
			const Vector2& textureClippingSize,
			const Vector2& textureUvMulRate,
			const Color& blendRate,
			const Vector2& spriteCenterRate
		);

	public:

		void start();
		void draw() const;

	public:

		// �e�N�X�`��ID���Đݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setTextureId(IdType id)
		{
			setTextureIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setTextureId(IdType id) { static_assert(false, "TextureId Fraud Type"); }

		// �u�����h�X�e�[�gID���Đݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setBlendStateId(IdType id)
		{
			setBlendStateIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setBlendStateId(IdType id) { static_assert(false, "BlendStateId Fraud Type"); }

		// �[�x�X�e���V���X�e�[�gID���Đݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setDepthStencilStateId(IdType id)
		{
			setDepthStencilStateIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setDepthStencilStateId(IdType id) { static_assert(false, "DepthStencilStateId Fraud Type"); }

		// �e�N�X�`�����\�[�X�̕`�悷��͈͂̍�����W���Đݒ肷��i�e�N�X�`�����W�j
		void setTextureClippingLeftTopPos(const Vector2& leftTopPos);

		// �e�N�X�`�����\�[�X�̕`�悷��͈͂��Đݒ肷��i�e�N�X�`�����W�j
		void setTextureClippingSize(const Vector2& size);

		// �e�N�X�`�����W�ɂ�����l���Đݒ肷��
		void setTextureUvMulRate(const Vector2& offset);

		// �u�����h���[�g���Đݒ肷��
		void setBlendRate(const Color& blendRate);

		// �X�v���C�g�̒��S�ʒu���Đݒ肷��
		void setSpriteCenterRate(const Vector2& centerRate);

	private:

		// �e��id�w��n�̊֐��̎���
		void setTextureIdImpl(int id);
		void setBlendStateIdImpl(int id);
		void setDepthStencilStateIdImpl(int id);

	private:

		int m_textureId{ -1 };
		int m_blendStateId{ -1 };
		int m_depthStencilStateId{ -1 };
		Vector2 m_textureClippingLeftTopPos{ 0.0f, 0.0f };
		Vector2 m_textureClippingSize{ 1.0f, 1.0f };
		Vector2 m_textureUvMulRate{ 1.0f, 1.0f };
		Color m_blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };
		Vector2 m_spriteCenterRate{ 0.5f, 0.5f };

		CfpPtr<Transform2D> m_transform{  };
	};
}
#endif // !SPRITE_CLIPPING_DRAWER_H_