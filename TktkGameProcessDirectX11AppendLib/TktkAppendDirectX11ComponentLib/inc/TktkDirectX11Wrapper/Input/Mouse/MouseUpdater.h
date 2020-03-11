#ifndef MOUSE_UPDATER_H_
#define MOUSE_UPDATER_H_

#include <unordered_map>
#include <TktkMath/Vector2.h>
#include "MouseButtonType.h"

namespace tktk
{
	class MouseUpdater
	{
	public:

		MouseUpdater();
		~MouseUpdater() = default;

		// コピー禁止
		MouseUpdater(const MouseUpdater& other) = delete;
		MouseUpdater& operator = (const MouseUpdater& other) = delete;

	public:

		void update();

	public:

		// 指定のボタンが押されているか
		bool isPush(MouseButtonType buttonType) const;

		// 指定のボタンが押され始めたかを判定
		bool isTrigger(MouseButtonType buttonType) const;

		// マウスカーソルの座標を取得する
		Vector2 mousePos() const;

	private:

		std::unordered_map<MouseButtonType, bool> m_curMouseButtonState;
		std::unordered_map<MouseButtonType, bool> m_preMouseButtonState;
	};
}
#endif // !MOUSE_UPDATER_H_
