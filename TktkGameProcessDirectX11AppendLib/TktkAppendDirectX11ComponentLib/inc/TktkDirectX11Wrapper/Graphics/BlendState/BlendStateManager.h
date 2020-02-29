#ifndef BLEND_STATE_MANAGER_H_
#define BLEND_STATE_MANAGER_H_

#include <type_traits>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/BlendStateAssets.h"

namespace tktk
{
	class BlendStateManager
	{
	private:

		// テンプレート引数の型がidを表す上で適切かを判定する定数
		template <class IdType>
		static constexpr bool is_idType = (std::is_enum_v<IdType> || std::is_integral_v<IdType>);

	public:

		// 「BlendStateAssets」を作成
		static void setUp();

	public:

		// 新たなブレンドステートを作成する（intに変換できる型のidが渡された場合）
		template <class IdType, std::enable_if_t<is_idType<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_BLEND_DESC& blendDesc)
		{
			createImpl(static_cast<int>(id), blendDesc);
		}
		// 新たなブレンドステートを作成する（不正な型のidが渡された場合）
		template <class IdType, std::enable_if_t<!is_idType<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_BLEND_DESC& blendDesc) { static_assert(false, "BlendStateId Fraud Value"); }

		// 指定したブレンドステートを削除する（intに変換できる型のidが渡された場合）
		template <class IdType, std::enable_if_t<is_idType<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		// 指定したブレンドステートを削除する（不正な型のidが渡された場合）
		template <class IdType, std::enable_if_t<!is_idType<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "BlendStateId Fraud Value"); }

		// 指定したブレンドステートを管理するクラスのポインタを取得する（intに変換できる型のidが渡された場合）
		template <class IdType, std::enable_if_t<is_idType<IdType>>* = nullptr>
		static BlendStateData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		// 指定したブレンドステートを管理するクラスのポインタを取得する（不正な型のidが渡された場合）
		template <class IdType, std::enable_if_t<!is_idType<IdType>>* = nullptr>
		static BlendStateData* getDataPtr(IdType id) { static_assert(false, "BlendStateId Fraud Value"); return nullptr; }

		// 全てのブレンドステートを削除する
		static void clear();

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const D3D11_BLEND_DESC& blendDesc);
		static void eraseImpl(int id);
		static BlendStateData* getDataPtrImpl(int id);

	private:

		static CfpPtr<BlendStateAssets> m_assetsPtr;
	};
}
#endif // !BLEND_STATE_MANAGER_H_