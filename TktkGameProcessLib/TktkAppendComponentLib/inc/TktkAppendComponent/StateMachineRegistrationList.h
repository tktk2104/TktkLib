#ifndef STATE_MACHINE_REGISTRATION_LIST_H_
#define STATE_MACHINE_REGISTRATION_LIST_H_

#include <forward_list>
#include <TktkClassFuncProcessor/ProcessingClass/ProcessingClassPtr.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>

namespace tktk
{
	// ステートマシーンに登録されているコンポーネントを管理するリスト
	class StateMachineRegistrationList
	{
	public:

		void addNode(ProcessingClassPtr newNode);

		void updateList();

		template <class T>
		bool contain(CfpPtr<T> conditions) const;

	private:

		std::forward_list<ProcessingClassPtr> m_stateMachineRegistrationList;
	};

	template<class T>
	inline bool StateMachineRegistrationList::contain(CfpPtr<T> conditions) const
	{
		auto findNode = std::find_if(
			std::begin(m_stateMachineRegistrationList),
			std::end(m_stateMachineRegistrationList),
			[](ProcessingClassPtr node) { return (!node.isNull() && node.isSame(conditions.processingClassPtr())); }
		);
		return (findNode != std::end(m_stateMachineRegistrationList));
	}
}
#endif // !STATE_MACHINE_REGISTRATION_LIST_H_