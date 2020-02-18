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
		template<class BufferDataType>
		void create(int id, BufferDataType* data);

		// 指定した定数バッファを削除する
		void erase(int id);

		// 全ての定数バッファを削除する
		void clear();

		// 指定した定数バッファを管理するクラスのポインタを取得する
		ConstantBufferData* getDataPtr(int id);

		// 指定した定数バッファに入れる予定のデータの特定の値にアクセスするための設定を行う
		void addParamLocation(int id, int locationType, unsigned int locationFromBufferTop);

	private:

		// 定数バッファを管理するクラスの連想配列
		std::unordered_map<int, ConstantBufferData> m_assets;
	};

	// 新たな定数バッファを作成する（テンプレート使用版）
	template<class BufferDataType>
	inline void ConstantBufferAssets::create(int id, BufferDataType* data)
	{
		erase(id);

		m_assets.emplace(id, data);
	}
}
#endif // !CONSTANT_BUFFER_ASSETS_H_