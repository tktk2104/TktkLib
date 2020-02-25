#ifndef SCENE_BASE_H_
#define SCENE_BASE_H_

namespace tktk
{
	class SceneBase
	{
	public:

		SceneBase() = default;

		virtual ~SceneBase() {};

	public:

		void frameBegin();

		void onEnable();

		void onDisable();

		bool isActive() const;

		void setActive(bool isActive);

	private:

		virtual void sceneStart() = 0;

		virtual void sceneEnd() = 0;

	private:

		bool m_isActive{ false };
		bool m_nextFrameIsActive{ true };
	};
}
#endif // !SCENE_BASE_H_