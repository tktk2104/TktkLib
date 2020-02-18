#ifndef PROCESSING_CLASS_PTR_H_
#define PROCESSING_CLASS_PTR_H_

#include "SafetyVoidPtr.h"
#include "ProcessingClassUseChecker.h"

namespace tktk
{
	// このフレームワークでのインスタンスの共通規格
	class ProcessingClassPtr
	{
	public:

		// デフォルトコンストラクタでnullptrとして作成される
		ProcessingClassPtr() = default;

		// 作成時に使用したポインタは自身のdeletePtr()を呼ぶと開放される
		// また、このクラスの静的変数がデストラクトされる時に開放されていなければ開放される
		template <class T>
		explicit ProcessingClassPtr(T* rawPtr);

		~ProcessingClassPtr() {}

	public:

		// 自身のポインタを削除する
		void deletePtr();

		// 自身のポインタが死んでいないかを判定する
		bool isNull() const;

		// 引数のポインタと自身の持つポインタが同じかどうかを判定する
		bool isSame(ProcessingClassPtr other) const;

		// 自身のポインタが死んでいたらnullptrが返る
		const SafetyVoidPtr* operator ->() const;

	private:

		SafetyVoidPtr* m_managementPtr { nullptr };

	private:

		static ProcessingClassUseChecker m_useChecker;
	};

	// 作成時に使用したポインタは自身のdeletePtr()を呼ぶと開放される
	// また、このクラスの静的変数がデストラクトされる時に開放されていなければ開放される
	template<class T>
	inline ProcessingClassPtr::ProcessingClassPtr(T * rawPtr)
		: m_managementPtr(m_useChecker.addPtr(rawPtr))
	{
	}
}
#endif // !PROCESSING_CLASS_PTR_H_