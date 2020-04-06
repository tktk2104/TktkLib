#ifndef DX12_GAME_MANAGER_H_
#define DX12_GAME_MANAGER_H_

#include <TktkDX12Wrapper/Graphics/Window/Window.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/_DX3DBaseObjects/DX3DBaseObjects.h>

namespace tktk
{
	class DX12GameManager
	{
	public:

		DX12GameManager(
			WindowInitParam&& param,
			const std::string& tktkLibResFolderPath = ""		// ライブラリで使用するリソースのフォルダのパス
		);

	public:

		void update();

	private:

		Window m_window;
		DX3DBaseObjects m_dx3dBaseObjects;
	};
}
#endif // !DX12_GAME_MANAGER_H_