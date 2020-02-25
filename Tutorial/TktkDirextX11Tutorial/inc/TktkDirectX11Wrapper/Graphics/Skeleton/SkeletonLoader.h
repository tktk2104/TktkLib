#ifndef SKELETON_LOADER_H_
#define SKELETON_LOADER_H_

#include <string>

namespace tktk
{
	// スケルトンを読み込む補助クラス
	class SkeletonLoader
	{
	public:

		// 以下の形式で整列しているバイナリデータの読み込み専用
		// 「char[32]name, int id, int parentId, Matrix4 transform, Matrix4 inverse」
		static void load(int id, const std::string& fileName);
	};
}
#endif // !SKELETON_LOADER_H_
