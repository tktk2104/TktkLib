#ifndef COMPONENT_BASE_H_
#define COMPONENT_BASE_H_

namespace tktk
{
	class ComponentBase
	{
	public:

		ComponentBase(float drawPriority = 0.0f);
		virtual ~ComponentBase();

	public:

		float getDrawPriority() const;

		bool activeChangeCheck();

		void setActive(bool activeFlag);

		void destroy();

		bool isActive() const;

		bool isDead() const;

	private:

		const float	m_drawPriority;
		bool		m_isActive			{ true };
		bool		m_nextFrameActive	{ true };
		bool		m_isDead			{ false };
	};
}
#endif // !COMPONENT_BASE_H_