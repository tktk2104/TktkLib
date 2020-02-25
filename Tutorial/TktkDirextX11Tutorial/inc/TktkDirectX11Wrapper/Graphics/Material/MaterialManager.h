#ifndef MATERIAL_MANAGER_H_
#define MATERIAL_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/MaterialAssets.h"

namespace tktk
{
	// 「MaterialAssets」に簡単にアクセスするためのクラス
	class MaterialManager
	{
	public:

		// 「MaterialAssets」を生成
		static void setUp();

	public:

		// 新たなマテリアルを生成する
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
		static void duplicate(int id, int originalId);

		// 指定したマテリアルを削除する
		static void erase(int id);

		// 全てのマテリアルを削除する
		static void clear();

		// マテリアルを管理するクラスのポインタを取得する
		static MaterialData* getDataPtr(int id);

	private:

		static CfpPtr<MaterialAssets> m_assetsPtr;
	};
}
#endif // !MATERIAL_MANAGER_H_