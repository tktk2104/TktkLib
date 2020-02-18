#ifndef MESH_DRAWER_H_
#define MESH_DRAWER_H_

#include <vector>
#include <unordered_map>
#include <TktkMath/Vector3.h>
#include <TktkMath/Quaternion.h>
#include <TktkMath/Matrix4.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include <TktkDxlib2DWrapper/Graphics/BlendMode.h>
#include "../../../TktkDxlib3DWrapper/Graphics/DxLibDraw3DParam.h"
#include "MeshMaterial.h"

namespace tktk
{
	// メッシュの描画コンポーネント
	// 【前提コンポーネント：Transform3D】
	class MeshDrawer
		: public ComponentBase
	{
	public:

		MeshDrawer(
			const DxLibDraw3DParam& dxLibDraw3DParam,	// DxLibを使った3D描画で使用するパラメータ
			int meshID									// 表示するメッシュのId
		);

	public:

		// <PolymorphismFunc>
		void awake();
		void start();
		void draw() const;

	public:

		// 表示しているメッシュIdを取得
		int getMeshID() const;
		// 表示しているメッシュIdを再設定
		void setMeshID(int meshID);

		// ボーンの総数を取得
		unsigned int getBoneCount() const;

		// 引数で指定したボーンの変換行列を取得
		const Matrix4& getLocalBoneMatrix(int boneIndex);
		// 引数で指定したボーンの変換行列を再設定
		void setLocalBoneMatrix(int boneIndex, const Matrix4& localBoneMatrix);

		// 全てのボーンの変換行列を取得
		const std::vector<Matrix4>& getLocalBoneMatrices() const;
		// 全てのボーンの変換行列を再設定
		void setLocalBoneMatrices(const std::vector<Matrix4>& localBoneMatrices);
		// 全てのボーンの変換行列を再設定
		template <class... Args>
		void setLocalBoneMatrices(Args... localBoneMatrices);

		// メッシュで使用するテクスチャを再設定する
		// （メッシュで使用するテクスチャは「ModelTextureLoader」で読み込みを行う必要があります）
		void setTextureGraphHandle(int materialIndex, int textureId, bool haveAlpha);

		// DxLibを使った3D描画で使用するパラメータを取得
		const DxLibDraw3DParam& getDxLibDraw3DParam() const;

		// 表示するメッシュのローカル行列を再設定
		void setMeshLocalMat(const Matrix4& localMat);
		// 描画のブレンド方法の種類を再設定
		void setBlendMode(BlendMode blendMode);
		// 描画のブレンドに使用する値を再設定
		void setBlendParam(float blendParam);
		// ライトを使用して描画を行うかを再設定
		void setUseLight(bool useLight);
		// Zバッファを使用して描画を行うかを再設定
		void setWriteZBuffer(bool writeZBuffer);
		// 指定したレンダーターゲットに描画する
		void useRenderTarget(int renderTargetId);
		// レンダーターゲットを使用せずに描画する
		void unUseRenderTarget();

	private:

		// 自身の３次元座標コンポーネント
		std::weak_ptr<Transform3D> m_transform3D;

		// 自身のマテリアル情報のコンポーネント
		std::weak_ptr<MeshMaterial> m_meshMaterial;

		// DxLibを使った3D描画で使用するパラメータ
		DxLibDraw3DParam m_dxLibDraw3DParam;

		// 描画するモデルのID
		int m_meshID{ -1 };

		// モデルのボーン毎の行列情報
		std::vector<Matrix4> m_localBoneMatrices;
	};

	template<class ...Args>
	inline void MeshDrawer::setLocalBoneMatrices(Args ...localBoneMatrices)
	{
		setLocalBoneMatrices(std::vector<Matrix4>({ localBoneMatrices... }));
	}
}
#endif // !MESH_DRAWER_H_