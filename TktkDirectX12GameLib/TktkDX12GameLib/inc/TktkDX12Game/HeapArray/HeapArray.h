#ifndef HEAP_ARRAY_H_
#define HEAP_ARRAY_H_

#include <memory>

namespace tktk
{
	template <class NodeType, class Allocator = std::allocator<NodeType>>
	class HeapArray
	{
	public:

		HeapArray(unsigned int arraySize);
		~HeapArray();

	public:

		template <class... ConstructorArgs>
		NodeType* emplace(ConstructorArgs&&... args);

		void erase(NodeType* eraseNode);

	private:

		Allocator		m_allocator;

		unsigned int	m_arraySize;
		NodeType*		m_arrayTopPos;
		
		unsigned int	m_arrayNodeUseCheckBitFlagsArraySize;
		unsigned int*	m_arrayNodeUseCheckBitFlagsArray;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class NodeType, class Allocator>
	inline HeapArray<NodeType, Allocator>::HeapArray(unsigned int arraySize)
		: m_arraySize(arraySize)
		, m_arrayTopPos(std::allocator_traits<Allocator>::allocate(m_allocator, m_arraySize))
		, m_arrayNodeUseCheckBitFlagsArraySize(1U + arraySize / (sizeof(unsigned int) * 8U))
		, m_arrayNodeUseCheckBitFlagsArray(new unsigned int[m_arrayNodeUseCheckBitFlagsArraySize])
	{
		memset(m_arrayNodeUseCheckBitFlagsArray, 0, m_arrayNodeUseCheckBitFlagsArraySize * sizeof(unsigned int));
	}

	template<class NodeType, class Allocator>
	inline HeapArray<NodeType, Allocator>::~HeapArray()
	{
		for (unsigned int i = 0; i < m_arraySize; i++)
		{
			if ((m_arrayNodeUseCheckBitFlagsArray[i / 32U] & (1U << (i % 32U))) != 0U)
			{
				std::allocator_traits<Allocator>::destroy(m_allocator, m_arrayTopPos + i);
			}
		}
		std::allocator_traits<Allocator>::deallocate(m_allocator, m_arrayTopPos, m_arraySize);

		delete[](m_arrayNodeUseCheckBitFlagsArray);
	}

	template<class NodeType, class Allocator>
	template<class ...ConstructorArgs>
	inline NodeType* HeapArray<NodeType, Allocator>::emplace(ConstructorArgs&& ...args)
	{
		for (unsigned int i = 0U; i < m_arraySize; i++)
		{
			if ((m_arrayNodeUseCheckBitFlagsArray[i / 32U] & (1U << (i % 32U))) == 0U)
			{
				std::allocator_traits<Allocator>::construct(m_allocator, m_arrayTopPos + i, std::forward<ConstructorArgs>(args)...);
				m_arrayNodeUseCheckBitFlagsArray[i / 32U] |= (1U << (i % 32U));
				return (m_arrayTopPos + i);
			}
		}
	}

	template<class NodeType, class Allocator>
	inline void HeapArray<NodeType, Allocator>::erase(NodeType* eraseNode)
	{
		
	}
}
#endif // !HEAP_ARRAY_H_

// 没コード
//// 配列の使用中ビットフラグを32ビットずつ巡回
//for (unsigned int i = 0; i < m_arrayNodeUseCheckBitFlagsArraySize; i++)
//{
//	// 全部のフラグが立っていたら何もしない
//	if (m_arrayNodeUseCheckBitFlagsArray[i] == 0xffffffff) continue;
//
//	// 各ビット毎に判定する
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