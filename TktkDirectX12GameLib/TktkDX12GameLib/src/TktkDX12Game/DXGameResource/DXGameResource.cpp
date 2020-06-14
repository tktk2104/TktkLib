#include "TktkDX12Game/DXGameResource/DXGameResource.h"

#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Loader/BasicMeshPmdLoader.h"

namespace tktk
{
	DXGameResource::DXGameResource(const DXGameResourceInitParam& initParam)
		: m_spriteMaterial(initParam.spriteShaderFilePaths, initParam.spriteNum)
		, m_basicMesh(initParam.writeShadowMapVsFilePath, initParam.basicMeshNum)
		, m_basicMeshMaterial(initParam.basicMeshShaderFilePaths, initParam.basicMeshMaterialNum)
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

	void DXGameResource::writeBasicMeshShadowMap(unsigned int id, const MeshWriteShadowFuncBaseArgs& baseArgs)
	{
		m_basicMesh.writeShadowMap(id, baseArgs);
	}

	void DXGameResource::drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs)
	{
		m_basicMesh.drawMesh(id, baseArgs);
	}

	void DXGameResource::drawBasicMeshMaterial(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs, const MeshMaterialDrawFuncArgs& materialArgs)
	{
		m_basicMeshMaterial.drawUseMaterial(id, baseArgs, materialArgs);
	}

	BasicMeshLoadPmdReturnValue DXGameResource::loadPmd(const BasicMeshLoadPmdArgs& args)
	{
		return BasicMeshPmdLoader::loadPmd(args);
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