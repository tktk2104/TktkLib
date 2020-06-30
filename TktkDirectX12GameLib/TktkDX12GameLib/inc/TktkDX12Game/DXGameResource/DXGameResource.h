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

	public: /* スプライト関係の処理 */

		void createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam);

		void drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs);

	public: /* メッシュ関係の処理 */

		void createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam);

		void createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam);

		void writeBasicMeshShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData);

		void setMaterialData(unsigned int id);

		void drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);

		BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

	public: /* スケルトン関連の処理 */

		void createSkeleton(unsigned int id, const SkeletonInitParam& initParam);

		void updateBoneMatrixCbuffer(unsigned int id);

	public: /* モーション関係の処理 */

		void loadMotion(unsigned int id, const std::string& motionFileName);

		void updateMotion(unsigned int skeletonId, unsigned int motionId, unsigned int curFrame);

	public: /* ポストエフェクト関係の処理 */

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
