#ifndef COMPONENT_UPDATE_PRIORITY_LIST_H_
#define COMPONENT_UPDATE_PRIORITY_LIST_H_

#include <unordered_map>
#include "../SafetyVoidPtr/ClassTypeChecker.h"

namespace tktk
{
	// コンポーネントの型ごとの更新優先度を管理するクラス
	class ComponentUpdatePriorityList
	{
	public:

		template <class ComponentType>
		void addPriority(float priority);

		template <class ComponentType>
		float getPriority() const;

		float getPriority(unsigned int typeId) const;

	private:

		static constexpr float m_basePriority{ 0.0f };

		std::unordered_map<unsigned int, float> m_updatePriorityMap;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class ComponentType>
	inline void ComponentUpdatePriorityList::addPriority(float priority)
	{
		if (m_updatePriorityMap.count(ClassTypeChecker::getClassId<ComponentType>()) == 0U)
		{
			m_updatePriorityMap.emplace(ClassTypeChecker::getClassId<ComponentType>(), priority);
		}
	}
	template<class ComponentType>
	inline float ComponentUpdatePriorityList::getPriority() const
	{
		return getPriority(ClassTypeChecker::getClassId<ComponentType>());
	}
}
#endif // !COMPONENT_UPDATE_PRIORITY_LIST_H_