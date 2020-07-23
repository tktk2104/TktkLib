#ifndef WINDOW_INIT_PARAM_H_
#define WINDOW_INIT_PARAM_H_

#include <string>
#include <Windows.h>
#undef min
#undef max
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// �E�B���h�E�����Ƃ��ɕK�v�Ȉ����̍\����
	struct WindowInitParam
	{
		HINSTANCE			hInstance;
		int					nCmdShow;
		std::string			windowName;
		tktkMath::Vector2	windowSize;
	};
}
#endif // !WINDOW_INIT_PARAM_H_