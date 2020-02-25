#ifndef VIEW_PORT_MANAGER_H_
#define VIEW_PORT_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/ViewPortAssets.h"
#include "Asset/SystemViewPortId.h"

namespace tktk
{
	// 「ViewPortAssets」に簡単にアクセスするためのクラス
	class ViewPortManager
	{
	public:

		// 「ViewPortAssets」を生成
		static void setUp();

	public:

		// 新たなビューポートを生成する
		static void create(int id, const Vector2& position, const Vector2& size);

		// 指定したビューポートを削除する
		static void erase(int id);

		// 全てのビューポートを削除する
		static void clear();

		// 指定したビューポートを管理するクラスの参照を取得する
		static const ViewPortData& getData(int id);

	private:

		static CfpPtr<ViewPortAssets> m_assetsPtr;
	};
}
#endif // !VIEW_PORT_MANAGER_H_