#ifndef SHADER_CONSTANT_BUFFER_ASSETS_H_
#define SHADER_CONSTANT_BUFFER_ASSETS_H_

#include <unordered_map>
#include "ShaderConstantBufferData.h"

namespace tktk
{
	class ShaderConstantBufferAssets
	{
	public:

		ShaderConstantBufferAssets() = default;

	public:

		void onDestroy() const;

	public:

		template <class BufferType>
		void create(int id);

		void create(int id, unsigned int bufferSize, std::type_index bufferType);

		void erase(int id);

		void clear();

		const ShaderConstantBufferData& getData(int id) const;

	private:

		std::unordered_map<int, ShaderConstantBufferData> m_shaderConstantBufferAssets;
	};

	template<class BufferType>
	inline void ShaderConstantBufferAssets::create(int id)
	{
		create(id, sizeof(BufferType), typeid(BufferType));
	}
}
#endif // !SHADER_CONSTANT_BUFFER_ASSETS_H_