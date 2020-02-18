#ifndef SHADER_CONSTANT_BUFFER_UPDATER_H_
#define SHADER_CONSTANT_BUFFER_UPDATER_H_

#include <stdexcept>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "TktkDxlib3DWrapper/Assets/Assets3DManager.h"

namespace tktk
{
	class ShaderConstantBufferUpdater
		: public ComponentBase
	{
	public:

		ShaderConstantBufferUpdater(
			int shaderConstantBufferId
		);

	public:

		template<class BufferDataType>
		void updateBufferData(const BufferDataType& newBufferData);

		template<class BufferDataType>
		BufferDataType* getBufferData() const;

	private:

		void* getRawBufferData(int constantBufferHandle);

	private:

		int m_shaderConstantBufferId;
	};

	template<class BufferDataType>
	inline void ShaderConstantBufferUpdater::updateBufferData(const BufferDataType & newBufferData)
	{
		const ShaderConstantBufferData& shaderConstantBufferData = Assets3DManager::getShaderConstantBufferAssets().lock()->getData(m_shaderConstantBufferId);

		if (shaderConstantBufferData.shaderConstantBufferType != typeid(BufferDataType))
		{
			throw std::runtime_error("ShaderConstantBufferType not Match");
		}
		BufferDataType* bufferData = (static_cast<BufferDataType*>(getRawBufferData(shaderConstantBufferData.shaderConstantBufferHandle)));
		(*bufferData) = newBufferData;
	}

	template<class BufferDataType>
	inline BufferDataType * ShaderConstantBufferUpdater::getBufferData() const
	{
		const ShaderConstantBufferData& shaderConstantBufferData = Assets3DManager::getShaderConstantBufferAssets().lock()->getData(m_shaderConstantBufferId);

		if (shaderConstantBufferData.shaderConstantBufferType != typeid(BufferDataType))
		{
			throw std::runtime_error("ShaderConstantBufferType not Match");
		}
		return reinterpret_cast<BufferDataType*>(getRawBufferData(shaderConstantBufferData.shaderConstantBufferHandle));
	}
}
#endif // !SHADER_CONSTANT_BUFFER_UPDATER_H_