#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBuffer.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBufferManager.h"

namespace tktk
{
	void ConstantBuffer::erase(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("ConstantBufferId Fraud Value");
		}
		ConstantBufferManager::erase(id);
	}

	ConstantBufferData * ConstantBuffer::getDataPtr(int id)
	{
		return ConstantBufferManager::getDataPtr(id);
	}

	void ConstantBuffer::addParamLocation(int id, int locationType, unsigned int locationFromBufferTop)
	{
		return ConstantBufferManager::addParamLocation(id, locationType, locationFromBufferTop);
	}
}