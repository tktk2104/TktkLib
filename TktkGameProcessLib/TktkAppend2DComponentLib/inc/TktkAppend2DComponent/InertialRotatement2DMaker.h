#ifndef INERTIAL_ROTATEMENT_2D_MAKER_H_
#define INERTIAL_ROTATEMENT_2D_MAKER_H_

#include "InertialRotatement2D.h"

namespace tktk
{
	// InertialRotatement2Dのインスタンスを作成するクラス
	class InertialRotatement2DMaker
	{
	public:

		// インスタンス作成開始
		static InertialRotatement2DMaker& makeStart();

	public:

		// 作成する
		InertialRotatement2D* create();

		// 速度を１秒間でどれだけ減速させるかを設定
		InertialRotatement2DMaker& decelerationPerSec(float value);

		// 初期速度を設定
		InertialRotatement2DMaker& initVelocity(float value);

	private:

		// 自身のポインタ
		static InertialRotatement2DMaker m_self;

	private:

		float m_decelerationPerSec{ 30.0f };
		float m_initVelocity{ 0.0f };
	};
}
#endif // !INERTIAL_ROTATEMENT_2D_MAKER_H_