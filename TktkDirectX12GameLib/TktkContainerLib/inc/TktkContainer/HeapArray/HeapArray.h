#ifndef HEAP_ARRAY_H_
#define HEAP_ARRAY_H_

#include <memory>

namespace tktk
{
	template <class NodeType, class Allocator = std::allocator<NodeType>>
	class HeapArray
	{
	public:

		HeapArray(unsigned int arrayMaxSize);
		~HeapArray();

	public:

		unsigned int arrayMaxSize() const;

	public:

		// �m�ۂ����������̐擪����g�p�\�ȃ����������݂��邩�T���A��������������g���ăC���X�^���X���������ł��̃A�h���X�̃|�C���^��Ԃ��A������Ȃ�������nullptr��Ԃ�
		template <class... ConstructorArgs>
		NodeType* emplace(ConstructorArgs&&... args);

		// �m�ۂ����������̓���ʒu�i�擪�A�h���X + (index * sizeof(NodeType))�j�̃����������g�p�Ȃ�Έ������g���ăC���X�^���X���������ł��̃A�h���X�̃|�C���^��Ԃ��A�g�p�ς݂�������nullptr��Ԃ�
		template <class... ConstructorArgs>
		NodeType* emplaceAt(unsigned int index, ConstructorArgs&&... args);

		// �w�肵���|�C���^���g�p�ς݂ł���΂��̃|�C���^���w���C���X�^���X���f�X�g���N�g����
		void erase(NodeType** eraseNode);

		// �m�ۂ����������̓���ʒu�i�擪�A�h���X + (index * sizeof(NodeType))�j�̃��������g�p���Ȃ�΁A���̃������ɑ��݂���C���X�^���X���f�X�g���N�g����
		void eraseAt(unsigned int index);

		// �g�p���̃������ɑ��݂���C���X�^���X��S�ăf�X�g���N�g����
		void clear();

	public:

		// �w�肵���C���f�b�N�X�̃|�C���^���擾����i�C���f�b�N�X���w�����������������g�p�Ȃ�nullPtr��Ԃ��j
		NodeType* at(unsigned int index) const;

	private:

		// �A���P�[�^
		Allocator		m_allocator;

		// �z��̍ő吔�i�um_arrayMaxSize * sizeof(NodeType)�v�̑傫���̃q�[�v�����������g�̔z��̂��߂Ɋm�ۂ����j
		unsigned int	m_arrayMaxSize;

		// �m�ۂ����������̐擪�A�h���X
		NodeType*		m_arrayTopPos;
		
		// �z��̗v�f���g�p���Ă��邩���Ǘ�����r�b�g�f�[�^�iuint�z��Ƃ��č쐬�j
		unsigned int*	m_arrayNodeUseCheckBitFlag;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class NodeType, class Allocator>
	inline HeapArray<NodeType, Allocator>::HeapArray(unsigned int arrayMaxSize)
		: m_arrayMaxSize(arrayMaxSize)
		, m_arrayTopPos(std::allocator_traits<Allocator>::allocate(m_allocator, m_arrayMaxSize)) // ���������m��
		, m_arrayNodeUseCheckBitFlag(new unsigned int[1U + (m_arrayMaxSize / 32U)])// ��uint�P��32�̗v�f���Ǘ��\
	{
		// �z��v�f�g�p�Ǘ��r�b�g�f�[�^�̃t���O��S�Đ؂�B��memset()�̑�O�����̓o�C�g���w��
		for (unsigned int i = 0; i < (1U + (m_arrayMaxSize / 32U)); i++)
		{
			m_arrayNodeUseCheckBitFlag[i] = 0U;
		}
	}

