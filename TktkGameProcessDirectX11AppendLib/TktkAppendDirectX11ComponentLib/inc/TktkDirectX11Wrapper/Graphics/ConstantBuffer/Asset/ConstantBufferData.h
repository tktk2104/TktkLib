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

		// 定数バッファに入れる予定のデータのポインタを取得する
		template <class BufferType>
		BufferType* getTempBufferPtr() const
		{
			if (m_tempBufferPtr.canCast<BufferType>())
			{
				return m_tempBufferPtr.castPtr<BufferType>();
			}
			throw std::runtime_error("getTempBufferPtr error BufferType Invalid type");

			return nullptr;
		}

		// 定数バッファに入れる予定のデータの特定の値にアクセスするための設定を行う（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class LocationType, std::enable_if_t<is_idType_v<LocationType>>* = nullptr>
		void addParamLocation(LocationType locationType, unsigned int locationFromBufferTop)
		{
			addParamLocationImpl(static_cast<int>(locationType), locationFromBufferTop);
		}
		template<class LocationType, std::enable_if_t<!is_idType_v<LocationType>>* = nullptr>
		void addParamLocation(LocationType locationType, unsigned int locationFromBufferTop) { static_assert(false, "LocationType Fraud Type"); }

		// 「addParamLocation」で設定を行った値を更新する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class LocationType, class BufferParamType, std::enable_if_t<is_idType_v<LocationType>>* = nullptr>
		void setBufferParam(LocationType locationType, const BufferParamType& param)
		{
			if (m_paramLocationMap.find(static_cast<int>(locationType)) == std::end(m_paramLocationMap)) return;

			char* tempBufferPtr = (char*)(m_tempBufferPtr.voidPtr());
			memcpy(tempBufferPtr + m_paramLocationMap.at(static_cast<int>(locationType)), &param, sizeof(BufferParamType));
		}
		template<class LocationType, class BufferParamType, std::enable_if_t<!is_idType_v<LocationType>>* = nullptr>
		void setBufferParam(LocationType locationType, const BufferParamType& param) { static_assert(false, "LocationType Fraud Type"); }

		// 「addParamLocation」で設定を行った値を更新する（SafetyVoidPtr版）（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class LocationType, std::enable_if_t<is_idType_v<LocationType>>* = nullptr>
		void setBufferParam(LocationType locationType, const SafetyVoidPtr& param)
		{
			if (m_paramLocationMap.find(static_cast<int>(locationType)) == std::end(m_paramLocationMap)) return;

			char* tempBufferPtr = (char*)(m_tempBufferPtr.voidPtr());
			memcpy(tempBufferPtr + m_paramLocationMap.at(static_cast<int>(locationType)), param.voidPtr(), param.getClassSize());
		}
		template<class LocationType, std::enable_if_t<!is_idType_v<LocationType>>* = nullptr>
		void setBufferParam(LocationType locationType, const SafetyVoidPtr& param) { static_assert(false, "LocationType Fraud Type"); }

		// 「addParamLocation」で設定を行った値を更新する（配列版）
		template<class LocationType, class BufferParamType, std::enable_if_t<is_idType_v<LocationType>>* = nullptr>
		void setBufferParamArray(LocationType locationType, BufferParamType * arrayFrontPtr, unsigned int arraySize)
		{
			if (m_paramLocationMap.find(static_cast<int>(locationType)) == std::end(m_paramLocationMap)) return;

			char* tempBufferPtr = (char*)(m_tempBufferPtr.voidPtr());
			memcpy(tempBufferPtr + m_paramLocationMap.at(static_cast<int>(locationType)), arrayFrontPtr, sizeof(BufferParamType) * arraySize);
		}
		template<class LocationType, class BufferParamType, std::enable_if_t<!is_idType_v<LocationType>>* = nullptr>
		void setBufferParamArray(LocationType locationType, BufferParamType * arrayFrontPtr, unsigned int arraySize) { static_assert(false, "LocationType Fraud Type"); }

	private:

		void addParamLocationImpl(int locationType, unsigned int locationFromBufferTop);

	private:

		// 定数バッファの大きさ
		unsigned int m_bufferSize { 0U };

		// 定数バッファのポインタ
		ID3D11Buffer* m_bufferPtr { nullptr };

		// 定数バッファに入れる予定のデータのポインタ
		SafetyVoidPtr m_tempBufferPtr;

		// 定数バッファに入れる予定のデータの特定の値にアクセスするための情報
		std::unordered_map<int, unsigned int> m_paramLocationMap{};
	};
}
#endif // !CONSTANT_BUFFER_DATA_H_