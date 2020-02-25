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

		// 新たなシーンを追加する
		template <class T>
		static void addScene(T* newScene);

		// 新たなシーンを生成して追加する
		template <class T, class... Args>
		static void createScene(const Args&... constructorValue);

		// テンプレート引数のシーンを有効にする
		template <class T>
		static void enableScene();

		// テンプレート引数のシーンを無効にする
		template <class T>
		static void disableScene();

	private:

		// シーンのポインタを取得するコストを減らすためのmap
		static std::unordered_map<unsigned int, ProcessingClassPtr> m_sceneMap;
	};

	// 新たなシーンを追加する
	template<class T>
	inline void SceneManager::addScene(T* newScene)
	{
		// 動的なクラスのシーンは想定しない
		CfpPtr<T> sceneProcessingClassPtr = ComponentFrameworkProcessor::addClass(true, newScene);
		m_sceneMap.insert(std::make_pair(ClassTypeChecker::getClassId<T>(), sceneProcessingClassPtr.processingClassPtr()));
	}

	// 新たなシーンを生成して追加する
	template<class T, class ...Args>
	inline void SceneManager::createScene(const Args & ...constructorValue)
	{
		addScene(new T(constructorValue...));
	}

	// テンプレート引数のシーンを有効にする
	template<class T>
	inline void SceneManager::enableScene()
	{
		auto findResult = m_sceneMap.find(ClassTypeChecker::getClassId<T>());
		if (findResult == std::end(m_sceneMap)) throw std::runtime_error("scene notFound");
		auto scene = (*findResult).second->castPtr<T>();
		setActive_runner<void, bool>::checkAndRun(scene, true);
	}

	// テンプレート引数のシーンを無効にする
	template<class T>
	inline void SceneManager::disableScene()
	{
		auto findResult = m_sceneMap.find(ClassTypeChecker::getClassId<T>());
		if (findResult == std::end(m_sceneMap)) throw std::runtime_error("scene notFound");
		auto scene = (*findResult).second->castPtr<T>();
		setActive_runner<void, bool>::checkAndRun<T*>(scene, false);
	}
}
#endif // !SCENE_MANAGER_H_