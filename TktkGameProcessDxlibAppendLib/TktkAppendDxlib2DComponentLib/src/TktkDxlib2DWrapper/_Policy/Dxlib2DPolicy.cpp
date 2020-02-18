#include "TktkDxlib2DWrapper/_Policy/Dxlib2DPolicy.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include "TktkDxlib2DWrapper/Graphics/Screen/ScreenManager.h"
#include "TktkDxlib2DWrapper/Assets/Assets2DManager.h"
#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h"
#include "TktkDxlib2DWrapper/Graphics/PostEffect/PostEffectManager.h"
#include "TktkDxlib2DWrapper/Input/Keyboard/KeyboardManager.h"
#include "TktkDxlib2DWrapper/Input/Mouse/MouseManager.h"
#include "TktkDxlib2DWrapper/Input/GamePad/GamePadManager.h"
#include "TktkDxlib2DWrapper/Sound2D/Sound2DManager.h"

#include <TktkComponentFramework/Component/CommonComponent/ParentChildManager/ParentChildManager.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include <TktkAppend2DComponent/InertialMovement2D.h>
#include <TktkAppend2DComponent/InertialRotatement2D.h>
#include <TktkAppend2DComponent/RectCollider.h>
#include <TktkAppend2DComponent/CircleCollider.h>
#include <TktkAppend2DComponent/Polygon2dCollider.h>
#include <TktkAppend2DComponent/RectColliderExtrusion.h>

namespace tktk
{
	Dxlib2DPolicy::Dxlib2DPolicy(
		const Vector2 & gameScreenSize,
		bool fullScreenFlag
	)
		: m_gameScreenSize(gameScreenSize)
		, m_fullScreenFlag(fullScreenFlag)
	{
	}

	void Dxlib2DPolicy::awake()
	{
		// 2Dアセット管理クラスを生成
		Assets2DManager::createAsset();

		// 画面管理クラスをセットアップ
		ScreenManager::setUp(m_gameScreenSize, m_fullScreenFlag);

		// レンダーターゲット管理クラスをセットアップ
		RenderTargetManager::setUp();

		// ポストエフェクト管理クラスをセットアップ
		PostEffectManager::setUp();

		// キーボード入力管理クラスをセットアップ
		KeyboardManager::setUp();

		// マウス入力管理クラスをセットアップ
		MouseManager::setUp();

		// ゲームパッド入力管理クラスをセットアップ
		GamePadManager::setUp();

		// サウンド再生管理クラスをセットアップ
		Sound2DManager::setUp();

		setUpdatePriority();
	}

	bool Dxlib2DPolicy::isDestroy() const
	{
		return true;
	}

	void Dxlib2DPolicy::setUpdatePriority()
	{
		ComponentFrameworkProcessor::addUpdatePriority<ScreenUpdater>(-10000.0f);

		ComponentFrameworkProcessor::addUpdatePriority<ParentChildManager>(-1000.0f);

		ComponentFrameworkProcessor::addUpdatePriority<InertialMovement2D>(1000.0f);
		ComponentFrameworkProcessor::addUpdatePriority<InertialRotatement2D>(1000.0f);

		ComponentFrameworkProcessor::addUpdatePriority<Transform2D>(1010.0f);

		ComponentFrameworkProcessor::addUpdatePriority<RectCollider>(1020.0f);
		ComponentFrameworkProcessor::addUpdatePriority<CircleCollider>(1020.0f);
		ComponentFrameworkProcessor::addUpdatePriority<Polygon2dCollider>(1020.0f);

		ComponentFrameworkProcessor::addUpdatePriority<RectColliderExtrusion>(1050.0f);
	}
}