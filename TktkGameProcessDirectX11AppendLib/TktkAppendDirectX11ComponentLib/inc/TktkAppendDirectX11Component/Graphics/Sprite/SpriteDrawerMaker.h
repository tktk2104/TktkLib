#ifndef SPRITE_DRAWER_MAKER_H_
#define SPRITE_DRAWER_MAKER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "TktkDirectX11Wrapper/Graphics/BlendState/Asset/SystemBlendStateId.h"
#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/Asset/SystemDepthStencilStateId.h"
#include "TktkDirectX11Wrapper/Graphics/RasterizerState/Asset/SystemRasterizerStateId.h"
#include "SpriteDrawer.h"

namespace tktk
{
	class SpriteDrawerMaker
	{
	public:

		// インスタンス作成開始
		static SpriteDrawerMaker& makeStart(GameObjectPtr user);

	private:

		// 自身のポインタ
		static SpriteDrawerMaker m_self;

	private:

		// プライベートコンストラクタ達
		SpriteDrawerMaker() = default;
		SpriteDrawerMaker(const SpriteDrawerMaker& other) = default;
		SpriteDrawerMaker& operator = (const SpriteDrawerMaker& other) = default;

	public:

		// 作成する
		CfpPtr<SpriteDrawer> create();

		// 描画優先度を設定する
		SpriteDrawerMaker& drawPriority(float value);

		// テクスチャ座標に足す値を設定する
		SpriteDrawerMaker& textureUvOffset(const Vector2& value);

		// テクスチャ座標にかける値を設定する
		SpriteDrawerMaker& textureUvMulRate(const Vector2& value);

		// 描画先画像に描画結果をどれぐらいの比率でブレンドするかを設定する
		SpriteDrawerMaker& blendRate(const Color& value);

		// スプライトの中心位置を設定する
		SpriteDrawerMaker& spriteCenterRate(const Vector2& value);

		// テクスチャIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SpriteDrawerMaker& textureId(IdType value)
		{
			return textureIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteDrawerMaker& textureId(IdType value) { static_assert(false, "TextureId Fraud Type"); }

		// ブレンドステートIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SpriteDrawerMaker& blendStateId(IdType value)
		{
			return blendStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteDrawerMaker& blendStateId(IdType value) { static_assert(false, "BlendStateId Fraud Type"); }

		// 深度ステンシルステートIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SpriteDrawerMaker& depthStencilStateId(IdType value)
		{
			return depthStencilStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteDrawerMaker& depthStencilStateId(IdType value) { static_assert(false, "DepthStencilStateId Fraud Type"); }

		// ラスタライザステートIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SpriteDrawerMaker& rasterizerStateId(IdType id)
		{
			return rasterizerStateIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteDrawerMaker& rasterizerStateId(IdType id) { static_assert(false, "RasterizerStateId Fraud Type"); }

	private:

		// 各種id指定系の関数の実装
		SpriteDrawerMaker& textureIdImpl(int value);
		SpriteDrawerMaker& blendStateIdImpl(int value);
		SpriteDrawerMaker& depthStencilStateIdImpl(int value);
		SpriteDrawerMaker& rasterizerStateIdImpl(int value);

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		float m_drawPriority{ 0.0f };
		int m_textureId{ 0 };
		int m_blendStateId{ static_cast<int>(SystemBlendStateId::Alpha) };
		int m_depthStencilStateId{ static_cast<int>(SystemDepthStencilStateId::NotUseDepth) };
		int m_rasterizerStateId{ static_cast<int>(SystemRasterizerStateId::Basic) };
		Vector2 m_textureUvOffset{ 0.0f, 0.0f };
		Vector2 m_textureUvMulRate{ 1.0f, 1.0f };
		Color m_blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };
		Vector2 m_spriteCenterRate{ 0.5f, 0.5f };
	};
}
#endif // !SPRITE_DRAWER_MAKER_H_