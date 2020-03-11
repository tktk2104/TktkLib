#ifndef MESH_ANIMATOR_MAKER_H_
#define MESH_ANIMATOR_MAKER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "MeshAnimator.h"

namespace tktk
{
	class MeshAnimatorMaker
	{
	public:

		// インスタンス作成開始
		static MeshAnimatorMaker& makeStart(GameObjectPtr user);

	private:

		// 自身のポインタ
		static MeshAnimatorMaker m_self;

	private:

		// プライベートコンストラクタ達
		MeshAnimatorMaker() = default;
		MeshAnimatorMaker(const MeshAnimatorMaker& other) = default;
		MeshAnimatorMaker& operator = (const MeshAnimatorMaker& other) = default;

	public:

		// 作成する
		CfpPtr<MeshAnimator> create();

		// アニメーションを適用するメッシュ描画コンポーネントを設定する
		MeshAnimatorMaker& meshDrawer(CfpPtr<MeshDrawer> value);

		// 使用するアニメーションのIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		MeshAnimatorMaker& animationId(IdType value)
		{
			return animationIdImpl(static_cast<int>(value));
		}
		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshAnimatorMaker& animationId(IdType value) { static_assert(false, "AnimationId Fraud Type"); }

		// １秒間に何フレームアニメーションを再生するかを設定する
		MeshAnimatorMaker& animFrameIntervalPerSec(float value);

		// アニメーションの再生速度割合を設定する
		MeshAnimatorMaker& animSpeedRate(float value);

	private:

		// 各種id指定系の関数の実装
		MeshAnimatorMaker& animationIdImpl(int value);

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		CfpPtr<MeshDrawer> m_meshDrawer{};
		int m_animationId{ 0 };
		float m_animFrameIntervalPerSec{ 60.0f };
		float m_animSpeedRate{ 1.0f };
	};
}

#endif // !MESH_ANIMATOR_MAKER_H_