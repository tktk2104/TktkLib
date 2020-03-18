#ifndef MATERIAL_DATA_H_
#define MATERIAL_DATA_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "MaterialParameters.h"

namespace tktk
{
	// �}�e���A�������Ǘ�����N���X
	class MaterialData
	{
	public:

		MaterialData(
			int useVertexShaderId,
			int usePixelShaderId,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Color& emissionColor,
			float shininess,
			const std::vector<int>& useTextureIdArray
		);
		~MaterialData() = default;

		MaterialData(const MaterialData& other) = delete;
		MaterialData& operator = (const MaterialData& other) = delete;

	public:

		// �g�p���钸�_�V�F�[�_�[��Id���擾����
		int getUseVertexShaderId() const;

		// �g�p����s�N�Z���V�F�[�_�[��Id���擾����
		int getUsePixelShaderId() const;

		// �g�p���钸�_�V�F�[�_�[��Id��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setUseVertexShaderId(IdType id)
		{
			m_useVertexShaderId = static_cast<int>(id);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setUseVertexShaderId(IdType id) { static_assert(false, "VertexShaderId Fraud Type"); }

		// �g�p����s�N�Z���V�F�[�_�[��Id��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setUsePixelShaderId(IdType id)
		{
			m_usePixelShaderId = static_cast<int>(id);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setUsePixelShaderId(IdType id) { static_assert(false, "PixelShaderId Fraud Type"); }

		// �}�e���A���p�����[�^���擾����
		MaterialParameters& getParametersRef();

	private:

		// �g�p���钸�_�V�F�[�_�[��Id
		int m_useVertexShaderId;
		// �g�p����s�N�Z���V�F�[�_�[��Id
		int m_usePixelShaderId;
		// �}�e���A���̃p�����[�^�[
		MaterialParameters m_materialParameters;
	};
}
#endif // !MATERIAL_DATA_H_