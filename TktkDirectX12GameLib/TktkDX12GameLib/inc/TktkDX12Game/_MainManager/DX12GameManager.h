#ifndef DX12_GAME_MANAGER_H_
#define DX12_GAME_MANAGER_H_

#include <string>
#include <vector>
#include <forward_list>
#include <memory>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include "../Scene/SceneManager.h"
#include "../GameObject/GameObjectPtr.h"
#include "../Component/ComponentManager.h"
#include "DX12GameManagerUseInitParams.h"
#include "DX12GameManagerFuncInOutValueType.h"

namespace tktk
{
	class GameObjectManager;
	class Window;
	class DX3DBaseObjects;
	class DXGameResource;
	class SoundPlayer;
	class Keyboard;
	class Mouse;

	class DX12GameManager
	{
	public: /* ���̃}�l�[�W���[���̂̏��� */

		static void initialize(unsigned int sceneNum, const DX3DBaseObjectsInitParam& dx3dInitParam, const WindowInitParam& windowInitParam, const std::string& tktkLibResFolderPath = "");
		static void run();

	public: /* �E�B���h�E�̏��� */

		// �E�B���h�E�T�C�Y���擾����
		static const tktkMath::Vector2& getWindowSize();

	public: /* �V�[���̏��� */

		template<class SceneType, class... Args>
		static void addScene(unsigned int id, Args... constructorArgs);

		static void enableScene(unsigned int id);

		static void disableScene(unsigned int id);

	public: /* �Q�[���I�u�W�F�N�g�̏��� */

		static GameObjectPtr createGameObject();
		
		static GameObjectPtr findGameObjectWithTag(int tag);
		
		static std::forward_list<GameObjectPtr> findGameObjectWithTags(int tag);

	public: /* �R���|�[�l���g�̏��� */

		// �R���|�[�l���g�̌^���Ƃ̍X�V�D��x��ݒ肷��
		// ���f�t�H���g�i0.0f�j�Œl�����������A�������s�����
		template <class ComponentType>
		static void addUpdatePriority(float priority);

		static void addCollisionGroup(int firstGroup, int secondGroup);

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		template <class ComponentType, class... Args>
		static std::weak_ptr<ComponentType> createComponent(Args... args);

	public: /* ����DX12�̏������Ă� */

		// �R�}���h���X�g���蓮�Ŏ��s����
		static void executeCommandList();

		static void setBackGroundColor(const tktkMath::Color& backGroundColor);

		static void setRenderTarget(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		static void unSetRenderTarget(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		static void unSetDepthStencil(unsigned int dsvDescriptorHeapId);

		static void setRenderTargetAndDepthStencil(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		static void setOnlyDepthStencil(unsigned int dsvDescriptorHeapId);

		static void setBackBuffer();

		static void setBackBufferAndDepthStencil(unsigned int dsvDescriptorHeapId);

		static void setViewport(unsigned int id);

		static void setScissorRect(unsigned int id);

		static void setPipeLineState(unsigned int id);

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

		// �p�C�v���C���X�e�[�g�����
		static void createPipeLineState(unsigned int graphicsPipeLineId, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// ���_�o�b�t�@�����
		template <class VertexData>
		static void createVertexBuffer(unsigned int id, const std::vector<VertexData>& vertexDataArray);

		// �C���f�b�N�X�o�b�t�@�����
		static void createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices);

		// �萔�o�b�t�@�����
		template <class ConstantBufferDataType>
		static void createConstantBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData);

		// �����_�[�^�[�Q�b�g�o�b�t�@�����
		static void createRenderTargetBuffer(unsigned int id, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// �[�x�X�e���V���o�b�t�@�����
		static void createDepthStencilBuffer(unsigned int id, const DepthStencilBufferInitParam& initParam);

		// �f�B�X�N���v�^�q�[�v�����
		static void createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam);

		// �����_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�����
		static void createRtvDescriptorHeap(unsigned int id, const RtvDescriptorHeapInitParam& initParam);

		// �[�x�X�e���V���f�B�X�N���v�^�q�[�v�����
		static void createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam);

		// CPU���D�揈���Ńe�N�X�`�������
		static void cpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// GPU���D�揈���Ńe�N�X�`�������i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		static void gpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// CPU���D�揈���Ńe�N�X�`�������[�h����
		static void cpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);

		// GPU���D�揈���Ńe�N�X�`�������[�h����i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		static void gpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);
		
	public: /* ����DX12�̃��\�[�X��ݒ�A�擾���� */

