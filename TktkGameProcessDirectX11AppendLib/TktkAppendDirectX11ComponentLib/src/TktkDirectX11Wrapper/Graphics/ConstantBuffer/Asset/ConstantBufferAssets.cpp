#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/Asset/ConstantBufferAssets.h"

namespace tktk
{
	ConstantBufferAssets::~ConstantBufferAssets()
	{
		clear();
	}

	void ConstantBufferAssets::create(int id, SafetyVoidPtr && data)
	{
		erase(id);

		m_assets.emplace(id, std::move(data));
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
}