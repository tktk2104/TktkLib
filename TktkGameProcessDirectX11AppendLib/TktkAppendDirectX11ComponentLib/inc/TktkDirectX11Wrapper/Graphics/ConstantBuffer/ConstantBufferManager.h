#ifndef CONSTANT_BUFFER_MANAGER_H_
#define CONSTANT_BUFFER_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/ConstantBufferAssets.h"
#include "Asset/SystemConstantBufferId.h"
#include "Asset/SystemConstantBufferParamLocationType.h"

namespace tktk
{
	// 「ConstantBufferAssets」に簡単にアクセスするためのクラス
	class ConstantBufferManager
	{
	public:

		// 「ConstantBufferAssets」を作成
		static void setUp();

	public:

		// 新たな定数バッファを作成する（テンプレート使用版）
		template<class BufferDataType>
		static void create(int id, BufferDataType* data);

		// 指定した定数バッファを削除する
		static void erase(int id);

		// 指定した定数バッファを管理するクラスのポインタを取得する
		static ConstantBufferData* getDataPtr(int id);

		// 指定した定数バッファに入れる予定のデータの特定の値にアクセスするための設定を行う
		static void addParamLocation(int id, int locationType, unsigned int locationFromBufferTop);

	private:

		static CfpPtr<ConstantBufferAssets> m_assetsPtr;
	};

	// 新たな定数バッファを作成する（テンプレート使用版）
	template<class BufferDataType>
	inline void ConstantBufferManager::create(int id, BufferDataType * data)
	{
		m_assetsPtr->create(id, data);
	}
}
#endif // !CONSTANT_BUFFER_MANAGER_H_