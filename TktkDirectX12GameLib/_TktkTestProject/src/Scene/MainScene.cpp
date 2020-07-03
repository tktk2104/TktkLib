#include "MainScene.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "../GameObject/Cursor/Cursor.h"
#include "../GameObject/Miku/Miku.h"
#include "../GameObject/PostEffectObject/PostEffectObject.h"

void MainScene::start()
{
	/*tktk::DX12GameManager::playSound(0U, false);
	tktk::DX12GameManager::playSound(1U, true);*/

	Cursor::create();

	Miku::create(tktkMath::vec3Zero);

	PostEffectObject::create();
}

void MainScene::end()
{
}
