#include "TktkDirectX11Wrapper/Utility/lodedds.h"

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <assert.h>

namespace tktk
{
#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)	\
		((unsigned int)(unsigned char)(ch0) | (unsigned int)(unsigned char)(ch1) << 8)	\
		((unsigned int)(unsigned char)(ch2) << 16 | (unsigned int)(unsigned char)(ch3) << 24)
#endif // !MAKEFOURCC

#pragma pack(push, 1)

#define DDS_MAGIC 0x20534444

	struct DDS_PIXELFORMAT
	{
		unsigned int size;
		unsigned int flags;
		unsigned int fourCC;
		unsigned int RGBBitCount;
		unsigned int RBitMask;
		unsigned int GBitMask;
		unsigned int BBitMask;
		unsigned int ABitMask;
	};

#define DDS_FOURCC      0x00000004	// DDPF_FOURCC
#define DDS_RGB         0x00000040	// DDPF_RGB
#define DDS_RGBA        0x00000041	// DDPF_RGB | DDPF_ALPHAPIXELS
#define DDS_LUMINANCE   0x00020000	// DDPF_LUMINANCE
#define DDS_LUMINANCEA  0x00020001	// DDPF_LUMINANCE | DDPF_ALPHAPIXELS
#define DDS_ALPHA       0x00000002	// DDPF_ALPHA
#define DDS_PAL8        0x00000020	// DDPF_PALETTEINDEXED8

#define DDS_HEADER_FLAGS_TEXTURE        0x00001007  // DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT
#define DDS_HEADER_FLAGS_MIPMAP         0x00020000  // DDSD_MIPMAPCOUNT
#define DDS_HEADER_FLAGS_VOLUME         0x00800000  // DDSD_DEPTH
#define DDS_HEADER_FLAGS_PITCH          0x00000008  // DDSD_PITCH
#define DDS_HEADER_FLAGS_LINEARSIZE     0x00080000  // DDSD_LINEARSIZE

#define DDS_HEIGHT 0x00000002 // DDSD_HEIGHT
#define DDS_WIDTH  0x00000004 // DDSD_WIDTH

#define DDS_SURFACE_FLAGS_TEXTURE 0x00001000 // DDSCAPS_TEXTURE
#define DDS_SURFACE_FLAGS_MIPMAP  0x00400008 // DDSCAPS_COMPLEX | DDSCAPS_MIPMAP
#define DDS_SURFACE_FLAGS_CUBEMAP 0x00000008 // DDSCAPS_COMPLEX

#define DDS_CUBEMAP_POSITIVEX 0x00000600 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEX
#define DDS_CUBEMAP_NEGATIVEX 0x00000a00 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_NEGATIVEX
#define DDS_CUBEMAP_POSITIVEY 0x00001200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEY
#define DDS_CUBEMAP_NEGATIVEY 0x00002200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_NEGATIVEY
#define DDS_CUBEMAP_POSITIVEZ 0x00004200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEZ
#define DDS_CUBEMAP_NEGATIVEZ 0x00008200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_NEGATIVEZ

#define DDS_CUBEMAP_ALLFACES (DDS_CUBEMAP_POSITIVEX | DDS_CUBEMAP_NEGATIVEX |\
                              DDS_CUBEMAP_POSITIVEY | DDS_CUBEMAP_NEGATIVEY |\
                              DDS_CUBEMAP_POSITIVEZ | DDS_CUBEMAP_NEGATIVEZ)

#define DDS_CUBEMAP 0x00000200 // DDSCAPS2_CUBEMAP

#define DDS_FLAGS_VOLUME 0x00200000 // DDSCAPS2_VOLUME

	typedef struct
	{
		unsigned int size;
		unsigned int flags;
		unsigned int height;
		unsigned int width;
		unsigned int pitchOrLinearSize;
		unsigned int depth;
		unsigned int mipMapCount;
		unsigned int reserved1[11];
		DDS_PIXELFORMAT ddspf;
		unsigned int caps;
		unsigned int caps2;
		unsigned int caps3;
		unsigned int caps4;
		unsigned int reserved2;
	} DDS_HEADER;

	typedef struct
	{
		DXGI_FORMAT dxgiFormat;
		unsigned int resourceDimension;
		unsigned int miscFlag;
		unsigned int arraySize;
		unsigned int reserved;
	} DDS_HEADER_DXT10;

