#ifndef VERTEX_BUFFER_DATA_H_
#define VERTEX_BUFFER_DATA_H_

#include <vector>
#include <d3d12.h>

namespace tktk
{
	// 頂点バッファ情報を管理するクラス
	class VertexBufferData
	{
	public:

		VertexBufferData() = default;
		~VertexBufferData();

	public:

		template <class VertexData>
		void initialize(ID3D12Device* device, const std::vector<VertexData>& vertexDataArray);

		void set(ID3D12GraphicsCommandList* commandList);

	private:

		void createVertexBuffer(ID3D12Device* device, unsigned int resouseWidth);
		void createVertexBufferView(unsigned int bufferSizeInByte, unsigned int bufferStrideInBytes);

	private:

		ID3D12Resource*				m_vertexBuffer		{ nullptr };
		D3D12_VERTEX_BUFFER_VIEW	m_vertexBufferView	{};
	};

	template<class VertexData>
	inline void VertexBufferData::initialize(ID3D12Device* device, const std::vector<VertexData>& vertexDataArray)
	{
		createVertexBuffer(device, sizeof(VertexData) * vertexDataArray.size());

		VertexData* mappedVertexData{ nullptr };
		m_vertexBuffer->Map(0, nullptr, (void**)(&mappedVertexData));
		std::copy(std::begin(vertexDataArray), std::end(vertexDataArray), mappedVertexData);
		m_vertexBuffer->Unmap(0, nullptr);

		createVertexBufferView(sizeof(VertexData) * vertexDataArray.size(), sizeof(VertexData));
	}
}
#endif // !VERTEX_BUFFER_DATA_H_