#ifndef TEXTURE_2D_DATA_H_
#define TEXTURE_2D_DATA_H_

#include <string>
#include <vector>
#include <d3d11.h>

namespace tktk
{
	// 2Dテクスチャを管理するクラス
	class Texture2DData
	{
	public:

		Texture2DData(unsigned char* data, unsigned int dataSize);
		explicit Texture2DData(const std::string& fileName);
		~Texture2DData();

		Texture2DData(const Texture2DData& other) = delete;
		Texture2DData& operator = (const Texture2DData& other) = delete;

	public:

		// 2Dテクスチャのポインタを取得する
		ID3D11Texture2D* getTexture2DPtr() const;

		// 2Dテクスチャのシェーダーリソースビューのポインタを取得する
		ID3D11ShaderResourceView* getShaderResourceViewPtr() const;

		// 2Dテクスチャのサンプラーステートのポインタを取得する
		ID3D11SamplerState* getSamplerStatePtr() const;

		// 2Dテクスチャの横幅を取得する
		unsigned int width() const;

		// 2Dテクスチャの立幅を取得する
		unsigned int height() const;

	private:

		void createTextrue2D(const std::vector<unsigned char>& image);
		void createShaderResourceView();
		void createSamplerState();

	private:

		ID3D11Texture2D* m_texturePtr{ nullptr };
		ID3D11ShaderResourceView* m_shaderResouceViewPtr{ nullptr };
		ID3D11SamplerState* m_samplerPtr{ nullptr };
		unsigned int m_width;
		unsigned int m_height;
	};
}
#endif // !TEXTURE_2D_DATA_H_