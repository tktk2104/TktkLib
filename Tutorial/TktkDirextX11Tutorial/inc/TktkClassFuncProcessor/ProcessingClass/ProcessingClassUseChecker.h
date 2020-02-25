#ifndef PROCESSING_CLASS_USE_CHECKER_H_
#define PROCESSING_CLASS_USE_CHECKER_H_

#include <unordered_set>
#include "SafetyVoidPtr.h"

namespace tktk
{
	// �|�C���^�̐������Ǘ�����N���X
	class ProcessingClassUseChecker
	{
	public:

		ProcessingClassUseChecker() = default;
		~ProcessingClassUseChecker();

	public:

		// �|�C���^��ǉ�����
		template<class T>
		SafetyVoidPtr* addPtr(T* ptr);

		// ���e���v���[�g�p�����[�^�̌^�̐V���ȃ|�C���^�𐶐����A�ǉ�����
		template<class T, class... Args>
		SafetyVoidPtr* createPtr(const Args&... constructorValue);

		// �����̃|�C���^���폜����
		void deletePtr(SafetyVoidPtr* ptr);

		// �����̃|�C���^������ł��邩�H
		bool isNull(SafetyVoidPtr* ptr) const;

	private:

		// ���݂��Ă���|�C���^�̃R���e�i
		std::unordered_set<SafetyVoidPtr*> m_usingPtrList;
	};

	// �|�C���^��ǉ�����
	template<class T>
	inline SafetyVoidPtr * ProcessingClassUseChecker::addPtr(T * ptr)
	{
		SafetyVoidPtr* newSafetyVoidPtr = new SafetyVoidPtr(ptr);
		m_usingPtrList.insert(newSafetyVoidPtr);
		return newSafetyVoidPtr;
	}

	// ���e���v���[�g�p�����[�^�̌^�̐V���ȃ|�C���^�𐶐����A�ǉ�����
	template<class T, class ...Args>
	inline SafetyVoidPtr* ProcessingClassUseChecker::createPtr(const Args & ...constructorValue)
	{
		return addPtr(new T(constructorValue...));
	}
}

#endif // !PROCESSING_CLASS_USE_CHECKER_H_