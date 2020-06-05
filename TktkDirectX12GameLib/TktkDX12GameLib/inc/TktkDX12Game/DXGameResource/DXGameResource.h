#ifndef DX_GAME_RESOURCE_H_
#define DX_GAME_RESOURCE_H_

#include "DXGameResourceInitParam.h"
#include "PostEffect/PostEffectMaterial.h"
#include "Sprite/SpriteMaterial.h"
#include "Mesh/BasicMesh/Mesh/BasicMesh.h"
#include "Mesh/BasicMesh/Material/BasicMeshMaterial.h"
#include "Mesh/BasicMesh/Loader/BasicMeshLoadPmdArgs.h"
#include "Mesh/BasicMesh/Loader/BasicMeshLoadPmdReturnValue.h"

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

		void drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);

		void drawBasicMeshMaterial(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs, const MeshMaterialDrawFuncArgs& materialArgs);

		BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

	public: /* ポストエフェクト関係の処理 */

		void createPostEffectMaterial(unsigned int id, const PostEffectMaterialInitParam& initParam);

		void drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		SpriteMaterial		m_spriteMaterial;
		BasicMesh			m_basicMesh;
		BasicMeshMaterial	m_basicMeshMaterial;
		PostEffectMaterial	m_postEffectMaterial;
	};
}
#endif // !DX_GAME_RESOURCE_H_
