#ifndef INERTIAL_MOVEMENT_3D_MAKER_H_
#define INERTIAL_MOVEMENT_3D_MAKER_H_

#include <TktkMath/Vector3.h>
#include "InertialMovement3D.h"

namespace tktk
{
	// InertialMovement3Dのインスタンスを作成するクラス
	class InertialMovement3DMaker
	{
	public:

		// インスタンス作成開始
		static InertialMovement3DMaker& makeStart();

	public:

		// 作成する
		InertialMovement3D* craete();

		// 速度を１秒間でどれだけ減速させるかを設定
		InertialMovement3DMaker& decelerationPerSec(float value);

		// 初期速度を設定
		InertialMovement3DMaker& initVelocity(const Vector3& value);

	private:

		// 自身のポインタ
		static InertialMovement3DMaker m_self;

	private:

		float m_decelerationPerSec{ 64.0f };
		Vector3 m_initVelocity{ Vector3::zero };
	};
}
#endif // !INERTIAL_MOVEMENT_3D_MAKER_H_