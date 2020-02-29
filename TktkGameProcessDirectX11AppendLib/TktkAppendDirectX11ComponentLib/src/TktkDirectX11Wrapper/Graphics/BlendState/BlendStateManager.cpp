#include "TktkDirectX11Wrapper/Graphics/BlendState/BlendStateManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include "TktkDirectX11Wrapper/Graphics/BlendState/Asset/SystemBlendStateId.h"

namespace tktk
{
	CfpPtr<BlendStateAssets> BlendStateManager::m_assetsPtr;

	void BlendStateManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::createClass<BlendStateAssets>(true);

		D3D11_BLEND_DESC blendDesc{};
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = true;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_DEST_COLOR;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_COLOR;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_DEST_ALPHA;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		create(SystemBlendStateId::Basic, blendDesc);
	}

	void BlendStateManager::clear()
	{
		m_assetsPtr->clear();
	}

	void BlendStateManager::createImpl(int id, const D3D11_BLEND_DESC & blendDesc)
	{
		m_assetsPtr->create(id, blendDesc);
	}

	void BlendStateManager::eraseImpl(int id)
	{
		m_assetsPtr->erase(id);
	}

	BlendStateData * BlendStateManager::getDataPtrImpl(int id)
	{
		return m_assetsPtr->getDataPtr(id);
	}
}