		template <class ConstantBufferDataType>
		static void updateConstantBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData);

		static void clearRenderTarget(unsigned int id, unsigned int rtvLocationIndex, const tktkMath::Color& color);

		static const tktkMath::Vector3& getTextureSize(unsigned int id);
		static const tktkMath::Vector2& getDepthStencilSize(unsigned int id);
		static const tktkMath::Vector2& getRenderTargetSize(unsigned int id);

	public: /* �X�v���C�g�֌W�̏��� */

		static void createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam);

		static void drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs);

	public: /* ���b�V���֌W�̏��� */

		static void createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam);

		static void createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam);

		static void writeBasicMeshShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData);

		static void setMaterialData(unsigned int id);

		static void drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);

		static BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

	public: /* �X�P���g���֘A�̏��� */

		static void createSkeleton(unsigned int id, const SkeletonInitParam& initParam);

		static void updateBoneMatrixCbuffer(unsigned int id);

	public: /* ���[�V�����֌W�̏��� */

		static void loadMotion(unsigned int id, const std::string& motionFileName);

		static void updateMotion(unsigned int skeletonId, unsigned int motionId, unsigned int curFrame);

	public: /* �|�X�g�G�t�F�N�g�֌W�̏��� */

		static void createPostEffectMaterial(unsigned int id, const PostEffectMaterialInitParam& initParam);

		static void drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs);

	public: /* �T�E���h�֌W�̏��� */

		// �V�����T�E���h��ǂݍ���
		// �����̊֐��œǂݍ��߂�T�E���h�̌`���́u.wav�v�̂�
		static void loadSound(unsigned int id, const std::string& fileName);

		// �w�肵���T�E���h���Đ�����
		static void playSound(unsigned int id, bool loopPlay);

		// �w�肵���T�E���h���~����
		static void stopSound(unsigned int id);

		// �w�肵���T�E���h���ꎞ��~����
		static void pauseSound(unsigned int id);

		// �匳�̉��ʂ�ύX����i0.0f�`1.0f�j
		static void setMasterVolume(float volume);

	public: /* �}�E�X���͊֌W�̏��� */

		// �w��̃{�^����������Ă��邩
		static bool isPush(MouseButtonType buttonType);

		// �w��̃{�^����������n�߂����𔻒�
		static bool isTrigger(MouseButtonType buttonType);

		// �}�E�X�J�[�\���̍��W���擾����
		static tktkMath::Vector2 mousePos();

	public: /* �L�[�{�[�h���͊֌W�̏��� */

		// �w��̃L�[��������Ă��邩�𔻒�
		static bool isPush(KeybordKeyType keyType);

		// �w��̃L�[��������n�߂����𔻒�
		static bool isTrigger(KeybordKeyType keyType);

	public: /* �f�t�H���g�̃��\�[�X���g�����߂�ID���擾���� */

		static unsigned int getSystemId(SystemViewportType type);
		static unsigned int getSystemId(SystemScissorRectType type);
		static unsigned int getSystemId(SystemVertexBufferType type);
		static unsigned int getSystemId(SystemIndexBufferType type);
		static unsigned int getSystemId(SystemConstantBufferType type);
		static unsigned int getSystemId(SystemTextureBufferType type);
		static unsigned int getSystemId(SystemDepthStencilBufferType type);
		static unsigned int getSystemId(SystemBasicDescriptorHeapType type);
		static unsigned int getSystemId(SystemRtvDescriptorHeapType type);
		static unsigned int getSystemId(SystemDsvDescriptorHeapType type);
		static unsigned int getSystemId(SystemRootSignatureType type);
		static unsigned int getSystemId(SystemPipeLineStateType type);

	private: /* ������ */

		static void createVertexBufferImpl(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);
		static void createConstantBufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);
		static void updateConstantBufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

	private:

		static std::unique_ptr<SceneManager>		m_sceneManager;
		static std::unique_ptr<GameObjectManager>	m_gameObjectManager;
		static std::unique_ptr<ComponentManager>	m_componentManager;
		static std::unique_ptr<Window>				m_window;
		static std::unique_ptr<DX3DBaseObjects>		m_dx3dBaseObjects;
		static std::unique_ptr<DXGameResource>		m_dxGameResource;
		static std::unique_ptr<SoundPlayer>			m_soundPlayer;
		static std::unique_ptr<Keyboard>			m_keyboard;
		static std::unique_ptr<Mouse>				m_mouse;
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