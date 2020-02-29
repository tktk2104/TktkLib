#ifndef DEPTH_STENCIL_VIEW_DATA_H_
#define DEPTH_STENCIL_VIEW_DATA_H_

#include <d3d11.h>
#include <TktkMath/Vector2.h>

namespace tktk
{
	// 深度バッファを管理するクラス
	class DepthStencilViewData
	{
	public:

		explicit DepthStencilViewData(const Vector2& useTextureSize);
		~DepthStencilViewData();

		DepthStencilViewData(const DepthStencilViewData& other) = delete;
		DepthStencilViewData& operator = (const DepthStencilViewData& other) = delete;

	public:

		// 深度ビューのポインタを取得する
		ID3D11DepthStencilView* getViewPtr() const;

	private:

		// 深度ビューで使用するテクスチャのポインタ
		ID3D11Texture2D*		m_useTexturePtr{ nullptr };

		// 深度ビューのポインタ
		ID3D11DepthStencilView* m_viewPtr{ nullptr };
	};
}
#endif // !DEPTH_STENCIL_VIEW_DATA_H_