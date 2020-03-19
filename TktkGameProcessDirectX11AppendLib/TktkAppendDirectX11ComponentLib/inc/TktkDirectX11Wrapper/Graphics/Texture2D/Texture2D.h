#ifndef TEXTURE_2D_H_
#define TEXTURE_2D_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/Texture2DData.h"
#include "Asset/SystemTexture2DId.h"

namespace tktk
{
	// �uTexture2DManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Texture2D
	{
	public:

		// �V����2D�e�N�X�`�����쐬����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐���2D�e�N�X�`�����쐬����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(
			IdType id,
			Texture2DBindFlag bindFlag,
			const std::vector<unsigned char>& textureData,
			unsigned int width,
			unsigned int height,
			unsigned int mipCount,
			unsigned int arraySize,
			DXGI_FORMAT format,
			Texture2DUsage usage,
			Texture2DCpuAccessFlag cpuAccessFlag,
			bool isCubeMap
		)
		{
			createImpl(static_cast<int>(id), bindFlag, textureData, width, height, mipCount, arraySize, format, usage, cpuAccessFlag, isCubeMap);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(
			IdType id,
			Texture2DBindFlag bindFlag,
			const std::vector<unsigned char>& textureData,
			unsigned int width,
			unsigned int height,
			unsigned int mipCount,
			unsigned int arraySize,
			DXGI_FORMAT format,
			Texture2DUsage usage,
			Texture2DCpuAccessFlag cpuAccessFlag,
			bool isCubeMap
		) {
			static_assert(false, "Texture2DId Fraud Type");
		}

		// �V����2D�e�N�X�`�������[�h����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐���2D�e�N�X�`�������[�h����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName)
		{
			loadImpl(static_cast<int>(id), fileName);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName) { static_assert(false, "Texture2DId Fraud Type"); }

		// �w�肵��2D�e�N�X�`�����폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐���2D�e�N�X�`�����폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "Texture2DId Fraud Type"); }

		// �w�肵��2D�e�N�X�`�����Ǘ�����N���X�̎Q�Ƃ��擾����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const Texture2DData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const Texture2DData& getData(IdType id) { static_assert(false, "Texture2DId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(
			int id,
			Texture2DBindFlag bindFlag,
			const std::vector<unsigned char>& textureData,
			unsigned int width,
			unsigned int height,
			unsigned int mipCount,
			unsigned int arraySize,
			DXGI_FORMAT format,
			Texture2DUsage usage,
			Texture2DCpuAccessFlag cpuAccessFlag,
			bool isCubeMap
		);
		static void loadImpl(int id, const std::string& fileName);
		static void eraseImpl(int id);
		static const Texture2DData& getDataImpl(int id);
	};
}
#endif // !TEXTURE_2D_H_