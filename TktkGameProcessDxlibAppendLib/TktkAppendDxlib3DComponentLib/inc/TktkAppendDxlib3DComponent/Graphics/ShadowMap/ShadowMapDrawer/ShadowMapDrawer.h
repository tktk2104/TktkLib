#ifndef SHADOW_MAP_DRAWER_H_
#define SHADOW_MAP_DRAWER_H_

#include <memory>
#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>

namespace tktk
{
	class ShadowMapDrawer
		: public ComponentBase
	{
	public:

		ShadowMapDrawer(
			float shadowMapCreateStarterDrawPriority,
			float shadowMapCreateFinisherDrawPriority,
			float shadowMapEnablerDrawPriority,
			float shadowMapDisablerDrawPriority,
			int shadowMapId,
			const Vector3& drawAreaMinPos,
			const Vector3& drawAreaMaxPos
		);

	public:

		// <PolymorphismFunc>
		void awake();
		void start();
		void update();

	public:

		int getShadowMapId() const;
		void setShadowMapId(int shadowMapId);

		const Vector3& getDrawAreaMinPos() const;
		const Vector3& getDrawAreaMaxPos() const;
		void setDrawArea(const Vector3& minPos, const Vector3& maxPos);

	private:

		std::weak_ptr<Transform3D> m_transform3D;

		float m_shadowMapCreateStarterDrawPriority;
		float m_shadowMapCreateFinisherDrawPriority;
		float m_shadowMapEnablerDrawPriority;
		float m_shadowMapDisablerDrawPriority;
		int m_shadowMapId;
		Vector3 m_drawAreaMinPos;
		Vector3 m_drawAreaMaxPos;
	};
}
#endif // !SHADOW_MAP_DRAWER_H_
