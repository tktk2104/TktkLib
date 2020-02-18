#ifndef PROCESSING_CLASS_PTR_H_
#define PROCESSING_CLASS_PTR_H_

#include "SafetyVoidPtr.h"
#include "ProcessingClassUseChecker.h"

namespace tktk
{
	// ���̃t���[�����[�N�ł̃C���X�^���X�̋��ʋK�i
	class ProcessingClassPtr
	{
	public:

		// �f�t�H���g�R���X�g���N�^��nullptr�Ƃ��č쐬�����
		ProcessingClassPtr() = default;

		// �쐬���Ɏg�p�����|�C���^�͎��g��deletePtr()���ĂԂƊJ�������
		// �܂��A���̃N���X�̐ÓI�ϐ����f�X�g���N�g����鎞�ɊJ������Ă��Ȃ���ΊJ�������
		template <class T>
		explicit ProcessingClassPtr(T* rawPtr);

		~ProcessingClassPtr() {}

	public:

		// ���g�̃|�C���^���폜����
		void deletePtr();

		// ���g�̃|�C���^������ł��Ȃ����𔻒肷��
		bool isNull() const;

		// �����̃|�C���^�Ǝ��g�̎��|�C���^���������ǂ����𔻒肷��
		bool isSame(ProcessingClassPtr other) const;

		// ���g�̃|�C���^������ł�����nullptr���Ԃ�
		const SafetyVoidPtr* operator ->() const;

	private:

		SafetyVoidPtr* m_managementPtr { nullptr };

	private:

		static ProcessingClassUseChecker m_useChecker;
	};

	// �쐬���Ɏg�p�����|�C���^�͎��g��deletePtr()���ĂԂƊJ�������
	// �܂��A���̃N���X�̐ÓI�ϐ����f�X�g���N�g����鎞�ɊJ������Ă��Ȃ���ΊJ�������
	template<class T>
	inline ProcessingClassPtr::ProcessingClassPtr(T * rawPtr)
		: m_managementPtr(m_useChecker.addPtr(rawPtr))
	{
	}
}
#endif // !PROCESSING_CLASS_PTR_H_