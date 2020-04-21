#ifndef SAFETY_UNIQUE_VOID_PTR_H_
#define SAFETY_UNIQUE_VOID_PTR_H_

#ifdef _DEBUG
#include <stdexcept>
#endif
#include "SafetyVoidPtrVTable.h"

namespace tktk
{
	// コンストラクタ引数のポインタを「voidPtr」として管理するクラス
	// コピー不可、ムーブ可能な「std::unique_ptr」のような性質
	// このクラスのデストラクタが呼ばれる時、管理するポインタの元の型のデストラクタを呼ぶ
	class SafetyUniqueVoidPtr
	{
	public:

		// void*のnullptrとして作成する
		SafetyUniqueVoidPtr();

		template<class T>
		explicit SafetyUniqueVoidPtr(T* rawPtr);

		// デストラクタで自身のポインタを開放する
		~SafetyUniqueVoidPtr();

		// コピー禁止
		SafetyUniqueVoidPtr(const SafetyUniqueVoidPtr& other) = delete;
		SafetyUniqueVoidPtr& operator = (const SafetyUniqueVoidPtr& other) = delete;

		// ムーブコンストラクタ
		SafetyUniqueVoidPtr(SafetyUniqueVoidPtr&& other) noexcept;
		SafetyUniqueVoidPtr& operator = (SafetyUniqueVoidPtr&& other) noexcept;

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

		void*					m_rawPtr;
		SafetyVoidPtrVTable*	m_vtablePtr;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class T>
	inline SafetyUniqueVoidPtr::SafetyUniqueVoidPtr(T* rawPtr)
		: m_rawPtr(rawPtr)
		, m_vtablePtr(&SafetyVoidPtrVTableInitializer<T>::m_vtable)
	{
	}

	// 引数のポインタと自身の持つポインタが同じかどうかを判定する
	template<class T>
	inline bool SafetyUniqueVoidPtr::isSame(T* other) const
	{
		return (m_rawPtr == other);
	}

	// テンプレートパラメーターの型に自身の持つポインタをキャストできるかを判定する
	template<class T>
	inline bool SafetyUniqueVoidPtr::canCast() const
	{
		return (m_vtablePtr->getTypeId() == ClassTypeChecker::getClassId<T>());
	}

	// テンプレートパラメーターの型に自身のポインタをキャストする
	template<class T>
	inline T* SafetyUniqueVoidPtr::castPtr() const
	{
#ifdef _DEBUG
		if (canCast<T>()) return reinterpret_cast<T*>(m_rawPtr);
		throw std::runtime_error("invalid cast");
#else
		return reinterpret_cast<T*>(m_rawPtr);
#endif // _DEBUG
	}
}
#endif // !SAFETY_UNIQUE_VOID_PTR_H_