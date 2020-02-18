#ifndef MESH_DRAWER_MAKER_H_
#define MESH_DRAWER_MAKER_H_

#include <memory>
#include "MeshDrawer.h"

namespace tktk
{
	class MeshDrawerMaker
	{
	public:

		// インスタンス作成開始
		static MeshDrawerMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<MeshDrawer> create();

		// 描画優先度
		MeshDrawerMaker& drawPriority(float value);

		// 表示するメッシュのId
		MeshDrawerMaker& meshID(int value);

		// 表示するメッシュのローカル座標
		MeshDrawerMaker& meshLocalPos(const Vector3& value);

		// 表示するメッシュのローカル回転
		MeshDrawerMaker& meshLocalRotation(const Quaternion& value);

		// 表示するメッシュのローカルスケール
		MeshDrawerMaker& meshLocalScale(const Vector3& value);

		// 描画のブレンド方法の種類
		MeshDrawerMaker& blendMode(BlendMode value);

		// 描画のブレンドに使用する値
		MeshDrawerMaker& blendParam(float value);

		// ライトを使用して描画を行うか？
		MeshDrawerMaker& useLight(bool value);

		// Zバッファを使用して描画を行うか?
		MeshDrawerMaker& writeZBuffer(bool value);

		// 描画するレンダーターゲットを設定する
		MeshDrawerMaker& renderTargetId(int value);

		// 影を生成するかを設定
		MeshDrawerMaker& createShadow(bool value);

		// 影の生成を行うコンポーネントの描画優先度を設定
		MeshDrawerMaker& shadowCreatorPriority(float value);

	private:

		// 自身のポインタ
		static MeshDrawerMaker m_self;

	private:

		float m_drawPriority{ 0.0f };
		int m_meshID{ -1 };
		Vector3 m_meshLocalPos{ Vector3::zero };
		Quaternion m_meshLocalRotation{ Quaternion::createFromEulerAngle(Vector3(0.0f, 180.0f, 0.0f)) };
		Vector3 m_meshLocalScale{ Vector3::one };
		BlendMode m_blendMode{ BlendMode::None };
		float m_blendParam{ 1.0f };
		bool m_useLight{ true };
		bool m_writeZBuffer{ true };
		int m_renderTargetId{ -1 };
		bool m_createShadow{ false };
		float m_shadowCreatorPriority{ 100 };
	};
}
#endif // !MESH_DRAWER_MAKER_H_