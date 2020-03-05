#ifndef VERTEX_SHADER_ASSETS_H_
#define VERTEX_SHADER_ASSETS_H_

#include <unordered_map>
#include "VertexShaderData.h"

namespace tktk
{
	// 「VertexShaderData」を管理するクラス
	class VertexShaderAssets
	{
	public:

		VertexShaderAssets() = default;
		~VertexShaderAssets();

		VertexShaderAssets(const VertexShaderAssets& other) = delete;
		VertexShaderAssets& operator = (const VertexShaderAssets& other) = delete;

	public:

		// 新たな頂点シェーダーをロードする
		void load(
			int id,
			const std::vector<int>& useConstantBufferIdArray,
			const std::string& fileName,
			const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout
		);

		// 指定した頂点シェーダーを削除する
		void erase(int id);

		// 全ての頂点シェーダーを削除する
		void clear();

		// 指定した頂点シェーダーを管理するクラスの参照を取得する
		const VertexShaderData& getData(int id) const;

	private:

		// 頂点シェーダーを管理するクラスの連想配列
		std::unordered_map<int, VertexShaderData> m_assets;
	};
}
#endif // !VERTEX_SHADER_ASSETS_H_