#ifndef MATERIAL_SLOTS_H_
#define MATERIAL_SLOTS_H_

#include <vector>
#include "Subset.h"
#include "../_MeshInitParams/MaterialSlotsInitParams.h"

namespace tktk
{
	class MaterialSlots
	{
	public:

		// 意図的に“explicit”を外している
		MaterialSlots(const MaterialSlotsInitParams& params);
		~MaterialSlots() = default;

		// コピー禁止
		MaterialSlots(const MaterialSlots& other) = delete;
		MaterialSlots& operator = (const MaterialSlots& other) = delete;

	public:

		// マテリアルスロットが何個あるかを取得
		unsigned int getSlotsCount() const;

		// 指定したマテリアルスロットのサブセットを取得する
		const Subset& getSubset(unsigned int slotIndex) const;

	private:

		std::vector<Subset> m_subsets;
	};
}
#endif // !MATERIAL_SLOTS_H_