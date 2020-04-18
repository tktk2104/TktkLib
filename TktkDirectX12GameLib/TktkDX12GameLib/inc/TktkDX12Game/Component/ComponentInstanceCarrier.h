#ifndef COMPONENT_INSTANCE_CARRIER_H_
#define COMPONENT_INSTANCE_CARRIER_H_

namespace tktk
{
	class ComponentInstanceCarrier
	{
	public:

		template<class ComponentType>
		ComponentInstanceCarrier(ComponentType* rawPtr);

	public:

		void runUpdate();
	};
}
#endif // !COMPONENT_INSTANCE_CARRIER_H_