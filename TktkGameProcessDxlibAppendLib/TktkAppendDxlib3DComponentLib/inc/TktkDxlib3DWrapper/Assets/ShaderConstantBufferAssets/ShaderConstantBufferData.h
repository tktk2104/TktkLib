#ifndef SHADER_CONSTANT_BUFFER_DATA_H_
#define SHADER_CONSTANT_BUFFER_DATA_H_

#include <typeindex>

namespace tktk
{
	struct ShaderConstantBufferData
	{
	public:

		ShaderConstantBufferData(
			int shaderConstantBufferHandle,
			std::type_index shaderConstantBufferType
		);

	public:

		int shaderConstantBufferHandle{ -1 };
		std::type_index shaderConstantBufferType;
	};
}
#endif // !SHADER_CONSTANT_BUFFER_DATA_H_