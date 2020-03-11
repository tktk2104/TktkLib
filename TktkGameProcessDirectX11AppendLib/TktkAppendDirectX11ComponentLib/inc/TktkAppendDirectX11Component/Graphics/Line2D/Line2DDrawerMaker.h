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

		// インスタンス作成開始
		static Line2DDrawerMaker& makeStart(GameObjectPtr user);

	private:

		// 自身のポインタ
		static Line2DDrawerMaker m_self;

	private:

		// プライベートコンストラクタ達
		Line2DDrawerMaker() = default;
		Line2DDrawerMaker(const Line2DDrawerMaker& other) = default;
		Line2DDrawerMaker& operator = (const Line2DDrawerMaker& other) = default;

	public:

		// 作成する
		CfpPtr<Line2DDrawer> create();

		// 描画優先度を設定する
		Line2DDrawerMaker& drawPriority(float value);

		// 線分を構成する頂点座標の配列を設定する
		Line2DDrawerMaker& lineVertexArray(const std::vector<Vector2>& value);

		// 線の色を設定する
		Line2DDrawerMaker& lineColor(const Color& value);

		// 描画先画像に描画結果をどれぐらいの比率でブレンドするかを設定する
		Line2DDrawerMaker& blendRate(const Color& value);

		// ブレンドステートIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		Line2DDrawerMaker& blendStateId(IdType value)
		{
			return blendStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		Line2DDrawerMaker& blendStateId(IdType value) { static_assert(false, "BlendStateId Fraud Type"); }

		// 深度ステンシルステートIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		Line2DDrawerMaker& depthStencilStateId(IdType value)
		{
			return depthStencilStateIdImpl(static_cast<int>(value));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		Line2DDrawerMaker& depthStencilStateId(IdType value) { static_assert(false, "DepthStencilStateId Fraud Type"); }
	
	private:

		// 各種id指定系の関数の実装
		Line2DDrawerMaker& blendStateIdImpl(int value);
		Line2DDrawerMaker& depthStencilStateIdImpl(int value);
	
	private:

		// 作成用変数達
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