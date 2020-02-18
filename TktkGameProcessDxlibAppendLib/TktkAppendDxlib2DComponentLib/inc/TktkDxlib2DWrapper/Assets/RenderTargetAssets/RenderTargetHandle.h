#ifndef RENDER_TARGET_HANDLE_H_
#define RENDER_TARGET_HANDLE_H_

#include <array>
#include "../../DxlibStructWrapper/Vertex2dShaderData.h"

namespace tktk
{
	class RenderTargetHandle
	{
	public:

		// SetDrawScreen で描画対象にできるグラフィックハンドル
		int screenGraphHandle{ -1 };

		// 頂点データの配列
		std::array<Vertex2dShaderData, 4U> vertices;

		// 毎フレーム自動で自身に描画された情報を消すか？
		bool autoRefresh{ true };
	};
}

#endif // !RENDER_TARGET_HANDLE_H_
