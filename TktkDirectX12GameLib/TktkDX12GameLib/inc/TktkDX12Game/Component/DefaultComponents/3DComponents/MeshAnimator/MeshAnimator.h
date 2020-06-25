#ifndef MESH_ANIMATOR_H_
#define MESH_ANIMATOR_H_

#include "../../../ComponentBase.h"

namespace tktk
{
	class MeshAnimator
		: public ComponentBase
	{
	public:

		MeshAnimator(unsigned int motionId);

	public:

		void update();

		void transformSkeleton(unsigned int skeletonId);

	public:

		void setMotionId(unsigned int motionId);

	private:

		unsigned int m_motionId;
		unsigned int m_curFrame{ 0U };
	};
}
#endif // !MESH_ANIMATOR_H_