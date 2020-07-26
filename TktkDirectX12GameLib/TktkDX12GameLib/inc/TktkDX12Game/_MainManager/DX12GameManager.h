#ifndef DX12_GAME_MANAGER_H_
#define DX12_GAME_MANAGER_H_

#include <string>
#include <vector>
#include <forward_list>
#include <memory>
#include <utility>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>

#include "../Component/ComponentManager.h"			// �e���v���[�g�����Ɍ^����n���K�v������׉B���ł��Ȃ�
#include "../DXGameResource/Scene/SceneVTable.h"	// �V�[���}�l�[�W���[�N���X���B������ׂɃe���v���[�g�֘A�̂ݕ���

// �֐��Ăяo���ɕK�v�Ȍ^�̃C���N���[�h
#include <TktkDX12Wrapper/Resource/_SystemResourceIdGetter/SystemResourceType.h>
#include "../GameObject/GameObjectPtr.h"			
#include "../EventMessage/MessageAttachment.h"

#include "DX12GameManagerUseInitParams.h"
#include "DX12GameManagerFuncInOutValueType.h"
#include "DX12GameManagerInitParam.h"

namespace tktk
{
	// �O���錾
	class Window;
	class DX3DBaseObjects;
	class GameObjectManager;
	class DXGameResource;
	class DirectInputWrapper;
	class Mouse;

	class DX12GameManager
	{
	public: /* ���̃}�l�[�W���[���̂̏��� */

		// ������
		static void initialize(const DX12GameManagerInitParam& initParam);

		// ���s
		static void run();

	public: /* �E�B���h�E�̏��� */

		// �E�B���h�E�T�C�Y���擾����
		static const tktkMath::Vector2& getWindowSize();

	public: /* �V�[���̏��� */

		// �V�[�����쐬���Ēǉ�����
		template<class SceneType, class... Args>
		static void addScene(unsigned int id, Args&&... constructorArgs);

		// �V�[����L���ɂ���
		static void enableScene(unsigned int id);

		// �V�[���𖳌��ɂ���
		static void disableScene(unsigned int id);

	public: /* �Q�[���I�u�W�F�N�g�̏��� */

		// �S�Ă�GameObject�Ƀ��b�Z�[�W�𑗐M����
		static void SendMessageAll(unsigned int messageId, const MessageAttachment& value = {});

		// �Q�[���I�u�W�F�N�g���쐬���A���̃|�C���^��Ԃ�
		static GameObjectPtr createGameObject();
		
		// �����̃^�O���������Q�[���I�u�W�F�N�g���擾����
		// �������Y���I�u�W�F�N�g���������ꍇ�A�ŏ��Ɍ������P���擾����
		static GameObjectPtr findGameObjectWithTag(int tag);
		
		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�Ď擾����
		static std::forward_list<GameObjectPtr> findGameObjectsWithTag(int tag);

	public: /* �R���|�[�l���g�̏��� */

		// �R���|�[�l���g�̌^���Ƃ̍X�V�D��x��ݒ肷��
		// ���f�t�H���g�i0.0f�j�Œl�����������A�������s�����
		template <class ComponentType>
		static void addUpdatePriority(float priority);

		// �Փ˔���̑g�ݍ��킹��ǉ�����
		static void addCollisionGroup(int firstGroup, int secondGroup);

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		template <class ComponentType, class... Args>
		static std::weak_ptr<ComponentType> createComponent(Args&&... args);

	public: /* ����DX12�̏������Ă� */

		// �R�}���h���X�g���蓮�Ŏ��s����
		static void executeCommandList();

		// �w�i�F��ݒ肷��
		static void setBackGroundColor(const tktkMath::Color& backGroundColor);

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���R�}���h���X�g�ɐݒ肷��
		static void setRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// �w��́i�����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V���r���[�j�p�̃f�B�X�N���v�^�q�[�v�Q���R�}���h���X�g�ɐݒ肷��
		static void setRtvAndDsv(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// �w��̐[�x�X�e���V���r���[�p�̃f�B�X�N���v�^�q�[�v���R�}���h���X�g�ɐݒ肷��i�������_�[�^�[�Q�b�g�͐ݒ�ł��Ȃ��j
		static void setOnlyDsv(unsigned int dsvDescriptorHeapId);

		// �o�b�N�o�b�t�@�[��ݒ肷��
		static void setBackBufferView();

		// �o�b�N�o�b�t�@�[�Ɛ[�x�X�e���V���r���[��ݒ肷��
		static void setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapId);

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���g�p���Ă��郌���_�[�^�[�Q�b�g�o�b�t�@�̏������݌㏈�����s��
		static void unSetRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// �w��̐[�x�������ݗp�̃f�B�X�N���v�^�q�[�v���g�p���Ă���[�x�o�b�t�@�̏������݌㏈�����s��
		static void unSetDsv(unsigned int dsvDescriptorHeapId);

		// �w��̃r���[�|�[�g���R�}���h���X�g�ɐݒ肷��
		static void setViewport(unsigned int id);

		// �w��̃V�U�[��`���R�}���h���X�g�ɐݒ肷��
		static void setScissorRect(unsigned int id);

		// �w��̃p�C�v���C���X�e�[�g���R�}���h���X�g�ɐݒ肷��
		static void setPipeLineState(unsigned int id);

		// �w��̒��_�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		static void setVertexBuffer(unsigned int id);

		// �w��̃C���f�b�N�X�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		static void setIndexBuffer(unsigned int id);

		// �w��̃f�B�X�N���v�^�q�[�v�̔z����R�}���h���X�g�ɐݒ肷��
		static void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray);

		// �v���~�e�B�u�g�|���W��ݒ肷��
		static void setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology);

