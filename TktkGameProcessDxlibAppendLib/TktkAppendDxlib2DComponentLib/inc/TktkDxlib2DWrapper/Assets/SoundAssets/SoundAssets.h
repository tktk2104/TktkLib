#ifndef SOUND_ASSETS_H_
#define SOUND_ASSETS_H_

#include <string>
#include <unordered_map>

namespace tktk
{
	class SoundAssets
	{
	public:

		SoundAssets() = default;

	public:

		void onDestroy() const;

	public:

		void loadSound(int id, const std::string & assetFilePath, float pitchRate, float timeStretchRate, bool sound3d);

		void duplicateSound(int id, int originalSoundId);

		void eraseSound(int id);

		void eraseSoundAll();

		int getSoundHandle(int id) const;

	private:

		std::unordered_map<int, int> m_soundAssetsMap;
	};
}
#endif // !SOUND_ASSETS_H_
