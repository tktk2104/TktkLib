#ifndef SHADER_USE_TEXTURE_ADDRESS_TYPE_H_
#define SHADER_USE_TEXTURE_ADDRESS_TYPE_H_

namespace tktk
{
	enum ShaderUseTextureAddressType
	{
		TEXTURE_ADDRESS_WRAP	= 1,
		TEXTURE_ADDRESS_MIRROR	= 2,
		TEXTURE_ADDRESS_CLAMP	= 3,
		TEXTURE_ADDRESS_BORDER	= 4,
	};
}
#endif // !SHADER_USE_TEXTURE_ADDRESS_TYPE_H_