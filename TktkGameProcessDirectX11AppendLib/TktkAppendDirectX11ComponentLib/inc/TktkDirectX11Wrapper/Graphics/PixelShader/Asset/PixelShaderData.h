#ifndef PIXEL_SHADER_DATA_H_
#define PIXEL_SHADER_DATA_H_

#include <string>
#include <vector>
#include <d3d11.h>

namespace tktk
{
	// ピクセルシェーダーを管理するクラス
	class PixelShaderData
	{
	public:

		PixelShaderData(const std::vector<int>& useConstantBufferIdArray, const std::string& fileName);
		~PixelShaderData();

		// コピー禁止
		PixelShaderData(const PixelShaderData& other) = delete;
		PixelShaderData& operator = (const PixelShaderData& other) = delete;

	public:

		// ピクセルシェーダーに定数バッファを設定してデバイスコンテキストに設定する
		void beginShader() const;

		// このピクセルシェーダーが使用する定数バッファのIdの配列を取得
		const std::vector<int>& getUseConstantBufferIdArray() const;

		// ピクセルシェーダーのポインタを取得する
		ID3D11PixelShader* getShaderPtr() const;

	private:

		// このピクセルシェーダーが使用する定数バッファのIdの配列
		std::vector<int> m_useConstantBufferIdArray;

		// ピクセルシェーダーのポインタ
		ID3D11PixelShader* m_shaderPtr{ nullptr };
	};
}
#endif // !PIXEL_SHADER_DATA_H_