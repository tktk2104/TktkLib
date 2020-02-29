#ifndef DEPTH_STENCIL_STATE_H_
#define DEPTH_STENCIL_STATE_H_

#include "Asset/DepthStencilStateData.h"

namespace tktk
{
	class DepthStencilState
	{
	public:

		// 新たな深度ステンシルステートを作成する
		// ※この関数で深度ステンシルステートを作る場合、idは1以上でなければならない
		static void create(int id, const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc);

		// 指定した深度ステンシルステートを削除する
		// ※この関数で深度ステンシルステートを削除する場合、idは1以上でなければならない
		static void erase(int id);

		// 指定した深度ステンシルステートを管理するクラスのポインタを取得する
		static DepthStencilStateData* getData(int id);
	};
}
#endif // !DEPTH_STENCIL_STATE_H_