	template<class NodeType, class Allocator>
	inline HeapArray<NodeType, Allocator>::~HeapArray()
	{
		// �g�p���������݂̂��f�X�g���N�g����
		for (unsigned int i = 0; i < m_arrayMaxSize; i++)
		{
			if ((m_arrayNodeUseCheckBitFlag[i / 32U] & (1U << (i % 32U))) != 0U)
			{
				std::allocator_traits<Allocator>::destroy(m_allocator, m_arrayTopPos + i);
			}
		}

		// �m�ۂ������������J������
		std::allocator_traits<Allocator>::deallocate(m_allocator, m_arrayTopPos, m_arrayMaxSize);

		// �z��v�f�g�p�Ǘ��r�b�g�f�[�^���J������
		delete[] m_arrayNodeUseCheckBitFlag;
	}

	template<class NodeType, class Allocator>
	inline unsigned int HeapArray<NodeType, Allocator>::arrayMaxSize() const
	{
		return m_arrayMaxSize;
	}

	// �m�ۂ����������̐擪����g�p�\�ȃ����������݂��邩�T���A��������������g���ăC���X�^���X���������ł��̃A�h���X�̃|�C���^��Ԃ��A������Ȃ�������nullptr��Ԃ�
	template<class NodeType, class Allocator>
	template<class ...ConstructorArgs>
	inline NodeType* HeapArray<NodeType, Allocator>::emplace(ConstructorArgs&& ...args)
	{
		for (unsigned int i = 0U; i < m_arrayMaxSize; i++)
		{
			// ���g�p����������������
			if ((m_arrayNodeUseCheckBitFlag[i / 32U] & (1U << (i % 32U))) == 0U)
			{
				// �R���X�g���N�g����
				std::allocator_traits<Allocator>::construct(m_allocator, m_arrayTopPos + i, std::forward<ConstructorArgs>(args)...);

				// �쐬�����C���X�^���X�̑��݂��郁�������g�p���ɂ���
				m_arrayNodeUseCheckBitFlag[i / 32U] |= (1U << (i % 32U));

				// �쐬�����C���X�^���X�̃|�C���^��Ԃ�
				return (m_arrayTopPos + i);
			}
		}
		return nullptr;
	}

	// �m�ۂ����������̓���ʒu�i�擪�A�h���X + (index * sizeof(NodeType))�j�̃����������g�p�Ȃ�Έ������g���ăC���X�^���X���������ł��̃A�h���X�̃|�C���^��Ԃ��A�g�p�ς݂�������nullptr��Ԃ�
	template<class NodeType, class Allocator>
	template<class ...ConstructorArgs>
	inline NodeType* HeapArray<NodeType, Allocator>::emplaceAt(unsigned int index, ConstructorArgs&& ...args)
	{
		// �C���f�b�N�X���͈͊O���w���Ă�����
		if (index >= m_arrayMaxSize)
		{
			return nullptr;
		}

		// �����̃C���f�b�N�X�����g�p���������w���Ă�����
		if ((m_arrayNodeUseCheckBitFlag[index / 32U] & (1U << (index % 32U))) == 0U)
		{
			// �R���X�g���N�g����
			std::allocator_traits<Allocator>::construct(m_allocator, m_arrayTopPos + index, std::forward<ConstructorArgs>(args)...);

			// �쐬�����C���X�^���X�̑��݂��郁�������g�p���ɂ���
			m_arrayNodeUseCheckBitFlag[index / 32U] |= (1U << (index % 32U));

			// �쐬�����C���X�^���X�̃|�C���^��Ԃ�
			return (m_arrayTopPos + index);
		}
		return nullptr;
	}

