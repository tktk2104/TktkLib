#ifndef CONSTANT_BUFFER_DATA_H_
#define CONSTANT_BUFFER_DATA_H_

#include <stdexcept>
#include <unordered_map>
#include <d3d11.h>
#include <TktkClassFuncProcessor/ProcessingClass/SafetyVoidPtr.h>
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	// 定数バッファと定数バッファに入れる予定のデータを管理するクラス
	class ConstantBufferData
	{
	public:

		template <class T>
		ConstantBufferData(T* data);
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
		BufferType* getTempBufferPtr() const;

		// 定数バッファに入れる予定のデータの特定の値にアクセスするための設定を行う
		void addParamLocation(int locationType, unsigned int locationFromBufferTop);

		// 「addParamLocation」で設定を行った値を更新する（テンプレート使用版）
		template <class BufferParamType>
		void setBufferParam(int locationType, const BufferParamType& param);

		// 「addParamLocation」で設定を行った値を更新する（テンプレート使用＆配列版）
		template <class BufferParamType>
		void setBufferParamArray(int locationType, BufferParamType * arrayFrontPtr, unsigned int arraySize);

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

	template<class T>
	inline ConstantBufferData::ConstantBufferData(T * data)
		: m_bufferSize(sizeof(T))
		, m_tempBufferPtr(data)
	{
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.ByteWidth = sizeof(T);
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;
		Screen::getDevicePtr()->CreateBuffer(&bufferDesc, NULL, &m_bufferPtr);
	}

	// 定数バッファに入れる予定のデータを取得する
	template<class BufferType>
	inline BufferType* ConstantBufferData::getTempBufferPtr() const
	{
		if (m_tempBufferPtr.canCast<BufferType>())
		{
			return m_tempBufferPtr.castPtr<BufferType>();
		}
		throw std::runtime_error("getTempBufferPtr error BufferType Invalid type");

		return nullptr;
	}

	// 「addParamLocation」で設定を行った値を更新する（テンプレート使用版）
	template<class BufferParamType>
	inline void ConstantBufferData::setBufferParam(int locationType, const BufferParamType & param)
	{
		if (m_paramLocationMap.find(locationType) == std::end(m_paramLocationMap)) return;

		char* tempBufferPtr = (char*)(m_tempBufferPtr.voidPtr());
		memcpy(tempBufferPtr + m_paramLocationMap.at(locationType), &param, sizeof(BufferParamType));
	}

	// 「addParamLocation」で設定を行った値を更新する（SafetyVoidPtr版）
	template<>
	inline void ConstantBufferData::setBufferParam(int locationType, const SafetyVoidPtr & param)
	{
		if (m_paramLocationMap.find(locationType) == std::end(m_paramLocationMap)) return;

		char* tempBufferPtr = (char*)(m_tempBufferPtr.voidPtr());
		memcpy(tempBufferPtr + m_paramLocationMap.at(locationType), param.voidPtr(), param.getClassSize());
	}

	// 「addParamLocation」で設定を行った値を更新する（テンプレート使用＆配列版）
	template<class BufferParamType>
	inline void ConstantBufferData::setBufferParamArray(int locationType, BufferParamType * arrayFrontPtr, unsigned int arraySize)
	{
		if (m_paramLocationMap.find(locationType) == std::end(m_paramLocationMap)) return;

		char* tempBufferPtr = (char*)(m_tempBufferPtr.voidPtr());
		memcpy(tempBufferPtr + m_paramLocationMap.at(locationType), arrayFrontPtr, sizeof(BufferParamType) * arraySize);
	}
}
#endif // !CONSTANT_BUFFER_DATA_H_