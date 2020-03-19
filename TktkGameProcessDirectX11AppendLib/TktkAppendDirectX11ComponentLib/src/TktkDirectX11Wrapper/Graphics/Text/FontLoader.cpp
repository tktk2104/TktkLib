#include "TktkDirectX11Wrapper/Graphics/Text/FontLoader.h"

#include <vector>
#include <stdlib.h>
#include "TktkDirectX11Wrapper/Utility/WindownsHeaderIncluder.h"
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"
#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2DManager.h"
#include "TktkDirectX11Wrapper/Graphics/Texture2D/Asset/SystemTexture2DId.h"

namespace tktk
{
	std::array<int, 65536> FontLoader::m_charTexture2DIdArray;

	int FontLoader::getCharTextureId(const std::string & fontName, const std::string & c)
	{
		wchar_t afterCastC[1];
		std::mbstowcs(afterCastC, c.c_str(), 1);

		unsigned int charTextureNum = static_cast<unsigned int>(*afterCastC);

		if (m_charTexture2DIdArray.at(charTextureNum) != 0)
		{
			return m_charTexture2DIdArray.at(charTextureNum);
		}

		int charTextureId = static_cast<int>(SystemTexture2DId::fontUseResStart) - static_cast<int>(charTextureNum);

		m_charTexture2DIdArray.at(charTextureNum) = charTextureId;

		int fontSize = 64;
		int fontWeight = 1000;

		wchar_t afterCastFontName[32];

		std::mbstowcs(afterCastFontName, fontName.c_str(), 32);

		LOGFONTW lf =
		{
			fontSize, 0, 0, 0, fontWeight, 0, 0, 0,
			SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN,
			*afterCastFontName
		};

		HFONT hFont = CreateFontIndirectW(&lf);

		HDC hdc = GetDC(NULL);

		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

		UINT code = (UINT)*afterCastC;

		const int gradFlag = GGO_GRAY4_BITMAP;

		int gard = 0;

		switch (gradFlag)
		{
		case GGO_GRAY2_BITMAP:
			gard = 4;
			break;
		case GGO_GRAY4_BITMAP:
			gard = 16;
			break;
		case GGO_GRAY8_BITMAP:
			gard = 64;
			break;
		}

		TEXTMETRIC tm;
		GetTextMetrics(hdc, &tm);
		GLYPHMETRICS gm;
		CONST MAT2 mat = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
		DWORD size = GetGlyphOutlineW(hdc, code, gradFlag, &gm, 0, NULL, &mat);

		std::vector<BYTE> mono;
		mono.resize(size);

		GetGlyphOutlineW(hdc, code, gradFlag, &gm, size, mono.data(), &mat);

		std::vector<unsigned char> textureData(4U * gm.gmCellIncX * tm.tmHeight, 0);

		Texture2DManager::create(
			charTextureId,
			Texture2DBindFlag::ShaderResource,
			textureData,
			gm.gmCellIncX,
			tm.tmHeight,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			Texture2DUsage::Dynamic,
			Texture2DCpuAccessFlag::Write,
			false
		);

		auto mappedRes = Texture2DManager::getData(charTextureId).mapSubResource();

		BYTE* bits = (BYTE*)mappedRes.pData;

		int ofs_x = gm.gmptGlyphOrigin.x;
		int ofs_y = tm.tmAscent - gm.gmptGlyphOrigin.y;
		int bmp_w = gm.gmBlackBoxX + (4 - (gm.gmBlackBoxX % 4)) % 4;
		int bmp_h = gm.gmBlackBoxY;
		int level = 17;

		DWORD alpha, color;

		memset(bits, 0, mappedRes.RowPitch * tm.tmHeight);

		for (int y = ofs_y; y < ofs_y + bmp_h; y++)
		{
			for (int x = ofs_x; x < ofs_x + bmp_w; x++)
			{
				alpha = (255 * mono.at(x - ofs_x + bmp_w * (y - ofs_y))) / (level - 1);
				color = 0x00ffffff | (alpha << 24);

				memcpy(
					(BYTE*)bits + mappedRes.RowPitch * y + 4 * x,
					&color,
					sizeof(DWORD)
				);
			}
		}
		Texture2DManager::getData(charTextureId).unMapSubResource();

		return charTextureId;
	}
}