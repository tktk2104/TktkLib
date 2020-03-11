#ifndef MESH_ANIMATOR_H_
#define MESH_ANIMATOR_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "MeshDrawer.h"

namespace tktk
{
	class MeshAnimator
		: public ComponentBase
	{
	public:

		MeshAnimator(
			CfpPtr<MeshDrawer> meshDrawer,
			int animationId,
			float animFrameIntervalPerSec,
			float animSpeedRate
		);
		~MeshAnimator();

	public:

		void start();
		void update();

	public:

		int getAnimationId() const;

		// 使用するアニメーションのIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setAnimationId(IdType id)
		{
			setAnimationIdImpl(static_cast<int>(id));
		}
		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setAnimationId(IdType id) { static_assert(false, "AnimationId Fraud Type"); }

		// アニメーションの再生速度割合を取得する
		float getAnimSpeedRate() const;

		// アニメーションの再生速度割合を設定する
		void setAnimSpeedRate(float rate);

	private:

		// 各種id指定系の関数の実装
		void setAnimationIdImpl(int id);

	private:

		CfpPtr<MeshDrawer> m_meshDrawer;

		int m_animationId{ 0 };

		float m_animSecTimer{ 0.0f };

		float m_animFrameIntervalPerSec{ 60.0f };

		float m_animSpeedRate{ 1.0f };
	};
}
#endif // !MESH_ANIMATOR_H_