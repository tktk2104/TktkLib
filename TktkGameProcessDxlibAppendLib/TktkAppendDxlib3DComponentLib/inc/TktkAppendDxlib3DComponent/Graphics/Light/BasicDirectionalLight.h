#ifndef BASIC_LIGHT_H_
#define BASIC_LIGHT_H_

#include <memory>
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

		std::weak_ptr<Transform3D> m_transform3D;

		Color m_difColor{ Color::white };
		Color m_spcColor{ Color::white };
		Color m_ambColor{ Color::white };
	};
}
#endif // !BASIC_LIGHT_H_