#ifndef SPHERE_MESH_WIRE_FRAME_DRAWER_MAKER_H_
#define SPHERE_MESH_WIRE_FRAME_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "SphereMeshWireFrameDrawer.h"

namespace tktk
{
	// 「SphereMeshWireFrameDrawer」を作るヘルパークラス
	class SphereMeshWireFrameDrawerMaker
	{
	private: /* プライベートコンストラクタ達 */

		SphereMeshWireFrameDrawerMaker() = default;
		SphereMeshWireFrameDrawerMaker(const SphereMeshWireFrameDrawerMaker& other) = default;
		SphereMeshWireFrameDrawerMaker& operator = (const SphereMeshWireFrameDrawerMaker& other) = default;

	public:

		// 作成開始
		static SphereMeshWireFrameDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<SphereMeshWireFrameDrawer> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		SphereMeshWireFrameDrawerMaker& drawPriority(float value);

		// 半径を設定する
		SphereMeshWireFrameDrawerMaker& radius(float value);

		// 描画色を設定する
		SphereMeshWireFrameDrawerMaker& albedoColor(const tktkMath::Color & value);

		// 使用するレンダーターゲットのディスクリプタヒープIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& useRtvDescriptorHeapId(IdType value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& cameraId(IdType value);

		// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& shadowMapCameraId(IdType value);

		// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& lightId(IdType value);

	private: /* 各種id指定系の関数の実装 */

		SphereMeshWireFrameDrawerMaker& useRtvDescriptorHeapIdImpl(unsigned int value);
		SphereMeshWireFrameDrawerMaker& cameraIdImpl(unsigned int value);
		SphereMeshWireFrameDrawerMaker& shadowMapCameraIdImpl(unsigned int value);
		SphereMeshWireFrameDrawerMaker& lightIdImpl(unsigned int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static SphereMeshWireFrameDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr	m_user{  };
		float			m_drawPriority{ 0.0f };
		float			m_radius{ 0.5f };
		tktkMath::Color	m_albedoColor{ tktkMath::colorWhite };
		unsigned int	m_useRtvDescriptorHeapId{  };		// ※初期パラメータはバックバッファー
		unsigned int	m_cameraId{ 0U };
		unsigned int	m_shadowMapCameraId{ 0U };
		unsigned int	m_lightId{ 0U };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& useRtvDescriptorHeapId(IdType value) { static_assert(false, "RtvDescriptorHeapId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshWireFrameDrawerMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 使用するレンダーターゲットのディスクリプタヒープIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::useRtvDescriptorHeapId(IdType value)
	{
		return useRtvDescriptorHeapIdImpl(static_cast<unsigned int>(value));
	}

	// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::cameraId(IdType value)
	{
		return cameraIdImpl(static_cast<unsigned int>(value));
	}

	// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::shadowMapCameraId(IdType value)
	{
		return shadowMapCameraIdImpl(static_cast<unsigned int>(value));
	}

	// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::lightId(IdType value)
	{
		return lightIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !SPHERE_MESH_WIRE_FRAME_DRAWER_MAKER_H_