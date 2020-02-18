#ifndef PROCESSING_SIMPLE_CONTAINER_H_
#define PROCESSING_SIMPLE_CONTAINER_H_

#include <vector>
#include <forward_list>
#include "ProcessingClassPtr.h"

namespace tktk
{
	// ���̃t���[�����[�N�̃C���X�^���X���Ǘ������{�̃R���e�i
	class ProcessingSimpleContainer
	{
	public:

		ProcessingSimpleContainer() = default;
		~ProcessingSimpleContainer();

		// �R�s�[�֎~
		ProcessingSimpleContainer(const ProcessingSimpleContainer& other) = delete;
		ProcessingSimpleContainer& operator = (const ProcessingSimpleContainer& other) = delete;

	public:

		// �V���ȃN���X��addClassList�ɒǉ�����
		// isStatic��true�ɂ���ƃC���X�^���X���ϒ��z��ŊǗ������
		template <class T>
		ProcessingClassPtr addClass(bool isStatic, T* rawPtr);

		// �R���e�i�̗v�f���X�V����
		void updateContainer();

		// �S�ẴN���X���폜����
		// ���폜���鏇�Ԃ͐���ł��Ȃ��̂Œ���
		void deleteAll();

	private:

		// addClassList�̗v�f��processingClassArray��processingClassList�Ɉړ�����
		void moveContainerNode();

		// �폜���ꂽ�N���X�̃|�C���^���R���e�i����폜����
		void removeDeleteClass();

	private:

		// �ǉ�����N���X�̏��
		struct AddClass
		{
			AddClass(ProcessingClassPtr arg1, bool arg2) 
				: processingClassPtr(arg1), isStatic(arg2){}

			ProcessingClassPtr processingClassPtr;
			bool isStatic{ true };
		};

	private:

		// �ǉ�����N���X�̈ꎞ�ۑ����X�g
		std::forward_list<AddClass> m_addClassList;
		// �ǉ�����ÓI�N���X�̐�
		unsigned int m_addStaticClassNum{ 0U };

		// �ÓI�ȃC���X�^���X���Ǘ�����ϒ��z��
		std::vector<ProcessingClassPtr> m_processingClassArray;
		// ���I�ȃC���X�^���X���Ǘ�����O�����X�g
		std::forward_list<ProcessingClassPtr> m_processingClassList;
	};

	// �V���ȃN���X��addClassList�ɒǉ�����
	// isStatic��true�ɂ���ƃC���X�^���X���ϒ��z��ŊǗ������
	template<class T>
	inline ProcessingClassPtr ProcessingSimpleContainer::addClass(bool isStatic, T * rawPtr)
	{
		if (isStatic) ++m_addStaticClassNum;
		ProcessingClassPtr newClass = ProcessingClassPtr(rawPtr);
		m_addClassList.emplace_front(newClass, isStatic);
		return newClass;
	}
}
#endif // !PROCESSING_SIMPLE_CONTAINER_H_