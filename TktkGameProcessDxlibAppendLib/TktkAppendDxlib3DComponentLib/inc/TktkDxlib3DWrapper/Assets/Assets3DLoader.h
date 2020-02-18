#ifndef ASSETS_3D_LOADER_H_
#define ASSETS_3D_LOADER_H_

#include <string>
#include <vector>

namespace tktk
{
	class Assets3DLoader
	{
	public:

		static void loadSoundFile(const std::string& loadFilePath);

		static void loadMeshFile(const std::string& loadFilePath);

		static void loadVertexShaderFile(const std::string& loadFilePath);

	private:

		static void loadSound(const std::vector<std::string>& splitWordData);

		static void duplicateSound(int originalSoundId, const std::string& rawId);

		static void loadMesh(const std::vector<std::string>& splitWordData);

		static void loadVertexShader(const std::vector<std::string>& splitWordData);
	};
}
#endif // !ASSETS_3D_LOADER_H_