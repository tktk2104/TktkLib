#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/Asset/ConstantBufferAssets.h"

namespace tktk
{
	ConstantBufferAssets::~ConstantBufferAssets()
	{
		clear();
	}

	void ConstantBufferAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void ConstantBufferAssets::clear()
	{
		m_assets.clear();
	}

	ConstantBufferData * ConstantBufferAssets::getDataPtr(int id)
	{
		return &(m_assets.at(id));
	}

	void ConstantBufferAssets::addParamLocation(int id, int locationType, unsigned int locationFromBufferTop)
	{
		m_assets.at(id).addParamLocation(locationType, locationFromBufferTop);
	}
}