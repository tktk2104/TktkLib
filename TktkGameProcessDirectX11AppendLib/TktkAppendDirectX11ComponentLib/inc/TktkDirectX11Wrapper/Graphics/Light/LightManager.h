#ifndef LIGHT_MANAGER_H_
#define LIGHT_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "LightUpdater.h"

namespace tktk
{
	// 「LightUpdater」に簡単にアクセスするためのクラス
	class LightManager
	{
	public:

		// 「LightUpdater」を生成
		static void setUp();

	public:

		// 新たなライトを生成する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Color& ambientColor, const Color& diffuseColor, const Color& specularColor, const Vector3& position)
		{
			createImpl(static_cast<int>(id), ambientColor, diffuseColor, specularColor, position);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Color& ambientColor, const Color& diffuseColor, const Color& specularColor, const Vector3& position)
			 { static_assert(false, "LightId Fraud Type"); }

		// 指定したライトを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "LightId Fraud Type"); }

		// ライトを管理するクラスのポインタを取得する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static LightData* getLightDataPtr(IdType id)
		{
			return getLightDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static LightData* getLightDataPtr(IdType id) { static_assert(false, "LightId Fraud Type"); }

		// 指定したライトを有効にする（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void enableLight(IdType id)
		{
			enableLightImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void enableLight(IdType id) { static_assert(false, "LightId Fraud Type"); }

		// 指定したライトを無効にする（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void disableLight(IdType id)
		{
			disableLightImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void disableLight(IdType id) { static_assert(false, "LightId Fraud Type"); }

		// 全てのライトを削除する
		void clear();

		// 全てのライトを無効にする
		static void disableLightAll();

		// 今有効になっているライトのIdの一覧を取得する
		static const std::unordered_set<int>& getEnableLightIdList();

		// 今有効になっているライトを管理するクラスのリストを作成する（引数で取得型）
		static void createEnableLightList(std::forward_list<LightData*>* result);

		// 今有効になっているライトを管理するクラスのリストを作成する（戻り値で取得型）
		static std::forward_list<LightData*> createEnableLightList();

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const Color& ambientColor, const Color& diffuseColor, const Color& specularColor, const Vector3& position);
		static void eraseImpl(int id);
		static LightData* getLightDataPtrImpl(int id);
		static void enableLightImpl(int id);
		static void disableLightImpl(int id);

	private:

		static CfpPtr<LightUpdater> m_updaterPtr;
	};
}
#endif // !LIGHT_MANAGER_H_