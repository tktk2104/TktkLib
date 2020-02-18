#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Asset/MaterialData.h"

namespace tktk
{
	// 「MaterialManager」の実装の一部を隠すためのクラス
	class Material
	{
	public:

		// 新たなマテリアルを生成する
		// ※この関数でマテリアルを作る場合、idは1以上でなければならない
		static void create(
			int id,
			int indexBufferStartPos,
			int indexBufferUseCount,
			int useVertexShaderId,
			int usePixelShaderId,
			const std::unordered_map<unsigned int, int>& useTextureIdMap,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Color& emissionColor,
			float shiniess
		);

		// マテリアルを複製する
		// ※この関数でマテリアルを作る場合、idは1以上でなければならない（複製元のidの値の制限はない）
		static void duplicate(int id, int originalId);

		// 指定したマテリアルを削除する
		// ※この関数でマテリアルを削除する場合、idは1以上でなければならない
		static void erase(int id);

		// マテリアルを管理するクラスのポインタを取得する
		static MaterialData* getDataPtr(int id);
	};
}
#endif // !MATERIAL_H_