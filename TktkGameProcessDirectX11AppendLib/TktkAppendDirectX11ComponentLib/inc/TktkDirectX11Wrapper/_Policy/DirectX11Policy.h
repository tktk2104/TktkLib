#ifndef DIRECTX_11_POLICY_H_
#define DIRECTX_11_POLICY_H_

#include <string>
#include <TktkMath/Vector2.h>
#include "TktkDirectX11Wrapper/Utility/WindownsHeaderIncluder.h"

namespace tktk
{
	class DirectX11Policy
	{
	public:

		DirectX11Policy(
			HINSTANCE hInstance,
			int nCmdShow,
			const std::string & windowName,
			const Vector2& gameScreenSize,						// ゲームウィンドウの大きさ
			bool fullScreenFlag,								// フルスクリーンにするか
			const std::string& line2DPixelShaderFileName,		// デフォルトの2次元線分表示用のピクセルシェーダーのファイルパス
			const std::string& line2DVertexShaderFileName,		// デフォルトの2次元線分表示用の頂点シェーダーのファイルパス
			const std::string& spritePixelShaderFileName,		// デフォルトのスプライト表示用のピクセルシェーダーのファイルパス
			const std::string& spriteVertexShaderFileName,		// デフォルトのスプライト表示用の頂点シェーダーのファイルパス
			const std::string& basicMeshPixelShaderFileName,	// デフォルトのメッシュ表示用のピクセルシェーダーのファイルパス
			const std::string& basicMeshVertexShaderFileName,	// デフォルトのメッシュ表示用の頂点シェーダーのファイルパス
			const std::string& pbrMeshPixelShaderFileName,		// デフォルトのPbrメッシュ表示用のピクセルシェーダーのファイルパス
			const std::string& pbrMeshVertexShaderFileName,		// デフォルトのPbrメッシュ表示用の頂点シェーダーのファイルパス
			const std::string& iblMeshPixelShaderFileName,		// デフォルトのIblメッシュ表示用のピクセルシェーダーのファイルパス
			const std::string& iblMeshVertexShaderFileName,		// デフォルトのIblメッシュ表示用の頂点シェーダーのファイルパス
			const std::string& pbrIblMeshPixelShaderFileName,	// デフォルトのPbrIblメッシュ表示用のピクセルシェーダーのファイルパス
			const std::string& pbrIblMeshVertexShaderFileName	// デフォルトのPbrIblメッシュ表示用の頂点シェーダーのファイルパス
		);

	public:

		bool isDestroy() const;

	private:

		void setUpdatePriority();
	};
}
#endif // !DIRECTX_11_POLICY_H_