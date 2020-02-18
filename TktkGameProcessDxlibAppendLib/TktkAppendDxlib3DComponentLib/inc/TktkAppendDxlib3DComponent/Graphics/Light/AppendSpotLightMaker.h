#ifndef APPEND_SPOT_LIGHT_MAKER_H_
#define APPEND_SPOT_LIGHT_MAKER_H_

#include <memory>
#include "AppendSpotLight.h"

namespace tktk
{
	class AppendSpotLightMaker
	{
	public:

		// インスタンス作成開始
		static AppendSpotLightMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<AppendSpotLight> create();

		// 自身のライトIDを設定
		AppendSpotLightMaker& lightId(int value);

		// スポットライトの影響角度を設定
		AppendSpotLightMaker& outAngleDegree(float value);

		// スポットライトの減衰開始角度を設定
		AppendSpotLightMaker& inAngleDegree(float value);

		// ライトの届く距離を設定
		AppendSpotLightMaker& range(float value);

		// ライトの影響力の距離減衰に使用する値を設定
		// d = ライトから頂点への距離
		// ライトの影響力(％) = 100.0f / (Atten0 + Atten1 * d + Atten2 * d * d)
		AppendSpotLightMaker& attenuation(const std::array<float, 3>& value);

		// 自身の拡散反射光を設定
		AppendSpotLightMaker& difColor(const Color& value);

		// 自身の鏡面反射光を設定
		AppendSpotLightMaker& spcColor(const Color& value);

		// 自身の環境光を設定
		AppendSpotLightMaker& ambColor(const Color& value);

	private:

		// 自身のポインタ
		static AppendSpotLightMaker m_self;

	private:

		int m_lightId{ -1 };
		float m_outAngleDegree{ 90.0f };
		float m_inAngleDegree{ 45.0f };
		float m_range{ 2000.0f };
		std::array<float, 3> m_attenuation{ std::array<float, 3>({ 0.0f, 0.0006f, 0.0f }) };
		Color m_difColor{ Color::white };
		Color m_spcColor{ Color::white };
		Color m_ambColor{ Color::white };
	};
}
#endif // !APPEND_SPOT_LIGHT_MAKER_H_