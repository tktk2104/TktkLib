#ifndef RUN_FUNC_TYPE_H_
#define RUN_FUNC_TYPE_H_

namespace tktk
{
	enum RunFuncType
	{
		RUN_FUNC_frameBegin,
		RUN_FUNC_isActive,
		RUN_FUNC_start,
		RUN_FUNC_update,
		RUN_FUNC_collide,
		RUN_FUNC_afterCollide,
		RUN_FUNC_draw,
		RUN_FUNC_frameEnd,
		RUN_FUNC_isDestroy
	};
}

#endif // !RUN_FUNC_TYPE_H_