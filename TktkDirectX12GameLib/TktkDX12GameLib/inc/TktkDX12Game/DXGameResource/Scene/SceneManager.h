#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "SceneInstanceCarrier.h"

namespace tktk
{
	// �V�[���Ǘ��N���X
	class SceneManager
	{
	public:

		SceneManager(unsigned int sceneNum);
		~SceneManager() = default;

	public:

		// �V�[�����쐬���Ēǉ�����
		void create(unsigned int id, const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr);

		// �V�[����L���ɂ���
		void enable(unsigned int id);

		// �V�[���𖳌��ɂ���
		void disable(unsigned int id);

		// �V�[���̍X�V����
		void update();

	private:

		HeapArray<SceneInstanceCarrier> m_sceneArray;
	};
}
#endif // !SCENE_MANAGER_H_