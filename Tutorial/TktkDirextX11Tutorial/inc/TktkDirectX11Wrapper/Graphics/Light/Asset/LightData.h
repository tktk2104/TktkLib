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

		// ライトの環境光の値のポインタを取得
		Color* getAmbientColorPtr();

		// ライトの拡散反射光の値のポインタを取得
		Color* getDiffuseColorPtr();

		// ライトの鏡面反射光の値のポインタを取得
		Color* getSpecularColorPtr();

		// ライトの座標の値のポインタを取得
		Vector3* getPositionPtr();

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