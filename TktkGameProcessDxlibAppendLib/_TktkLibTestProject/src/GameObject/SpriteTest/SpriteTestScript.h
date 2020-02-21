#ifndef SPRITE_TEST_SCRIPT_H_
#define SPRITE_TEST_SCRIPT_H_

#include "CommonIncludePaths.h"

class SpriteTestScript
	: public tktk::ComponentBase
{
public:

	SpriteTestScript() = default;

public:

	void start();
	void update();

private:

	tktk::CfpPtr<tktk::CurStateTypeList> m_curStateTypeList;
};
#endif // !SPRITE_TEST_SCRIPT_H_