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

		// �Ӑ}�I�Ɂgexplicit�h���O���Ă���
		MaterialSlots(const MaterialSlotsInitParams& params);
		~MaterialSlots() = default;

		// �R�s�[�֎~
		MaterialSlots(const MaterialSlots& other) = delete;
		MaterialSlots& operator = (const MaterialSlots& other) = delete;

	public:

		// �}�e���A���X���b�g�������邩���擾
		unsigned int getSlotsCount() const;

		// �w�肵���}�e���A���X���b�g�̃T�u�Z�b�g���擾����
		const Subset& getSubset(unsigned int slotIndex) const;

	private:

		std::vector<Subset> m_subsets;
	};
}
#endif // !MATERIAL_SLOTS_H_