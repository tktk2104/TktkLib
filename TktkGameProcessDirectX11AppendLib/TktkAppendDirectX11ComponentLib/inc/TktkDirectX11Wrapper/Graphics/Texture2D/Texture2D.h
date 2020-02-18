#ifndef TEXTURE_2D_H_
#define TEXTURE_2D_H_

#include <string>
#include "Asset/Texture2DData.h"

namespace tktk
{
	// 「Texture2DManager」の実装の一部を隠すためのクラス
	class Texture2D
	{
	public:

		// 新たな2Dテクスチャをロードする
		// ※この関数で2Dテクスチャをロードする場合、idは1以上でなければならない
		static void load(int id, const std::string& fileName);

		// 指定した2Dテクスチャを削除する
		// ※この関数で2Dテクスチャを削除する場合、idは1以上でなければならない
		static void erase(int id);

		// 指定した2Dテクスチャを管理するクラスの参照を取得する
		static const Texture2DData& getData(int id);
	};
}
#endif // !TEXTURE_2D_H_