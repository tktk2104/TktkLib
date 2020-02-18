#ifndef APPEND_DIRECTIONAL_LIGHT_MAKER_H_
#define APPEND_DIRECTIONAL_LIGHT_MAKER_H_

#include <memory>
#include "AppendDirectionalLight.h"

namespace tktk
{
	class AppendDirectionalLightMaker
	{
	public:

		// インスタンス作成開始
		static AppendDirectionalLightMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<AppendDirectionalLight> create();

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

		int m_lightId{ -1 };
		Color m_difColor{ Color::white };
		Color m_spcColor{ Color::white };
		Color m_ambColor{ Color::white };
	};
}
#endif // !APPEND_DIRECTIONAL_LIGHT_MAKER_H_