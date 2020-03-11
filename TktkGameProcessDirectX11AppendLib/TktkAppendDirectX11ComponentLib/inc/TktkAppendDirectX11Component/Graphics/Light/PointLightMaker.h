#ifndef POINT_LIGHT_MAKER_H_
#define POINT_LIGHT_MAKER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "PointLight.h"

namespace tktk
{
	class PointLightMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static PointLightMaker& makeStart(GameObjectPtr user);

	private:

		// ���g�̃|�C���^
		static PointLightMaker m_self;

	private:

		// �v���C�x�[�g�R���X�g���N�^�B
		PointLightMaker() = default;
		PointLightMaker(const PointLightMaker& other) = default;
		PointLightMaker& operator = (const PointLightMaker& other) = default;

	public:

		// �쐬����
		CfpPtr<PointLight> create();

		// �쐬���郉�C�g��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		PointLightMaker& lightId(IdType value)
		{
			return lightIdImpl(static_cast<int>(value));
		}
		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		PointLightMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }

		// �����̐F��ݒ肷��
		PointLightMaker& ambientColor(const Color& value);

		// �g�U���ˌ��̐F��ݒ肷��
		PointLightMaker& diffuseColor(const Color& value);

		// ���ʔ��ˌ��̐F���擾����
		PointLightMaker& specularColor(const Color& value);

	private:

		// �e��id�w��n�̊֐��̎���
		PointLightMaker& lightIdImpl(int value);

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		int m_lightId{ 0 };
		Color m_ambientColor{ Color(0.3f, 0.3f, 0.3f, 1.0f) };
		Color m_diffuseColor{ Color::white };
		Color m_specularColor{ Color::white };
	};
}
#endif // !POINT_LIGHT_MAKER_H_