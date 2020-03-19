#ifndef MATERIAL_LOAD_TEXTURE_ID_MANAGER_H_
#define MATERIAL_LOAD_TEXTURE_ID_MANAGER_H_

#include <unordered_map>
#include <vector>
#include <TktkMetaFunc/TypeCheck/isIdType.h>

namespace tktk
{
	class MaterialLoadTextureIdManager
	{
	public:

		template <class MaterialIdType, std::enable_if_t<is_idType_v<MaterialIdType>>* = nullptr>
		static int getMaterialTextureId(MaterialIdType materialId, unsigned int textureSlot)
		{
			return getMaterialTextureIdImpl(static_cast<int>(materialId), textureSlot);
		}
		template <class MaterialIdType, std::enable_if_t<!is_idType_v<MaterialIdType>>* = nullptr>
		static int getMaterialTextureId(MaterialIdType materialId, unsigned int textureSlot) { static_assert(false, "MaterialId Fraud Type"); }

	private:

		static int getMaterialTextureIdImpl(int materialId, unsigned int textureSlot);

	private:

		static int m_curMaterialTexture2DId;

		static std::unordered_map<int, std::vector<int>> m_materialTexture2DIdArrayMap;
	};
}
#endif // !MATERIAL_LOAD_TEXTURE_ID_MANAGER_H_
