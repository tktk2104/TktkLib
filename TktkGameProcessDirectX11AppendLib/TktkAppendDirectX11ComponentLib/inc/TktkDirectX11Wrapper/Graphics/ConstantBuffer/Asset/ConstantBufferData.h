#ifndef CONSTANT_BUFFER_DATA_H_
#define CONSTANT_BUFFER_DATA_H_

#include <stdexcept>
#include <unordered_map>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/SafetyVoidPtr.h>
#include <d3d11.h>
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	// 定数バッファと定数バッファに入れる予定のデータを管理するクラス
	class ConstantBufferData
	{
	public:

		explicit ConstantBufferData(SafetyVoidPtr&& data);
		~ConstantBufferData();

		ConstantBufferData(const ConstantBufferData& other) = delete;
		ConstantBufferData& operator = (const ConstantBufferData& other) = delete;

	public:

		// 定数バッファに入れる予定のデータを定数バッファに入れる
		void updateBuffer();

		// 定数バッファのポインタを取得する
		ID3D11Buffer* getBufferPtr() const;

		// 仮定数バッファデータに値を登録する（SafetyVoidPtr使用版）（updateBuffer()を呼ぶと実際の定数バッファにデータが適応される）
		void setBufferData(const SafetyVoidPtr& bufferData);

		// 仮定数バッファデータに値を登録する（updateBuffer()を呼ぶと実際の定数バッファにデータが適応される）
		template <class BufferType>
		void setBufferData(BufferType&& bufferData)
		{
			if (m_tempBufferPtr.canCast<BufferType>())
			{
				auto afterCastPtr = m_tempBufferPtr.castPtr<BufferType>();
				(*afterCastPtr) = std::move(bufferData);
				return;
			}
			throw std::runtime_error("getTempBufferPtr error BufferType Invalid type");
		}

		// 仮定数バッファデータの特定の値を登録するための関数（TktkMetaFunc/HasValueCheckerを使用する事を前提とした関数）
		template <class BufferType, class BufferParamType, template<class ValueType> class ValueSetter>
		void setBufferParam(BufferParamType&& param)
		{
			if (m_tempBufferPtr.canCast<BufferType>())
			{
				ValueSetter<BufferParamType>::chackAndSet(m_tempBufferPtr.castPtr<BufferType>(), std::move(param));
				return;
			}
			throw std::runtime_error("getTempBufferPtr error BufferType Invalid type");
		}

		// 仮定数バッファデータの特定の配列の値を登録するための関数（TktkMetaFunc/HasValueCheckerを使用する事を前提とした関数）
		template <class BufferType, class BufferParamType, int ArraySize, template<class ValueType, int ArraySize> class ValueArraySetter>
		void setBufferArrayParam(const BufferParamType* arrayTop)
		{
			if (m_tempBufferPtr.canCast<BufferType>())
			{
				auto temp = m_tempBufferPtr.castPtr<BufferType>();

				ValueArraySetter<BufferParamType, ArraySize>::chackAndSet(m_tempBufferPtr.castPtr<BufferType>(), arrayTop);
				return;
			}
			throw std::runtime_error("getTempBufferPtr error BufferType Invalid type");
		}

	private:

		// 定数バッファの大きさ
		unsigned int m_bufferSize { 0U };

		// 定数バッファのポインタ
		ID3D11Buffer* m_bufferPtr { nullptr };

		// 定数バッファに入れる予定のデータのポインタ
		SafetyVoidPtr m_tempBufferPtr;
	};
}
#endif // !CONSTANT_BUFFER_DATA_H_