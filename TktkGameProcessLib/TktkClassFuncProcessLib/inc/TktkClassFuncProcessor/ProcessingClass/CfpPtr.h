#ifndef CFP_PTR_H_
#define CFP_PTR_H_

#include <stdexcept>
#include "ProcessingClassPtr.h"

namespace tktk
{
	// ���̃t���[�����[�N���g����Ŏg�p����|�C���^�N���X
	template <class T>
	class CfpPtr
	{
	public:

		// �f�t�H���g�R���X�g���N�^��nullptr�Ƃ��č쐬�����
		CfpPtr() = default;
		explicit CfpPtr(ProcessingClassPtr processingClassPtr);

		~CfpPtr() {}

	public:

		// ���g�̃|�C���^������ł�����nullptr���Ԃ�
		T* operator ->() const;

		// ���݂��̃|�C���^�������Ԓn���w���Ă�����true���Ԃ�
		// ���݂��Ƀ|�C���^������ł�����true���Ԃ�A�Е��̃|�C���^������ł�����false���Ԃ�
		bool operator ==(CfpPtr other) const;

		// ���݂��̃|�C���^�������Ԓn���w���Ă�����false���Ԃ�
		// ���݂��Ƀ|�C���^������ł�����false���Ԃ�A�Е��̃|�C���^������ł�����true���Ԃ�
		bool operator !=(CfpPtr other) const;

		// ���g�̃|�C���^������ł��Ȃ����𔻒肷��
		bool isNull() const;

		// ���̃t���[�����[�N�ł̃C���X�^���X�̋��ʋK�i���擾
		ProcessingClassPtr processingClassPtr() const;

	private:

		ProcessingClassPtr m_processingClassPtr;
	};

	template<class T>
	inline CfpPtr<T>::CfpPtr(ProcessingClassPtr processingClassPtr)
		: m_processingClassPtr(processingClassPtr)
	{
	}

	// ���g�̃|�C���^������ł�����nullptr���Ԃ�
	template<class T>
	inline T * CfpPtr<T>::operator->() const
	{
		if (m_processingClassPtr.isNull()) return nullptr;
		return m_processingClassPtr->castPtr<T>();
	}

	// ���݂��̃|�C���^�������Ԓn���w���Ă�����true���Ԃ�
	// ���݂��Ƀ|�C���^������ł�����true���Ԃ�A�Е��̃|�C���^������ł�����false���Ԃ�
	template<class T>
	inline bool CfpPtr<T>::operator==(CfpPtr other) const
	{
		if (m_processingClassPtr.isNull() && other.m_processingClassPtr.isNull()) return true;
		if (m_processingClassPtr.isNull() || other.m_processingClassPtr.isNull()) return false;
		return m_processingClassPtr->isSame(other.m_processingClassPtr->voidPtr());
	}

	// ���݂��̃|�C���^�������Ԓn���w���Ă�����false���Ԃ�
	// ���݂��Ƀ|�C���^������ł�����false���Ԃ�A�Е��̃|�C���^������ł�����true���Ԃ�
	template<class T>
	inline bool CfpPtr<T>::operator!=(CfpPtr other) const
	{
		return !(*this == other);
	}

	// �|�C���^������ł��Ȃ����𔻒肷��
	template<class T>
	inline bool CfpPtr<T>::isNull() const
	{
		return m_processingClassPtr.isNull();
	}

	// ���̃t���[�����[�N�ł̃C���X�^���X�̋��ʋK�i���擾
	template<class T>
	inline ProcessingClassPtr CfpPtr<T>::processingClassPtr() const
	{
		return m_processingClassPtr;
	}
}
#endif // !CFP_PTR_H_