#pragma pack(pop)

	static unsigned int bitsPerPixel(DXGI_FORMAT fmt)
	{
		switch (fmt)
		{
		case DXGI_FORMAT_R32G32B32A32_TYPELESS:
		case DXGI_FORMAT_R32G32B32A32_FLOAT:
		case DXGI_FORMAT_R32G32B32A32_UINT:
		case DXGI_FORMAT_R32G32B32A32_SINT:
			return 128U;

		case DXGI_FORMAT_R32G32B32_TYPELESS:
		case DXGI_FORMAT_R32G32B32_FLOAT:
		case DXGI_FORMAT_R32G32B32_UINT:
		case DXGI_FORMAT_R32G32B32_SINT:
			return 96U;

		case DXGI_FORMAT_R16G16B16A16_TYPELESS:
		case DXGI_FORMAT_R16G16B16A16_FLOAT:
		case DXGI_FORMAT_R16G16B16A16_UNORM:
		case DXGI_FORMAT_R16G16B16A16_UINT:
		case DXGI_FORMAT_R16G16B16A16_SNORM:
		case DXGI_FORMAT_R16G16B16A16_SINT:
		case DXGI_FORMAT_R32G32_TYPELESS:
		case DXGI_FORMAT_R32G32_FLOAT:
		case DXGI_FORMAT_R32G32_UINT:
		case DXGI_FORMAT_R32G32_SINT:
		case DXGI_FORMAT_R32G8X24_TYPELESS:
		case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
		case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
		case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
			return 64U;

		case DXGI_FORMAT_R10G10B10A2_TYPELESS:
		case DXGI_FORMAT_R10G10B10A2_UNORM:
		case DXGI_FORMAT_R10G10B10A2_UINT:
		case DXGI_FORMAT_R11G11B10_FLOAT:
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:
		case DXGI_FORMAT_R8G8B8A8_UNORM:
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		case DXGI_FORMAT_R8G8B8A8_UINT:
		case DXGI_FORMAT_R8G8B8A8_SNORM:
		case DXGI_FORMAT_R8G8B8A8_SINT:
		case DXGI_FORMAT_R16G16_TYPELESS:
		case DXGI_FORMAT_R16G16_FLOAT:
		case DXGI_FORMAT_R16G16_UNORM:
		case DXGI_FORMAT_R16G16_UINT:
		case DXGI_FORMAT_R16G16_SNORM:
		case DXGI_FORMAT_R16G16_SINT:
		case DXGI_FORMAT_R32_TYPELESS:
		case DXGI_FORMAT_D32_FLOAT:
		case DXGI_FORMAT_R32_FLOAT:
		case DXGI_FORMAT_R32_UINT:
		case DXGI_FORMAT_R32_SINT:
		case DXGI_FORMAT_R24G8_TYPELESS:
		case DXGI_FORMAT_D24_UNORM_S8_UINT:
		case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
		case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
		case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
		case DXGI_FORMAT_R8G8_B8G8_UNORM:
		case DXGI_FORMAT_G8R8_G8B8_UNORM:
		case DXGI_FORMAT_B8G8R8A8_UNORM:
		case DXGI_FORMAT_B8G8R8X8_UNORM:
		case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
		case DXGI_FORMAT_B8G8R8A8_TYPELESS:
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
		case DXGI_FORMAT_B8G8R8X8_TYPELESS:
		case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
			return 32U;

		case DXGI_FORMAT_R8G8_TYPELESS:
		case DXGI_FORMAT_R8G8_UNORM:
		case DXGI_FORMAT_R8G8_UINT:
		case DXGI_FORMAT_R8G8_SNORM:
		case DXGI_FORMAT_R8G8_SINT:
		case DXGI_FORMAT_R16_TYPELESS:
		case DXGI_FORMAT_R16_FLOAT:
		case DXGI_FORMAT_D16_UNORM:
		case DXGI_FORMAT_R16_UNORM:
		case DXGI_FORMAT_R16_UINT:
		case DXGI_FORMAT_R16_SNORM:
		case DXGI_FORMAT_R16_SINT:
		case DXGI_FORMAT_B5G6R5_UNORM:
		case DXGI_FORMAT_B5G5R5A1_UNORM:
		case DXGI_FORMAT_B4G4R4A4_UNORM:
			return 16U;

		case DXGI_FORMAT_R8_TYPELESS:
		case DXGI_FORMAT_R8_UNORM:
		case DXGI_FORMAT_R8_UINT:
		case DXGI_FORMAT_R8_SNORM:
		case DXGI_FORMAT_R8_SINT:
		case DXGI_FORMAT_A8_UNORM:
			return 8U;

		case DXGI_FORMAT_R1_UNORM:
			return 1U;

		case DXGI_FORMAT_BC1_TYPELESS:
		case DXGI_FORMAT_BC1_UNORM:
		case DXGI_FORMAT_BC1_UNORM_SRGB:
		case DXGI_FORMAT_BC4_TYPELESS:
		case DXGI_FORMAT_BC4_UNORM:
		case DXGI_FORMAT_BC4_SNORM:
			return 4U;

		case DXGI_FORMAT_BC2_TYPELESS:
		case DXGI_FORMAT_BC2_UNORM:
		case DXGI_FORMAT_BC2_UNORM_SRGB:
		case DXGI_FORMAT_BC3_TYPELESS:
		case DXGI_FORMAT_BC3_UNORM:
		case DXGI_FORMAT_BC3_UNORM_SRGB:
		case DXGI_FORMAT_BC5_TYPELESS:
		case DXGI_FORMAT_BC5_UNORM:
		case DXGI_FORMAT_BC5_SNORM:
		case DXGI_FORMAT_BC6H_TYPELESS:
		case DXGI_FORMAT_BC6H_UF16:
		case DXGI_FORMAT_BC6H_SF16:
		case DXGI_FORMAT_BC7_TYPELESS:
		case DXGI_FORMAT_BC7_UNORM:
		case DXGI_FORMAT_BC7_UNORM_SRGB:
			return 8U;

		default:
			return 0U;
		}
	}

	static void getSurfaceInfo(
		unsigned int width,
		unsigned int height,
		DXGI_FORMAT fmt,
		unsigned int* outNumBytes,
		unsigned int* outRowBytes,
		unsigned int* outNumRows
	)
	{
		unsigned int numBytes = 0U;
		unsigned int rowBytes = 0U;
		unsigned int numRows = 0U;

		bool bc = false;
		bool packed = false;
		unsigned int bcnumBytesPerBlock = 0U;

		switch (fmt)
		{
		case DXGI_FORMAT_BC1_TYPELESS:
		case DXGI_FORMAT_BC1_UNORM:
		case DXGI_FORMAT_BC1_UNORM_SRGB:
		case DXGI_FORMAT_BC4_TYPELESS:
		case DXGI_FORMAT_BC4_UNORM:
		case DXGI_FORMAT_BC4_SNORM:
			bc = true;
			bcnumBytesPerBlock = 8U;
			break;

		case DXGI_FORMAT_BC2_TYPELESS:
		case DXGI_FORMAT_BC2_UNORM:
		case DXGI_FORMAT_BC2_UNORM_SRGB:
		case DXGI_FORMAT_BC3_TYPELESS:
		case DXGI_FORMAT_BC3_UNORM:
		case DXGI_FORMAT_BC3_UNORM_SRGB:
		case DXGI_FORMAT_BC5_TYPELESS:
		case DXGI_FORMAT_BC5_UNORM:
		case DXGI_FORMAT_BC5_SNORM:
		case DXGI_FORMAT_BC6H_TYPELESS:
		case DXGI_FORMAT_BC6H_UF16:
		case DXGI_FORMAT_BC6H_SF16:
		case DXGI_FORMAT_BC7_TYPELESS:
		case DXGI_FORMAT_BC7_UNORM:
		case DXGI_FORMAT_BC7_UNORM_SRGB:
			bc = true;
			bcnumBytesPerBlock = 16U;
			break;

		case DXGI_FORMAT_R8G8_B8G8_UNORM:
		case DXGI_FORMAT_G8R8_G8B8_UNORM:
			packed = true;
			break;
		}

		if (bc)
		{
			unsigned int numBlocksWide = 0U;

			if (width > 0U)
			{
				numBlocksWide = std::max<unsigned int>(1U, (width + 3U) / 4U);
			}

			unsigned int numBlocksHigh = 0U;

			if (height > 0U)
			{
				numBlocksHigh = std::max<unsigned int>(1U, (height + 3U) / 4U);
			}
			rowBytes = numBlocksWide * bcnumBytesPerBlock;
			numRows = numBlocksHigh;
		}
		else if (packed)
		{
			rowBytes = ((width + 1) >> 1) * 4;
			numRows = height;
		}
		else
		{
			unsigned int bpp = bitsPerPixel(fmt);
			rowBytes = (width * bpp + 7) / 8;
			numRows = height;
		}

		numBytes = rowBytes * numRows;

		if (outNumBytes)
		{
			*outNumBytes = numBytes;
		}

		if (outRowBytes)
		{
			*outRowBytes = rowBytes;
		}

		if (outNumRows)
		{
			*outNumRows = numRows;
		}

	}

