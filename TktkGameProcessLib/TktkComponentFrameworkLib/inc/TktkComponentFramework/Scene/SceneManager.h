#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <unordered_map>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasSetActiveChecker.h>
#include <TktkClassFuncProcessor/ProcessingClass/ProcessingClassPtr.h>
#include <TktkClassFuncProcessor/ProcessingClass/ClassTypeChecker.h>
#include "../ComponentFrameworkProcessor.h"

namespace tktk
{
	class SceneManager
	{
	public:

		// �V���ȃV�[����ǉ�����
		template <class T>
		static void addScene(T* newScene);

		// �V���ȃV�[���𐶐����Ēǉ�����
		template <class T, class... Args>
		static void createScene(const Args&... constructorValue);

		// �e���v���[�g�����̃V�[����L���ɂ���
		template <class T>
		static void enableScene();

		// �e���v���[�g�����̃V�[���𖳌��ɂ���
		template <class T>
		static void disableScene();

	private:

		// �V�[���̃|�C���^���擾����R�X�g�����炷���߂�map
		static std::unordered_map<unsigned int, ProcessingClassPtr> m_sceneMap;
	};

	// �V���ȃV�[����ǉ�����
	template<class T>
	inline void SceneManager::addScene(T* newScene)
	{
		// ���I�ȃN���X�̃V�[���͑z�肵�Ȃ�
		CfpPtr<T> sceneProcessingClassPtr = ComponentFrameworkProcessor::addClass(true, newScene);
		m_sceneMap.insert(std::make_pair(ClassTypeChecker::getClassId<T>(), sceneProcessingClassPtr.processingClassPtr()));
	}

	// �V���ȃV�[���𐶐����Ēǉ�����
	template<class T, class ...Args>
	inline void SceneManager::createScene(const Args & ...constructorValue)
	{
		addScene(new T(constructorValue...));
	}

	// �e���v���[�g�����̃V�[����L���ɂ���
	template<class T>
	inline void SceneManager::enableScene()
	{
		auto findResult = m_sceneMap.find(ClassTypeChecker::getClassId<T>());
		if (findResult == std::end(m_sceneMap)) throw std::runtime_error("scene notFound");
		auto scene = (*findResult).second->castPtr<T>();
		setActive_runner<bool>::checkAndRun(scene, true);
	}

	// �e���v���[�g�����̃V�[���𖳌��ɂ���
	template<class T>
	inline void SceneManager::disableScene()
	{
		auto findResult = m_sceneMap.find(ClassTypeChecker::getClassId<T>());
		if (findResult == std::end(m_sceneMap)) throw std::runtime_error("scene notFound");
		auto scene = (*findResult).second->castPtr<T>();
		setActive_runner<bool>::checkAndRun(scene, false);
	}
}
#endif // !SCENE_MANAGER_H_