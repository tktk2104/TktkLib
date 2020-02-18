#ifndef LIGHT_ASSETS_H_
#define LIGHT_ASSETS_H_

#include <array>
#include <unordered_map>
#include <TktkMath/Color.h>
#include <TktkMath/Vector3.h>

namespace tktk
{
	class LightAssets
	{
	public:

		LightAssets() = default;

	public:

		void onDestroy() const;

	public:

		void createDirectionalLight(
			int id,
			const Vector3& direction = Vector3::forwardLH,
			const Color& diffuse = Color::white,
			const Color& specular = Color::white,
			const Color& ambient = Color::white
		);

		void createPointLight(
			int id,
			const Vector3& position = Vector3::zero,
			float range = 2000.0f,
			const std::array<float, 3>& attenuation = std::array<float, 3>({ 0.0f, 0.0006f, 0.0f }),
			const Color& diffuse = Color::white,
			const Color& specular = Color::white,
			const Color& ambient = Color::white
		);

		void createSpotLight(
			int id,
			const Vector3& position = Vector3::zero,
			const Vector3& direction = Vector3::forwardLH,
			float outAngleDegree = 90.0f,
			float inAngleDegree = 45.0f,
			float range = 2000.0f,
			const std::array<float, 3>& attenuation = std::array<float, 3>({ 0.0f, 0.0006f, 0.0f }),
			const Color& diffuse = Color::white,
			const Color& specular = Color::white,
			const Color& ambient = Color::white
		);

		void eraseLight(int id);

		void eraseLightAll();

		int getLightHandle(int id) const;

	private:

		std::unordered_map<int, int> m_lightAssetsMap;
	};
}
#endif // !LIGHT_ASSETS_H_