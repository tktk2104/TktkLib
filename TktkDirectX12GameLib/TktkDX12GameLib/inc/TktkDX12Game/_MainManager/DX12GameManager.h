#ifndef DX12_GAME_MANAGER_H_
#define DX12_GAME_MANAGER_H_

#include <string>
#include <vector>
#include <memory>
#include <TktkDX12Wrapper/Graphics/Window/WindowInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/_DX3DBaseObjects/DX3DBaseObjectsInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/GraphicsPipeLineState/RootSignature/RootSignatureInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/GraphicsPipeLineState/GraphicsPipeLineStateInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/DescriptorHeap/BasicDescriptorHeap/BasicDescriptorHeapInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/DescriptorHeap/BufferResource/TextureBuffer/TextureBufferInitParam.h>
#include "../Scene/SceneManager.h"

namespace tktk
{
	class Window;
	class DX3DBaseObjects;

	class DX12GameManager
	{
	public:

		static void initialize(unsigned int sceneNum, const DX3DBaseObjectsInitParam& dx3dInitParam, const WindowInitParam& windowInitParam, const std::string& tktkLibResFolderPath = "");
		static void run();

	public:

		template<class SceneType, class... Args>
		static void addScene(unsigned int id, Args... constructorArgs);

		static void enableScene(unsigned int id);

		static void disableScene(unsigned int id);

	public:

		static void executeCommandList();

		static void createRootSignature(unsigned int id, const RootSignatureInitParam& initParam);

		static void createGraphicsPipeLineState(unsigned int graphicsPipeLineId, const GraphicsPipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath, unsigned int useRootSignatureId);

		template <class VertexData>
		static void createVertexBuffer(unsigned int id, const std::vector<VertexData>& vertexDataArray);

		static void createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices);

		template <class ConstantBufferDataType>
		static void createConstantBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData);

		static void createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam);

		static void gpuPriorityLoadTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const std::string& texDataPath);

	private:

		static void createVertexBufferImpl(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);
		static void createConstantBufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

	private:

		static std::unique_ptr<SceneManager>	m_sceneManager;
		static std::unique_ptr<Window>			m_window;
		static std::unique_ptr<DX3DBaseObjects> m_dx3dBaseObjects;
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template<class SceneType, class ...Args>
	inline void DX12GameManager::addScene(unsigned int id, Args ...constructorArgs)
	{
		m_sceneManager->addScene<SceneType>(id, constructorArgs...);
	}

	template<class VertexData>
	inline void DX12GameManager::createVertexBuffer(unsigned int id, const std::vector<VertexData>& vertexDataArray)
	{
		createVertexBufferImpl(id, sizeof(VertexData), vertexDataArray.size(), vertexDataArray.data());
	}

	template<class ConstantBufferDataType>
	inline void DX12GameManager::createConstantBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData)
	{
		createConstantBufferImpl(id, sizeof(ConstantBufferDataType), &rawConstantBufferData);
	}
}
#endif // !DX12_GAME_MANAGER_H_