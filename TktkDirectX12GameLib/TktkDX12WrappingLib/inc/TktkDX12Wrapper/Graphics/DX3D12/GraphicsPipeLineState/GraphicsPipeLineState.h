#ifndef GRAPHICS_PIPELINE_STATE_H_
#define GRAPHICS_PIPELINE_STATE_H_

#include <string>
#include <array>
#include "GraphicsPipeLineStateData.h"
#include "RootSignature/RootSignature.h"

namespace tktk
{
	template <int GraphicsPipeLineNum, int RootSignatureNum>
	class GraphicsPipeLineState
	{
	public:

		GraphicsPipeLineState() = default;

	public:

		template <int RootSignatureIndex>
		void createRootSignature(ID3D12Device* device, const RootSignatureInitParam& initParam);

		template <int GraphicsPipeLineIndex, int UseRootSignatureIndex>
		void createGraphicsPipeLineState(ID3D12Device* device, const GraphicsPipeLineStateInitParam& initParam, const std::string& vsFilePath, const std::string& psFilePath);

		template <int GraphicsPipeLineIndex>
		void set(ID3D12GraphicsCommandList* commandList) const;

	private:

		RootSignature<RootSignatureNum> m_rootSignatureNum{};

		std::array<GraphicsPipeLineStateData, GraphicsPipeLineNum> m_graphicsPipeLineStateDataArray{};
	};

	template<int GraphicsPipeLineNum, int RootSignatureNum>
	template<int RootSignatureIndex>
	inline void GraphicsPipeLineState<GraphicsPipeLineNum, RootSignatureNum>::createRootSignature(ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		m_rootSignatureNum.create<RootSignatureIndex>(device, initParam);
	}

	template<int GraphicsPipeLineNum, int RootSignatureNum>
	template<int GraphicsPipeLineIndex, int UseRootSignatureIndex>
	inline void GraphicsPipeLineState<GraphicsPipeLineNum, RootSignatureNum>::createGraphicsPipeLineState(ID3D12Device* device, const GraphicsPipeLineStateInitParam& initParam, const std::string& vsFilePath, const std::string& psFilePath)
	{
		// 頂点シェーダーを読み込む
		std::vector<char> vsByteArray;
		{
			std::FILE* fp;

			int ret = fopen_s(&fp, vsFilePath.c_str(), "rb");

			if (ret != 0)
			{
				throw std::runtime_error("load vertexShader error");
			}

			fseek(fp, 0, SEEK_END);
			vsByteArray.resize(ftell(fp));
			fseek(fp, 0, SEEK_SET);

			fread(vsByteArray.data(), vsByteArray.size(), 1, fp);
			fclose(fp);
		}

		// ピクセルシェーダーを読み込む
		std::vector<char> psByteArray;
		{
			std::FILE* fp;

			int ret = fopen_s(&fp, psFilePath.c_str(), "rb");

			if (ret != 0)
			{
				throw std::runtime_error("load vertexShader error");
			}

			fseek(fp, 0, SEEK_END);
			psByteArray.resize(ftell(fp));
			fseek(fp, 0, SEEK_SET);

			fread(psByteArray.data(), psByteArray.size(), 1, fp);
			fclose(fp);
		}

		m_graphicsPipeLineStateDataArray.at(GraphicsPipeLineIndex).initialize(
			device,
			initParam,
			vsByteArray,
			psByteArray,
			m_rootSignatureNum.getPtr<UseRootSignatureIndex>(),
			UseRootSignatureIndex
		);
	}

	template<int GraphicsPipeLineNum, int RootSignatureNum>
	template<int GraphicsPipeLineIndex>
	inline void GraphicsPipeLineState<GraphicsPipeLineNum, RootSignatureNum>::set(ID3D12GraphicsCommandList* commandList) const
	{
		m_rootSignatureNum.set(m_graphicsPipeLineStateDataArray.at(GraphicsPipeLineIndex).getUseRootSignatureIndex(), commandList);
		m_graphicsPipeLineStateDataArray.at(GraphicsPipeLineIndex).set(commandList);
	}
}
#endif // !GRAPHICS_PIPELINE_STATE_H_