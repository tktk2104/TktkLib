#ifndef DX_GAME_RESOURCE_H_
#define DX_GAME_RESOURCE_H_

#include "DXGameResourceInitParam.h"
#include "PostEffect/PostEffectMaterial.h"
#include "Sprite/SpriteMaterial.h"
#include "Mesh/BasicMesh/Mesh/BasicMesh.h"
#include "Mesh/BasicMesh/Material/BasicMeshMaterial.h"
#include "Mesh/BasicMesh/Loader/BasicMeshLoadPmdArgs.h"
#include "Mesh/BasicMesh/Loader/BasicMeshLoadPmdReturnValue.h"
#include "Mesh/Skeleton/Skeleton.h"
#include "Mesh/Motion/Motion.h"

namespace tktk
{
	class DXGameResource
	{
	public:

		DXGameResource(const DXGameResourceInitParam& initParam);
		~DXGameResource() = default;

	public: /* �X�v���C�g�֌W�̏��� */

		void createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam);

		void drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs);

	public: /* ���b�V���֌W�̏��� */

		void createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam);

		void createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam);

		void writeBasicMeshShadowMap(unsigned int id, const MeshWriteShadowFuncBaseArgs& baseArgs);

		void setMaterialData(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);

		void drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);

		BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

	public: /* �X�P���g���֘A�̏��� */

		void createSkeleton(unsigned int id, const SkeletonInitParam& initParam);

		void updateBoneMatrixCbuffer(unsigned int id);

	public: /* ���[�V�����֌W�̏��� */

		void loadMotion(unsigned int id, const std::string& motionFileName);

		void updateMotion(unsigned int skeletonId, unsigned int motionId, unsigned int curFrame);

	public: /* �|�X�g�G�t�F�N�g�֌W�̏��� */

		void createPostEffectMaterial(unsigned int id, const PostEffectMaterialInitParam& initParam);

		void drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		SpriteMaterial		m_spriteMaterial;
		Skeleton			m_skeleton;
		BasicMesh			m_basicMesh;
		BasicMeshMaterial	m_basicMeshMaterial;
		Motion				m_motion;
		PostEffectMaterial	m_postEffectMaterial;
	};
}
#endif // !DX_GAME_RESOURCE_H_
