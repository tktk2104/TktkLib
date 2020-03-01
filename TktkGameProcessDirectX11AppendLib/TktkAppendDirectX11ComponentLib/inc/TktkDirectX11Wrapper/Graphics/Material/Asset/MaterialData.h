#ifndef MATERIAL_DATA_H_
#define MATERIAL_DATA_H_

#include <unordered_map>
#include <TktkMath/Color.h>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/SafetyVoidPtr.h>
#include "../../ConstantBuffer/Asset/ConstantBufferData.h"

namespace tktk
{
	// �}�e���A�������Ǘ�����N���X
	class MaterialData
	{
	public:

		MaterialData(
			int indexBufferStartPos,
			int indexBufferUseCount,
			int useVertexShaderId,
			int usePixelShaderId,
			const std::unordered_map<unsigned int, int>& useTextureIdMap,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Color& emissionColor,
			float shininess
		);
		~MaterialData();

		MaterialData(const MaterialData& other) = delete;
		MaterialData& operator = (const MaterialData& other) = delete;

	public:

		// �g�p����C���f�b�N�X�o�b�t�@�̊J�n�ʒu���擾����
		int getIndexBufferStartPos() const;

		// �g�p����C���f�b�N�X�o�b�t�@�̕����擾����
		int getIndexBufferUseCount() const;

		// �g�p���钸�_�V�F�[�_�[��Id���擾����
		int getUseVertexShaderId() const;

		// �g�p���钸�_�V�F�[�_�[��Id��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setUseVertexShaderId(IdType id)
		{
			m_useVertexShaderId = static_cast<int>(id);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setUseVertexShaderId(IdType id) { static_assert(false, "VertexShaderId Fraud Type"); }

		// �g�p����s�N�Z���V�F�[�_�[��Id���擾����
		int getUsePixelShaderId() const;

		// �g�p����s�N�Z���V�F�[�_�[��Id��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setUsePixelShaderId(IdType id)
		{
			m_usePixelShaderId = static_cast<int>(id);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setUsePixelShaderId(IdType id) { static_assert(false, "PixelShaderId Fraud Type"); }

		// �V�F�[�_�[�Ŏg�p����e�N�X�`��Id�̘A�z�z����擾����
		const std::unordered_map<unsigned int, int>& getUseTextureIdMap() const;
		// �V�F�[�_�[�Ŏg�p����e�N�X�`��Id��ǉ�����
		void addUseTextureId(unsigned int stage, int id);
		// �V�F�[�_�[�Ŏg�p����e�N�X�`��Id��S�č폜����
		void clearUseTextureId();

		// �}�e���A���̊����̃|�C���^���擾����
		Color* getAmbientColorPtr();

		// �}�e���A���̊g�U���ˌ��̃|�C���^���擾����
		Color* getDiffuseColorPtr();

		// �}�e���A���̋��ʔ��ˌ��̃|�C���^���擾����
		Color* getSpecularColorPtr();

		// �}�e���A���̎��Ȕ����̃|�C���^���擾����
		Color* getEmissionColorPtr();

		// �}�e���A���̌���̃|�C���^���擾����
		float* getShininessPtr();

		// ���_�V�F�[�_�[���g�p����萔�o�b�t�@�ɐݒ肷�鐔�l�̘A�z�z����擾����
		const std::unordered_map<int, SafetyVoidPtr>& getSetVSConstantBufferParamMap() const;

		// ���_�V�F�[�_�[���g�p����萔�o�b�t�@�̐��l��ݒ肷��\�������i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ���uBufferParamType�v���R�s�[�R���X�g���N�^�������Ă���ꍇ�̂݃r���h�j
		template<class LocationType, class BufferParamType, std::enable_if_t<is_idType_v<LocationType>>* = nullptr>
		void settingReservationVSConstantBufferParam(LocationType locationType, const BufferParamType& param)
		{
			if (m_setVSConstantBufferParamMap.count(static_cast<int>(locationType)) != 0)
			{
				if (m_setVSConstantBufferParamMap.at(static_cast<int>(locationType)).canCast<BufferParamType>())
				{
					*(m_setVSConstantBufferParamMap.at(static_cast<int>(locationType)).castPtr<BufferParamType>()) = param;
					return;
				}
				m_setVSConstantBufferParamMap.erase(static_cast<int>(locationType));
			}
			m_setVSConstantBufferParamMap.emplace(static_cast<int>(locationType), new BufferParamType(param));
		}
		template<class LocationType, class BufferParamType, std::enable_if_t<!is_idType_v<LocationType>>* = nullptr>
		void settingReservationVSConstantBufferParam(LocationType locationType, const BufferParamType& param) { static_assert(false, "LocationType Fraud Type"); }

		// �s�N�Z���V�F�[�_�[���g�p����萔�o�b�t�@�ɐݒ肷�鐔�l�̘A�z�z����擾����
		const std::unordered_map<int, SafetyVoidPtr>& getSetPSConstantBufferParamMap() const;

		// �s�N�Z���V�F�[�_�[���g�p����萔�o�b�t�@�̐��l��ݒ肷��\�������i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ���uBufferParamType�v���R�s�[�R���X�g���N�^�������Ă���ꍇ�̂݃r���h�j
		template<class LocationType, class BufferParamType, std::enable_if_t<is_idType_v<LocationType>>* = nullptr>
		void settingReservationPSConstantBufferParam(LocationType locationType, const BufferParamType& param)
		{
			if (m_setPSConstantBufferParamMap.count(static_cast<int>(locationType)) != 0)
			{
				if (m_setPSConstantBufferParamMap.at(static_cast<int>(locationType)).canCast<BufferParamType>())
				{
					*(m_setPSConstantBufferParamMap.at(static_cast<int>(locationType)).castPtr<BufferParamType>()) = param;
					return;
				}
				m_setPSConstantBufferParamMap.erase(static_cast<int>(locationType));
			}
			m_setPSConstantBufferParamMap.emplace(static_cast<int>(locationType), new BufferParamType(param));
		}
		template<class LocationType, class BufferParamType, std::enable_if_t<!is_idType_v<LocationType>>* = nullptr>
		void settingReservationPSConstantBufferParam(LocationType locationType, const BufferParamType& param) { static_assert(false, "LocationType Fraud Type"); }

	private:

		// �g�p����C���f�b�N�X�o�b�t�@�̊J�n�ʒu
		int m_indexBufferStartPos;
		// �g�p����C���f�b�N�X�o�b�t�@�̕�
		int m_indexBufferUseCount;

		// �g�p���钸�_�V�F�[�_�[��Id
		int m_useVertexShaderId;
		// �g�p����s�N�Z���V�F�[�_�[��Id
		int m_usePixelShaderId;

		// �V�F�[�_�[�Ŏg�p����e�N�X�`��Id�̘A�z�z��
		std::unordered_map<unsigned int, int> m_useTextureIdMap;

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

		// ���_�V�F�[�_�[���g�p����萔�o�b�t�@�ɐݒ肷�鐔�l�̘A�z�z��
		std::unordered_map<int, SafetyVoidPtr> m_setVSConstantBufferParamMap;
		// �s�N�Z���V�F�[�_�[���g�p����萔�o�b�t�@�ɐݒ肷�鐔�l�̘A�z�z��
		std::unordered_map<int, SafetyVoidPtr> m_setPSConstantBufferParamMap;
	};
}
#endif // !MATERIAL_DATA_H_