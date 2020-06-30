#include "CursorScript.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

void CursorScript::start()
{
	m_transform = getComponent<tktk::Transform2D>();
}

void CursorScript::update()
{
	auto pos = tktk::DX12GameManager::mousePos();

	m_transform->setWorldPosition(pos);
}
