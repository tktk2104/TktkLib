#include "TktkDirectX11Wrapper/_Policy/DirectX11Policy.h"

#include <TktkDirectX11Wrapper/Graphics/Window/WindowManager.h>
#include <TktkDirectX11Wrapper/Graphics/Screen/ScreenManager.h>

#include <TktkDirectX11Wrapper/Graphics/ViewPort/ViewPortManager.h>
#include <TktkDirectX11Wrapper/Input/Keyboard/KeyboardManager.h>
#include <TktkDirectX11Wrapper/Input/Mouse/MouseManager.h>
#include <TktkDirectX11Wrapper/Sound/SoundManager.h>

#include <TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBufferManager.h>
#include <TktkDirectX11Wrapper/Graphics/PixelShader/PixelShaderManager.h>
#include <TktkDirectX11Wrapper/Graphics/RenderTarget/RenderTargetManager.h>
#include <TktkDirectX11Wrapper/Graphics/Texture2D/Texture2DManager.h>
#include <TktkDirectX11Wrapper/Graphics/VertexShader/VertexShaderManager.h>

#include "TktkDirectX11Wrapper/Graphics/BlendState/BlendStateManager.h"
#include "TktkDirectX11Wrapper/Graphics/DepthStencilView/DepthStencilViewManager.h"
#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/DepthStencilStateManager.h"
#include "TktkDirectX11Wrapper/Graphics/Animation/AnimationManager.h"
#include "TktkDirectX11Wrapper/Graphics/Camera/CameraManager.h"
#include "TktkDirectX11Wrapper/Graphics/Light/LightManager.h"
#include "TktkDirectX11Wrapper/Graphics/Material/MaterialManager.h"
#include "TktkDirectX11Wrapper/Graphics/Skeleton/SkeletonManager.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/MeshManager.h"

#include "TktkDirectX11Wrapper/Graphics/Line2D/Line2DDrawerSetupper.h"
#include "TktkDirectX11Wrapper/Graphics/Sprite/SpriteDrawerSetupper.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/MeshDrawerSetupper.h"

namespace tktk
{
	DirectX11Policy::DirectX11Policy(
		HINSTANCE hInstance,
		int nCmdShow,
		const std::string & windowName,
		const Vector2 & gameScreenSize,
		bool fullScreenFlag,
		const std::string& libResPath
	)
	{
		WindowManager::setUp(hInstance, nCmdShow, windowName, gameScreenSize);

		ScreenManager::setUp(fullScreenFlag);

		BlendStateManager::setUp();

		DepthStencilViewManager::setUp();

		DepthStencilStateManager::setUp();

		ViewPortManager::setUp();

		KeyboardManager::setUp(hInstance);
		MouseManager::setUp();

		SoundManager::setUp();

		ConstantBufferManager::setUp();
		PixelShaderManager::setUp();
		RenderTargetManager::setUp();
		Texture2DManager::setUp();
		VertexShaderManager::setUp();

		AnimationManager::setUp();
		CameraManager::setUp();
		LightManager::setUp();
		MaterialManager::setUp();
		SkeletonManager::setUp();
		MeshManager::setUp();

		SpriteDrawerSetupper::setUp(
			libResPath + "TktkLibRes/shader/SpritePixelShader.cso",
			libResPath + "TktkLibRes/shader/SpriteVertexShader.cso"
		);
		Line2DDrawerSetupper::setUp(
			libResPath + "TktkLibRes/shader/Line2DPixelShader.cso",
			libResPath + "TktkLibRes/shader/Line2DVertexShader.cso"
		);
		MeshDrawerSetupper::setUp(
			libResPath + "TktkLibRes/shader/MeshPixelShader.cso",
			libResPath + "TktkLibRes/shader/MeshVertexShader.cso",
			libResPath + "TktkLibRes/shader/BasicMonoColorMeshPixelShader.cso",
			libResPath + "TktkLibRes/shader/BasicMonoColorMeshVertexShader.cso",
			libResPath + "TktkLibRes/shader/PbrMeshPixelShader.cso",
			libResPath + "TktkLibRes/shader/PbrMeshVertexShader.cso",
			libResPath + "TktkLibRes/shader/IblMeshPixelShader.cso",
			libResPath + "TktkLibRes/shader/IblMeshVertexShader.cso",
			libResPath + "TktkLibRes/shader/PbrIblMeshPixelShader.cso",
			libResPath + "TktkLibRes/shader/PbrIblMeshVertexShader.cso"
		);

		setUpdatePriority();
	}

	bool DirectX11Policy::isDestroy() const
	{
		return true;
	}

	void DirectX11Policy::setUpdatePriority()
	{
	}
}