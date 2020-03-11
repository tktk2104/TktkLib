#ifndef LINE_2D_DRAWER_H_
#define LINE_2D_DRAWER_H_

#include <vector>
#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>

namespace tktk
{
	// 2次元線分描画コンポーネント
	// 【必須コンポーネント：Transform2D】
	class Line2DDrawer
		: public ComponentBase
	{
	public:

		Line2DDrawer(
			float drawPriority,
			const std::vector<Vector2>& lineVertexArray,
			const Color& lineColor,
			int blendStateId,
			int depthStencilStateId,
			const Color& blendRate
		);

	public:

		void start();
		void draw() const;

	public:

		// 線分を構成する頂点座標の配列を取得する
		const std::vector<Vector2>& getLineVertexArray() const;

		// 線分を構成する頂点座標の配列を設定する
		void setLineVertexArray(const std::vector<Vector2>& vertexArray);

		// 線の色を取得する
		const Color& getLineColor() const;

		// 線の色を設定する
		void setLineColor(const Color& color);

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

		// ブレンドレートを再設定する
		void setBlendRate(const Color& blendRate);

	private:

		// 各種id指定系の関数の実装
		void setBlendStateIdImpl(int id);
		void setDepthStencilStateIdImpl(int id);

	private:

		std::vector<Vector2> m_lineVertexArray;
		Color m_lineColor{ Color::white };
		int m_blendStateId{ -1 };
		int m_depthStencilStateId{ -1 };
		Color m_blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };
		
		CfpPtr<Transform2D> m_transform{  };
	};
}
#endif // !LINE_2D_DRAWER_H_