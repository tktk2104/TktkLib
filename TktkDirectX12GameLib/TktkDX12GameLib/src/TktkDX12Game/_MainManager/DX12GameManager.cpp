#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	DX12GameManager::DX12GameManager(
		WindowInitParam&& param,
		const std::string& tktkLibResFolderPath
	)
		: m_window(std::move(param))
	{

	}
}