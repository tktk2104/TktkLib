#include "TktkDxlib2DWrapper/Assets/RenderTargetAssets/RenderTargetAssets.h"

#include <algorithm>
#include <DxLib.h>

namespace tktk
{
	void RenderTargetAssets::onDestroy() const
	{
		std::for_each(
			std::begin(m_renderTargetAssetsMap),
			std::end(m_renderTargetAssetsMap),
			[](const auto& node) { DxLib::DeleteGraph(node.second.screenGraphHandle); }
		);
	}

	void RenderTargetAssets::createRenderTarget(
		int id,
		const Vector2 & size,
		bool autoRefresh,
		bool hdr,
		bool useZbuffer,
		int bitDepth,
		int channel
	)
	{
		eraseRenderTarget(id);

		RenderTargetHandle renderTargetHandle;

		DxLib::SetDrawValidAlphaChannelGraphCreateFlag(TRUE);
		{
			if (hdr)
			{
				// 浮動小数点テクスチャの場合
				DxLib::SetDrawValidFloatTypeGraphCreateFlag(TRUE);
				DxLib::SetCreateDrawValidGraphChannelNum(channel);
				DxLib::SetCreateGraphChannelBitDepth(bitDepth);
			}
			else
			{
				DxLib::SetDrawValidFloatTypeGraphCreateFlag(FALSE);
				DxLib::SetCreateGraphColorBitDepth(bitDepth);
			}

			// Ｚバッファ作成フラグ
			DxLib::SetDrawValidGraphCreateZBufferFlag(useZbuffer ? TRUE : FALSE);

			renderTargetHandle.screenGraphHandle = DxLib::MakeScreen(
				static_cast<int>(size.x),
				static_cast<int>(size.y),
				TRUE
			);

			// 設定をデフォルトに戻す
			DxLib::SetDrawValidFloatTypeGraphCreateFlag(FALSE);
			DxLib::SetCreateGraphChannelBitDepth(0);
			DxLib::SetCreateDrawValidGraphChannelNum(0);
			DxLib::SetCreateGraphColorBitDepth(4);

			renderTargetHandle.vertices[0] = { { 0.0f,		0.0f	}, 1.0f, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, {0.0f, 0.0f}, {0.0f, 0.0f} }; // 左上
			renderTargetHandle.vertices[1] = { { size.x,	0.0f	}, 1.0f, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, {1.0f, 0.0f}, {1.0f, 0.0f} }; // 右下
			renderTargetHandle.vertices[2] = { { 0.0f,		size.y	}, 1.0f, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, {0.0f, 1.0f}, {0.0f, 1.0f} }; // 左下
			renderTargetHandle.vertices[3] = { { size.x,	size.y	}, 1.0f, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, {1.0f, 1.0f}, {1.0f, 1.0f} }; // 右下

			renderTargetHandle.autoRefresh = autoRefresh;
		}
		DxLib::SetDrawValidAlphaChannelGraphCreateFlag(FALSE);

		m_renderTargetAssetsMap.insert(std::make_pair(id, renderTargetHandle));
	}

	void RenderTargetAssets::eraseRenderTarget(int id)
	{
		auto eraseNode = m_renderTargetAssetsMap.find(id);
		if (eraseNode == std::end(m_renderTargetAssetsMap)) return;

		DxLib::DeleteGraph((*eraseNode).second.screenGraphHandle);
		m_renderTargetAssetsMap.erase(id);
	}

	void RenderTargetAssets::eraseRenderTargetAll()
	{
		std::for_each(
			std::begin(m_renderTargetAssetsMap),
			std::end(m_renderTargetAssetsMap),
			[](const auto& node) { DxLib::DeleteGraph(node.second.screenGraphHandle); }
		);
		m_renderTargetAssetsMap.clear();
	}

	RenderTargetHandle RenderTargetAssets::getRenderTargetHandle(int id) const
	{
		return m_renderTargetAssetsMap.at(id);
	}

	void RenderTargetAssets::clearAutoRefreshRenderTargetAll(int mainScreenHandle)
	{
		std::for_each(
			std::begin(m_renderTargetAssetsMap),
			std::end(m_renderTargetAssetsMap),
			[this, &mainScreenHandle](const auto& node) { if (node.second.autoRefresh) clearRenderTarget(node.first, mainScreenHandle); }
		);
	}

	void RenderTargetAssets::clearRenderTarget(int id, int mainScreenHandle)
	{
		DxLib::SetDrawScreen(m_renderTargetAssetsMap.at(id).screenGraphHandle);
		DxLib::ClearDrawScreen();
		DxLib::SetDrawScreen(mainScreenHandle);
	}
}