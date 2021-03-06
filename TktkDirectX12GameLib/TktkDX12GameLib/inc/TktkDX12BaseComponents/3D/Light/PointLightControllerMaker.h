#ifndef POINT_LIGHT_CONTROLLER_MAKER_H_
#define POINT_LIGHT_CONTROLLER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "PointLightController.h"

namespace tktk
{
	// 「PointLightController」を作るヘルパークラス
	class PointLightControllerMaker
	{
	private: /* プライベートコンストラクタ達 */

		PointLightControllerMaker() = default;
		PointLightControllerMaker(const PointLightControllerMaker& other) = default;
		PointLightControllerMaker& operator = (const PointLightControllerMaker& other) = default;

	public:

		// 作成開始
		static PointLightControllerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<PointLightController> create();

	public:  /* パラメータ設定関数 */

		// 使用する初期ライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		PointLightControllerMaker& initLightId(IdType value);

		// 初期環境光を設定する
		PointLightControllerMaker& initAmbient(const tktkMath::Color& value);

		// 初期拡散反射光を設定する
		PointLightControllerMaker& initDiffuse(const tktkMath::Color& value);

		// 初期鏡面反射光を設定する
		PointLightControllerMaker& initSpeqular(const tktkMath::Color& value);

	private: /* 各種id指定系の関数の実装 */

		PointLightControllerMaker& initLightIdImpl(unsigned int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static PointLightControllerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr	m_user			{  };
		unsigned int	m_initLightId	{ 0U };
		tktkMath::Color	m_initAmbient	{ 0.25f, 1.0f };
		tktkMath::Color	m_initDiffuse	{ 0.25f, 1.0f };
		tktkMath::Color	m_initSpeqular	{ 0.25f, 1.0f };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		PointLightControllerMaker& initLightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 使用する初期ライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, std::enable_if_t<is_idType_v<IdType>>*>
	inline PointLightControllerMaker& PointLightControllerMaker::initLightId(IdType value)
	{
		return initLightIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !POINT_LIGHT_CONTROLLER_MAKER_H_