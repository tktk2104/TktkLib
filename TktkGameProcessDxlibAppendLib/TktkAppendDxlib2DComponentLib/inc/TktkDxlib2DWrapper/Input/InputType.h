#ifndef INPUT_TYPE_H_
#define INPUT_TYPE_H_

namespace tktk
{
	// 入力の種類
	enum InputType
	{
		INPUT_BEGIN		= (0b0001),		// 入力開始時
		INPUT_PUSHING	= (0b0010),		// 入力継続中
		INPUT_ENDED		= (0b0100),		// 入力終了時
	};
}
#endif // !INPUT_TYPE_H_