#ifndef GAME_OBJECT_PTR_H_
#define GAME_OBJECT_PTR_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>

namespace tktk
{
	class GameObject;
}
using GameObjectPtr = tktk::CfpPtr<tktk::GameObject>;

#endif // !GAME_OBJECT_PTR_H_
