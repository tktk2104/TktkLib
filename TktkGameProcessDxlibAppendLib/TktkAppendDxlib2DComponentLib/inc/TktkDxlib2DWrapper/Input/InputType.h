#ifndef INPUT_TYPE_H_
#define INPUT_TYPE_H_

namespace tktk
{
	// ���͂̎��
	enum InputType
	{
		INPUT_BEGIN		= (0b0001),		// ���͊J�n��
		INPUT_PUSHING	= (0b0010),		// ���͌p����
		INPUT_ENDED		= (0b0100),		// ���͏I����
	};
}
#endif // !INPUT_TYPE_H_