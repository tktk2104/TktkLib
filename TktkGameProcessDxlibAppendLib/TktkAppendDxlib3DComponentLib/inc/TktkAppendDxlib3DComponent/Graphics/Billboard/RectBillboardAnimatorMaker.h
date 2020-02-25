#ifndef RECT_BILLBOARD_ANIMATOR_MAKER_H_
#define RECT_BILLBOARD_ANIMATOR_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include <vector>
#include "RectBillboardAnimator.h"

namespace tktk
{
	class RectBillboardAnimatorMaker
	{
	public:

		// インスタンス作成開始
		static RectBillboardAnimatorMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<RectBillboardAnimator> create();

		// 使用するテクスチャのIdを設定する
		RectBillboardAnimatorMaker& textureId(int value);

		// アニメーションに使用する分割画像番号を設定する
		template <int... Args>
		RectBillboardAnimatorMaker& splitTextureIndexList()
		{
			m_splitTextureIndexList = std::vector<int>({ Args... });
			return *this;
		};

		// アニメーションで使用する静止画１枚当たりの時間を設定する（秒）
		RectBillboardAnimatorMaker& animationIntervalSec(float value);

		// アニメーションをループさせるかを設定する
		RectBillboardAnimatorMaker& loop(bool value);

		// アニメーションの再生速度倍率を設定する
		RectBillboardAnimatorMaker& animSpeedRate(float value);

	private:

		// 自身のポインタ
		static RectBillboardAnimatorMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{};
		int m_textureId{ -1 };
		std::vector<int> m_splitTextureIndexList;
		float m_animationIntervalSec{ 0.1f };
		bool m_loop{ false };
		float m_animSpeedRate{ 1.0f };
	};
}
#endif // !RECT_BILLBOARD_ANIMATOR_MAKER_H_