#include "TktkDxlib3DWrapper/_Policy/Dxlib3DPolicy.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include "TktkDxlib2DWrapper/Graphics/Screen/ScreenManager.h"
#include "TktkDxlib2DWrapper/Assets/Assets2DManager.h"
#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h"
#include "TktkDxlib2DWrapper/Graphics/PostEffect/PostEffectManager.h"
#include "TktkDxlib2DWrapper/Input/Keyboard/KeyboardManager.h"
#include "TktkDxlib2DWrapper/Input/Mouse/MouseManager.h"
#include "TktkDxlib2DWrapper/Input/GamePad/GamePadManager.h"
#include "TktkDxlib2DWrapper/Sound2D/Sound2DManager.h"

#include "TktkDxlib3DWrapper/Sound3D/Sound3DManager.h"
#include "TktkDxlib3DWrapper/Assets/Assets3DManager.h"


#include <TktkComponentFramework/Component/CommonComponent/ParentChildManager/ParentChildManager.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include <TktkAppend2DComponent/InertialMovement2D.h>
#include <TktkAppend2DComponent/InertialRotatement2D.h>
#include <TktkAppend2DComponent/RectCollider.h>
#include <TktkAppend2DComponent/CircleCollider.h>
#include <TktkAppend2DComponent/Polygon2dCollider.h>
#include <TktkAppend2DComponent/RectColliderExtrusion.h>

#include <TktkAppend3DComponent/Transform3D.h>
#include <TktkAppend3DComponent/InertialMovement3D.h>
#include <TktkAppend3DComponent/SphereCollider.h>
#include <TktkAppend3DComponent/BoxCollider.h>

#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/ShadowMapDrawer/ShadowMapDrawer.h"

#include <DxLib.h>

namespace tktk
{
	Dxlib3DPolicy::Dxlib3DPolicy(
		const Vector2 & gameScreenSize,
		bool fullScreenFlag,
		float oneMeterDistance,
		bool useXAudio
	)
		: m_gameScreenSize(gameScreenSize)
		, m_fullScreenFlag(fullScreenFlag)
		, m_oneMeterDistance(oneMeterDistance)
		, m_useXAudio(useXAudio)
	{
	}

	void Dxlib3DPolicy::awake()
	{
		DxLib::Set3DSoundOneMetre(m_oneMeterDistance);
		DxLib::SetEnableXAudioFlag((m_useXAudio) ? TRUE : FALSE);

		// 2Dアセット管理クラスを生成
		Assets2DManager::createAsset();

		// 3Dアセット管理クラスを生成
		Assets3DManager::createAsset();

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

		// ２次元サウンド再生管理クラスをセットアップ
		Sound2DManager::setUp();

		// ３次元サウンド管理クラスをセットアップ
		Sound3DManager::setUp();

		setUpdatePriority();

		DxLib::SetUseZBuffer3D(TRUE);
		
	}

	bool Dxlib3DPolicy::isDestroy() const
	{
		return true;
	}

	void Dxlib3DPolicy::setUpdatePriority()
	{
		ComponentFrameworkProcessor::addUpdatePriority<ScreenUpdater>(-10000.0f);

		ComponentFrameworkProcessor::addUpdatePriority<ParentChildManager>(-1000.0f);

		ComponentFrameworkProcessor::addUpdatePriority<ShadowMapDrawer>(-100.0f);


		ComponentFrameworkProcessor::addUpdatePriority<InertialMovement2D>(1000.0f);
		ComponentFrameworkProcessor::addUpdatePriority<InertialRotatement2D>(1000.0f);
		ComponentFrameworkProcessor::addUpdatePriority<InertialMovement3D>(1000.0f);

		ComponentFrameworkProcessor::addUpdatePriority<Transform2D>(1010.0f);
		ComponentFrameworkProcessor::addUpdatePriority<Transform3D>(1010.0f);

		ComponentFrameworkProcessor::addUpdatePriority<RectCollider>(1020.0f);
		ComponentFrameworkProcessor::addUpdatePriority<CircleCollider>(1020.0f);
		ComponentFrameworkProcessor::addUpdatePriority<Polygon2dCollider>(1020.0f);
		ComponentFrameworkProcessor::addUpdatePriority<SphereCollider>(1020.0f);
		ComponentFrameworkProcessor::addUpdatePriority<BoxCollider>(1020.0f);

		ComponentFrameworkProcessor::addUpdatePriority<RectColliderExtrusion>(1050.0f);
	}
}