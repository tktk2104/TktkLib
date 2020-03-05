#ifndef MATERIAL_PARAMETERS_H_
#define MATERIAL_PARAMETERS_H_

#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <TktkMath/Color.h>
#include <TktkClassFuncProcessor/ProcessingClass/SafetyVoidPtr.h>
#include <TktkMetaFunc/TypeCheck/isIdType.h>

namespace tktk
{
	class MaterialParameters
	{
	public:

		MaterialParameters(
			const std::vector<int>& useTextureIdArray,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Color& emissionColor,
			float shininess
		);

		// �R�s�[�֎~
		MaterialParameters(const MaterialParameters& other) = delete;
		MaterialParameters& operator = (const MaterialParameters& other) = delete;

	public:

		// �萔�o�b�t�@�ɐݒ肷��l��ێ�����A�z�z����擾����
		const std::unordered_map<int, SafetyVoidPtr>& getConstantBufferSetData() const;

		// �萔�o�b�t�@�ɐݒ肷��l��ݒ肷��
		template<class BufferType, class BufferId, std::enable_if_t<is_idType_v<BufferId>>* = nullptr>
		void setConstantBufferSetData(BufferId id, BufferType&& bufferData)
		{
			if (m_constantBufferSetData.count(static_cast<int>(id)) == 0)
			{
				m_constantBufferSetData.emplace(static_cast<int>(id), new BufferType(std::move(bufferData)));
				return;
			}

			if (m_constantBufferSetData.at(static_cast<int>(id)).canCast<BufferType>())
			{
				*(m_constantBufferSetData.at(static_cast<int>(id)).castPtr<BufferType>()) = std::move(bufferData);
			}
			throw std::runtime_error("BufferType Fraud Type");
		}
		template<class BufferType, class BufferId, std::enable_if_t<!is_idType_v<BufferId>>* = nullptr>
		void setConstantBufferSetData(BufferId id) { static_assert(false, "ConstantBufferId Fraud Type"); }

		// �V�F�[�_�[�Ŏg�p����e�N�X�`��Id�̔z����擾����
		const std::vector<int>& getUseTextureIdArray() const;

		// �V�F�[�_�[�Ŏg�p����e�N�X�`��Id��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class... IdTypes, std::enable_if_t<is_idType_all_v<IdTypes...>>* = nullptr>
		void setUseTextureId(IdTypes... textureIds)
		{
			setUseTextureIdImpl({ static_cast<int>(textureIds)... });
		}
		template<class... IdTypes, std::enable_if_t<!is_idType_all_v<IdTypes...>>* = nullptr>
		void setUseTextureId(IdTypes... textureIds) { static_assert(false, "TextureId Fraud Type"); }

		// �V�F�[�_�[�Ŏg�p����e�N�X�`��Id��ǉ�����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void addUseTextureId(IdType textureId)
		{
			addUseTextureIdImpl(static_cast<int>(textureId));
		}
		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void addUseTextureId(IdType textureId) { static_assert(false, "TextureId Fraud Type"); }

		// �}�e���A���̊����F���擾����
		const Color& getAmbientColor() const;

		// �}�e���A���̊����F��ݒ肷��
		void setAmbientColor(Color&& value);

		// �}�e���A���̊g�U���ˌ��F���擾����
		const Color& getDiffuseColor() const;

		// �}�e���A���̊g�U���ˌ��F��ݒ肷��
		void setDiffuseColor(Color&& value);

		// �}�e���A���̋��ʔ��ˌ��F���擾����
		const Color& getSpecularColor() const;

		// �}�e���A���̋��ʔ��ˌ��F��ݒ肷��
		void setSpecularColor(Color&& value);

		// �}�e���A���̎��Ȕ����F���擾����
		const Color& getEmissionColor() const;

		// �}�e���A���̎��Ȕ����F��ݒ肷��
		void setEmissionColor(Color&& value);

		// �}�e���A���̌�����擾����
		float getShininess() const;

		// �}�e���A���̌����ݒ肷��
		void setShininess(float value);

	private:

		// �e��id�w��n�̊֐��̎���
		void setUseTextureIdImpl(std::vector<int>&& textureIdArray);
		void addUseTextureIdImpl(int textureId);

	private:

		// �萔�o�b�t�@�ɐݒ肷��l��ێ�����A�z�z��
		std::unordered_map<int, SafetyVoidPtr> m_constantBufferSetData;
		// �V�F�[�_�[�Ŏg�p����e�N�X�`��Id�̔z��
		std::vector<int> m_useTextureIdArray;
		// �}�e���A���̊���
		Color m_ambientColor;
		// �}�e���A���̊g�U���ˌ�
		Color m_diffuseColor;
		// �}�e���A���̋��ʔ��ˌ�
		Color m_specularColor;
		// �}�e���A���̎��Ȕ���
		Color m_emissionColor;
		// �}�e���A���̌���
		float m_shininess;
	};
}
#endif // !MATERIAL_PARAMETERS_H_