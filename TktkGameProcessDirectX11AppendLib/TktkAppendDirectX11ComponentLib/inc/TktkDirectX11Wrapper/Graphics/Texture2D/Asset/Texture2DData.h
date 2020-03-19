#ifndef TEXTURE_2D_DATA_H_
#define TEXTURE_2D_DATA_H_

#include <string>
#include <vector>
#include <d3d11.h>
#include "Texture2DBindFlag.h"
#include "Texture2DUsage.h"
#include "Texture2DCpuAccessFlag.h"

namespace tktk
{
	// 2Dテクスチャを管理するクラス
	class Texture2DData
	{
	public:

		Texture2DData(
			Texture2DBindFlag bindFlag,
			const std::vector<D3D11_SUBRESOURCE_DATA>& subrescorceDataArray,
			unsigned int width,
			unsigned int height,
			unsigned int mipCount,
			unsigned int arraySize,
			DXGI_FORMAT format,
			Texture2DUsage usage,
			Texture2DCpuAccessFlag cpuAccessFlag,
			bool isCubeMap
		);

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

		// マップされたサブリソースを取得する
		// ※この関数の戻り値の使用が終わった後は必ず「unMapSubResource()」を呼んでください
		D3D11_MAPPED_SUBRESOURCE mapSubResource() const;

		// 「mapSubResource()」でMapしたリソースをUnmapする
		void unMapSubResource() const;

	private:

		ID3D11Texture2D* m_texturePtr{ nullptr };
		ID3D11ShaderResourceView* m_shaderResouceViewPtr{ nullptr };
		ID3D11SamplerState* m_samplerPtr{ nullptr };
		unsigned int m_width;
		unsigned int m_height;
		bool m_isAfterChange;
	};
}
#endif // !TEXTURE_2D_DATA_H_