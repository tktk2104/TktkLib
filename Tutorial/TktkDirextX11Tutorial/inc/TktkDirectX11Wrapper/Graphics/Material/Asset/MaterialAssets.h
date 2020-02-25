#ifndef MATERIAL_ASSETS_H_
#define MATERIAL_ASSETS_H_

#include <unordered_map>
#include "MaterialData.h"

namespace tktk
{
	// 「MaterialData」を管理するクラス
	class MaterialAssets
	{
	public:

		MaterialAssets() = default;
		~MaterialAssets();

		MaterialAssets(const MaterialAssets& other) = delete;
		MaterialAssets& operator = (const MaterialAssets& other) = delete;

	public:

		// 新たなマテリアルを生成する
		void create(
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
		void duplicate(int id, int originalId);

		// 指定したマテリアルを削除する
		void erase(int id);

		// 全てのマテリアルを削除する
		void clear();

		// マテリアルを管理するクラスのポインタを取得する
		MaterialData* getDataPtr(int id);

	private:

		std::unordered_map<int, MaterialData> m_assets;
	};
}
#endif // !MATERIAL_ASSETS_H_
