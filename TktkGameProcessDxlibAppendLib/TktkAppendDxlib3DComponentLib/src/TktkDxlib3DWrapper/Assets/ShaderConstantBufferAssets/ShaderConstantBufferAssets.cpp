#include "TktkDxlib3DWrapper/Assets/ShaderConstantBufferAssets/ShaderConstantBufferAssets.h"

#include <stdexcept>
#include <algorithm>
#include <DxLib.h>

namespace tktk
{
	void ShaderConstantBufferAssets::onDestroy() const
	{
		std::for_each(
			std::begin(m_shaderConstantBufferAssets),
			std::end(m_shaderConstantBufferAssets),
			[](const auto& node) { DxLib::DeleteShaderConstantBuffer(node.second.shaderConstantBufferHandle); }
		);
	}

	void ShaderConstantBufferAssets::create(int id, unsigned int bufferSize, std::type_index bufferType)
	{
		erase(id);

		ShaderConstantBufferData shaderConstantBufferData = ShaderConstantBufferData(
			DxLib::CreateShaderConstantBuffer(static_cast<int>(bufferSize)),
			bufferType
		);

		m_shaderConstantBufferAssets.insert(std::make_pair(id, shaderConstantBufferData));
	}

	void ShaderConstantBufferAssets::erase(int id)
	{
		auto eraseNode = m_shaderConstantBufferAssets.find(id);
		if (eraseNode == std::end(m_shaderConstantBufferAssets)) return;

		DxLib::DeleteShaderConstantBuffer((*eraseNode).second.shaderConstantBufferHandle);
		m_shaderConstantBufferAssets.erase(id);
	}

	void ShaderConstantBufferAssets::clear()
	{
		std::for_each(
			std::begin(m_shaderConstantBufferAssets),
			std::end(m_shaderConstantBufferAssets),
			[](const auto& node) { DxLib::DeleteShaderConstantBuffer(node.second.shaderConstantBufferHandle); }
		);
		m_shaderConstantBufferAssets.clear();
	}

	const ShaderConstantBufferData & ShaderConstantBufferAssets::getData(int id) const
	{
		return m_shaderConstantBufferAssets.at(id);
	}
}