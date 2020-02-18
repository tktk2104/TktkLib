#if defined(NDEBUG) || !defined(_DEBUG)
#pragma comment( lib, "TktkClassFuncProcessLib_mt.lib" )
#pragma comment( lib, "TktkComponentFrameworkLib_mt.lib" )
#pragma comment( lib, "TktkAppendComponentLib_mt.lib" )
#pragma comment( lib, "TktkAppend2DComponentLib_mt.lib" )
#pragma comment( lib, "TktkAppend3DComponentLib_mt.lib" )
#pragma comment( lib, "TktkTextProcessingLib_mt.lib" )
#pragma comment( lib, "TktkMathLib_mt.lib" )
#pragma comment( lib, "Tktk2dCollisionLib_mt.lib" )
#pragma comment( lib, "Tktk3dCollisionLib_mt.lib" )
#else
#pragma comment( lib, "TktkClassFuncProcessLib_mtd.lib" )
#pragma comment( lib, "TktkComponentFrameworkLib_mtd.lib" )
#pragma comment( lib, "TktkAppendComponentLib_mtd.lib" )
#pragma comment( lib, "TktkAppend2DComponentLib_mtd.lib" )
#pragma comment( lib, "TktkAppend3DComponentLib_mtd.lib" )
#pragma comment( lib, "TktkTextProcessingLib_mtd.lib" )
#pragma comment( lib, "TktkMathLib_mtd.lib" )
#pragma comment( lib, "Tktk2dCollisionLib_mtd.lib" )
#pragma comment( lib, "Tktk3dCollisionLib_mtd.lib" )
#endif

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include <TktkComponentFramework/GameObject/GameObjectManager.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include "Utility/UpdatePrioritySetter.h"
#include "Utility/CollisionGroupSetter.h"
#include "Utility/SceneSetter.h"

#include "TestObject/RunFuncCheckTest.h"

int main()
{
	UpdatePrioritySetter::set();
	CollisionGroupSetter::set();
	SceneSetter::set();

	tktk::ComponentFrameworkProcessor::createClass<RunFuncCheckTest>(true, true);

	tktk::ComponentFrameworkProcessor::run();

	return 0;
}