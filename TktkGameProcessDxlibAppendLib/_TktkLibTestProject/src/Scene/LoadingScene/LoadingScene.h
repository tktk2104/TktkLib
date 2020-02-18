#ifndef LOADING_SCENE_H_
#define LOADING_SCENE_H_

#include "CommonIncludePaths.h"

class LoadingScene
	: public tktk::SceneBase
{
public:

	void sceneStart() override;

	void sceneEnd() override;
};
#endif // !LOADING_SCENE_H_