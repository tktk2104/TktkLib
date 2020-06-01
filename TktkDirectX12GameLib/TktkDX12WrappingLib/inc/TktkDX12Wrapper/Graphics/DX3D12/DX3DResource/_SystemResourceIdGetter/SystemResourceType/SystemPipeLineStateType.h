#ifndef SYSTEM_PIPELINE_STATE_TYPE_H_
#define SYSTEM_PIPELINE_STATE_TYPE_H_

namespace tktk
{
	constexpr unsigned int SystemPipeLineStateNum = 2U;

	enum class SystemPipeLineStateType
	{
		Sprite		= 0U,
		BasicMesh	= 1U,
	};
}
#endif // !SYSTEM_PIPELINE_STATE_TYPE_H_