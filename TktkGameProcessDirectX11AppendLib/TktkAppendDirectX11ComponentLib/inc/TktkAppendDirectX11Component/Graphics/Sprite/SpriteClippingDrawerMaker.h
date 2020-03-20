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

		// インスタンス作成開始
		static SpriteClippingDrawerMaker& makeStart(GameObjectPtr user);

	private:

		// 自身のポインタ
		static SpriteClippingDrawerMaker m_self;

	private:

		// プライベートコンストラクタ達
		SpriteClippingDrawerMaker() = default;
		SpriteClippingDrawerMaker(const SpriteClippingDrawerMaker& other) = default;
		SpriteClippingDrawerMaker& operator = (const SpriteClippingDrawerMaker& other) = default;
	
	public:

		// 作成する
		CfpPtr<SpriteClippingDrawer> create();
	
		// 描画優先度を設定する
		SpriteClippingDrawerMaker& drawPriority(float value);

		// テクスチャリソースの描画する範囲の左上座標を設定する（テクスチャ座標）
		SpriteClippingDrawerMaker& textureClippingLeftTopPos(const Vector2& value);

		// テクスチャリソースの描画する範囲を設定する（テクスチャ座標）
		SpriteClippingDrawerMaker& textureClippingSize(const Vector2& value);

		// テクスチャ座標にかける値を設定する
		SpriteClippingDrawerMaker& textureUvMulRate(const Vector2& value);

		// 描画先画像に描画結果をどれぐらいの比率でブレンドするかを設定する
		SpriteClippingDrawerMaker& blendRate(const Color& value);

		// スプライトの中心位置を設定する
		SpriteClippingDrawerMaker& spriteCenterRate(const Vector2& value);

		// テクスチャIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& textureId(IdType value)
		{
			return textureIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& textureId(IdType value) { static_assert(false, "TextureId Fraud Type"); }

		// ブレンドステートIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& blendStateId(IdType value)
		{
			return blendStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& blendStateId(IdType value) { static_assert(false, "BlendStateId Fraud Type"); }

		// 深度ステンシルステートIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& depthStencilStateId(IdType value)
		{
			return depthStencilStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& depthStencilStateId(IdType value) { static_assert(false, "DepthStencilStateId Fraud Type"); }

		// ラスタライザステートIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& rasterizerStateId(IdType id)
		{
			return rasterizerStateIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& rasterizerStateId(IdType id) { static_assert(false, "RasterizerStateId Fraud Type"); }

	private:

		// 各種id指定系の関数の実装
		SpriteClippingDrawerMaker& textureIdImpl(int value);
		SpriteClippingDrawerMaker& blendStateIdImpl(int value);
		SpriteClippingDrawerMaker& depthStencilStateIdImpl(int value);
		SpriteClippingDrawerMaker& rasterizerStateIdImpl(int value);

	private:

		// 作成用変数達
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