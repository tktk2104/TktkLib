#ifndef FIRST_PERSON_MODULE_H_
#define FIRST_PERSON_MODULE_H_

#include <memory>
#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>

namespace tktk
{
	// １人称的にTransform3Dを移動させるコンポーネント
	// 【前提コンポーネント：Transform3D】
	class FirstPersonModule
		: public tktk::ComponentBase
	{
	public:

		FirstPersonModule(
			float rotationDegPerPixelOnMouseMove,	// マウスカーソルが１ピクセル移動した時の回転角度（度数法）
			float moveSpeedPerSec,					// 毎秒どれだけの速度で移動するか
			bool alwaysMoveForward,					// 常に前方に移動するか
			bool enableUpDownKey					// スペース、シフトキーで上下に移動するか
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();

	private:

		// マウス操作による回転
		void rotateWithMouse();

		// 垂直方向への移動
		void moveVertical();

		// wasdキーによる移動
		void inputToMove();

	private:

		// 自身の３次元座標コンポーネント
		std::weak_ptr<tktk::Transform3D> m_selfTransform;

		// 前フレームのマウスの座標
		Vector2 m_preMousePos;

		// マウスカーソルが１ピクセル移動した時の回転角度（度数法）
		float m_rotationDegPerPixelOnMouseMove;

		// 毎秒の移動速度
		float m_moveSpeedPerSec;

		// 常に前方に移動するか
		bool m_alwaysMoveForward{ false };

		// スペース、シフトキーで上下に移動するか
		bool m_enableUpDownKey{ false };
	};
}
#endif // !FIRST_PERSON_MODULE_H_