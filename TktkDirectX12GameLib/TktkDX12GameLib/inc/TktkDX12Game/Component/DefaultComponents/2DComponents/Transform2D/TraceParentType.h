#ifndef TRACE_PARENT_TYPE_H_
#define TRACE_PARENT_TYPE_H_

namespace tktk
{
	// �e��Transform�Ƃ̊֌W���̎��
	enum class TraceParentType
	{
		// �e�̍��W�݂̂��Q�Ƃ���
		tracePos				= 1 << 0,

		// �e�̃X�P�[���݂̂��Q�Ƃ���
		traceScale				= 1 << 1,

		// �e�̉�]�݂̂��Q�Ƃ���
		traceRotation			= 1 << 2,

		// �e��Transform���Q�Ƃ��Ȃ�
		notTrace = 0,

		// �e�̍��W�ƃX�P�[�����Q�Ƃ���
		tracePosAndScale		= tracePos | traceScale,

		// �e�̍��W�Ɖ�]���Q�Ƃ���
		tracePosAndRotation		= tracePos | traceRotation,

		// �e�̃X�P�[���Ɖ�]���Q�Ƃ���
		traceScaleAndRotation	= traceScale | traceRotation,

		// �e��Transform�����S�ɎQ�Ƃ���
		trace_All				= tracePos | traceScale | traceRotation,
	};
}
#endif // !TRACE_PARENT_TYPE_H_