		// �C���f�b�N�X���g�p���ăC���X�^���X�`����s��
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
		static void createCBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData);

		// �����_�[�^�[�Q�b�g�o�b�t�@�����
		static void createRtBuffer(unsigned int id, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// �[�x�X�e���V���o�b�t�@�����
		static void createDsBuffer(unsigned int id, const DepthStencilBufferInitParam& initParam);

		// �f�B�X�N���v�^�q�[�v�����
		static void createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam);

		// �����_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�����
		static void createRtvDescriptorHeap(unsigned int id, const RtvDescriptorHeapInitParam& initParam);

		// �[�x�X�e���V���f�B�X�N���v�^�q�[�v�����
		static void createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam);

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`�������
		static void cpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g���ăe�N�X�`�������i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		static void gpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`�������[�h����
		static void cpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);

		// �R�}���h���X�g���g���ăe�N�X�`�������[�h����i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		static void gpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);
		
	public: /* ����DX12�̃��\�[�X��ݒ�A�擾���� */

		// �w��̒萔�o�b�t�@���X�V����
		template <class ConstantBufferDataType>
		static void updateCBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData);

		// �w��̃����_�[�^�[�Q�b�g�r���[���w��̐F�ŃN���A����
		static void clearRtv(unsigned int id, unsigned int rtvLocationIndex, const tktkMath::Color& color);

		// �w��̃e�N�X�`���̃T�C�Y���擾����i�s�N�Z���i�e�N�Z���j�j
		static const tktkMath::Vector3& getTextureBufferSizePx(unsigned int id);
		static const tktkMath::Vector2& getDsBufferSizePx(unsigned int id);
		static const tktkMath::Vector2& getRtBufferSizePx(unsigned int id);

	public: /* �X�v���C�g�֌W�̏��� */

		// �X�v���C�g�}�e���A�������
		static void createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam);

		// �w�肵���X�v���C�g��`�悷��
		static void drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs);

	public: /* ���b�V���֌W�̏��� */

		// �ʏ탁�b�V�������
		static void createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam);

		// �ʏ탁�b�V���}�e���A�������
		static void createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam);

		// �w��̒ʏ탁�b�V���ŃV���h�E�}�b�v����������
		static void writeBasicMeshShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData);

		// �w��̒ʏ탁�b�V���̃}�e���A�������O���t�B�b�N�p�C�v���C���ɐݒ肷��
		static void setMaterialData(unsigned int id);

		// �w��̒ʏ탁�b�V����`�悷��
		static void drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);

		// pmd�t�@�C�������[�h���ăQ�[���̊e�탊�\�[�X�N���X�����
		static BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

	public: /* �X�P���g���֘A�̏��� */

		// �X�P���g�����쐬����
		static void createSkeleton(unsigned int id, const SkeletonInitParam& initParam);

		// �w��̃X�P���g�����g���č������Ǘ�����萔�o�b�t�@���X�V����
		static void updateBoneMatrixCbuffer(unsigned int id);

	public: /* ���[�V�����֌W�̏��� */

		// vmd�t�@�C����ǂݍ���ŁuMotionData�v�̃C���X�^���X�����
		static void loadMotion(unsigned int id, const std::string& motionFileName);

		// �w��̃t���[���̃��[�V���������g�p���ăX�P���g�����X�V����
		static void updateMotion(unsigned int skeletonId, unsigned int motionId, unsigned int curFrame);

	public: /* �|�X�g�G�t�F�N�g�֌W�̏��� */

		// �|�X�g�G�t�F�N�g�̃}�e���A�������
		static void createPostEffectMaterial(unsigned int id, const PostEffectMaterialInitParam& initParam);

		// �w��̃|�X�g�G�t�F�N�g��`�悷��
		static void drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs);

	public: /* �J�����֌W�̏��� */

		// �J���������
		static void createCamera(unsigned int id);

		// �w��̃J�����̃r���[�s����擾����
		static const tktkMath::Matrix4& getViewMatrix(unsigned int cameraId);

		// �w��̃J�����̃r���[�s���ݒ肷��
		static void setViewMatrix(unsigned int cameraId, const tktkMath::Matrix4& view);

		// �w��̃J�����̃v���W�F�N�V�����s����擾����
		static const tktkMath::Matrix4& getProjectionMatrix(unsigned int cameraId);

		// �w��̃J�����̃v���W�F�N�V�����s���ݒ肷��
		static void setProjectionMatrix(unsigned int cameraId, const tktkMath::Matrix4& projection);

	public: /* ���C�g�֌W�̏��� */

		// ���C�g�����
		static void createLight(
			unsigned int id,
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ���C�g���̒萔�o�b�t�@���X�V����
		static void updateLightCBuffer(unsigned int id);

		// �w��̃��C�g�̊�����ݒ肷��
		static void setLightAmbient(unsigned int id, const tktkMath::Color& ambient);

		// �w��̃��C�g�̊g�U���ˌ���ݒ肷��
		static void setLightDiffuse(unsigned int id, const tktkMath::Color& diffuse);

		// �w��̃��C�g�̋��ʔ��ˌ���ݒ肷��
		static void setLightSpeqular(unsigned int id, const tktkMath::Color& speqular);

		// �w��̃��C�g�̍��W��ݒ肷��
		static void setLightPosition(unsigned int id, const tktkMath::Vector3& position);

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

	public: /* �Q�[���p�b�h���͊֌W�̏��� */

		// ���X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		static tktkMath::Vector2 getLstick();

		// �E�X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		static tktkMath::Vector2 getRstick();

		// �w��̃{�^����������Ă��邩�𔻒�
		static bool isPush(GamePadBtnType btnType);

		// �w��̃{�^����������n�߂����𔻒�
		static bool isTrigger(GamePadBtnType btnType);

	public: /* �f�t�H���g�̃��\�[�X���g�����߂�ID���擾���� */

		static unsigned int getSystemId(SystemViewportType type);
		static unsigned int getSystemId(SystemScissorRectType type);
		static unsigned int getSystemId(SystemVertexBufferType type);
		static unsigned int getSystemId(SystemIndexBufferType type);
		static unsigned int getSystemId(SystemCBufferType type);
		static unsigned int getSystemId(SystemTextureBufferType type);
		static unsigned int getSystemId(SystemDsBufferType type);
		static unsigned int getSystemId(SystemBasicDescriptorHeapType type);
		static unsigned int getSystemId(SystemRtvDescriptorHeapType type);
		static unsigned int getSystemId(SystemDsvDescriptorHeapType type);
		static unsigned int getSystemId(SystemRootSignatureType type);
		static unsigned int getSystemId(SystemPipeLineStateType type);

	private: /* ������ */

		static void createSceneImpl(unsigned int id, const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr);
		static void createVertexBufferImpl(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);
		static void createConstantBufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);
		static void updateConstantBufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

	private:
		static std::unique_ptr<Window>				m_window;
		static std::unique_ptr<DX3DBaseObjects>		m_dx3dBaseObjects;
		static std::unique_ptr<GameObjectManager>	m_gameObjectManager;
		static std::unique_ptr<ComponentManager>	m_componentManager;
		static std::unique_ptr<DXGameResource>		m_dxGameResource;
		static std::unique_ptr<DirectInputWrapper>	m_directInputWrapper;

		static std::unique_ptr<Mouse>				m_mouse;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class SceneType, class ...Args>
	inline void DX12GameManager::addScene(unsigned int id, Args&&...constructorArgs)
	{
		createSceneImpl(id, std::make_shared<SceneType>(std::forward<Args>(constructorArgs)...), &SceneVTableInitializer<SceneType>::m_vtable);
	}

	template<class ComponentType>
	inline void DX12GameManager::addUpdatePriority(float priority)
	{
		m_componentManager->addUpdatePriority<ComponentType>(priority);
	}

	template<class ComponentType, class ...Args>
	inline std::weak_ptr<ComponentType> DX12GameManager::createComponent(Args&&...args)
	{
		return m_componentManager->createComponent<ComponentType>(std::forward<Args>(args)...);
	}

	template<class VertexData>
	inline void DX12GameManager::createVertexBuffer(unsigned int id, const std::vector<VertexData>& vertexDataArray)
	{
		createVertexBufferImpl(id, sizeof(VertexData), vertexDataArray.size(), vertexDataArray.data());
	}

	template<class ConstantBufferDataType>
	inline void DX12GameManager::createCBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData)
	{
		createConstantBufferImpl(id, sizeof(ConstantBufferDataType), &rawConstantBufferData);
	}

	template<class ConstantBufferDataType>
	inline void DX12GameManager::updateCBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData)
	{
		updateConstantBufferImpl(id, sizeof(ConstantBufferDataType), &rawConstantBufferData);
	}
}
#endif // !DX12_GAME_MANAGER_H_