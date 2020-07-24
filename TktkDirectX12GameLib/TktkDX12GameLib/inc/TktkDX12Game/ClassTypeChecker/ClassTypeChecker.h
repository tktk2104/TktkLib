#ifndef CLASS_TYPE_CHECKER_H_
#define CLASS_TYPE_CHECKER_H_

namespace tktk
{
	// �N���X�̌^���ɑΉ�����uint�^���擾����N���X
	class ClassTypeChecker
	{
	public:

		// �e���v���[�g�����̌^�ɑΉ�����uint�^���擾����
		template <class T>
		static unsigned int getClassId();

	private:

		static unsigned int m_nextClassId;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class T>
	inline unsigned int ClassTypeChecker::getClassId()
	{
		static const unsigned int classId = m_nextClassId++;
		return classId;
	}
}
#endif // !CLASS_TYPE_CHECKER_H_