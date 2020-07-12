#ifndef DX_12_GAME_MANAGER_INIT_PARAM_H_
#define DX_12_GAME_MANAGER_INIT_PARAM_H_

#include <string>
#include <TktkDX12Wrapper/Graphics/DX3D12/_DX3DBaseObjects/DX3DBaseObjectsInitParam.h>
#include <TktkDX12Wrapper/Graphics/Window/WindowInitParam.h>
#include "TktkDX12Game/DXGameResource/DXGameResourceNum.h"

namespace tktk
{
	struct DX12GameManagerInitParam
	{
		DX3DBaseObjectsInitParam	dx3dParam			{};
		WindowInitParam				windowParam			{};
		DXGameResourceNum			dxGameResourceNum	{};
		std::string					tktkLibResFolderPath{""};
	};
}
#endif // !DX_12_GAME_MANAGER_INIT_PARAM_H_