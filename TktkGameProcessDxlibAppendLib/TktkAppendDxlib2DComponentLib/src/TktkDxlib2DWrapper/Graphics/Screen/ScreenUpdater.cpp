#include "TktkDxlib2DWrapper/Graphics/Screen/ScreenUpdater.h"

#include <stdexcept>
#include <TktkMath/Matrix4.h>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include <DxLib.h>
#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h"

namespace tktk
{
	ScreenUpdater::ScreenUpdater(
		const Vector2 & gameScreenSize,
		bool fullScreen
	)
		: m_gameScreenSize(gameScreenSize)
		, m_fullScreen(fullScreen)
	{
	}

	void ScreenUpdater::awake()
	{
		if (m_fullScreen)
		{
			m_displaySize.x = static_cast<float>(GetSystemMetrics(SM_CXSCREEN));
			m_displaySize.y = static_cast<float>(GetSystemMetrics(SM_CYSCREEN));

			calculateLetterBoxSize();
		}
		else
		{
			m_displaySize = m_gameScreenSize;

			DxLib::SetWindowSize(
				static_cast<int>(m_gameScreenSize.x),
				static_cast<int>(m_gameScreenSize.y)
			);
		}

		DxLib::ChangeWindowMode(m_fullScreen ? FALSE : TRUE);

		DxLib::SetGraphMode(
			static_cast<int>(m_displaySize.x),
			static_cast<int>(m_displaySize.y),
			32
		);

		DxLib::DxLib_Init();
	}

	void ScreenUpdater::start()
	{
		RenderTargetManager::makeMainScreen(m_gameScreenSize);
	}

	void ScreenUpdater::onDestroy()
	{
		DxLib::DxLib_End();
	}

	void ScreenUpdater::update()
	{
		if (DxLib::ProcessMessage() != 0)
		{
			ComponentFrameworkProcessor::exitGame();
		}
	}

	void ScreenUpdater::draw()
	{
		int mainScreenHandle = RenderTargetManager::getMainScreenHandle();

		DxLib::SetDrawScreen(DX_SCREEN_BACK);
		DxLib::ClearDrawScreen();
		DxLib::DrawExtendGraph(
			static_cast<int>(m_letterBoxSize.x),
			static_cast<int>(m_letterBoxSize.y),
			static_cast<int>(m_displaySize.x - m_letterBoxSize.x),
			static_cast<int>(m_displaySize.y - m_letterBoxSize.y),
			mainScreenHandle,
			FALSE
		);
		DxLib::SetDrawScreen(mainScreenHandle);
		DxLib::ClearDrawScreen();
	}

	void ScreenUpdater::frameEnd()
	{
		DxLib::ScreenFlip();
	}

	float ScreenUpdater::getUpdatePriority()
	{
		return -10000.0f;
	}

	float ScreenUpdater::getDrawPriority()
	{
		return 10000.0f;
	}

	const Vector2 & ScreenUpdater::getDisplaySize() const
	{
		return m_displaySize;
	}

	const Vector2 & ScreenUpdater::getGameScreenSize() const
	{
		return m_gameScreenSize;
	}

	const Vector2 & ScreenUpdater::getLetterBoxSize() const
	{
		return m_letterBoxSize;
	}

	void ScreenUpdater::backgroundColor(const Color & color)
	{
		DxLib::SetBackgroundColor(
			static_cast<int>(color.r * 255),
			static_cast<int>(color.g * 255),
			static_cast<int>(color.b * 255)
		);
	}

	void ScreenUpdater::calculateLetterBoxSize()
	{
		if (m_displaySize.x / m_gameScreenSize.x >= m_displaySize.y / m_gameScreenSize.y)
		{
			m_letterBoxSize.x = (m_displaySize.x - (m_displaySize.y * m_gameScreenSize.x / m_gameScreenSize.y)) / 2;
			m_letterBoxSize.y = 0.0f;
		}
		else
		{
			m_letterBoxSize.x = 0.0f;
			m_letterBoxSize.y = (m_displaySize.y - (m_displaySize.x * m_gameScreenSize.y / m_gameScreenSize.x)) / 2;
		}
	}
}