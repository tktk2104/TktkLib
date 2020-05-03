#ifndef DX12_GAME_MANAGER_H_
#define DX12_GAME_MANAGER_H_

#include <string>
#include <vector>
#include <forward_list>
#include <memory>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkDX12Wrapper/Graphics/Window/WindowInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/_DX3DBaseObjects/DX3DBaseObjectsInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/GraphicsPipeLineState/RootSignature/RootSignatureInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/GraphicsPipeLineState/GraphicsPipeLineStateInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/DescriptorHeap/DescriptorHeapParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/DescriptorHeap/BasicDescriptorHeap/BasicDescriptorHeapInitParam.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/DescriptorHeap/BufferResource/TextureBuffer/TextureBufferInitParam.h>
#include "../Scene/SceneManager.h"
#include "../GameObject/GameObjectPtr.h"
#include "../Component/ComponentManager.h"
#include "../Sprite/SpriteMaterialInitParam.h"

namespace tktk
{
	class GameObjectManager;
	class Window;
	class DX3DBaseObjects;
	class Sprite;

	class DX12GameManager
	{
	public:

		static void initialize(unsigned int sceneNum, const DX3DBaseObjectsInitParam& dx3dInitParam, const WindowInitParam& windowInitParam, const std::string& tktkLibResFolderPath = "");
		static void run();

	public:

		// �E�B���h�E�T�C�Y���擾����
		static const tktkMath::Vector2& getWindowSize();

	public:

		template<class SceneType, class... Args>
		static void addScene(unsigned int id, Args... constructorArgs);

		static void enableScene(unsigned int id);

		static void disableScene(unsigned int id);

	public:

		static GameObjectPtr createGameObject();
		
		static GameObjectPtr findGameObjectWithTag(int tag);
		
		static std::forward_list<GameObjectPtr> findGameObjectWithTags(int tag);

	public:

		// �R���|�[�l���g�̌^���Ƃ̍X�V�D��x��ݒ肷��
		// ���f�t�H���g�i0.0f�j�Œl�����������A�������s�����
		template <class ComponentType>
		static void addUpdatePriority(float priority);

		static void addCollisionGroup(int firstGroup, int secondGroup);

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		template <class ComponentType, class... Args>
		static std::weak_ptr<ComponentType> createComponent(Args... args);

	public:

		// �R�}���h���X�g���蓮�Ŏ��s����
		static void executeCommandList();

		static void setBackGroundColor(const tktkMath::Color& backGroundColor);

		static void setBackBufferRenderTarget();

		static void setViewport(unsigned int id);

		static void setScissorRect(unsigned int id);

		static void setGraphicsPipeLineState(unsigned int id);

		static void setVertexBuffer(unsigned int id);

		static void setIndexBuffer(unsigned int id);

		static void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray);

		static void setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology);

		static void drawIndexedInstanced(
			unsigned int indexCountPerInstance,
			unsigned int instanceCount,
			unsigned int startIndexLocation,
			unsigned int baseVertexLocation,
			unsigned int startInstanceLocation
		);

	public: /* ����DX12�̃��\�[�X����� */

		// ���[�g�V�O�l�`�������
		static void createRootSignature(unsigned int id, const RootSignatureInitParam& initParam);

		// �O���t�B�b�N�p�C�v���C���X�e�[�g�����
		static void createGraphicsPipeLineState(unsigned int graphicsPipeLineId, const GraphicsPipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath, unsigned int useRootSignatureId);

		// ���_�o�b�t�@�����
		template <class VertexData>
		static void createVertexBuffer(unsigned int id, const std::vector<VertexData>& vertexDataArray);

		// �C���f�b�N�X�o�b�t�@�����
		static void createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices);

		// �萔�o�b�t�@�����
		template <class ConstantBufferDataType>
		static void createConstantBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData);

		// �f�B�X�N���v�^�q�[�v�����
		static void createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam);

		// GPU���D�揈���Ńe�N�X�`�������[�h����
		static void gpuPriorityLoadTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const std::string& texDataPath);

	public: /* ����DX12�̃��\�[�X��ݒ�A�擾���� */

		template <class ConstantBufferDataType>
		static void updateConstantBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData);

		static const tktkMath::Vector3& getTextureSize(unsigned int id);

	public: /* �X�v���C�g�֌W�̏��� */

		static void createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam);

		static void drawSprite(unsigned int spriteMaterialId, const tktkMath::Matrix3& worldMatrix);

	private:

		static void createVertexBufferImpl(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);
		static void createConstantBufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		static void updateConstantBufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

	private:

		static std::unique_ptr<SceneManager>		m_sceneManager;
		static std::unique_ptr<GameObjectManager>	m_gameObjectManager;
		static std::unique_ptr<ComponentManager>	m_componentManager;
		static std::unique_ptr<Window>				m_window;
		static std::unique_ptr<DX3DBaseObjects>		m_dx3dBaseObjects;
		static std::unique_ptr<Sprite>				m_sprite;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class SceneType, class ...Args>
	inline void DX12GameManager::addScene(unsigned int id, Args ...constructorArgs)
	{
		m_sceneManager->addScene<SceneType>(id, constructorArgs...);
	}

	template<class ComponentType>
	inline void DX12GameManager::addUpdatePriority(float priority)
	{
		m_componentManager->addUpdatePriority<ComponentType>(priority);
	}

	template<class ComponentType, class ...Args>
	inline std::weak_ptr<ComponentType> DX12GameManager::createComponent(Args ...args)
	{
		return m_componentManager->createComponent<ComponentType>(args...);
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

	template<class ConstantBufferDataType>
	inline void DX12GameManager::updateConstantBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData)
	{
		updateConstantBufferImpl(id, sizeof(ConstantBufferDataType), &rawConstantBufferData);
	}
}
#endif // !DX12_GAME_MANAGER_H_