#ifndef FIRST_PERSON_MODULE_H_
#define FIRST_PERSON_MODULE_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>

namespace tktk
{
	class FirstPersonModule
		: public ComponentBase
	{
	public:

		FirstPersonModule(
			float rotateDegSpeedPerSec,		// 毎秒の回転角度（度数法）
			float moveSpeedPerSec,			// 毎秒の移動速度
			bool alwaysMoveForward,			// 常に前方に移動するか
			bool enableUpDownKey			// スペース、シフトキーで上下に移動するか
		);
		~FirstPersonModule();

	public:

		void start();
		void update();

	public:

		float* getRotateDegSpeedPerSecPtr();

		float* getMoveSpeedPerSecPtr();

		bool* getAlwaysMoveForwardPtr();

		bool* getEnableUpDownKeyPtr();

	private:

		void rotate();

		void moveHorizontal();

		void moveVertical();

	private:

		// 自身の３次元座標コンポーネント
		CfpPtr<Transform3D> m_transform;

		// 毎秒の回転角度（度数法）
		float m_rotateDegSpeedPerSec;

		// 毎秒の移動速度
		float m_moveSpeedPerSec;

		// 常に前方に移動するか
		bool m_alwaysMoveForward{ false };

		// スペース、シフトキーで上下に移動するか
		bool m_enableUpDownKey{ false };
	};
}
#endif // !FIRST_PERSON_MODULE_H_