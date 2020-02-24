#ifndef COMPONENT_UPDATE_PRIORITY_SETTER_H_
#define COMPONENT_UPDATE_PRIORITY_SETTER_H_

#include <unordered_map>
#include <TktkClassFuncProcessor/ProcessingClass/ClassTypeChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasSetUpdatePriorityChecker.h>

namespace tktk
{
	// 特定の型のコンポーネントの更新優先度を設定するクラス
	class ComponentUpdatePrioritySetter
	{
	public:

		// 指定した型のコンポーネントの更新優先度を設定
		template <class T>
		static void addUpdatePriority(float priority);

		// 引数のポインタのクラスが「setUpdatePriority(float)」を持っていたらこのクラスで設定した対応する更新優先度を設定する。
		// 更新優先度を設定していない型のポインタだった場合、更新優先度0.0として設定します。
		template <class T>
		static void setUpdatePriority(T* addComponent);

	private:

		// 型情報とそれに対応する更新優先度を管理する連想配列
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