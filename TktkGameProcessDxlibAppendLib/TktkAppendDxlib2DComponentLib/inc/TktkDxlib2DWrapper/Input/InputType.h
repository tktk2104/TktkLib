#ifndef INPUT_TYPE_H_
#define INPUT_TYPE_H_

namespace tktk
{
	// “ü—Í‚Ìí—Ş
	enum InputType
	{
		INPUT_BEGIN		= (0b0001),		// “ü—ÍŠJn
		INPUT_PUSHING	= (0b0010),		// “ü—ÍŒp‘±’†
		INPUT_ENDED		= (0b0100),		// “ü—ÍI—¹
	};
}
#endif // !INPUT_TYPE_H_