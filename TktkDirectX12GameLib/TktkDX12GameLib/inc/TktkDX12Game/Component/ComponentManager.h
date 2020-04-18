#ifndef COMPONENT_MANAGER_H_
#define COMPONENT_MANAGER_H_

#include <map>

namespace tktk
{
	class ComponentManager
	{
	public:

		ComponentManager() = default;

	public:



	private:

		std::multimap<float, void*> m_runUpdateContainer;
		std::multimap<float, void*> m_runDrawContainer;
	};
}
#endif // !COMPONENT_MANAGER_H_