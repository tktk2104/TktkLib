#ifndef WINDOW_INIT_PARAM_H_
#define WINDOW_INIT_PARAM_H_

#include <string>
#include <TktkMath/Structs/Vector2.h>
#include <Windows.h>
#undef min
#undef max

namespace tktk
{
	// �E�B���h�E�����Ƃ��ɕK�v�Ȉ����̍\����
	struct WindowInitParam
	{
		HINSTANCE hInstance;
		int nCmdShow;
		const std::string& windowName;
		const tktkMath::Vector2& windowSize;
	};
}
#endif // !WINDOW_INIT_PARAM_H_