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
	// ゲームで使用するリソースを管理するクラス
	class DXGameResource
	{
	public:

		DXGameResource(const DXGameResourceInitParam& initParam);
		~DXGameResource() = default;

	public: /* スプライト関係の処理 */

		// スプライトマテリアルを作る
		void createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam);

		// 指定したスプライトを描画する
		void drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs);

	public: /* メッシュ関係の処理 */

		// 通常メッシュを作る
		void createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam);

		// 通常メッシュマテリアルを作る
		void createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam);

		// 指定の通常メッシュでシャドウマップを書き込む
		void writeBasicMeshShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData);

		// 指定の通常メッシュのマテリアル情報をグラフィックパイプラインに設定する
		void setMaterialData(unsigned int id);

		// 指定の通常メッシュを描画する
		void drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);

		// pmdファイルをロードしてゲームの各種リソースクラスを作る
		BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

	public: /* スケルトン関連の処理 */

		// スケルトンを作成する
		void createSkeleton(unsigned int id, const SkeletonInitParam& initParam);

		// 指定のスケルトンを使って骨情報を管理する定数バッファを更新する
		void updateBoneMatrixCbuffer(unsigned int id);

	public: /* モーション関係の処理 */

		// vmdファイルを読み込んで「MotionData」のインスタンスを作る
		void loadMotion(unsigned int id, const std::string& motionFileName);

		// 指定のフレームのモーション情報を使用してスケルトンを更新する
		// TODO : モーションの補完を実装する
		void updateMotion(unsigned int skeletonId, unsigned int motionId, unsigned int curFrame);

	public: /* ポストエフェクト関係の処理 */

		// ポストエフェクトのマテリアルを作る
		void createPostEffectMaterial(unsigned int id, const PostEffectMaterialInitParam& initParam);

		// 指定のポストエフェクトを描画する
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
