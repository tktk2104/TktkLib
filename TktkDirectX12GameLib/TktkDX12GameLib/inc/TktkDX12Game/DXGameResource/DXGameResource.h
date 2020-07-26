#ifndef DX_GAME_RESOURCE_H_
#define DX_GAME_RESOURCE_H_

#include "DXGameResourceNum.h"
#include "DXGameBaseShaderFilePaths.h"

#include "Scene/SceneManager.h"
#include "Sound/Sound.h"
#include "PostEffect/PostEffectMaterial.h"
#include "Sprite/SpriteMaterial.h"
#include "Mesh/BasicMesh/Mesh/BasicMesh.h"
#include "Mesh/BasicMesh/Material/BasicMeshMaterial.h"
#include "Mesh/BasicMesh/Loader/BasicMeshLoadPmdArgs.h"
#include "Mesh/BasicMesh/Loader/BasicMeshLoadPmdReturnValue.h"
#include "Mesh/Skeleton/Skeleton.h"
#include "Mesh/Motion/Motion.h"
#include "Camera/Camera.h"
#include "Light/Light.h"

namespace tktk
{
	// �Q�[���Ŏg�p���郊�\�[�X���Ǘ�����N���X
	class DXGameResource
	{
	public:

		DXGameResource(const DXGameResourceNum& resourceNum, const DXGameBaseShaderFilePaths& filePaths);
		~DXGameResource() = default;

	public: /* �V�[���֌W�̏��� */

		// �V�[�����쐬���Ēǉ�����
		void createScene(unsigned int id, const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr);

		// �V�[����L���ɂ���
		void enableScene(unsigned int id);

		// �V�[���𖳌��ɂ���
		void disableScene(unsigned int id);

		// �L���ɂȂ��Ă���V�[�����X�V����
		void updateScene();

	public: /* �T�E���h�֌W�̏��� */

		// �T�E���h���X�V����
		void updateSound();

		// �ǂݍ��񂾃T�E���h�����ׂč폜����
		void clearSound();

		// �V�����T�E���h��ǂݍ���
		// �����̊֐��œǂݍ��߂�T�E���h�̌`���́u.wav�v�̂�
		void loadSound(unsigned int id, const std::string& fileName);

		// �w�肵���T�E���h���Đ�����
		void playSound(unsigned int id, bool loopPlay);

		// �w�肵���T�E���h���~����
		void stopSound(unsigned int id);

		// �w�肵���T�E���h���ꎞ��~����
		void pauseSound(unsigned int id);

		// �匳�̉��ʂ�ύX����i0.0f�`1.0f�j
		void setMasterVolume(float volume);

	public: /* �X�v���C�g�֌W�̏��� */

		// �X�v���C�g�}�e���A�������
		void createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam);

		// �w�肵���X�v���C�g��`�悷��
		void drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

	public: /* ���b�V���֌W�̏��� */

		// �ʏ탁�b�V�������
		void createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam);

		// �ʏ탁�b�V���}�e���A�������
		void createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam);

		// �w��̒ʏ탁�b�V���ŃV���h�E�}�b�v����������
		void writeBasicMeshShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData) const;

		// �w��̒ʏ탁�b�V���̃}�e���A�������O���t�B�b�N�p�C�v���C���ɐݒ肷��
		void setMaterialData(unsigned int id) const;

		// �w��̒ʏ탁�b�V����`�悷��
		void drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs) const;

		// pmd�t�@�C�������[�h���ăQ�[���̊e�탊�\�[�X�N���X�����
		BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

	public: /* �X�P���g���֘A�̏��� */

		// �X�P���g�����쐬����
		void createSkeleton(unsigned int id, const SkeletonInitParam& initParam);

		// �w��̃X�P���g�����g���č������Ǘ�����萔�o�b�t�@���X�V����
		void updateBoneMatrixCbuffer(unsigned int id) const;

	public: /* ���[�V�����֌W�̏��� */

		// vmd�t�@�C����ǂݍ���ŁuMotionData�v�̃C���X�^���X�����
		void loadMotion(unsigned int id, const std::string& motionFileName);

		// �w��̃t���[���̃��[�V���������g�p���ăX�P���g�����X�V����
		// TODO : ���[�V�����̕⊮����������
		void updateMotion(unsigned int skeletonId, unsigned int motionId, unsigned int curFrame);

	public: /* �|�X�g�G�t�F�N�g�֌W�̏��� */

		// �|�X�g�G�t�F�N�g�̃}�e���A�������
		void createPostEffectMaterial(unsigned int id, const PostEffectMaterialInitParam& initParam);

		// �w��̃|�X�g�G�t�F�N�g��`�悷��
		void drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

	public: /* �J�����֌W�̏��� */

		// �J���������
		void createCamera(unsigned int id);

		// �w��̃J�����̃r���[�s����擾����
		const tktkMath::Matrix4& getViewMatrix(unsigned int cameraId) const;

		// �w��̃J�����̃r���[�s���ݒ肷��
		void setViewMatrix(unsigned int cameraId, const tktkMath::Matrix4& view);

		// �w��̃J�����̃v���W�F�N�V�����s����擾����
		const tktkMath::Matrix4& getProjectionMatrix(unsigned int cameraId) const;

		// �w��̃J�����̃v���W�F�N�V�����s���ݒ肷��
		void setProjectionMatrix(unsigned int cameraId, const tktkMath::Matrix4& projection);

	public: /* ���C�g�֌W�̏��� */

		// ���C�g�����
		void createLight(
			unsigned int id,
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ���C�g���̒萔�o�b�t�@���X�V����
		void updateLightCBuffer(unsigned int id) const;

		// �w��̃��C�g�̊�����ݒ肷��
		void setLightAmbient(unsigned int id, const tktkMath::Color& ambient);

		// �w��̃��C�g�̊g�U���ˌ���ݒ肷��
		void setLightDiffuse(unsigned int id, const tktkMath::Color& diffuse);

		// �w��̃��C�g�̋��ʔ��ˌ���ݒ肷��
		void setLightSpeqular(unsigned int id, const tktkMath::Color& speqular);

		// �w��̃��C�g�̍��W��ݒ肷��
		void setLightPosition(unsigned int id, const tktkMath::Vector3& position);

	private:

		SceneManager		m_sceneManager;
		Sound				m_sound;
		SpriteMaterial		m_spriteMaterial;
		Skeleton			m_skeleton;
		BasicMesh			m_basicMesh;
		BasicMeshMaterial	m_basicMeshMaterial;
		Motion				m_motion;
		PostEffectMaterial	m_postEffectMaterial;
		Camera				m_camera;
		Light				m_light;
	};
}
#endif // !DX_GAME_RESOURCE_H_
