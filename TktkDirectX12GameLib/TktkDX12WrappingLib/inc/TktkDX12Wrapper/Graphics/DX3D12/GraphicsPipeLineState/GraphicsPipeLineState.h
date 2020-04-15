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

		void createRootSignature(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam);

		void createGraphicsPipeLineState(unsigned int graphicsPipeLineId, ID3D12Device* device, const GraphicsPipeLineStateInitParam& initParam, const std::string& vsFilePath, const std::string& psFilePath, unsigned int useRootSignatureId);

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	private:

		RootSignature<RootSignatureNum> m_rootSignatureNum{};

		std::array<GraphicsPipeLineStateData, GraphicsPipeLineNum> m_graphicsPipeLineStateDataArray{};
	};

	template<int GraphicsPipeLineNum, int RootSignatureNum>
	inline void GraphicsPipeLineState<GraphicsPipeLineNum, RootSignatureNum>::createRootSignature(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		m_rootSignatureNum.create(id, device, initParam);
	}

	template<int GraphicsPipeLineNum, int RootSignatureNum>
	inline void GraphicsPipeLineState<GraphicsPipeLineNum, RootSignatureNum>::createGraphicsPipeLineState(unsigned int graphicsPipeLineId, ID3D12Device* device, const GraphicsPipeLineStateInitParam& initParam, const std::string& vsFilePath, const std::string& psFilePath, unsigned int useRootSignatureId)
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
				throw std::runtime_error("load pixelShader error");
			}

			fseek(fp, 0, SEEK_END);
			psByteArray.resize(ftell(fp));
			fseek(fp, 0, SEEK_SET);

			fread(psByteArray.data(), psByteArray.size(), 1, fp);
			fclose(fp);
		}

		m_graphicsPipeLineStateDataArray.at(graphicsPipeLineId).initialize(
			device,
			initParam,
			vsByteArray,
			psByteArray,
			m_rootSignatureNum.getPtr(useRootSignatureId),
			useRootSignatureId
		);
	}

	template<int GraphicsPipeLineNum, int RootSignatureNum>
	inline void GraphicsPipeLineState<GraphicsPipeLineNum, RootSignatureNum>::set(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_rootSignatureNum.set(m_graphicsPipeLineStateDataArray.at(id).getUseRootSignatureIndex(), commandList);
		m_graphicsPipeLineStateDataArray.at(id).set(commandList);
	}
}
#endif // !GRAPHICS_PIPELINE_STATE_H_