#ifndef COMPONENT_UPDATE_PRIORITY_SETTER_H_
#define COMPONENT_UPDATE_PRIORITY_SETTER_H_

#include <unordered_map>
#include <TktkClassFuncProcessor/ProcessingClass/ClassTypeChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasSetUpdatePriorityChecker.h>

namespace tktk
{
	// ����̌^�̃R���|�[�l���g�̍X�V�D��x��ݒ肷��N���X
	class ComponentUpdatePrioritySetter
	{
	public:

		// �w�肵���^�̃R���|�[�l���g�̍X�V�D��x��ݒ�
		template <class T>
		static void addUpdatePriority(float priority);

		// �����̃|�C���^�̃N���X���usetUpdatePriority(float)�v�������Ă����炱�̃N���X�Őݒ肵���Ή�����X�V�D��x��ݒ肷��B
		// �X�V�D��x��ݒ肵�Ă��Ȃ��^�̃|�C���^�������ꍇ�A�X�V�D��x0.0�Ƃ��Đݒ肵�܂��B
		template <class T>
		static void setUpdatePriority(T* addComponent);

	private:

		// �^���Ƃ���ɑΉ�����X�V�D��x���Ǘ�����A�z�z��
		static std::unordered_map<unsigned int, float> m_updatePriorityMap;
	};

	template<class T>
	inline void ComponentUpdatePrioritySetter::addUpdatePriority(float priority)
	{
		unsigned int classId = ClassTypeChecker::getClassId<T>();
		
		if (m_updatePriorityMap.count(classId) == 0)
		{
			m_updatePriorityMap.insert(std::make_pair(classId, priority));
			return;
		}
		m_updatePriorityMap.at(classId) = priority;
	}

	template<class T>
	inline void ComponentUpdatePrioritySetter::setUpdatePriority(T * addComponent)
	{
		unsigned int classId = ClassTypeChecker::getClassId<T>();
		float priority = 0.0f;

		if (m_updatePriorityMap.count(classId) != 0)
		{
			priority = m_updatePriorityMap.at(classId);
		}
		setUpdatePriority_runner<void, float>::checkAndRun(addComponent, priority);
	}
}
#endif // !COMPONENT_UPDATE_PRIORITY_SETTER_H_