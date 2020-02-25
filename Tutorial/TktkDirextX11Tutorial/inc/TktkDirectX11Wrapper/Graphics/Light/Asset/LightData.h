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

		// ���C�g�̊����̒l�̃|�C���^���擾
		Color* getAmbientColorPtr();

		// ���C�g�̊g�U���ˌ��̒l�̃|�C���^���擾
		Color* getDiffuseColorPtr();

		// ���C�g�̋��ʔ��ˌ��̒l�̃|�C���^���擾
		Color* getSpecularColorPtr();

		// ���C�g�̍��W�̒l�̃|�C���^���擾
		Vector3* getPositionPtr();

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