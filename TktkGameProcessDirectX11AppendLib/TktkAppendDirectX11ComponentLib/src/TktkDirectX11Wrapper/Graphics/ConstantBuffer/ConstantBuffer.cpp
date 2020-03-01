#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBuffer.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBufferManager.h"

namespace tktk
{
	void ConstantBuffer::createImpl(int id, SafetyVoidPtr && data)
	{
		if (id <= 0)
		{
			throw std::runtime_error("ConstantBufferId Fraud Value");
		}
		ConstantBufferManager::createImpl(id, std::move(data));
	}

	void ConstantBuffer::eraseImpl(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("ConstantBufferId Fraud Value");
		}
		ConstantBufferManager::erase(id);
	}

	ConstantBufferData * ConstantBuffer::getDataPtrImpl(int id)
	{
		return ConstantBufferManager::getDataPtr(id);
	}

	void ConstantBuffer::addParamLocationImpl(int id, int locationType, unsigned int locationFromBufferTop)
	{
		return ConstantBufferManager::addParamLocation(id, locationType, locationFromBufferTop);
	}
}