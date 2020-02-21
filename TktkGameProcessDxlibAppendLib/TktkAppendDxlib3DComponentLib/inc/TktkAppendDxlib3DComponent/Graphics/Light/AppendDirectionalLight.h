#ifndef APPEND_DIRECTIONAL_LIGHT_H_
#define APPEND_DIRECTIONAL_LIGHT_H_

#include <TktkMath/Color.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>

namespace tktk
{
	class AppendDirectionalLight
		: public ComponentBase
	{
	public:

		AppendDirectionalLight(
			int lightId,
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

		// ���g�̊g�U���ˌ����擾
		const Color& getDifColor() const;
		// ���g�̊g�U���ˌ����Đݒ�
		void setDifColor(const Color& difColor);

		// ���g�̋��ʔ��ˌ����擾
		const Color& getSpcColor() const;
		// ���g�̋��ʔ��ˌ����Đݒ�
		void setSpcColor(const Color& spcColor);

		// ���g�̊������擾
		const Color& getAmbColor() const;
		// ���g�̊������Đݒ�
		void setAmbColor(const Color& ambColor);

	private:

		CfpPtr<Transform3D> m_transform3D;


		int m_lightId{ -1 };
		Color m_difColor{ Color::white };
		Color m_spcColor{ Color::white };
		Color m_ambColor{ Color::white };
	};
}
#endif // !APPEND_DIRECTIONAL_LIGHT_H_