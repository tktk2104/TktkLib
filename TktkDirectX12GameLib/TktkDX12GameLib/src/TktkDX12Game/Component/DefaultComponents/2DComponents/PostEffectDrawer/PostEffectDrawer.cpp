#include "TktkDX12Game/Component/DefaultComponents/2DComponents/PostEffectDrawer/PostEffectDrawer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

namespace tktk
{
	PostEffectDrawer::PostEffectDrawer(float drawPriority, unsigned int postEffectMaterialId, unsigned int useRtvDescriptorHeapId)
		: ComponentBase(drawPriority)
		, m_useRtvDescriptorHeapId(useRtvDescriptorHeapId)
		, m_postEffectMaterialId(postEffectMaterialId)
	{
	}

	void PostEffectDrawer::draw() const
	{
		PostEffectMaterialDrawFuncArgs drawFuncArgs{};
		drawFuncArgs.viewportId		= DX12GameManager::getSystemId(SystemViewportType::Basic);
		drawFuncArgs.scissorRectId	= DX12GameManager::getSystemId(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapId = m_useRtvDescriptorHeapId;

		DX12GameManager::drawPostEffect(m_postEffectMaterialId, drawFuncArgs);

		// TODO : レンダーターゲットのクリア処理は仮
		DX12GameManager::setRenderTarget(0U, 0U, 1U);
		DX12GameManager::clearRenderTarget(0U, 0U, tktkMath::colorRed);
		DX12GameManager::unSetRenderTarget(0U, 0U, 1U);
	}
}