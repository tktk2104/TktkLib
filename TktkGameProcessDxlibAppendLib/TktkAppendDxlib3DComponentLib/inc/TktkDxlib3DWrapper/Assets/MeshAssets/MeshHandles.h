#ifndef MESH_HANDLES_H_
#define MESH_HANDLES_H_

#include <vector>

namespace tktk
{
	// メッシュと対応するアニメーションを同時に格納する構造体
	struct MeshHandles
	{
	public:

		// メッシュと対応するアニメーションをアンロードする
		void unLoadMesh() const;

	public:

		// メッシュ本体のハンドル
		int meshHandle{ -1 };

		// メッシュに対応するアニメーションのハンドル
		std::vector<int> animHandles;
	};
}
#endif // !MESH_HANDLES_H_