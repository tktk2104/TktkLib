#ifndef SIMPLE_CAMERA_MAKER_H_
#define SIMPLE_CAMERA_MAKER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "SimpleCamera.h"

namespace tktk
{
	class SimpleCameraMaker
	{
	public:

		// インスタンス作成開始
		static SimpleCameraMaker& makeStart(GameObjectPtr user);

	private:

		// 自身のポインタ
		static SimpleCameraMaker m_self;

	private:

		// プライベートコンストラクタ達
		SimpleCameraMaker() = default;
		SimpleCameraMaker(const SimpleCameraMaker& other) = default;
		SimpleCameraMaker& operator = (const SimpleCameraMaker& other) = default;

	public:

		// 作成する
		CfpPtr<SimpleCamera> create();

		// 作成するカメラのIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		SimpleCameraMaker& cameraId(IdType value)
		{
			return cameraIdImpl(static_cast<int>(value));
		}
		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SimpleCameraMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		// カメラの射角を設定する
		SimpleCameraMaker& cameraFov(float value);

		// カメラのニアクリップを設定する
		SimpleCameraMaker& cameraNear(float value);

		// カメラのファークリップを設定する
		SimpleCameraMaker& cameraFar(float value);

	private:

		// 各種id指定系の関数の実装
		SimpleCameraMaker& cameraIdImpl(int value);

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		int m_cameraId{ 0 };
		float m_cameraFov{ 45.0f };
		float m_cameraNear{ 0.01f };
		float m_cameraFar{ 1000.0f };
	};
}
#endif // !SIMPLE_CAMERA_MAKER_H_