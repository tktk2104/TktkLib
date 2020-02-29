#include "TktkDirectX11Wrapper/_Policy/DirectX11Policy.h"

#include <TktkDirectX11Wrapper/Graphics/Window/WindowManager.h>
#include <TktkDirectX11Wrapper/Graphics/Screen/ScreenManager.h>
#include <TktkDirectX11Wrapper/Graphics/DepthStencilView/DepthStencilViewManager.h>
#include <TktkDirectX11Wrapper/Graphics/ViewPort/ViewPortManager.h>
#include <TktkDirectX11Wrapper/Input/Keyboard/KeyboardManager.h>
#include <TktkDirectX11Wrapper/Sound/SoundManager.h>

#include <TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBufferManager.h>
#include <TktkDirectX11Wrapper/Graphics/PixelShader/PixelShaderManager.h>
#include <TktkDirectX11Wrapper/Graphics/RenderTarget/RenderTargetManager.h>
#include <TktkDirectX11Wrapper/Graphics/Texture2D/Texture2DManager.h>
#include <TktkDirectX11Wrapper/Graphics/VertexShader/VertexShaderManager.h>

#include <TktkDirectX11Wrapper/Graphics/Sprite/SpriteDrawerSetupper.h>

#include "TktkDirectX11Wrapper/Graphics/Animation/AnimationManager.h"
#include "TktkDirectX11Wrapper/Graphics/Camera/CameraManager.h"
#include "TktkDirectX11Wrapper/Graphics/Light/LightManager.h"
#include "TktkDirectX11Wrapper/Graphics/Material/MaterialManager.h"
#include "TktkDirectX11Wrapper/Graphics/Skeleton/SkeletonManager.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/MeshManager.h"

#include "TktkDirectX11Wrapper/Graphics/Mesh/MeshDrawerSetupper.h"

namespace tktk
{
	DirectX11Policy::DirectX11Policy(
		HINSTANCE hInstance,
		int nCmdShow,
		const std::string & windowName,
		const Vector2 & gameScreenSize,
		bool fullScreenFlag,
		const std::string & spritePixelShaderFileName,
		const std::string & spriteVertexShaderFileName,
		const std::string & basicMeshPixelShaderFileName,
		const std::string & basicMeshVertexShaderFileName,
		const std::string & pbrMeshPixelShaderFileName,
		const std::string & pbrMeshVertexShaderFileName,
		const std::string & iblMeshPixelShaderFileName,
		const std::string & iblMeshVertexShaderFileName,
		const std::string & pbrIblMeshPixelShaderFileName,
		const std::string & pbrIblMeshVertexShaderFileName
	)
	{
		WindowManager::setUp(hInstance, nCmdShow, windowName, gameScreenSize);

		ScreenManager::setUp(fullScreenFlag);

		DepthStencilViewManager::setUp();

		ViewPortManager::setUp();

		KeyboardManager::setUp(hInstance);

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

		SpriteDrawerSetupper::setUp(spritePixelShaderFileName, spriteVertexShaderFileName);
		MeshDrawerSetupper::setUp(
			basicMeshPixelShaderFileName,
			basicMeshVertexShaderFileName,
			pbrMeshPixelShaderFileName,
			pbrMeshVertexShaderFileName,
			iblMeshPixelShaderFileName,
			iblMeshVertexShaderFileName,
			pbrIblMeshPixelShaderFileName,
			pbrIblMeshVertexShaderFileName
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