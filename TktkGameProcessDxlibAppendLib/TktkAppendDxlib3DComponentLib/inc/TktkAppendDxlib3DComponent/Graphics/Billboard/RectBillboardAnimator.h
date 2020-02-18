#ifndef RECT_BILLBOARD_ANIMATOR_H_
#define RECT_BILLBOARD_ANIMATOR_H_

#include <memory>
#include <vector>
#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "RectBillboardDrawer.h"

namespace tktk
{
	class RectBillboardAnimator
		: public ComponentBase
	{
	public:

		RectBillboardAnimator(
			int textureId,									// アニメーションで使用する画像の種類
			const std::vector<int>& splitTextureIndexList,	// アニメーションで使用する画像分割番号の配列
			float animationIntervalSec,						// アニメーションで画像が切り替わる間隔（秒）
			bool isLoop,									// アニメーションをループさせるか？
			float animSpeedRate								// アニメーションの再生倍率
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();

	public:

		// アニメーションが終了したかを取得
		bool isEndAnimation() const;

		// アニメーションで使用する画像の種類を再設定
		void setTextureId(int textureId);

		// アニメーションで使用する画像の種類を取得
		int getTextureId() const;

		// アニメーションに使用する分割画像番号のリストを再設定
		void setSplitTextureIndexList(const std::vector<int>& splitTextureIndexList);

		// アニメーションに使用する分割画像番号のリストを再設定
		template <int... Args>
		void setSplitTextureIndexList()
		{
			setSplitTextureIndexList(std::vector<int>({ Args... }));
		};

		// アニメーションに使用する分割画像番号のリストを設定
		const std::vector<int>& getSplitTextureIndexList() const;

		// アニメーションの再生速度を再設定
		void setAnimSpeedRate(float animSpeedRate);

		// アニメーションの再生速度を取得
		float getAnimSpeedRate() const;

		// アニメーションをループさせるかを再設定
		void setIsLoop(bool isLoop);

		// アニメーションのループフラグを取得
		bool getIsLoop() const;

	private:

		// 自身の長方形ビルボード描画コンポーネント
		std::weak_ptr<RectBillboardDrawer> m_rectBillboardDrawer;

		// 使用するテクスチャのId
		int m_textureId{ -1 };

		// アニメーションに使用する分割画像番号のリスト
		std::vector<int> m_splitTextureIndexList;

		// アニメーションの再生速度倍率
		float m_animSpeedRate{ 1.0f };

		// アニメーションの経過時間（秒）
		float m_animationTimer{ 0.0f };

		// アニメーションの合計時間（秒）
		float m_animationTotalTime{ 0.0f };

		// アニメーションで使用する静止画１枚当たりの時間（秒）
		float m_animationIntervalSec;

		// アニメーションのループフラグ
		bool m_isLoop;
	};
}
#endif // !RECT_BILLBOARD_ANIMATOR_H_