#ifndef THIRD_PERSON_MODULE_MAKER_H_
#define THIRD_PERSON_MODULE_MAKER_H_

#include <memory>
#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "ThirdPersonModule.h"

namespace tktk
{
	// ThirdPersonModuleのインスタンスを作成する構造体
	struct ThirdPersonModuleMaker
	{
	public:

		// インスタンス作成開始
		static ThirdPersonModuleMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<ThirdPersonModule> create();

		// カメラが追うGameObjectを設定する
		ThirdPersonModuleMaker& target(GameObjectPtr value);

		// カメラが注視する第一引数のGameObjectからの相対座標を設定する
		ThirdPersonModuleMaker& targetRelativeLookAtPos(const Vector3& value);

		// 第一引数のGameObjectからどれだけ離れた位置にカメラを置くかを設定する
		ThirdPersonModuleMaker& relativePos(const Vector3& value);

	private:

		// 自身のポインタ
		static ThirdPersonModuleMaker m_self;

	private:

		GameObjectPtr m_target;
		Vector3 m_targetRelativeLookAtPos{ Vector3::zero };
		Vector3 m_relativePos{ Vector3(0.0f, 0.0f, -100.0f) };
	};
}
#endif // !THIRD_PERSON_MODULE_MAKER_H_