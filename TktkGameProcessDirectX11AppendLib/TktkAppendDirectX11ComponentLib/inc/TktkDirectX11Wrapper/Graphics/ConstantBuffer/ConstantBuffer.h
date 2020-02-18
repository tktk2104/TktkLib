#ifndef CONSTANT_BUFFER_H_
#define CONSTANT_BUFFER_H_

#include "Asset/ConstantBufferData.h"
#include "Asset/SystemConstantBufferId.h"
#include "Asset/SystemConstantBufferParamLocationType.h"
#include "ConstantBufferManager.h"

namespace tktk
{
	// 「ConstantBufferManager」の実装の一部を隠すためのクラス
	class ConstantBuffer
	{
	public:

		// 新たな定数バッファを作成する（テンプレート使用版）
		// ※この関数でバッファを作る場合、idは1以上でなければならない
		template<class BufferDataType>
		static void create(int id, BufferDataType* data);

		// 指定した定数バッファを削除する
		// ※この関数でバッファを削除する場合、idは1以上でなければならない
		static void erase(int id);

		// 指定した定数バッファを管理するクラスのポインタを取得する
		static ConstantBufferData* getDataPtr(int id);

		// 指定した定数バッファに入れる予定のデータの特定の値にアクセスするための設定を行う
		static void addParamLocation(int id, int locationType, unsigned int locationFromBufferTop);
	};

	// 新たな定数バッファを作成する（テンプレート使用版）
	// ※この関数でバッファを作る場合、idは1以上でなければならない
	template<class BufferDataType>
	inline void ConstantBuffer::create(int id, BufferDataType* data)
	{
		if (id <= 0)
		{
			throw std::runtime_error("ConstantBufferId Fraud Value");
		}
		ConstantBufferManager::create(id, data);
	}
}
#endif // !CONSTANT_BUFFER_H_