#ifndef MOVIE_ASSETS_H_
#define MOVIE_ASSETS_H_

#include <string>
#include <unordered_map>
#include <TktkMath/Vector2.h>

namespace tktk
{
	class MovieAssets
	{
	public:
		
		MovieAssets() = default;

	public:

		void onDestroy() const;

	public:

		void loadMovie(int id, const std::string& assetFilePath);

		void eraseMovie(int id);

		void eraseMovieAll();

		int getMovieHandle(int id) const;

		Vector2 getMovieSize(int id) const;

	private:

		std::unordered_map<int, int> m_movieAssetsMap;
	};
}
#endif // !MOVIE_ASSETS_H_