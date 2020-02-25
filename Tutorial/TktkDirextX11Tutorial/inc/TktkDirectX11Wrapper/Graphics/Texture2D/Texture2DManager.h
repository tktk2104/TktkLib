#ifndef TEXTURE_2D_MANAGER_H_
#define TEXTURE_2D_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/Texture2DAssets.h"

namespace tktk
{
	// 「Texture2DAssets」に簡単にアクセスするためのクラス
	class Texture2DManager
	{
	public:

		// 「Texture2DAssets」を生成
		static void setUp();

	public:

		// 新たな2Dテクスチャをロードする
		static void load(int id, const std::string& fileName);

		// 指定した2Dテクスチャを削除する
		static void erase(int id);

		// 全ての2Dテクスチャを削除する
		static void clear();

		// 指定した2Dテクスチャを管理するクラスの参照を取得する
		static const Texture2DData& getData(int id);

	private:

		static CfpPtr<Texture2DAssets> m_assetsPtr;
	};
}
#endif // !TEXTURE_2D_MANAGER_H_