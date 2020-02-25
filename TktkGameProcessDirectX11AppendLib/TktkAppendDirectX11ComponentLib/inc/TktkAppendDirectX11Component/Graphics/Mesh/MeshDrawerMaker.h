#ifndef MESH_DRAWER_MAKER_H_
#define MESH_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "MeshDrawer.h"

namespace tktk
{
	class MeshDrawerMaker
	{
	public:

		// インスタンス作成開始
		static MeshDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<MeshDrawer> create();

		MeshDrawerMaker& drawPriority(float value);

		MeshDrawerMaker& cameraId(int value);

		MeshDrawerMaker& meshId(int value);

		MeshDrawerMaker& skeltonId(int value);

		MeshDrawerMaker& materialIdArray(const std::vector<int>& value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static MeshDrawerMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		float m_drawPriority{ 0.0f };
		int m_cameraId{ 0 };
		int m_meshId{ 0 };
		int m_skeltonId{ 0 };
		std::vector<int> m_materialIdArray{ };
	};
}

#endif // !MESH_DRAWER_MAKER_H_