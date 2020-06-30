#include "TktkDX12Game/DXGameResource/DXGameResource.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Loader/BasicMeshPmdLoader.h"
#include "TktkDX12Game/DXGameResource/Mesh/MeshTransformCbuffer.h"

namespace tktk
{
	DXGameResource::DXGameResource(const DXGameResourceInitParam& initParam)
		: m_spriteMaterial(initParam.spriteShaderFilePaths, initParam.spriteNum)
		, m_skeleton(initParam.skeletonNum) // ※メッシュクラスの初期化にボーン行列定数バッファが必要なので先にコンストラクトする必要がある
		, m_basicMesh(initParam.writeShadowMapVsFilePath, initParam.basicMeshNum)
		, m_basicMeshMaterial(initParam.basicMeshShaderFilePaths, initParam.basicMeshMaterialNum)
		, m_motion(initParam.motionNum)
		, m_postEffectMaterial(initParam.postEffectShaderFilePaths, initParam.postEffectMaterialNum)
	{
	}

	void DXGameResource::createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam)
	{
		m_spriteMaterial.create(id, initParam);
	}

	void DXGameResource::drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_spriteMaterial.drawSprite(id, drawFuncArgs);
	}

	void DXGameResource::createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam)
	{
		m_basicMesh.craete(id, initParam);
	}

	void DXGameResource::createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam)
	{
		m_basicMeshMaterial.create(id, initParam);
	}

	void DXGameResource::writeBasicMeshShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData)
	{
		m_basicMesh.writeShadowMap(id, transformBufferData);
	}

	void DXGameResource::setMaterialData(unsigned int id)
	{
		m_basicMeshMaterial.setMaterialData(id);
	}

	void DXGameResource::drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs)
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

	void DXGameResource::updateBoneMatrixCbuffer(unsigned int id)
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
}