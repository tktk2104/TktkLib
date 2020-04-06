#ifndef DX12_GAME_MANAGER_H_
#define DX12_GAME_MANAGER_H_

#include <TktkDX12Wrapper/Graphics/Window/Window.h>

namespace tktk
{
	class DX12GameManager
	{
	public:

		DX12GameManager(
			WindowInitParam&& param,
			const std::string& tktkLibResFolderPath = ""		// ライブラリで使用するリソースのフォルダのパス
		);

	private:

		Window m_window;
	};
}
#endif // !DX12_GAME_MANAGER_H_