#ifndef CONSTANT_BUFFER_ASSETS_H_
#define CONSTANT_BUFFER_ASSETS_H_

#include <unordered_map>
#include "ConstantBufferData.h"

namespace tktk
{
	// 「ConstantBufferData」を管理するクラス
	class ConstantBufferAssets
	{
	public:

		ConstantBufferAssets() = default;
		~ConstantBufferAssets();

		ConstantBufferAssets(const ConstantBufferAssets& other) = delete;
		ConstantBufferAssets& operator = (const ConstantBufferAssets& other) = delete;

	public:

		// 新たな定数バッファを作成する
		void create(int id, SafetyVoidPtr&& data);

		// 指定した定数バッファを削除する
		void erase(int id);

		// 全ての定数バッファを削除する
		void clear();

		// 指定した定数バッファを管理するクラスのポインタを取得する
		ConstantBufferData* getDataPtr(int id);

	private:

		// 定数バッファを管理するクラスの連想配列
		std::unordered_map<int, ConstantBufferData> m_assets;
	};
}
#endif // !CONSTANT_BUFFER_ASSETS_H_