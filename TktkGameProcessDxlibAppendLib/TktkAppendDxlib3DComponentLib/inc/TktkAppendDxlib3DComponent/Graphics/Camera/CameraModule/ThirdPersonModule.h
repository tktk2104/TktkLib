#ifndef THIRD_PERSON_MODULE_H_
#define THIRD_PERSON_MODULE_H_

#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>

namespace tktk
{
	// ３人称的にTransform3Dを移動させるコンポーネント
	// 【前提コンポーネント：Transform3D】
	class ThirdPersonModule
		: public ComponentBase
	{
	public:

		ThirdPersonModule(
			GameObjectPtr target,						// カメラが追うGameObject
			const Vector3&  targetRelativeLookAtPos,	// カメラが注視する第一引数のGameObjectからの相対座標
			const Vector3&  relativePos					// 第一引数のGameObjectからどれだけ離れた位置にカメラを置くか
		);

	public:

		// <PolymorphismFunc>
		void start();
		void afterCollide();

	public:

		// カメラが追うGameObjectを再設定
		void setTarget(GameObjectPtr target);

		// カメラが注視する第一引数のGameObjectからの相対座標を再設定
		void setTargetRelativeLookAtPos(const Vector3&  targetRelativeLookAtPos);

		// 第一引数のGameObjectからどれだけ離れた位置にカメラを置くかを再設定
		void setRelativePos(const Vector3&  relativePos);

	private:

		// 自身の３次元座標コンポーネント
		CfpPtr<Transform3D> m_selfTransform;

		// カメラが追うGameObject
		GameObjectPtr m_target;

		// カメラが注視する第一引数のGameObjectからの相対座標
		Vector3 m_targetRelativeLookAtPos;

		// 第一引数のGameObjectからどれだけ離れた位置にカメラを置くか
		Vector3 m_relativePos;
	};
}
#endif // !THIRD_PERSON_MODULE_H_