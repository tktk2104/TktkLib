#ifndef CURSOR_H_
#define CURSOR_H_

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12Game/Component/DefaultComponents/2DComponents/Transform2D/Transform2D.h>
#include <TktkDX12Game/Component/DefaultComponents/2DComponents/SpriteDrawer/SpriteDrawer.h>
#include "CursorScript.h"

struct Cursor
{
	static tktk::GameObjectPtr create()
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		gameObject->createComponent<tktk::Transform2D>(
			tktkMath::Vector2(0.0f, 0.0f),
			tktkMath::vec2One,
			0.0f,
			tktk::TraceParentType::notTrace
			);

		gameObject->createComponent<tktk::SpriteDrawer>(
			0.0f,
			0U,
			0U
			);

		gameObject->createComponent<CursorScript>();

		return gameObject;
	}
};
#endif // !CURSOR_H_