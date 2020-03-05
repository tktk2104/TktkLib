#ifndef VERTEX_SHADER_DATA_H_
#define VERTEX_SHADER_DATA_H_

#include <string>
#include <vector>
#include <d3d11.h>

namespace tktk
{
	// 頂点シェーダーを管理するクラス
	class VertexShaderData
	{
	public:

		VertexShaderData(
			const std::vector<int>& useConstantBufferIdArray,
			const std::string& fileName,
			const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout
		);
		~VertexShaderData();

		VertexShaderData(const VertexShaderData& other) = delete;
		VertexShaderData& operator = (const VertexShaderData& other) = delete;

	public:

		// 頂点シェーダーに定数バッファを設定してデバイスコンテキストに設定する
		void beginVertexShader() const;

		// この頂点シェーダーが使用する定数バッファのIdの配列を取得
		const std::vector<int>& getUseConstantBufferIdArray() const;

		// 頂点シェーダーのポインタを取得する
		ID3D11VertexShader* getShaderPtr() const;

		// 入力レイアウトのポインタを取得する
		ID3D11InputLayout* getVertexLayoutPtr() const;

	private:

		// この頂点シェーダーが使用する定数バッファのIdの配列
		std::vector<int> m_useConstantBufferIdArray;

		// 頂点シェーダーのポインタ
		ID3D11VertexShader* m_vertexShaderPtr{ nullptr };

		// 入力レイアウトのポインタ
		ID3D11InputLayout*	m_vertexLayoutPtr{ nullptr };
	};
}
#endif // !VERTEX_SHADER_DATA_H_