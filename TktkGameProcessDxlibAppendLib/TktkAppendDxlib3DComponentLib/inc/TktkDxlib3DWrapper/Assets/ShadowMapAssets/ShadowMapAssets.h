#ifndef SHADOW_MAP_ASSETS_H_
#define SHADOW_MAP_ASSETS_H_

#include <unordered_map>

namespace tktk
{
	class ShadowMapAssets
	{
	public:

		ShadowMapAssets() = default;

	public:

		void onDestroy() const;

	public:

		// ¦‘å‚«‚³‚Í‚Q‚Ì‚æ‚Å‚ ‚é•K—v‚ª‚ ‚è‚Ü‚·
		void createShadowMap(int id, int sizeX, int sizeY);

		void eraseShadowMap(int id);

		void eraseShadowMapAll();

		int getShadowMapHandle(int id) const;

	private:

		std::unordered_map<int, int> m_shadowMapAssetsMap;
	};
}
#endif // !SHADOW_MAP_ASSETS_H_