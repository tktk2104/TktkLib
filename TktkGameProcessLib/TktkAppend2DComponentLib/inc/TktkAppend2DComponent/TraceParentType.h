#ifndef TRACE_PARENT_TYPE_H_
#define TRACE_PARENT_TYPE_H_

namespace tktk
{
	// �e��Transform�Ƃ̊֌W���̎��
	enum TraceParentType
	{
		// �e�̍��W�݂̂��Q�Ƃ���
		TRACE_PARENT_POS = 1 << 0,

		// �e�̃X�P�[���݂̂��Q�Ƃ���
		TRACE_PARENT_SCALE = 1 << 1,

		// �e�̉�]�݂̂��Q�Ƃ���
		TRACE_PARENT_ROTATION = 1 << 2,

		// �e��Transform���Q�Ƃ��Ȃ�
		NOT_TRACE_PARENT = 0,

		// �e�̍��W�ƃX�P�[�����Q�Ƃ���
		TRACE_PARENT_POS_AND_SCALE = TRACE_PARENT_POS | TRACE_PARENT_SCALE,

		// �e�̍��W�Ɖ�]���Q�Ƃ���
		TRACE_PARENT_POS_AND_ROTATION = TRACE_PARENT_POS | TRACE_PARENT_ROTATION,

		// �e�̃X�P�[���Ɖ�]���Q�Ƃ���
		TRACE_PARENT_SCALE_AND_ROTATION = TRACE_PARENT_SCALE | TRACE_PARENT_ROTATION,

		// �e��Transform�����S�ɎQ�Ƃ���
		TRACE_PARENT_ALL = TRACE_PARENT_POS | TRACE_PARENT_SCALE | TRACE_PARENT_ROTATION,
	};
}

#endif // !TRACE_PARENT_TYPE_H_