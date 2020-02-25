#ifndef INERTIAL_MOVEMENT_2D_MAKER_H_
#define INERTIAL_MOVEMENT_2D_MAKER_H_

#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "InertialMovement2D.h"

namespace tktk
{
	// InertialMovement2Dのインスタンスを作成するクラス
	class InertialMovement2DMaker
	{
	public:

		// インスタンス作成開始
		static InertialMovement2DMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<InertialMovement2D> create();

		// 速度を１秒間でどれだけ減速させるかを設定
		InertialMovement2DMaker& decelerationPerSec(float value);

		// 初期速度を設定
		InertialMovement2DMaker& initVelocity(const Vector2& value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static InertialMovement2DMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		float m_decelerationPerSec{ 64.0f };
		Vector2 m_initVelocity{ Vector2::zero };
	};
}
#endif // !INERTIAL_MOVEMENT_2D_MAKER_H_