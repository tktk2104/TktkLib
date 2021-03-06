#ifndef SPRITE_DRAWER_H_
#define SPRITE_DRAWER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform2D/Transform2D.h"

namespace tktk
{
	// スプライト描画コンポーネント
	// 【必須コンポーネント：Transform2D】
	class SpriteDrawer
		: public ComponentBase
	{
	public:

		SpriteDrawer(float drawPriority, unsigned int spriteMaterialId, unsigned int useRtvDescriptorHeapId);

	public:

		void start();
		void draw() const;

	public:

		// テクスチャIDを再設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setSpriteMaterialId(IdType id)
		{
			setSpriteMaterialIdImpl(static_cast<unsigned int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setSpriteMaterialId(IdType id) { static_assert(false, "SpriteMaterialId Fraud Type"); }

	private:

		// 各種id指定系の関数の実装
		void setSpriteMaterialIdImpl(unsigned int id);

	private:

		unsigned int				m_useRtvDescriptorHeapId;
		unsigned int				m_spriteMaterialId;
		ComponentPtr<Transform2D>	m_transform			{ };
	};
}
#endif // !SPRITE_DRAWER_H_
