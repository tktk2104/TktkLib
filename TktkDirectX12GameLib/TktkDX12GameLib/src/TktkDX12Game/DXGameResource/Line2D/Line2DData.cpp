#include "TktkDX12Game/DXGameResource/Line2D/Line2DData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Line2D/Line2DConstantBufferData.h"

namespace tktk
{
	void Line2DData::drawLine(const Line2DDrawFuncArgs& drawFuncArgs) const
	{
		// ライン用の頂点バッファを作る
		createVertexBuffer(drawFuncArgs.lineVertexArray);

		// ライン用の定数バッファを更新する
		updateLine2DCbuffer(drawFuncArgs);

		// ビューポートを設定する
		DX12GameManager::setViewport(drawFuncArgs.viewportId);

		// シザー矩形を設定する
		DX12GameManager::setScissorRect(drawFuncArgs.scissorRectId);

		// レンダーターゲットを設定する（バックバッファーに直で描画する場合は特殊処理）
		if (drawFuncArgs.rtvDescriptorHeapId == DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBufferView();
		}
		else
		{
			DX12GameManager::setRtv(drawFuncArgs.rtvDescriptorHeapId, 0U, 1U);
		}

		// ライン用のパイプラインステートを設定する
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::Line2D));

		// ブレンドファクターを設定する
		DX12GameManager::setBlendFactor({ 1.0f, 1.0f, 1.0f, 1.0f });

		// ライン用のディスクリプタヒープを設定する
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, DX12GameManager::getSystemId(SystemBasicDescriptorHeapType::Line2D)} });
		
		// ラインストリップで描画を行う
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);

		// ライン用の頂点バッファを設定する
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemId(SystemVertexBufferType::Line2D));
		
		// ドローコール
		DX12GameManager::drawInstanced(drawFuncArgs.lineVertexArray.size(), 1U, 0U, 0U);

		// バックバッファ以外に描画していたら使用したレンダーターゲットバッファをシェーダーで使用する状態にする
		if (drawFuncArgs.rtvDescriptorHeapId != DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapId, 0U, 1U);
		}

		// コマンドリストを実行する
		DX12GameManager::executeCommandList();
	}

	// ライン用の頂点バッファを作る
	void Line2DData::createVertexBuffer(const std::vector<tktkMath::Vector2>& lineVertexArray) const
	{
		DX12GameManager::createVertexBuffer(DX12GameManager::getSystemId(SystemVertexBufferType::Line2D), lineVertexArray);
	}

	// ライン用の定数バッファを更新する
	void Line2DData::updateLine2DCbuffer(const Line2DDrawFuncArgs& drawFuncArgs) const
	{
		Line2DConstantBufferData cbufferData{};
		for (unsigned int i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;
			cbufferData.worldMatrix[i] = drawFuncArgs.worldMatrix.m[i / 4U][i % 4U];
		}
		cbufferData.lineColor = drawFuncArgs.lineColor;
		cbufferData.screenSize = DX12GameManager::getWindowSize();

		DX12GameManager::updateCBuffer(DX12GameManager::getSystemId(SystemCBufferType::Line2D), cbufferData);
	}
}