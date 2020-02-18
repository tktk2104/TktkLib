#ifndef APPEND_POINT_LIGHT_MAKER_H_
#define APPEND_POINT_LIGHT_MAKER_H_

#include <memory>
#include "AppendPointLight.h"

namespace tktk
{
	class AppendPointLightMaker
	{
	public:

		// インスタンス作成開始
		static AppendPointLightMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<AppendPointLight> create();

		// 自身のライトIDを設定
		AppendPointLightMaker& lightId(int value);

		// ライトの届く距離を設定
		AppendPointLightMaker& range(float value);

		// ライトの影響力の距離減衰に使用する値を設定
		// d = ライトから頂点への距離
		// ライトの影響力(％) = 100.0f / (Atten0 + Atten1 * d + Atten2 * d * d)
		AppendPointLightMaker& attenuation(const std::array<float, 3>& value);

		// 自身の拡散反射光を設定
		AppendPointLightMaker& difColor(const Color& value);

		// 自身の鏡面反射光を設定
		AppendPointLightMaker& spcColor(const Color& value);

		// 自身の環境光を設定
		AppendPointLightMaker& ambColor(const Color& value);

	private:

		// 自身のポインタ
		static AppendPointLightMaker m_self;

	private:

		int m_lightId{ -1 };
		float m_range{ 2000.0f };
		std::array<float, 3> m_attenuation{ std::array<float, 3>({ 0.0f, 0.0006f, 0.0f }) };
		Color m_difColor{ Color::white };
		Color m_spcColor{ Color::white };
		Color m_ambColor{ Color::white };
	};
}
#endif // !APPEND_POINT_LIGHT_MAKER_H_