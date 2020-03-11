#ifndef POINT_LIGHT_MAKER_H_
#define POINT_LIGHT_MAKER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "PointLight.h"

namespace tktk
{
	class PointLightMaker
	{
	public:

		// インスタンス作成開始
		static PointLightMaker& makeStart(GameObjectPtr user);

	private:

		// 自身のポインタ
		static PointLightMaker m_self;

	private:

		// プライベートコンストラクタ達
		PointLightMaker() = default;
		PointLightMaker(const PointLightMaker& other) = default;
		PointLightMaker& operator = (const PointLightMaker& other) = default;

	public:

		// 作成する
		CfpPtr<PointLight> create();

		// 作成するライトのIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		PointLightMaker& lightId(IdType value)
		{
			return lightIdImpl(static_cast<int>(value));
		}
		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		PointLightMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }

		// 環境光の色を設定する
		PointLightMaker& ambientColor(const Color& value);

		// 拡散反射光の色を設定する
		PointLightMaker& diffuseColor(const Color& value);

		// 鏡面反射光の色を取得する
		PointLightMaker& specularColor(const Color& value);

	private:

		// 各種id指定系の関数の実装
		PointLightMaker& lightIdImpl(int value);

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		int m_lightId{ 0 };
		Color m_ambientColor{ Color(0.3f, 0.3f, 0.3f, 1.0f) };
		Color m_diffuseColor{ Color::white };
		Color m_specularColor{ Color::white };
	};
}
#endif // !POINT_LIGHT_MAKER_H_