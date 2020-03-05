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
	// �萔�o�b�t�@�ƒ萔�o�b�t�@�ɓ����\��̃f�[�^���Ǘ�����N���X
	class ConstantBufferData
	{
	public:

		explicit ConstantBufferData(SafetyVoidPtr&& data);
		~ConstantBufferData();

		ConstantBufferData(const ConstantBufferData& other) = delete;
		ConstantBufferData& operator = (const ConstantBufferData& other) = delete;

	public:

		// �萔�o�b�t�@�ɓ����\��̃f�[�^��萔�o�b�t�@�ɓ����
		void updateBuffer();

		// �萔�o�b�t�@�̃|�C���^���擾����
		ID3D11Buffer* getBufferPtr() const;

		// ���萔�o�b�t�@�f�[�^�ɒl��o�^����iSafetyVoidPtr�g�p�Łj�iupdateBuffer()���ĂԂƎ��ۂ̒萔�o�b�t�@�Ƀf�[�^���K�������j
		void setBufferData(const SafetyVoidPtr& bufferData);

		// ���萔�o�b�t�@�f�[�^�ɒl��o�^����iupdateBuffer()���ĂԂƎ��ۂ̒萔�o�b�t�@�Ƀf�[�^���K�������j
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

		// ���萔�o�b�t�@�f�[�^�̓���̒l��o�^���邽�߂̊֐��iTktkMetaFunc/HasValueChecker���g�p���鎖��O��Ƃ����֐��j
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

		// ���萔�o�b�t�@�f�[�^�̓���̔z��̒l��o�^���邽�߂̊֐��iTktkMetaFunc/HasValueChecker���g�p���鎖��O��Ƃ����֐��j
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

		// �萔�o�b�t�@�̑傫��
		unsigned int m_bufferSize { 0U };

		// �萔�o�b�t�@�̃|�C���^
		ID3D11Buffer* m_bufferPtr { nullptr };

		// �萔�o�b�t�@�ɓ����\��̃f�[�^�̃|�C���^
		SafetyVoidPtr m_tempBufferPtr;
	};
}
#endif // !CONSTANT_BUFFER_DATA_H_