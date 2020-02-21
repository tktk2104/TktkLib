#ifndef APPEND_POINT_LIGHT_H_
#define APPEND_POINT_LIGHT_H_

#include <array>
#include <TktkMath/Color.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>

namespace tktk
{
	class AppendPointLight
		: public ComponentBase
	{
	public:

		AppendPointLight(
			int lightId,
			float range,
			const std::array<float, 3>& attenuation,
			const Color& difColor,
			const Color& spcColor,
			const Color& ambColor
		);

	public:

		void start();
		void onEnable();
		void onDisable();
		void update();

	public:

		// ライトの届く距離を取得
		float getRange() const;
		// ライトの届く距離を再設定
		void setRange(float range);

		// ライトの影響力の距離減衰に使用する値を取得
		// d = ライトから頂点への距離
		// ライトの影響力(％) = 100.0f / (Atten0 + Atten1 * d + Atten2 * d * d)
		const std::array<float, 3>& getAttenuation() const;
		// ライトの影響力の距離減衰に使用する値を再設定
		// d = ライトから頂点への距離
		// ライトの影響力(％) = 100.0f / (Atten0 + Atten1 * d + Atten2 * d * d)
		void setAttenuation(const std::array<float, 3>& attenuation);

		// 自身の拡散反射光を取得
		const Color& getDifColor() const;
		// 自身の拡散反射光を再設定
		void setDifColor(const Color& difColor);

		// 自身の鏡面反射光を取得
		const Color& getSpcColor() const;
		// 自身の鏡面反射光を再設定
		void setSpcColor(const Color& spcColor);

		// 自身の環境光を取得
		const Color& getAmbColor() const;
		// 自身の環境光を再設定
		void setAmbColor(const Color& ambColor);

	private:

		CfpPtr<Transform3D> m_transform3D;

		int m_lightId{ -1 };
		float m_range{ 2000.0f };
		std::array<float, 3> m_attenuation{ std::array<float, 3>({ 0.0f, 0.0006f, 0.0f }) };
		Color m_difColor{ Color::white };
		Color m_spcColor{ Color::white };
		Color m_ambColor{ Color::white };
	};
}
#endif // !APPEND_POINT_LIGHT_H_