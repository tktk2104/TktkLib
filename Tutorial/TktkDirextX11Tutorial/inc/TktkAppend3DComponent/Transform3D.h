#ifndef TRANSFORM_3D_H_
#define TRANSFORM_3D_H_

#include <TktkMath/Matrix4.h>
#include <TktkMath/Vector3.h>
#include <TktkMath/Quaternion.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/TraceParentType.h>

namespace tktk
{
	// ３次元の自身の座標、回転、スケールを管理するコンポーネント
	class Transform3D
		: public ComponentBase
	{
	public:

		Transform3D(
			const Vector3& initPosition,	// 初期座標
			const Vector3& initScaleRate,	// 初期スケール
			const Quaternion& initRotation,	// 初期回転
			TraceParentType traceType		// 親のTransform2Dとの関係性の種類
		);

	public:

		// <PolymorphismFunc>
		void start();
		void afterChangeParent(CfpPtr<GameObject> beforParent);

	public:

		// ワールド座標を取得
		const Vector3& getWorldPosition() const;
		// ワールドスケールを取得
		const Vector3& getWorldScaleRate() const;
		// ワールド回転を取得
		const Quaternion& getWorldRotation() const;
		// ワールド回転（オイラー角）を計算
		Vector3 calculateWorldEulerAngles() const;

		// ローカル座標を取得
		const Vector3& getLocalPosition() const;
		// ローカルスケールを取得
		const Vector3& getLocalScaleRate() const;
		// ローカル回転を取得
		const Quaternion& getLocalRotation() const;
		// ローカル回転（オイラー角）を計算
		Vector3 calculateLocalEulerAngles() const;

		// ワールドの行列を計算
		Matrix4 calculateWorldMatrix() const;
		// ローカルの行列を計算
		Matrix4 calculateLocalMatrix() const;

		// ワールド座標を指定分だけ増加
		void addWorldPosition(const Vector3& position);
		// ワールド回転を指定分だけ増加
		void addWorldRotation(const Quaternion& rotation);
		// ワールド回転（オイラー角）を指定分だけ増加
		void addWorldEulerAngles(const Vector3& eulerAngles);

		// ローカル座標を指定分だけ増加
		void addLocalPosition(const Vector3& position);
		// ローカルスケールを指定分だけ増加
		void addLocalScaleRate(const Vector3& scaleRate);
		// ローカル回転を指定分だけ増加
		void addLocalRotation(const Quaternion& rotation);
		// ローカル回転（オイラー角）を指定分だけ増加
		void addLocalEulerAngles(const Vector3& eulerAngles);

		// ワールド座標を設定
		void setWorldPosition(const Vector3& position);
		// ワールド回転を設定
		void setWorldRotation(const Quaternion& rotation);
		// ワールド回転（オイラー角）を設定
		void setWorldEulerAngles(const Vector3& eulerAngles);
		// 「axis」を軸として「degree」度だけ回転したワールド回転を設定
		void setWorldAxisAngle(const Vector3& axis, float degree);

		// ローカル座標を設定
		void setLocalPosition(const Vector3& position);
		// ローカルスケールを設定
		void setLocalScaleRate(const Vector3& scaleRate);
		// ローカル回転を設定
		void setLocalRotation(const Quaternion& rotation);
		// ローカル回転（オイラー角）を設定
		void setLocalEulerAngles(const Vector3& eulerAngles);
		// 「axis」を軸として「degree」度だけ回転したローカル回転を設定
		void setLocalAxisAngle(const Vector3& axis, float degree);

	public:

		// ワールド空間の左手座標系の前方ベクトルを計算（DirectX等）
		Vector3 calculateWorldForwardLH() const;
		// ワールド空間の右手座標系の前方ベクトルを計算（OpenGL等）
		Vector3 calculateWorldForwardRH() const;
		// ワールド空間の右方ベクトルを計算
		Vector3 calculateWorldRight() const;
		// ワールド空間の上方ベクトルを計算
		Vector3 calculateWorldUp() const;

		// ワールド空間の左手座標系の前方ベクトルを計算（DirectX等）
		Vector3 calculateLocalForwardLH() const;
		// ワールド空間の右手座標系の前方ベクトルを計算（OpenGL等）
		Vector3 calculateLocalForwardRH() const;
		// ワールド空間の右方ベクトルを計算
		Vector3 calculateLocalRight() const;
		// ワールド空間の上方ベクトルを計算
		Vector3 calculateLocalUp() const;

		// ワールド空間の左手座標系の前方ベクトルを設定（DirectX等）
		void setWorldForwardLH(const Vector3& forward);
		// ワールド空間の右手座標系の前方ベクトルを設定（OpenGL等）
		void setWorldForwardRH(const Vector3& forward);
		// ワールド空間の右方ベクトルを設定
		void setWorldRight(const Vector3& right);
		// ワールド空間の上方ベクトルを設定
		void setWorldUp(const Vector3& up);

		// ローカル空間の左手座標系の前方ベクトルを設定（DirectX等）
		void setLocalForwardLH(const Vector3& forward);
		// ローカル空間の右手座標系の前方ベクトルを設定（OpenGL等）
		void setLocalForwardRH(const Vector3& forward);
		// ローカル空間の右方ベクトルを設定
		void setLocalRight(const Vector3& right);
		// ローカル空間の上方ベクトルを設定
		void setLocalUp(const Vector3& up);

		// 指定のTransform3Dの方を向くように自身のワールド行列を変換する
		void lookAt(CfpPtr<Transform3D> target, const Vector3& worldUp = Vector3::up);
		// 指定の座標の方を向くように自身のワールド行列を変換する
		void lookAt(const Vector3& target, const Vector3& worldUp = Vector3::up);

		// 指定の座標を中心とした軸で指定した角度だけ回転させる。
		void rotateAround(const Vector3& worldPoint, const Vector3& axis, float angle);

		//// ローカル座標からワールド座標へと変換した行列を取得する
		//Matrix4 calculateLocalToWorldMatrix() const;
		//// ワールド座標からローカル座標へと変換した行列を取得する
		//Matrix4 calculateWorldToLocalMatrix() const;

	private:

		// 引数のTransform3Dを追従するのに使用するワールド行列を計算
		static Matrix4 calculateTraceUseMat(CfpPtr<Transform3D> target, TraceParentType traceType);

		// 引数のTransform3Dを追従するのに使用するスケール値を計算
		static Vector3 calculateTraceUseScale(CfpPtr<Transform3D> target, TraceParentType traceType);

		// 引数のTransform3Dを追従するのに使用する逆スケール値を計算
		static Vector3 calculateTraceUseInvScale(CfpPtr<Transform3D> target, TraceParentType traceType);

	private:

		// 新しいローカル行列を指定して自身のローカルのトランスフォームを更新する
		void updateLocalTransform(const Matrix4& newLocalMat, const Vector3 newLocalScale);

		// 新しいワールド行列を指定して自身のワールドのトランスフォームを更新する
		void updateWorldTransform(const Matrix4& newWorldMat, const Vector3 newWorldScale);

		// 親のTransform3Dを探す
		CfpPtr<Transform3D> findParentTransform3D() const;

		// 全ての子供のTransform3Dを更新する
		void updateAllChildTransform();

		// 指定した子供のTransform3Dを更新する
		void updateChildTransform(CfpPtr<GameObject> child);

		// 親のTransform3Dの追従を開始
		void enableParentTransform(CfpPtr<GameObject> curParent);

		// 親のTransform3Dの追従を終了
		void disableParentTransform(CfpPtr<GameObject> beforParent);

		// 大元のTransformから全ての子供を更新する（生ポインタ版）
		void findAndUpdateRootTransform(Transform3D* curTransform);

		// 大元のTransformから全ての子供を更新する（CfpPtr版）
		void findAndUpdateRootTransform(CfpPtr<Transform3D> curTransform);

	private:

		// ローカルの座標
		Vector3 m_localPosition{ Vector3::zero };
		// ローカルのスケール
		Vector3 m_localScaleRate{ Vector3::one };
		// ローカルの回転
		Quaternion m_localRotation{ Quaternion::identity };

		// ワールドの座標
		Vector3 m_worldPosition{ Vector3::zero };
		// ワールドのスケール
		Vector3 m_worldScaleRate{ Vector3::one };
		// ローカルの回転
		Quaternion m_worldRotation{ Quaternion::identity };

		// 親のTransform3Dとの関係性
		TraceParentType m_traceType;
	};
}
#endif // !TRANSFORM_3D_H_