#define ISBITMASK(r, g, b, a) (ddpf.RBitMask == r && ddpf.GBitMask == g && ddpf.BBitMask == b && ddpf.ABitMask == a)

	static DXGI_FORMAT getDXGIFormat(const DDS_PIXELFORMAT& ddpf)
	{
		if (ddpf.flags & DDS_RGB)
		{
			switch (ddpf.RGBBitCount)
			{
			case 32:

				if (ISBITMASK(0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000))
				{
					return DXGI_FORMAT_R8G8B8A8_UNORM;
				}

				if (ISBITMASK(0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000))
				{
					return DXGI_FORMAT_B8G8R8A8_UNORM;
				}

				if (ISBITMASK(0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000))
				{
					return DXGI_FORMAT_B8G8R8X8_UNORM;
				}

				if (ISBITMASK(0x3ff00000, 0x000ffc00, 0x000003ff, 0xc0000000))
				{
					return DXGI_FORMAT_R10G10B10A2_UNORM;
				}

				if (ISBITMASK(0x0000ffff, 0xffff0000, 0x00000000, 0x00000000))
				{
					return DXGI_FORMAT_R16G16_UNORM;
				}

				if (ISBITMASK(0xffffffff, 0x00000000, 0x00000000, 0x00000000))
				{
					return DXGI_FORMAT_R32_FLOAT;
				}

				break;

			case 24:

				break;

			case 16:

				if (ISBITMASK(0x7c00, 0x03e0, 0x001f, 0x8000))
				{
					return DXGI_FORMAT_B5G5R5A1_UNORM;
				}

				if (ISBITMASK(0xf800, 0x07e0, 0x001f, 0x0000))
				{
					return DXGI_FORMAT_B5G6R5_UNORM;
				}

				if (ISBITMASK(0x0f00, 0x00f0, 0x000f, 0xf000))
				{
					return DXGI_FORMAT_B4G4R4A4_UNORM;
				}

				break;

			default:
				break;
			}
		}
		else if (ddpf.flags & DDS_LUMINANCE)
		{
			if (ddpf.RGBBitCount == 8)
			{
				if (ISBITMASK(0x000000ff, 0x00000000, 0x00000000, 0x00000000))
				{
					return DXGI_FORMAT_R8_UNORM;
				}
			}

			if (ddpf.RGBBitCount == 16)
			{
				if (ISBITMASK(0x0000ffff, 0x00000000, 0x00000000, 0x00000000))
				{
					return DXGI_FORMAT_R16_UNORM;
				}

				if (ISBITMASK(0x000000ff, 0x00000000, 0x00000000, 0x0000ff00))
				{
					return DXGI_FORMAT_R8G8_UNORM;
				}
			}
		}
		else if (ddpf.flags & DDS_ALPHA)
		{
			if (ddpf.RGBBitCount == 8)
			{
				return DXGI_FORMAT_A8_UNORM;
			}
		}
		else if (ddpf.flags & DDS_FOURCC)
		{
			if (ddpf.fourCC == MAKEFOURCC('D', 'X', 'T', '1'))
			{
				return DXGI_FORMAT_BC1_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('D', 'X', 'T', '3'))
			{
				return DXGI_FORMAT_BC2_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('D', 'X', 'T', '5'))
			{
				return DXGI_FORMAT_BC3_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('D', 'X', 'T', '2'))
			{
				return DXGI_FORMAT_BC2_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('D', 'X', 'T', '4'))
			{
				return DXGI_FORMAT_BC3_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('A', 'T', 'I', '1'))
			{
				return DXGI_FORMAT_BC4_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('B', 'C', '4', 'U'))
			{
				return DXGI_FORMAT_BC4_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('B', 'C', '4', 'S'))
			{
				return DXGI_FORMAT_BC4_SNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('A', 'T', 'I', '2'))
			{
				return DXGI_FORMAT_BC4_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('B', 'C', '5', 'U'))
			{
				return DXGI_FORMAT_BC5_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('B', 'C', '5', 'S'))
			{
				return DXGI_FORMAT_BC5_SNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('R', 'G', 'B', 'G'))
			{
				return DXGI_FORMAT_R8G8_B8G8_UNORM;;
			}

			if (ddpf.fourCC == MAKEFOURCC('G', 'R', 'G', 'B'))
			{
				return DXGI_FORMAT_G8R8_G8B8_UNORM;;
			}

			switch (ddpf.fourCC)
			{
			case 36:

				return DXGI_FORMAT_R16G16B16A16_UNORM;

			case 110:

				return DXGI_FORMAT_R16G16B16A16_SNORM;

			case 111:

				return DXGI_FORMAT_R16_FLOAT;

			case 112:

				return DXGI_FORMAT_R16G16_FLOAT;

			case 113:

				return DXGI_FORMAT_R16G16B16A16_FLOAT;

			case 114:

				return DXGI_FORMAT_R32_FLOAT;

			case 115:

				return DXGI_FORMAT_R32G32_FLOAT;

			case 116:

				return DXGI_FORMAT_R32G32B32A32_FLOAT;
			}
		}

		return DXGI_FORMAT_UNKNOWN;
	}


	static void fillInitData(
		unsigned int width,
		unsigned int height,
		unsigned int depth,
		unsigned int mipCount,
		unsigned int arraySize,
		DXGI_FORMAT format,
		unsigned int maxSize,
		unsigned int bitSize,
		const unsigned char* bitData,
		unsigned int* twidth,
		unsigned int* theight,
		unsigned int* tdepth,
		unsigned int* skipMip,
		D3D11_SUBRESOURCE_DATA* initData
	)
	{
		if (!bitData || !initData)
		{
			throw std::runtime_error("lode dds file error");
		}

		*skipMip = 0U;
		*twidth = 0U;
		*theight = 0U;
		*tdepth = 0U;

		unsigned int NumBytes = 0U;
		unsigned int RowBytes = 0U;
		unsigned int NumRows = 0U;
		const unsigned char* pSrcBits = bitData;
		const unsigned char* pEndBits = bitData + bitSize;

		unsigned int index = 0U;

		for (unsigned int i = 0U; i < arraySize; i++)
		{
			unsigned int w = width;
			unsigned int h = height;
			unsigned int d = depth;

			for (unsigned int j = 0U; j < mipCount; j++)
			{
				getSurfaceInfo(w, h, format, &NumBytes, &RowBytes, &NumRows);

				if ((mipCount <= 1) || !maxSize || (w <= maxSize && h <= maxSize && d <= maxSize))
				{
					if (!*twidth)
					{
						*twidth = w;
						*theight = h;
						*tdepth = d;
					}

					initData[index].pSysMem = (const void*)pSrcBits;
					initData[index].SysMemPitch = static_cast<unsigned int>(RowBytes);
					initData[index].SysMemSlicePitch = static_cast<unsigned int>(NumBytes);

					++index;
				}
				else
				{
					++skipMip;
				}

				if (pSrcBits + (NumBytes * d) > pEndBits)
				{
					throw std::runtime_error("lode dds file error");
				}

				pSrcBits += NumBytes * d;

				w = w >> 1;
				h = h >> 1;
				d = d >> 1;

				if (w == 0)
				{
					w = 1;
				}

				if (h == 0)
				{
					h = 1;
				}

				if (d == 0)
				{
					d = 1;
				}
			}
		}

		if (!index)
		{
			throw std::runtime_error("lode dds file error");
		}
	}

	static HRESULT createD3DResources(
		ID3D11Device* device,
		unsigned int resDim,
		unsigned int width,
		unsigned int height,
		unsigned int depth,
		unsigned int mipCount,
		unsigned int arraySize,
		DXGI_FORMAT format,
		bool isCubeMap,
		D3D11_SUBRESOURCE_DATA* initData,
		ID3D11Resource** outTexture,
		ID3D11ShaderResourceView ** outTextureView
	)
	{
		if (!device || !initData)
		{
			return E_INVALIDARG;
		}

		HRESULT hr = E_FAIL;

		switch (resDim)
		{
		case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
			{
				D3D11_TEXTURE1D_DESC desc;
				desc.Width = width;
				desc.MipLevels = mipCount;
				desc.ArraySize = arraySize;
				desc.Format = format;
				desc.CPUAccessFlags = 0U;
				desc.MiscFlags = 0U;

				ID3D11Texture1D* tex = nullptr;
				hr = device->CreateTexture1D(&desc, initData, &tex);

				if (SUCCEEDED(hr) && tex != 0)
				{
					if (outTextureView != 0)
					{
						D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
						memset(&SRVDesc, 0, sizeof(SRVDesc));
						SRVDesc.Format = format;

						if (arraySize > 1U)
						{
							SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE1DARRAY;
							SRVDesc.Texture1DArray.MipLevels = desc.MipLevels;
							SRVDesc.Texture1DArray.ArraySize = arraySize;
						}
						else
						{
							SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE1D;
							SRVDesc.Texture1D.MipLevels = desc.MipLevels;
						}

						hr = device->CreateShaderResourceView(tex, &SRVDesc, outTextureView);

						if (FAILED(hr))
						{
							tex->Release();
							return hr;
						}
					}

					if (outTexture != 0)
					{
						*outTexture = tex;
					}
					else
					{
						tex->Release();
					}
				}
			}
			break;

		case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
			{
				D3D11_TEXTURE2D_DESC desc;
				desc.Width = width;
				desc.Height = height;
				desc.MipLevels = mipCount;
				desc.ArraySize = arraySize;
				desc.Format = format;
				desc.SampleDesc.Count = 1U;
				desc.SampleDesc.Quality = 0U;
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
				desc.CPUAccessFlags = 0U;
				desc.MiscFlags = (isCubeMap) ? D3D11_RESOURCE_MISC_TEXTURECUBE : 0U;

				ID3D11Texture2D* tex = nullptr;
				hr = device->CreateTexture2D(&desc, initData, &tex);

				if (SUCCEEDED(hr) && tex != 0)
				{
					if (outTextureView != 0)
					{
						D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
						memset(&SRVDesc, 0, sizeof(SRVDesc));
						SRVDesc.Format = format;

						if (isCubeMap)
						{
							if (arraySize > 6)
							{
								SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURECUBEARRAY;
								SRVDesc.TextureCubeArray.MipLevels = desc.MipLevels;
								SRVDesc.TextureCubeArray.NumCubes = arraySize / 6U;
							}
							else
							{
								SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURECUBE;
								SRVDesc.TextureCube.MipLevels = desc.MipLevels;
							}
						}
						else if (arraySize > 1U)
						{
							SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2DARRAY;
							SRVDesc.Texture2DArray.MipLevels = desc.MipLevels;
							SRVDesc.Texture2DArray.ArraySize = arraySize;
						}
						else
						{
							SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
							SRVDesc.Texture2D.MipLevels = desc.MipLevels;
						}

						hr = device->CreateShaderResourceView(tex, &SRVDesc, outTextureView);

						if (FAILED(hr))
						{
							tex->Release();
							return hr;
						}
					}

					if (outTexture != 0)
					{
						*outTexture = tex;
					}
					else
					{
						tex->Release();
					}
				}
			}
			break;

		case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
			{
				D3D11_TEXTURE3D_DESC desc;
				desc.Width = width;
				desc.Height = height;
				desc.Depth = depth;
				desc.MipLevels = mipCount;
				desc.Format = format;
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
				desc.CPUAccessFlags = 0U;
				desc.MiscFlags = 0U;

				ID3D11Texture3D* tex = nullptr;
				hr = device->CreateTexture3D(&desc, initData, &tex);

				if (SUCCEEDED(hr) && tex != 0)
				{
					if (outTextureView != 0)
					{
						D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
						memset(&SRVDesc, 0, sizeof(SRVDesc));
						SRVDesc.Format = format;
						SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE3D;
						SRVDesc.Texture3D.MipLevels = desc.MipLevels;

						hr = device->CreateShaderResourceView(tex, &SRVDesc, outTextureView);

						if (FAILED(hr))
						{
							tex->Release();
							return hr;
						}
					}

					if (outTexture != 0)
					{
						*outTexture = tex;
					}
					else
					{
						tex->Release();
					}
				}
			}
			break;
		}
		return hr;
	}

	static void createTextureFromDDS(
		ID3D11Device* device,
		const DDS_HEADER* header,
		const unsigned char* bitData,
		unsigned int bitSize,
		ID3D11Resource** outTexture,
		ID3D11ShaderResourceView** outTextureView,
		unsigned int maxSize
	)
	{
		HRESULT hr = S_OK;

		unsigned int width = header->width;
		unsigned int height = header->height;
		unsigned int depth = header->depth;

		unsigned int resDim = D3D11_RESOURCE_DIMENSION_UNKNOWN;
		unsigned int arraySize = 1;
		DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
		bool isCubeMap = false;

		unsigned int mipCount = header->mipMapCount;

		if (mipCount == 0U)
		{
			mipCount = 1U;
		}

		if ((header->ddspf.flags & DDS_FOURCC) && header->ddspf.fourCC == (MAKEFOURCC('D', 'X', '1', '0')))
		{
			const DDS_HEADER_DXT10* d3d10dxt = reinterpret_cast<const DDS_HEADER_DXT10*>((const char*)header + sizeof(DDS_HEADER));

			arraySize = d3d10dxt->arraySize;

			if (arraySize == 0)
			{
				throw std::runtime_error("lode dds file error");
			}

			if (bitsPerPixel(d3d10dxt->dxgiFormat) == 0)
			{
				throw std::runtime_error("lode dds file error");
			}

			format = d3d10dxt->dxgiFormat;

			switch (d3d10dxt->resourceDimension)
			{
			case D3D11_RESOURCE_DIMENSION_TEXTURE1D:

				if ((header->flags & DDS_HEIGHT) && height != 1)
				{
					throw std::runtime_error("lode dds file error");
				}
				height = depth = 1;
				break;

			case D3D11_RESOURCE_DIMENSION_TEXTURE2D:

				if (d3d10dxt->miscFlag & D3D11_RESOURCE_MISC_TEXTURECUBE)
				{
					arraySize *= 6;
					isCubeMap = true;
				}
				depth = 1;
				break;

			case D3D11_RESOURCE_DIMENSION_TEXTURE3D:

				if (!(header->flags & DDS_HEADER_FLAGS_VOLUME))
				{
					throw std::runtime_error("lode dds file error");
				}

				if (arraySize > 1)
				{
					throw std::runtime_error("lode dds file error");
				}
				break;

			default:

				throw std::runtime_error("lode dds file error");
			}

			resDim = d3d10dxt->resourceDimension;
		}
		else
		{
			format = getDXGIFormat(header->ddspf);

			if (format == DXGI_FORMAT_UNKNOWN)
			{
				throw std::runtime_error("lode dds file error");
			}

			if (header->flags & DDS_HEADER_FLAGS_VOLUME)
			{
				resDim = D3D11_RESOURCE_DIMENSION_TEXTURE3D;
			}
			else
			{
				if (header->caps2 & DDS_CUBEMAP)
				{
					if ((header->caps2 & DDS_CUBEMAP_ALLFACES) != DDS_CUBEMAP_ALLFACES)
					{
						throw std::runtime_error("lode dds file error");
					}

					arraySize = 6;
					isCubeMap = true;
				}

				depth = 1;
				resDim = D3D11_RESOURCE_DIMENSION_TEXTURE2D;
			}

			assert(bitsPerPixel(format) != 0U);
		}

		if (mipCount > D3D11_REQ_MIP_LEVELS)
		{
			throw std::runtime_error("lode dds file error");
		}

		switch (resDim)
		{
		case D3D11_RESOURCE_DIMENSION_TEXTURE1D:

			if ((arraySize > D3D11_REQ_TEXTURE1D_ARRAY_AXIS_DIMENSION) ||
				(width > D3D11_REQ_TEXTURE1D_U_DIMENSION))
			{
				throw std::runtime_error("lode dds file error");
			}
			break;

		case D3D11_RESOURCE_DIMENSION_TEXTURE2D:

			if (isCubeMap)
			{
				if ((arraySize > D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION) ||
					(width > D3D11_REQ_TEXTURECUBE_DIMENSION) ||
					(height > D3D11_REQ_TEXTURECUBE_DIMENSION))
				{
					throw std::runtime_error("lode dds file error");
				}
			}
			else if ((arraySize > D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION) ||
				(width > D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION) ||
				(height > D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION))
			{
				throw std::runtime_error("lode dds file error");
			}
			break;

		case D3D11_RESOURCE_DIMENSION_TEXTURE3D:

			if ((arraySize > 1U) ||
				(width > D3D11_REQ_TEXTURE3D_U_V_OR_W_DIMENSION) ||
				(height > D3D11_REQ_TEXTURE3D_U_V_OR_W_DIMENSION) ||
				(depth > D3D11_REQ_TEXTURE3D_U_V_OR_W_DIMENSION))
			{
				throw std::runtime_error("lode dds file error");
			}
			break;
		}

		std::unique_ptr<D3D11_SUBRESOURCE_DATA> initData(new D3D11_SUBRESOURCE_DATA[mipCount * arraySize]);

		unsigned int skipMip = 0U;
		unsigned int twidth = 0U;
		unsigned int theight = 0U;
		unsigned int tdepth = 0U;

		fillInitData(width, height, depth, mipCount, arraySize, format, maxSize, bitSize, bitData, &twidth, &theight, &tdepth, &skipMip, initData.get());

		hr = createD3DResources(device, resDim, twidth, theight, tdepth, mipCount - skipMip, arraySize, format, isCubeMap, initData.get(), outTexture, outTextureView);

		if (FAILED(hr) && !maxSize && (mipCount > 1))
		{
			switch (device->GetFeatureLevel())
			{
			case D3D_FEATURE_LEVEL_9_1:
			case D3D_FEATURE_LEVEL_9_2:

				if (isCubeMap)
				{
					maxSize = D3D_FL9_1_REQ_TEXTURECUBE_DIMENSION;
				}
				else
				{
					maxSize = (resDim == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
						? D3D_FL9_1_REQ_TEXTURE3D_U_V_OR_W_DIMENSION
						: D3D_FL9_1_REQ_TEXTURE2D_U_OR_V_DIMENSION;
				}
				break;

			case D3D_FEATURE_LEVEL_9_3:

				maxSize = (resDim == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
					? D3D_FL9_1_REQ_TEXTURE3D_U_V_OR_W_DIMENSION
					: D3D_FL9_3_REQ_TEXTURE2D_U_OR_V_DIMENSION;
				break;

			default:

				maxSize = (resDim == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
					? D3D10_REQ_TEXTURE3D_U_V_OR_W_DIMENSION
					: D3D10_REQ_TEXTURE2D_U_OR_V_DIMENSION;
				break;
			}

			fillInitData(width, height, depth, mipCount, arraySize, format, maxSize, bitSize, bitData, &twidth, &theight, &tdepth, &skipMip, initData.get());

			hr = createD3DResources(device, resDim, twidth, theight, tdepth, mipCount - skipMip, arraySize, format, isCubeMap, initData.get(), outTexture, outTextureView);
		}

		// TODO : どのヘッダーに定義があるのか調べる
		//DX::ThrowIfFailed(hr);
		if (FAILED(hr))
		{
			throw std::runtime_error("lode dds file error");
		}
	}

	void lodedds::load(
		ID3D11Device * device,
		const unsigned char * ddsData,
		unsigned int ddsDataSize,
		ID3D11Resource ** outTexture,
		ID3D11ShaderResourceView ** outTextureView,
		unsigned int maxSize
	)
	{
		if (!device || !ddsData || (!outTexture && !outTextureView))
		{
			throw std::runtime_error("lode dds file error");
		}

		if (ddsDataSize < (sizeof(unsigned int) + sizeof(DDS_HEADER)))
		{
			throw std::runtime_error("lode dds file error");
		}

		unsigned int dwMagicNumber = *(const unsigned int*)(ddsData);
		if (dwMagicNumber != DDS_MAGIC)
		{
			throw std::runtime_error("lode dds file error");
		}

		const DDS_HEADER* header = reinterpret_cast<const DDS_HEADER*>(ddsData + sizeof(unsigned int));

		if (header->size != sizeof(DDS_HEADER) ||
			header->ddspf.size != sizeof(DDS_PIXELFORMAT))
		{
			throw std::runtime_error("lode dds file error");
		}

		bool bDXT10Header = false;
		if ((header->ddspf.flags & DDS_FOURCC) &&
			(header->ddspf.fourCC == MAKEFOURCC('D', 'X', '1', '0')))
		{
			if (ddsDataSize < (sizeof(DDS_HEADER) + sizeof(unsigned int) + sizeof(DDS_HEADER_DXT10)))
			{
				throw std::runtime_error("lode dds file error");
			}
			bDXT10Header = true;
		}

		int offset = static_cast<int>(sizeof(unsigned int) + sizeof(DDS_HEADER) + (bDXT10Header ? sizeof(DDS_HEADER_DXT10) : 0));

		createTextureFromDDS(device, header, ddsData + offset, ddsDataSize - offset, outTexture, outTextureView, maxSize);
	}
}