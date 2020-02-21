#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetUpdater.h"

#include <stdexcept>
#include <TktkMath/Matrix4.h>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include <DxLib.h>
#include "TktkDxlib2DWrapper/Utility/DXConverter.h"
#include "TktkDxlib2DWrapper/Assets/Assets2DManager.h"

namespace tktk
{
	void RenderTargetUpdater::onDestroy() const
	{
		if (m_mainScreenHandle == -1) return;

		DxLib::DeleteGraph(m_mainScreenHandle);
	}

	void RenderTargetUpdater::frameEnd()
	{
		Assets2DManager::getRenderTargetAssets()->clearAutoRefreshRenderTargetAll(m_mainScreenHandle);
	}

	void RenderTargetUpdater::makeMainScreen(const Vector2 & screenSize)
	{
		m_mainScreenHandle = DxLib::MakeScreen(
			static_cast<int>(screenSize.x),
			static_cast<int>(screenSize.y)
		);

		DxLib::SetDrawScreen(m_mainScreenHandle);
	}

	int RenderTargetUpdater::getMainScreenHandle() const
	{
		return m_mainScreenHandle;
	}

	void RenderTargetUpdater::setRenderTarget(int id)
	{
		setDrawScreen(Assets2DManager::getRenderTargetAssets()->getRenderTargetHandle(id).screenGraphHandle);
	}

	void RenderTargetUpdater::unSetRenderTarget()
	{
		setDrawScreen(m_mainScreenHandle);
	}

	void RenderTargetUpdater::drawRenderTargetTexture(int id)
	{
		DxLib::DrawGraph(
			0,
			0,
			Assets2DManager::getRenderTargetAssets()->getRenderTargetHandle(id).screenGraphHandle,
			TRUE
		);
	}

	void RenderTargetUpdater::setDrawScreen(int drawScreenHandle)
	{
		Matrix4 view = DXConverter::toMatrix(DxLib::GetCameraViewMatrix());
		Matrix4 proj = DXConverter::toMatrix(DxLib::GetCameraProjectionMatrix());

		DxLib::SetDrawScreen(drawScreenHandle);

		DxLib::SetCameraViewMatrix(DXConverter::toMATRIX(view));
		DxLib::SetupCamera_ProjectionMatrix(DXConverter::toMATRIX(proj));
	}
}