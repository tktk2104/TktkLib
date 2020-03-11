#ifndef POINT_LIGHT_H_
#define POINT_LIGHT_H_

#include <TktkMath/Color.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include "TktkDirectX11Wrapper/Graphics/Light/Asset/LightData.h"

namespace tktk
{
	class PointLight
		: public ComponentBase
	{
	public:

		PointLight(int lightId, const Color& ambient, const Color& diffuse, const Color& specular);
		~PointLight();

	public:

		void start();

		void afterCollide();

	public:

		void enable();

		void disable();

		// 環境光の色を取得する
		Color getAmbientColor() const;

		// 環境光の色を設定する
		void setAmbientColor(const Color& ambient);

		// 拡散反射光の色を取得する
		Color getDiffuseColor() const;

		// 拡散反射光の色を設定する
		void setDiffuseColor(const Color& diffuse);

		// 鏡面反射光の色を取得する
		Color getSpecularColor() const;

		// 鏡面反射光の色を設定する
		void setSpecularColor(const Color& specular);

	private:

		CfpPtr<Transform3D> m_transform;

		int m_lightId;
		LightData* m_lightDataPtr;
	};
}
#endif // !POINT_LIGHT_H_