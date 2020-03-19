#ifndef FONT_LOADER_H_
#define FONT_LOADER_H_

#include <array>
#include <string>

namespace tktk
{
	class FontLoader
	{
	public:

		// "ÑMÇrÅ@Çoñæí©"
		static int getCharTextureId(const std::string& fontName, const std::string& c);

	private:

		static std::array<int, 65536> m_charTexture2DIdArray;
	};
}
#endif // !FONT_LOADER_H_
