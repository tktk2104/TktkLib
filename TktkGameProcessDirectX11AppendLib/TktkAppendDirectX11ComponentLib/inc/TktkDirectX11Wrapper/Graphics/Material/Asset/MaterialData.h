#ifndef MATERIAL_DATA_H_
#define MATERIAL_DATA_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "MaterialParameters.h"

namespace tktk
{
	// マテリアル情報を管理するクラス
	class MaterialData
	{
	public:

		MaterialData(
			int useVertexShaderId,
			int usePixelShaderId,
			const std::vector<int>& useTextureIdArray,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Color& emissionColor,
			float shininess
		);
		~MaterialData() = default;

		MaterialData(const MaterialData& other) = delete;
		MaterialData& operator = (const MaterialData& other) = delete;

	public:

		// 使用する頂点シェーダーのIdを取得する
		int getUseVertexShaderId() const;

		// 使用するピクセルシェーダーのIdを取得する
		int getUsePixelShaderId() const;

		// 使用する頂点シェーダーのIdを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setUseVertexShaderId(IdType id)
		{
			m_useVertexShaderId = static_cast<int>(id);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setUseVertexShaderId(IdType id) { static_assert(false, "VertexShaderId Fraud Type"); }

		// 使用するピクセルシェーダーのIdを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setUsePixelShaderId(IdType id)
		{
			m_usePixelShaderId = static_cast<int>(id);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setUsePixelShaderId(IdType id) { static_assert(false, "PixelShaderId Fraud Type"); }

		// マテリアルパラメータを取得する
		MaterialParameters& getParametersRef();

	private:

		// 使用する頂点シェーダーのId
		int m_useVertexShaderId;
		// 使用するピクセルシェーダーのId
		int m_usePixelShaderId;
		// マテリアルのパラメーター
		MaterialParameters m_materialParameters;
	};
}
#endif // !MATERIAL_DATA_H_