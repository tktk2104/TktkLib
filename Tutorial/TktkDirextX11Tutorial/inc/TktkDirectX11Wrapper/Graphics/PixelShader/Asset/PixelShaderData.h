#ifndef PIXEL_SHADER_DATA_H_
#define PIXEL_SHADER_DATA_H_

#include <string>
#include <d3d11.h>

namespace tktk
{
	// ピクセルシェーダーを管理するクラス
	class PixelShaderData
	{
	public:

		PixelShaderData(int useConstantBufferId, const std::string& fileName);
		~PixelShaderData();

		PixelShaderData(const PixelShaderData& other) = delete;
		PixelShaderData& operator = (const PixelShaderData& other) = delete;

	public:

		// ピクセルシェーダーに定数バッファを設定してデバイスコンテキストに設定する
		void beginShader() const;

		// このピクセルシェーダーが使用する定数バッファのIdを取得
		int getUseConstantBufferId() const;

		// ピクセルシェーダーのポインタを取得する
		ID3D11PixelShader* getShaderPtr() const;

	private:

		// このピクセルシェーダーが使用する定数バッファのId
		int m_useConstantBufferId;

		// ピクセルシェーダーのポインタ
		ID3D11PixelShader* m_shaderPtr{ nullptr };
	};
}
#endif // !PIXEL_SHADER_DATA_H_