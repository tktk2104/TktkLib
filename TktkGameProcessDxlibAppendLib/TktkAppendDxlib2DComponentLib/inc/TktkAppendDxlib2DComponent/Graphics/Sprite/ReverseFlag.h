#ifndef REVERSE_FLAG_H_
#define REVERSE_FLAG_H_

namespace tktk
{
	// ���]�r�b�g�t���O
	enum ReverseFlag
	{
		// ���������̔��]�i�����Ȑ������ɂ��Ĕ��]�j
		HORIZONTAL_REVERSE	= 1 << 0,

		// ���������̔��]�i�����Ȑ������ɂ��Ĕ��]�j
		VERTICAL_REVERSE	= 1 << 1,

		// ���]����
		NOT_REVERSE = 0,
	};
}

#endif // !REVERSE_FLAG_H_