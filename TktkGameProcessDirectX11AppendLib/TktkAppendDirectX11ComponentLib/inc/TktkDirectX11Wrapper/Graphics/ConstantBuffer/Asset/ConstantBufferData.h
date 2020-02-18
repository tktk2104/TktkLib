#ifndef CONSTANT_BUFFER_DATA_H_
#define CONSTANT_BUFFER_DATA_H_

#include <stdexcept>
#include <unordered_map>
#include <d3d11.h>
#include <TktkClassFuncProcessor/ProcessingClass/SafetyVoidPtr.h>
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	// �萔�o�b�t�@�ƒ萔�o�b�t�@�ɓ����\��̃f�[�^���Ǘ�����N���X
	class ConstantBufferData
	{
	public:

		template <class T>
		ConstantBufferData(T* data);
		~ConstantBufferData();

		ConstantBufferData(const ConstantBufferData& other) = delete;
		ConstantBufferData& operator = (const ConstantBufferData& other) = delete;

	public:

		// �萔�o�b�t�@�ɓ����\��̃f�[�^��萔�o�b�t�@�ɓ����
		void updateBuffer();

		// �萔�o�b�t�@�̃|�C���^���擾����
		ID3D11Buffer* getBufferPtr() const;

		// �萔�o�b�t�@�ɓ����\��̃f�[�^�̃|�C���^���擾����
		template <class BufferType>
		BufferType* getTempBufferPtr() const;

		// �萔�o�b�t�@�ɓ����\��̃f�[�^�̓���̒l�ɃA�N�Z�X���邽�߂̐ݒ���s��
		void addParamLocation(int locationType, unsigned int locationFromBufferTop);

		// �uaddParamLocation�v�Őݒ���s�����l���X�V����i�e���v���[�g�g�p�Łj
		template <class BufferParamType>
		void setBufferParam(int locationType, const BufferParamType& param);

		// �uaddParamLocation�v�Őݒ���s�����l���X�V����i�e���v���[�g�g�p���z��Łj
		template <class BufferParamType>
		void setBufferParamArray(int locationType, BufferParamType * arrayFrontPtr, unsigned int arraySize);

	private:

		// �萔�o�b�t�@�̑傫��
		unsigned int m_bufferSize { 0U };

		// �萔�o�b�t�@�̃|�C���^
		ID3D11Buffer* m_bufferPtr { nullptr };

		// �萔�o�b�t�@�ɓ����\��̃f�[�^�̃|�C���^
		SafetyVoidPtr m_tempBufferPtr;

		// �萔�o�b�t�@�ɓ����\��̃f�[�^�̓���̒l�ɃA�N�Z�X���邽�߂̏��
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

	// �萔�o�b�t�@�ɓ����\��̃f�[�^���擾����
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

	// �uaddParamLocation�v�Őݒ���s�����l���X�V����i�e���v���[�g�g�p�Łj
	template<class BufferParamType>
	inline void ConstantBufferData::setBufferParam(int locationType, const BufferParamType & param)
	{
		if (m_paramLocationMap.find(locationType) == std::end(m_paramLocationMap)) return;

		char* tempBufferPtr = (char*)(m_tempBufferPtr.voidPtr());
		memcpy(tempBufferPtr + m_paramLocationMap.at(locationType), &param, sizeof(BufferParamType));
	}

	// �uaddParamLocation�v�Őݒ���s�����l���X�V����iSafetyVoidPtr�Łj
	template<>
	inline void ConstantBufferData::setBufferParam(int locationType, const SafetyVoidPtr & param)
	{
		if (m_paramLocationMap.find(locationType) == std::end(m_paramLocationMap)) return;

		char* tempBufferPtr = (char*)(m_tempBufferPtr.voidPtr());
		memcpy(tempBufferPtr + m_paramLocationMap.at(locationType), param.voidPtr(), param.getClassSize());
	}

	// �uaddParamLocation�v�Őݒ���s�����l���X�V����i�e���v���[�g�g�p���z��Łj
	template<class BufferParamType>
	inline void ConstantBufferData::setBufferParamArray(int locationType, BufferParamType * arrayFrontPtr, unsigned int arraySize)
	{
		if (m_paramLocationMap.find(locationType) == std::end(m_paramLocationMap)) return;

		char* tempBufferPtr = (char*)(m_tempBufferPtr.voidPtr());
		memcpy(tempBufferPtr + m_paramLocationMap.at(locationType), arrayFrontPtr, sizeof(BufferParamType) * arraySize);
	}
}
#endif // !CONSTANT_BUFFER_DATA_H_