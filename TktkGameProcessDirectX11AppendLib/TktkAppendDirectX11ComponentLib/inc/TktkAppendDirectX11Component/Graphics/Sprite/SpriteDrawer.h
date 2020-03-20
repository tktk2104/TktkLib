#ifndef SPRITE_DRAWER_H_
#define SPRITE_DRAWER_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>

namespace tktk
{
	// スプライト描画コンポーネント
	// 【必須コンポーネント：Transform2D】
	class SpriteDrawer
		: public ComponentBase
	{
	public:

		SpriteDrawer(
			float drawPriority,
			int textureId,
			int blendStateId,
			int depthStencilStateId,
			int rasterizerStateId,
			const Vector2& textureUvOffset,
			const Vector2& textureUvMulRate,
			const Color& blendRate,
			const Vector2& spriteCenterRate
		);

	public:

		void start();
		void draw() const;

	public:

		// テクスチャIDを取得する
		int getTextureId() const;

		// テクスチャIDを再設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setTextureId(IdType id)
		{
			setTextureIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setTextureId(IdType id) { static_assert(false, "TextureId Fraud Type"); }

		// ブレンドステートIDを再設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setBlendStateId(IdType id)
		{
			setBlendStateIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setBlendStateId(IdType id) { static_assert(false, "BlendStateId Fraud Type"); }

		// 深度ステンシルステートIDを再設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setDepthStencilStateId(IdType id)
		{
			setDepthStencilStateIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setDepthStencilStateId(IdType id) { static_assert(false, "DepthStencilStateId Fraud Type"); }

		// ラスタライザステートIDを再設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setRasterizerStateId(IdType id)
		{
			setRasterizerStateIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setRasterizerStateId(IdType id) { static_assert(false, "RasterizerStateId Fraud Type"); }

		// テクスチャ座標に足す値を再設定する
		void setTextureUvOffset(const Vector2& offset);

		// テクスチャ座標にかける値を再設定する
		void setTextureUvMulRate(const Vector2& offset);

		// ブレンドレートを再設定する
		void setBlendRate(const Color& blendRate);

		// スプライトの中心位置を再設定する
		void setSpriteCenterRate(const Vector2& centerRate);

	private:

		// 各種id指定系の関数の実装
		void setTextureIdImpl(int id);
		void setBlendStateIdImpl(int id);
		void setDepthStencilStateIdImpl(int id);
		void setRasterizerStateIdImpl(int id);

	private:

		int m_textureId{ -1 };
		int m_blendStateId{ -1 };
		int m_depthStencilStateId{ -1 };
		int m_rasterizerStateId{ -1 };
		Vector2 m_textureUvOffset{ 0.0f, 0.0f };
		Vector2 m_textureUvMulRate{ 1.0f, 1.0f };
		Color m_blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };
		Vector2 m_spriteCenterRate{ 0.5f, 0.5f };
		
		CfpPtr<Transform2D> m_transform{  };
	};
}
#endif // !SPRITE_DRAWER_H_