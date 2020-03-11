#ifndef LIGHT_DATA_H_
#define LIGHT_DATA_H_

#include <TktkMath/Vector3.h>
#include <TktkMath/Color.h>

namespace tktk
{
	// ライトを管理するクラス
	class LightData
	{
	public:

		LightData(
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Vector3& position
		);
		~LightData();

		LightData(const LightData& other) = delete;
		LightData& operator = (const LightData& other) = delete;

	public:

		// ライトの環境光の値を取得
		const Color& getAmbientColor() const;

		// ライトの環境光の値を設定
		void setAmbientColor(const Color& ambient);

		// ライトの拡散反射光の値を取得
		const Color& getDiffuseColor() const;

		// ライトの拡散反射光の値を設定
		void setDiffuseColor(const Color& diffuse);

		// ライトの鏡面反射光の値を取得
		const Color& getSpecularColor() const;

		// ライトの鏡面反射光の値を設定
		void setSpecularColor(const Color& specular);

		// ライトの座標の値を取得
		const Vector3& getPosition() const;

		// ライトの座標の値を設定
		void setPosition(const Vector3& pos);

	private:

		// ライトの環境光の値
		Color m_ambientColor;

		// ライトの拡散反射光の値
		Color m_diffuseColor;

		// ライトの鏡面反射光の値
		Color m_specularColor;

		// ライトの座標の値
		Vector3 m_position;
	};
}
#endif // !LIGHT_DATA_H_