	// �w�肵���|�C���^���g�p�ς݂ł���΂��̃|�C���^���w���C���X�^���X���f�X�g���N�g����
	template<class NodeType, class Allocator>
	inline void HeapArray<NodeType, Allocator>::erase(NodeType** eraseNode)
	{
		// �|�C���^���s���������牽�����Ȃ�
		if ((*eraseNode) < m_arrayTopPos || (*eraseNode) > (m_arrayTopPos * m_arrayMaxSize))
		{
			return;
		}

		// �|�C���^����C���f�b�N�X���t�Z����
		unsigned int index = (static_cast<unsigned int>((*eraseNode)) - static_cast<unsigned int>(m_arrayTopPos)) / sizeof(NodeType);

		// �����̃C���f�b�N�X���g�p�����������w���Ă�����
		if ((m_arrayNodeUseCheckBitFlag[index / 32U] & (1U << (index % 32U))) != 0U)
		{
			// �����̃C���f�b�N�X�̃C���X�^���X���f�X�g���N�g����
			std::allocator_traits<Allocator>::destroy(m_allocator, m_arrayTopPos + index);

			// �폜�����C���X�^���X�̃������𖢎g�p�ɂ���
			m_arrayNodeUseCheckBitFlag[index / 32U] ^= (1U << (index % 32U));

			(*eraseNode) = nullptr;
		}
	}

	// �m�ۂ����������̓���ʒu�i�擪�A�h���X + (index * sizeof(NodeType))�j�̃��������g�p���Ȃ�΁A���̃������ɑ��݂���C���X�^���X���f�X�g���N�g����
	template<class NodeType, class Allocator>
	inline void HeapArray<NodeType, Allocator>::eraseAt(unsigned int index)
	{
		// �����̃C���f�b�N�X���g�p�����������w���Ă�����
		if ((m_arrayNodeUseCheckBitFlag[index / 32U] & (1U << (index % 32U))) != 0U)
		{
			// �����̃C���f�b�N�X�̃C���X�^���X���f�X�g���N�g����
			std::allocator_traits<Allocator>::destroy(m_allocator, m_arrayTopPos + index);

			// �폜�����C���X�^���X�̃������𖢎g�p�ɂ���
			m_arrayNodeUseCheckBitFlag[index / 32U] ^= (1U << (index % 32U));
		}
	}

	// �g�p���̃������ɑ��݂���C���X�^���X��S�ăf�X�g���N�g����
	template<class NodeType, class Allocator>
	inline void HeapArray<NodeType, Allocator>::clear()
	{
		// �g�p���������݂̂��f�X�g���N�g����
		for (unsigned int i = 0; i < m_arrayMaxSize; i++)
		{
			if ((m_arrayNodeUseCheckBitFlag[i / 32U] & (1U << (i % 32U))) != 0U)
			{
				std::allocator_traits<Allocator>::destroy(m_allocator, m_arrayTopPos + i);

				// �폜�����C���X�^���X�̃������𖢎g�p�ɂ���
				m_arrayNodeUseCheckBitFlag[i / 32U] ^= (1U << (i % 32U));
			}
		}
	}

	template<class NodeType, class Allocator>
	inline NodeType* HeapArray<NodeType, Allocator>::at(unsigned int index) const
	{
		// �����̃C���f�b�N�X�����g�p���������w���Ă�����nullptr��Ԃ�
		if ((m_arrayNodeUseCheckBitFlag[index / 32U] & (1U << (index % 32U))) == 0U) return nullptr;

		return (m_arrayTopPos + index);
	}
}
#endif // !HEAP_ARRAY_H_

// �v�R�[�h
//// �z��̎g�p���r�b�g�t���O��32�r�b�g������
//for (unsigned int i = 0; i < m_arrayNodeUseCheckBitFlagsArraySize; i++)
//{
//	// �S���̃t���O�������Ă����牽�����Ȃ�
//	if (m_arrayNodeUseCheckBitFlagsArray[i] == 0xffffffff) continue;
//
//	// �e�r�b�g���ɔ��肷��
//	for (unsigned int j = 0; j < 32U; j++)
//	{
//		if ((m_arrayNodeUseCheckBitFlagsArray[i] & (1U << j)) != 0U)
//		{
//			emplacePoint = (i * 32U) + j;
//			break;
//		}
//	}
//	break;
//}