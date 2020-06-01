#ifndef SYSTEM_ROOT_SIGNATURE_TYPE_H_
#define SYSTEM_ROOT_SIGNATURE_TYPE_H_

namespace tktk
{
	constexpr unsigned int SystemRootSignatureNum = 2U;

	enum class SystemRootSignatureType
	{
		Sprite		= 0U,
		BasicMesh	= 1U
	};
}
#endif // !SYSTEM_ROOT_SIGNATURE_TYPE_H_