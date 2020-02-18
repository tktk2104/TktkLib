#ifndef FIRST_PERSON_MODULE_MAKER_H_
#define FIRST_PERSON_MODULE_MAKER_H_

#include <memory>
#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "FirstPersonModule.h"

namespace tktk
{
	// FirstPersonModuleのインスタンスを作成する構造体
	struct FirstPersonModuleMaker
	{
	public:

		// インスタンス作成開始
		static FirstPersonModuleMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<FirstPersonModule> create();

		// マウスカーソルが１ピクセル移動した時の回転角度を設定する（度数法）
		FirstPersonModuleMaker& rotationDegPerPixelOnMouseMove(float value);

		// 毎秒どれだけの速度で移動するかを設定する
		FirstPersonModuleMaker& moveSpeedPerSec(float value);

		// 常に前方に移動するかを設定する
		FirstPersonModuleMaker& alwaysMoveForward(bool value);

		// スペース、シフトキーで上下に移動するかを設定する
		FirstPersonModuleMaker& enableUpDownKey(bool value);

	private:

		// 自身のポインタ
		static FirstPersonModuleMaker m_self;

	private:

		float m_rotationDegPerPixelOnMouseMove;
		float m_moveSpeedPerSec;
		bool m_alwaysMoveForward{ false };
		bool m_enableUpDownKey{ false };
	};
}
#endif // !FIRST_PERSON_MODULE_MAKER_H_