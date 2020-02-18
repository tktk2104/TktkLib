#ifndef LODE_DDS_H_
#define LODE_DDS_H_

#include <d3d11.h>

namespace tktk
{
	class lodedds
	{
	public:

		static void load(
			ID3D11Device* device,
			const unsigned char* ddsData,
			unsigned int ddsDataSize,
			ID3D11Resource** outTexture,
			ID3D11ShaderResourceView** outTextureView,
			unsigned int maxSize
		);
	};
}
#endif // !LODE_DDS_H_