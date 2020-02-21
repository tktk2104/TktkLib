#ifndef BASIC_LIGHT_H_
#define BASIC_LIGHT_H_

#include <TktkMath/Color.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>

namespace tktk
{
	class BasicDirectionalLight
		: public ComponentBase
	{
	public:

		BasicDirectionalLight(
			const Color& difColor,
			const Color& spcColor,
			const Color& ambColor
		);

	public:

		// <PolymorphismFunc>
		void start();
		void onEnable();
		void onDisable();
		void update();

	public:

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

		Color m_difColor{ Color::white };
		Color m_spcColor{ Color::white };
		Color m_ambColor{ Color::white };
	};
}
#endif // !BASIC_LIGHT_H_