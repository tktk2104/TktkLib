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
			const std::string& tktkLibResFolderPath = ""		// ライブラリで使用するリソースのフォルダのパス
		);

	public:

		bool isDestroy() const;

	private:

		void setUpdatePriority();
	};
}
#endif // !DIRECTX_11_POLICY_H_