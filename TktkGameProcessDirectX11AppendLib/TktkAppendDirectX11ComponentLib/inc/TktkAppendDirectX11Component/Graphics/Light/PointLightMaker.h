#ifndef POINT_LIGHT_MAKER_H_
#define POINT_LIGHT_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "PointLight.h"

namespace tktk
{
	class PointLightMaker
	{
	public:

		// インスタンス作成開始
		static PointLightMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<PointLight> create();

		PointLightMaker& lightId(int value);

		PointLightMaker& ambientColor(const Color& value);

		PointLightMaker& diffuseColor(const Color& value);

		PointLightMaker& specularColor(const Color& value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static PointLightMaker m_self;

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