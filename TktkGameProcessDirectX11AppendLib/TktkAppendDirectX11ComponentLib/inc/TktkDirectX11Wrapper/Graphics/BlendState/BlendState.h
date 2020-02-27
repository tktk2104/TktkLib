#ifndef BLEND_STATE_H_
#define BLEND_STATE_H_

#include "Asset/BlendStateData.h"

namespace tktk
{
	// 「BlendStateManager」の実装の一部を隠すためのクラス
	class BlendState
	{
	public:

		// 新たなブレンドステートを作成する
		// ※この関数でブレンドステートを作る場合、idは1以上でなければならない
		static void create(int id, const D3D11_BLEND_DESC& blendDesc);

		// 指定したブレンドステートを削除する
		// ※この関数でブレンドステートを削除する場合、idは1以上でなければならない
		static void erase(int id);

		// 指定したブレンドステートを管理するクラスのポインタを取得する
		static BlendStateData* getDataPtr(int id);
	};
}
#endif // !BLEND_STATE_H_