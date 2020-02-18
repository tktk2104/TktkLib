#include "TktkDxlib3DWrapper/Assets/MeshAssets/MeshAssets.h"

#include <algorithm>
#include <DxLib.h>

namespace tktk
{
	void MeshHandles::unLoadMesh() const
	{
		DxLib::MV1DeleteModel(meshHandle);

		std::for_each(
			std::begin(animHandles),
			std::end(animHandles),
			[](const auto& node) { DxLib::MV1DeleteModel(node); }
		);
	}
}