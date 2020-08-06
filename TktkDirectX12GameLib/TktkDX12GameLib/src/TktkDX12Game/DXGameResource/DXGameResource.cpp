#include "TktkDX12Game/DXGameResource/DXGameResource.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Loader/BasicMeshPmdLoader.h"

namespace tktk
{
	DXGameResource::DXGameResource(const DXGameResourceNum& resourceNum, const DXGameBaseShaderFilePaths& filePaths)
		: m_sceneManager(resourceNum.sceneNum)
		, m_sound(resourceNum.soundNum)
		, m_spriteMaterial(filePaths.spriteShaderFilePaths, resourceNum.spriteNum)
		, m_line2D(filePaths.line2DShaderFilePaths)
		, m_skeleton(resourceNum.skeletonNum) // �����b�V���N���X�̏������Ƀ{�[���s��萔�o�b�t�@���K�v�Ȃ̂Ő�ɃR���X�g���N�g����K�v������
		, m_basicMesh(filePaths.writeShadowMapVsFilePath, resourceNum.basicMeshNum)
		, m_basicMeshMaterial(filePaths.basicMeshShaderFilePaths, resourceNum.basicMeshMaterialNum)
		, m_motion(resourceNum.motionNum)
		, m_postEffectMaterial(filePaths.postEffectShaderFilePaths, resourceNum.postEffectMaterialNum)
		, m_camera(resourceNum.cameraNum)
		, m_light(resourceNum.lightNum)
	{
	}

	void DXGameResource::createScene(unsigned int id, const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr)
	{
		m_sceneManager.create(id, scenePtr, vtablePtr);
	}

	void DXGameResource::enableScene(unsigned int id)
	{
		m_sceneManager.enable(id);
	}

	void DXGameResource::disableScene(unsigned int id)
	{
		m_sceneManager.disable(id);
	}

	void DXGameResource::updateScene()
	{
		m_sceneManager.update();
	}

	void DXGameResource::updateSound()
	{
		m_sound.update();
	}

	void DXGameResource::clearSound()
	{
		m_sound.clear();
	}

	void DXGameResource::loadSound(unsigned int id, const std::string& fileName)
	{
		m_sound.load(id, fileName);
	}

	void DXGameResource::playSound(unsigned int id, bool loopPlay)
	{
		m_sound.play(id, loopPlay);
	}

	void DXGameResource::stopSound(unsigned int id)
	{
		m_sound.stop(id);
	}

	void DXGameResource::pauseSound(unsigned int id)
	{
		m_sound.pause(id);
	}

	void DXGameResource::setMasterVolume(float volume)
	{
		m_sound.setMasterVolume(volume);
	}

	void DXGameResource::createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam)
	{
		m_spriteMaterial.create(id, initParam);
	}

	void DXGameResource::drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const
	{
		m_spriteMaterial.drawSprite(id, drawFuncArgs);
	}

	void DXGameResource::drawLine(const Line2DDrawFuncArgs& drawFuncArgs) const
	{
		m_line2D.drawLine(drawFuncArgs);
	}

	void DXGameResource::createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam)
	{
		m_basicMesh.craete(id, initParam);
	}

	void DXGameResource::createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam)
	{
		m_basicMeshMaterial.create(id, initParam);
	}

	void DXGameResource::writeBasicMeshShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData) const
	{
		m_basicMesh.writeShadowMap(id, transformBufferData);
	}

	void DXGameResource::setMaterialData(unsigned int id) const
	{
		m_basicMeshMaterial.setMaterialData(id);
	}

	void DXGameResource::drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs) const
	{
		m_basicMesh.drawMesh(id, baseArgs);
	}

	BasicMeshLoadPmdReturnValue DXGameResource::loadPmd(const BasicMeshLoadPmdArgs& args)
	{
		return BasicMeshPmdLoader::loadPmd(args);
	}

	void DXGameResource::createSkeleton(unsigned int id, const SkeletonInitParam& initParam)
	{
		m_skeleton.create(id, initParam);
	}

	void DXGameResource::updateBoneMatrixCbuffer(unsigned int id) const
	{
		m_skeleton.updateBoneMatrixCbuffer(id);
	}

	void DXGameResource::loadMotion(unsigned int id, const std::string& motionFileName)
	{
		m_motion.load(id, motionFileName);
	}

	void DXGameResource::updateMotion(unsigned int skeletonId, unsigned int motionId, unsigned int curFrame)
	{
		m_skeleton.transform(skeletonId, m_motion.calculateBoneTransformMatrices(motionId, curFrame));
	}

	void DXGameResource::createPostEffectMaterial(unsigned int id, const PostEffectMaterialInitParam& initParam)
	{
		m_postEffectMaterial.create(id, initParam);
	}

	void DXGameResource::drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const
	{
		m_postEffectMaterial.drawPostEffect(id, drawFuncArgs);
	}

	void DXGameResource::createCamera(unsigned int id)
	{
		m_camera.create(id);
	}

	const tktkMath::Matrix4& DXGameResource::getViewMatrix(unsigned int cameraId) const
	{
		return m_camera.getViewMatrix(cameraId);
	}

	void DXGameResource::setViewMatrix(unsigned int cameraId, const tktkMath::Matrix4& view)
	{
		m_camera.setViewMatrix(cameraId, view);
	}

	const tktkMath::Matrix4& DXGameResource::getProjectionMatrix(unsigned int cameraId) const
	{
		return m_camera.getProjectionMatrix(cameraId);
	}

	void DXGameResource::setProjectionMatrix(unsigned int cameraId, const tktkMath::Matrix4& projection)
	{
		m_camera.setProjectionMatrix(cameraId, projection);
	}

	void DXGameResource::createLight(unsigned int id, const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular, const tktkMath::Vector3& position)
	{
		m_light.create(id, ambient, diffuse, speqular, position);
	}

	void DXGameResource::updateLightCBuffer(unsigned int id) const
	{
		m_light.updateLightCBuffer(id);
	}

	void DXGameResource::setLightAmbient(unsigned int id, const tktkMath::Color& ambient)
	{
		return m_light.setAmbient(id, ambient);
	}

	void DXGameResource::setLightDiffuse(unsigned int id, const tktkMath::Color& diffuse)
	{
		return m_light.setDiffuse(id, diffuse);
	}

	void DXGameResource::setLightSpeqular(unsigned int id, const tktkMath::Color& speqular)
	{
		return m_light.setSpeqular(id, speqular);
	}

	void DXGameResource::setLightPosition(unsigned int id, const tktkMath::Vector3& position)
	{
		return m_light.setPosition(id, position);
	}
}