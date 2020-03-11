#ifndef LIGHT_DATA_H_
#define LIGHT_DATA_H_

#include <TktkMath/Vector3.h>
#include <TktkMath/Color.h>

namespace tktk
{
	// ���C�g���Ǘ�����N���X
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

		// ���C�g�̊����̒l���擾
		const Color& getAmbientColor() const;

		// ���C�g�̊����̒l��ݒ�
		void setAmbientColor(const Color& ambient);

		// ���C�g�̊g�U���ˌ��̒l���擾
		const Color& getDiffuseColor() const;

		// ���C�g�̊g�U���ˌ��̒l��ݒ�
		void setDiffuseColor(const Color& diffuse);

		// ���C�g�̋��ʔ��ˌ��̒l���擾
		const Color& getSpecularColor() const;

		// ���C�g�̋��ʔ��ˌ��̒l��ݒ�
		void setSpecularColor(const Color& specular);

		// ���C�g�̍��W�̒l���擾
		const Vector3& getPosition() const;

		// ���C�g�̍��W�̒l��ݒ�
		void setPosition(const Vector3& pos);

	private:

		// ���C�g�̊����̒l
		Color m_ambientColor;

		// ���C�g�̊g�U���ˌ��̒l
		Color m_diffuseColor;

		// ���C�g�̋��ʔ��ˌ��̒l
		Color m_specularColor;

		// ���C�g�̍��W�̒l
		Vector3 m_position;
	};
}
#endif // !LIGHT_DATA_H_