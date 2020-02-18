#ifndef PROCESSING_CLASS_USE_CHECKER_H_
#define PROCESSING_CLASS_USE_CHECKER_H_

#include <unordered_set>
#include "SafetyVoidPtr.h"

namespace tktk
{
	// ポインタの生存を管理するクラス
	class ProcessingClassUseChecker
	{
	public:

		ProcessingClassUseChecker() = default;
		~ProcessingClassUseChecker();

	public:

		// ポインタを追加する
		template<class T>
		SafetyVoidPtr* addPtr(T* ptr);

		// 第一テンプレートパラメータの型の新たなポインタを生成し、追加する
		template<class T, class... Args>
		SafetyVoidPtr* createPtr(const Args&... constructorValue);

		// 引数のポインタを削除する
		void deletePtr(SafetyVoidPtr* ptr);

		// 引数のポインタが死んでいるか？
		bool isNull(SafetyVoidPtr* ptr) const;

	private:

		// 存在しているポインタのコンテナ
		std::unordered_set<SafetyVoidPtr*> m_usingPtrList;
	};

	// ポインタを追加する
	template<class T>
	inline SafetyVoidPtr * ProcessingClassUseChecker::addPtr(T * ptr)
	{
		SafetyVoidPtr* newSafetyVoidPtr = new SafetyVoidPtr(ptr);
		m_usingPtrList.insert(newSafetyVoidPtr);
		return newSafetyVoidPtr;
	}

	// 第一テンプレートパラメータの型の新たなポインタを生成し、追加する
	template<class T, class ...Args>
	inline SafetyVoidPtr* ProcessingClassUseChecker::createPtr(const Args & ...constructorValue)
	{
		return addPtr(new T(constructorValue...));
	}
}

#endif // !PROCESSING_CLASS_USE_CHECKER_H_