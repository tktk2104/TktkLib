#ifndef APPEND_DIRECTIONAL_LIGHT_MAKER_H_
#define APPEND_DIRECTIONAL_LIGHT_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "AppendDirectionalLight.h"

namespace tktk
{
	class AppendDirectionalLightMaker
	{
	public:

		// インスタンス作成開始
		static AppendDirectionalLightMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<AppendDirectionalLight> create();

		// 自身のライトIDを設定
		AppendDirectionalLightMaker& lightId(int value);

		// 自身の拡散反射光を設定
		AppendDirectionalLightMaker& difColor(const Color& value);

		// 自身の鏡面反射光を設定
		AppendDirectionalLightMaker& spcColor(const Color& value);

		// 自身の環境光を設定
		AppendDirectionalLightMaker& ambColor(const Color& value);

	private:

		// 自身のポインタ
		static AppendDirectionalLightMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{};
		int m_lightId{ -1 };
		Color m_difColor{ Color::white };
		Color m_spcColor{ Color::white };
		Color m_ambColor{ Color::white };
	};
}
#endif // !APPEND_DIRECTIONAL_LIGHT_MAKER_H_