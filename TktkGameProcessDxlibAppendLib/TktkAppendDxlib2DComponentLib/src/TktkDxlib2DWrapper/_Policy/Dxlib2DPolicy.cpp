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
		// 2D�A�Z�b�g�Ǘ��N���X�𐶐�
		Assets2DManager::createAsset();

		// ��ʊǗ��N���X���Z�b�g�A�b�v
		ScreenManager::setUp(m_gameScreenSize, m_fullScreenFlag);

		// �����_�[�^�[�Q�b�g�Ǘ��N���X���Z�b�g�A�b�v
		RenderTargetManager::setUp();

		// �|�X�g�G�t�F�N�g�Ǘ��N���X���Z�b�g�A�b�v
		PostEffectManager::setUp();

		// �L�[�{�[�h���͊Ǘ��N���X���Z�b�g�A�b�v
		KeyboardManager::setUp();

		// �}�E�X���͊Ǘ��N���X���Z�b�g�A�b�v
		MouseManager::setUp();

		// �Q�[���p�b�h���͊Ǘ��N���X���Z�b�g�A�b�v
		GamePadManager::setUp();

		// �T�E���h�Đ��Ǘ��N���X���Z�b�g�A�b�v
		Sound2DManager::setUp();

		setUpdatePriority();
	}

	bool Dxlib2DPolicy::isDestroy() const
	{
		return true;
	}

	void Dxlib2DPolicy::setUpdatePriority()
	{
		// ScreenUpdater UpdatePriority : -10000.0f

		ComponentFrameworkProcessor::addComponentUpdatePriority<ParentChildManager>(-1000.0f);

		ComponentFrameworkProcessor::addComponentUpdatePriority<InertialMovement2D>(1000.0f);
		ComponentFrameworkProcessor::addComponentUpdatePriority<InertialRotatement2D>(1000.0f);

		ComponentFrameworkProcessor::addComponentUpdatePriority<Transform2D>(1010.0f);

		ComponentFrameworkProcessor::addComponentUpdatePriority<RectCollider>(1020.0f);
		ComponentFrameworkProcessor::addComponentUpdatePriority<CircleCollider>(1020.0f);
		ComponentFrameworkProcessor::addComponentUpdatePriority<Polygon2dCollider>(1020.0f);

		ComponentFrameworkProcessor::addComponentUpdatePriority<RectColliderExtrusion>(1050.0f);
	}
}