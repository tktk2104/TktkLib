#ifndef COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_
#define COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "ColliderWireFrameDrawer3D.h"

namespace tktk
{
	// 「ColliderWireFrameDrawer3D」のインスタンスを作成するクラス
	class ColliderWireFrameDrawer3DMaker
	{
	private:  /* プライベートコンストラクタ達 */

		ColliderWireFrameDrawer3DMaker() = default;
		ColliderWireFrameDrawer3DMaker(const ColliderWireFrameDrawer3DMaker& other) = default;
		ColliderWireFrameDrawer3DMaker& operator = (const ColliderWireFrameDrawer3DMaker& other) = default;

	public:

		// 作成開始
		static ColliderWireFrameDrawer3DMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<ColliderWireFrameDrawer3D> create();

		// 描画優先度を設定する
		ColliderWireFrameDrawer3DMaker& drawPriority(float value);

		// 使用するレンダーターゲットのディスクリプタヒープIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& useRtvDescriptorHeapId(IdType value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& cameraId(IdType value);

		// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& shadowMapCameraId(IdType value);

		// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& lightId(IdType value);

		// 線の色を設定する
		ColliderWireFrameDrawer3DMaker& lineColor(const tktkMath::Color & value);

	private: /* 各種id指定系の関数の実装 */

		ColliderWireFrameDrawer3DMaker& useRtvDescriptorHeapIdImpl(unsigned int value);
		ColliderWireFrameDrawer3DMaker& cameraIdImpl(unsigned int value);
		ColliderWireFrameDrawer3DMaker& shadowMapCameraIdImpl(unsigned int value);
		ColliderWireFrameDrawer3DMaker& lightIdImpl(unsigned int value);

	private:

		static ColliderWireFrameDrawer3DMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr				m_user{ };
		float						m_drawPriority{ 0.0f };
		unsigned int				m_cameraId{ 0U };
		unsigned int				m_shadowMapCameraId{ 0U };
		unsigned int				m_lightId{ 0U };
		unsigned int				m_useRtvDescriptorHeapId{  };// ※初期パラメータはバックバッファー
		tktkMath::Color				m_lineColor{ tktkMath::colorWhite };
	
	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& useRtvDescriptorHeapId(IdType value) { static_assert(false, "RtvDescriptorHeapId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		ColliderWireFrameDrawer3DMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 使用するレンダーターゲットのディスクリプタヒープIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::useRtvDescriptorHeapId(IdType value)
	{
		return useRtvDescriptorHeapIdImpl(static_cast<unsigned int>(value));
	}

	// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::cameraId(IdType value)
	{
		return cameraIdImpl(static_cast<unsigned int>(value));
	}

	// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::shadowMapCameraId(IdType value)
	{
		return shadowMapCameraIdImpl(static_cast<unsigned int>(value));
	}

	// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::lightId(IdType value)
	{
		return lightIdImpl(static_cast<unsigned int>(value));
	}
}

#endif // !COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_