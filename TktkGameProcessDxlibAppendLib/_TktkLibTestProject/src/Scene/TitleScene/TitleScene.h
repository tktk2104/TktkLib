#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include "CommonIncludePaths.h"

class TitleScene
	: public tktk::SceneBase
{
public:

	void sceneStart() override;

	void sceneEnd() override;
};
#endif // !TITLE_SCENE_H_