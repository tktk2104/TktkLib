#ifndef COMPONENT_UPDATE_PRIORITY_LIST_H_
#define COMPONENT_UPDATE_PRIORITY_LIST_H_

#include <unordered_map>
#include "../ClassTypeChecker/ClassTypeChecker.h"

namespace tktk
{
	// �R���|�[�l���g�̌^���Ƃ̍X�V�D��x���Ǘ�����N���X
	class ComponentUpdatePriorityList
	{
	public:

		// �e���v���[�g�����̌^�̃R���|�[�l���g�̍X�V�D��x��ݒ肷��
		template <class ComponentType>
		void addPriority(float priority);

		// �e���v���[�g�����̌^�̃R���|�[�l���g�̍X�V�D��x���擾����
		// �o�^����Ă��Ȃ��^�̏ꍇ�A�um_basePriority�v���Ԃ�
		template <class ComponentType>
		float getPriority() const;

		// �����̃N���XID�̌^�̃R���|�[�l���g�̍X�V�D��x���擾����
		// �o�^����Ă��Ȃ��^�̏ꍇ�A�f�t�H���g�l�́u0.0f�v���Ԃ�
		float getPriority(unsigned int typeId) const;

	private:

		static constexpr float m_basePriority{ 0.0f };

		std::unordered_map<unsigned int, float> m_updatePriorityMap;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �e���v���[�g�����̌^�̃R���|�[�l���g�̍X�V�D��x��ݒ肷��
	template<class ComponentType>
	inline void ComponentUpdatePriorityList::addPriority(float priority)
	{
		if (m_updatePriorityMap.count(ClassTypeChecker::getClassId<ComponentType>()) == 0U)
		{
			m_updatePriorityMap.emplace(ClassTypeChecker::getClassId<ComponentType>(), priority);
		}
	}

	// �e���v���[�g�����̌^�̃R���|�[�l���g�̍X�V�D��x���擾����
	// �o�^����Ă��Ȃ��^�̏ꍇ�A�f�t�H���g�l�́u0.0f�v���Ԃ�
	template<class ComponentType>
	inline float ComponentUpdatePriorityList::getPriority() const
	{
		return getPriority(ClassTypeChecker::getClassId<ComponentType>());
	}
}
#endif // !COMPONENT_UPDATE_PRIORITY_LIST_H_