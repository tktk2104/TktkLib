#ifndef RENDER_TARGET_DATA_H_
#define RENDER_TARGET_DATA_H_

#include <d3d11.h>

namespace tktk
{
	// レンダーターゲットを管理するクラス
	class RenderTargetData
	{
	public:

		explicit RenderTargetData(ID3D11Texture2D* renderTargetTexturePtr);
		~RenderTargetData();

		RenderTargetData(const RenderTargetData& other) = delete;
		RenderTargetData& operator = (const RenderTargetData& other) = delete;

	public:

		// レンダーターゲットビューのポインタを取得する
		ID3D11RenderTargetView* getViewPtr() const;

	private:

		// レンダーターゲットビューのポインタ
		ID3D11RenderTargetView* m_viewPtr;
	};
}
#endif // !RENDER_TARGET_DATA_H_
