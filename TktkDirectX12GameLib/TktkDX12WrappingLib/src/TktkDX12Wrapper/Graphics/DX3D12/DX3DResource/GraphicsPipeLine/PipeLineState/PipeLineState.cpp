#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/GraphicsPipeLine/PipeLineState/PipeLineState.h"
#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	PipeLineState::PipeLineState(unsigned int pipeLineNum)
	{
		m_pipeLineStateDataArray.resize(pipeLineNum);
	}

	void PipeLineState::createPipeLineState(unsigned int id, ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath, ID3D12RootSignature* rootSignaturePtr)
	{
		// 頂点シェーダーを読み込む
		std::vector<char> vsByteArray;
		{
			std::FILE* fp;
	
			int ret = fopen_s(&fp, shaderFilePath.vsFilePath.c_str(), "rb");
	
#ifdef _DEBUG
			if (ret != 0)
			{
				throw std::runtime_error("load vertexShader error");
			}
#endif // _DEBUG
	
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
	
			int ret = fopen_s(&fp, shaderFilePath.psFilePath.c_str(), "rb");
	
#ifdef _DEBUG
			if (ret != 0)
			{
				throw std::runtime_error("load pixelShader error");
			}
#endif // _DEBUG
	
			fseek(fp, 0, SEEK_END);
			psByteArray.resize(ftell(fp));
			fseek(fp, 0, SEEK_SET);
	
			fread(psByteArray.data(), psByteArray.size(), 1, fp);
			fclose(fp);
		}
	
		m_pipeLineStateDataArray.at(id).initialize(
			device,
			initParam,
			vsByteArray,
			psByteArray,
			rootSignaturePtr
		);
	}

	int PipeLineState::getUseRootSignatureIndex(unsigned int id) const
	{
		return m_pipeLineStateDataArray.at(id).getUseRootSignatureIndex();
	}

	void PipeLineState::set(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_pipeLineStateDataArray.at(id).set(commandList);
	}
}