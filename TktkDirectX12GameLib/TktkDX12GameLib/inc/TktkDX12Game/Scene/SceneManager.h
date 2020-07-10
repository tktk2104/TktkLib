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
		template<class SceneType, class... Args>
		void createScene(unsigned int id, Args... constructorArgs);

		// �V�[����L���ɂ���
		void enableScene(unsigned int id);

		// �V�[���𖳌��ɂ���
		void disableScene(unsigned int id);

		// �V�[���̍X�V����
		void update();

	private:

		HeapArray<SceneInstanceCarrier> m_sceneArray;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �V�[����ǉ�����
	template<class SceneType, class ...Args>
	inline void SceneManager::createScene(unsigned int id, Args ...constructorArgs)
	{
		m_sceneArray.emplaceAt(id, new SceneType(constructorArgs...));
	}
}
#endif // !SCENE_MANAGER_H_