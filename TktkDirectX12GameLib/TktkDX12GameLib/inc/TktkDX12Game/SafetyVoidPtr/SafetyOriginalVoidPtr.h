#ifndef SAFETY_ORIGINAL_VOID_PTR_H_
#define SAFETY_ORIGINAL_VOID_PTR_H_

#ifdef _DEBUG
#include <stdexcept>
#endif
#include <unordered_set>
#include "SafetyVoidPtrVTable.h"
#include "SafetyReplicaVoidPtr.h"

namespace tktk
{
	// コンストラクタ引数のポインタを「voidPtr」として管理するクラス
	// コピー不可、ムーブ可能だが、このクラスが管理するポインタを管理する「SafetyReplicaVoidPtr」を作る関数を持つ
	// このクラスのデストラクタが呼ばれる時、管理するポインタの元の型のデストラクタを呼ぶ
	class SafetyOriginalVoidPtr
	{
	public:

		friend SafetyReplicaVoidPtr;

	public:

		// void*のnullptrとして作成する
		SafetyOriginalVoidPtr();

		template<class T>
		explicit SafetyOriginalVoidPtr(T* rawPtr);

		// デストラクタで自身のポインタを開放する
		~SafetyOriginalVoidPtr();

		// コピー禁止
		SafetyOriginalVoidPtr(const SafetyOriginalVoidPtr& other) = delete;
		SafetyOriginalVoidPtr& operator = (const SafetyOriginalVoidPtr& other) = delete;

		// ムーブコンストラクタ
		SafetyOriginalVoidPtr(SafetyOriginalVoidPtr&& other) noexcept;
		SafetyOriginalVoidPtr& operator = (SafetyOriginalVoidPtr&& other) noexcept;

	public:

		static bool isUsePtr(void* ptr);

	public:

		// 引数のポインタと自身の持つポインタが同じかどうかを判定する
		template<class T>
		bool isSame(T* other) const;

		// テンプレートパラメーターの型に自身の持つポインタをキャストできるかを判定する
		template<class T>
		bool canCast() const;

		// テンプレートパラメーターの型に自身のポインタをキャストする
		template<class T>
		T* castPtr() const;

		// voidPtrを取得する
		void* voidPtr() const;

		// 管理しているポインタの元の型番号を取得する
		unsigned int getClassId() const;

		// 管理しているポインタの元の型のサイズを取得する
		unsigned int getClassSize() const;

	private:

		static std::unordered_set<void*> m_useChecker;

	private:

		void*					m_rawPtr;
		SafetyVoidPtrVTable*	m_vtablePtr;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class T>
	inline SafetyOriginalVoidPtr::SafetyOriginalVoidPtr(T* rawPtr)
		: m_rawPtr(rawPtr)
		, m_vtablePtr(&SafetyVoidPtrVTableInitializer<T>::m_vtable)
	{
		m_useChecker.insert(m_rawPtr);
	}

	template<class T>
	inline bool SafetyOriginalVoidPtr::isSame(T* other) const
	{
		return (m_rawPtr == other);
	}

	template<class T>
	inline bool SafetyOriginalVoidPtr::canCast() const
	{
		return (m_vtablePtr->getTypeId() == ClassTypeChecker::getClassId<T>());
	}

	template<class T>
	inline T* SafetyOriginalVoidPtr::castPtr() const
	{
#ifdef _DEBUG
		if (canCast<T>()) return reinterpret_cast<T*>(m_rawPtr);
		throw std::runtime_error("invalid cast");
#else
		return reinterpret_cast<T*>(m_rawPtr);
#endif // _DEBUG
	}
}
#endif // !SAFETY_ORIGINAL_VOID_PTR_H_