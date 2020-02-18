#ifndef ASSETS_2D_LOADER_H_
#define ASSETS_2D_LOADER_H_

#include <string>
#include <vector>

namespace tktk
{
	class Assets2DLoader
	{
	public:

		static void loadSoundFile(const std::string& loadFilePath);

		static void loadTextureFile(const std::string& loadFilePath);

		static void loadMovieFile(const std::string& loadFilePath);

		static void loadPixelShaderFile(const std::string& loadFilePath);

	private:

		static void loadSound(const std::vector<std::string>& splitWordData);

		static void loadTexture(const std::vector<std::string>& splitWordData);

		static void loadMovie(const std::vector<std::string>& splitWordData);

		static void loadPixelShader(const std::vector<std::string>& splitWordData);
	};
}
#endif // !ASSETS_2D_LOADER_H_