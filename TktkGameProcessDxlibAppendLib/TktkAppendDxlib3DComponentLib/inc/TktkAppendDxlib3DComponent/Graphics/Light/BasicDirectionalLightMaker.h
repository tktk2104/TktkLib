#ifndef BASIC_DIRECTIONAL_LIGHT_MAKER_H_
#define BASIC_DIRECTIONAL_LIGHT_MAKER_H_

#include <memory>
#include "BasicDirectionalLight.h"

namespace tktk
{
	class BasicDirectionalLightMaker
	{
	public:

		// インスタンス作成開始
		static BasicDirectionalLightMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<BasicDirectionalLight> create();

		// 自身の拡散反射光を設定
		BasicDirectionalLightMaker& difColor(const Color& value);

		// 自身の鏡面反射光を設定
		BasicDirectionalLightMaker& spcColor(const Color& value);

		// 自身の環境光を設定
		BasicDirectionalLightMaker& ambColor(const Color& value);

	private:

		// 自身のポインタ
		static BasicDirectionalLightMaker m_self;

	private:

		Color m_difColor{ Color::white };
		Color m_spcColor{ Color::white };
		Color m_ambColor{ Color::white };
	};
}
#endif // !BASIC_DIRECTIONAL_LIGHT_MAKER_H_