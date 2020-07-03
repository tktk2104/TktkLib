#ifndef POST_EFFECT_OBJECT_H_
#define POST_EFFECT_OBJECT_H_

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12Game/Component/DefaultComponents/2DComponents/PostEffectDrawer/PostEffectDrawerMaker.h>

struct PostEffectObject
{
	static tktk::GameObjectPtr create()
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		tktk::PostEffectDrawerMaker::makeStart(gameObject)
			.drawPriority(1.0f)
			.postEffectMaterialId(0U)
			.create();

		return gameObject;
	}
};

#endif // !POST_EFFECT_OBJECT_H_
