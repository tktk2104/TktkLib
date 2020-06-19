#ifndef MATH_HELPER_H_
#define MATH_HELPER_H_

#include <limits>
#include <algorithm>
#include <TktkTemplateMetaLib/TypeCheck/IsNumber.h>

#include <cmath>
/*
┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
┃【constexprに対応した数学関連の定数、関数】
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
┃《定数一覧》
┃┌───────────────────────────────────────────────────────────────────────────────
┃│pi
┃├───────────────────────────────────────────────────────────────────────────────
┃│「float型」円周率
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│kEpsilon
┃├───────────────────────────────────────────────────────────────────────────────
┃│「float型」限りなく０に近い数字
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│sinTableDataNum
┃├───────────────────────────────────────────────────────────────────────────────
┃│「unsigned int型」三角関数の計算で使用するsinテーブルの分割数
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│sinTable[sinTableDataNum + 1U]
┃├───────────────────────────────────────────────────────────────────────────────
┃│「double[sinTableDataNum]型」三角関数の計算で使用するsinテーブル
┃└───────────────────────────────────────────────────────────────────────────────
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
┃《関数一覧》
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType sqrt(JudgeType value)
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数の値の平方根を計算します（引数に負の数が渡されたならNAN値または0を返す）
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型１つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType abs(JudgeType value)
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数の値の絶対値を計算します
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型１つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType distance(JudgeType value1, JudgeType value2)
┃├───────────────────────────────────────────────────────────────────────────────
┃│2つの値の差の絶対値を計算します
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型２つ（同一の型である必要がある）
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│bool equals(JudgeType value1, JudgeType value2)
┃├───────────────────────────────────────────────────────────────────────────────
┃│２つの値が大体同じだったら真を返す
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型２つ（同一の型である必要がある）
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：bool型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType sign(JudgeType value)
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数の値が正の数なら1、負の数なら-1を返します
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型１つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType clamp(JudgeType value, JudgeType min, JudgeType max)
┃├───────────────────────────────────────────────────────────────────────────────
┃│値を指定された範囲内に制限します
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型３つ（同一の型である必要がある）
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType lerpUnclamped(JudgeType value1, JudgeType value2, float amount)
┃├───────────────────────────────────────────────────────────────────────────────
┃│2つの値の間を線形補間します（amountの値がClampされない）
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型２つ（同一の型である必要がある）float型1つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType lerp(JudgeType value1, JudgeType value2, float amount)
┃├───────────────────────────────────────────────────────────────────────────────
┃│2つの値の間を線形補間します（amountの値が0.0f～1.0fの間にClampされる）
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型２つ（同一の型である必要がある）float型1つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType moveTowards(JudgeType current, JudgeType target, JudgeType maxDistanceDelta)
┃├───────────────────────────────────────────────────────────────────────────────
┃│currentからtargetへ向けて移動します
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型３つ（同一の型である必要がある）
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType toDegrees(JudgeType value)
┃├───────────────────────────────────────────────────────────────────────────────
┃│ラジアンを度に変換します
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型１つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType toRadians(JudgeType value)
┃├───────────────────────────────────────────────────────────────────────────────
┃│度をラジアンに変換します
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型１つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType sin<int Accuracy>(JudgeType value)
┃├───────────────────────────────────────────────────────────────────────────────
┃│度数法で指定した角度のサインを計算する（Accuracyを大きくする程精度が上がる）
┃├───────────────────────────────────────────────────────────────────────────────
┃│Ｔ引数：int型１つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型１つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType sin(JudgeType value)
┃├───────────────────────────────────────────────────────────────────────────────
┃│度数法で指定した角度のサインを計算する（固定精度版 ※Accuracy=3 ）
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型１つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType cos<int Accuracy>(JudgeType value)
┃├───────────────────────────────────────────────────────────────────────────────
┃│度数法で指定した角度のコサインを計算する（Accuracyを大きくする程精度が上がる）
┃├───────────────────────────────────────────────────────────────────────────────
┃│Ｔ引数：int型１つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型１つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType cos(JudgeType value)
┃├───────────────────────────────────────────────────────────────────────────────
┃│度数法で指定した角度のコサインを計算する（固定精度版 ※Accuracy=3 ）
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型１つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType tan<int Accuracy>(JudgeType value)
┃├───────────────────────────────────────────────────────────────────────────────
┃│度数法で指定した角度のタンジェントを計算する（Accuracyを大きくする程精度が上がる）
┃├───────────────────────────────────────────────────────────────────────────────
┃│Ｔ引数：int型１つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型１つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┃┌───────────────────────────────────────────────────────────────────────────────
┃│JudgeType tan(JudgeType value)
┃├───────────────────────────────────────────────────────────────────────────────
┃│度数法で指定した角度のタンジェントを計算する（固定精度版 ※Accuracy=3 ）
┃├───────────────────────────────────────────────────────────────────────────────
┃│引数　：数値型１つ
┃├───────────────────────────────────────────────────────────────────────────────
┃│戻り値：引数と同じ数値型
┃└───────────────────────────────────────────────────────────────────────────────
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
namespace tktkConstexprMath::helper
{
	// 円周率
	constexpr float pi{ 3.14159265359f };

	// 限りなく０に近い数字
	constexpr float kEpsilon{ 1e-5f };

	// sinテーブルの分割数
	constexpr unsigned int sinTableDataNum = 90;

	// sinテーブル
	constexpr double sinTable[sinTableDataNum + 1U]{
		0,					0.0174524064372835,	0.034899496702501,	0.0523359562429438,
		0.0697564737441253, 0.0871557427476582, 0.104528463267653,	0.121869343405147,
		0.139173100960065,	0.156434465040231,	0.17364817766693,	0.190808995376545,
		0.207911690817759,	0.224951054343865,	0.241921895599668,	0.258819045102521,
		0.275637355816999,	0.292371704722737,	0.309016994374947,	0.325568154457157,
		0.342020143325669,	0.3583679495453,	0.374606593415912,	0.390731128489274,
		0.4067366430758,	0.422618261740699,	0.438371146789077,	0.453990499739547,
		0.469471562785891,	0.484809620246337,	0.5,				0.515038074910054,
		0.529919264233205,	0.544639035015027,	0.559192903470747,	0.573576436351046,
		0.587785252292473,	0.601815023152048,	0.615661475325658,	0.629320391049837,
		0.642787609686539,	0.656059028990507,	0.669130606358858,	0.681998360062498,
		0.694658370458997,	0.707106781186547,	0.719339800338651,	0.73135370161917,
		0.743144825477394,	0.754709580222772,	0.766044443118978,	0.777145961456971,
		0.788010753606722,	0.798635510047293,	0.809016994374947,	0.819152044288992,
		0.829037572555042,	0.838670567945424,	0.848048096156426,	0.857167300702112,
		0.866025403784439,	0.874619707139396,	0.882947592858927,	0.891006524188368,
		0.898794046299167,	0.90630778703665,	0.913545457642601,	0.92050485345244,
		0.927183854566787,	0.933580426497202,	0.939692620785908,	0.945518575599317,
		0.951056516295154,	0.956304755963035,	0.961261695938319,	0.965925826289068,
		0.970295726275996,	0.974370064785235,	0.978147600733806,	0.981627183447664,
		0.984807753012208,	0.987688340595138,	0.99026806874157,	0.992546151641322,
		0.994521895368273,	0.996194698091746,	0.997564050259824,	0.998629534754574,
		0.999390827019096,	0.999847695156391,	1
	};

	// 引数の値の平方根を計算します（引数に負の数が渡されたならNAN値または0を返す）（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType sqrt(JudgeType value)
	{
		if (value <= static_cast<JudgeType>(0)) return std::numeric_limits<JudgeType>::quiet_NaN();

		JudgeType x = value / 2;
		JudgeType lastX = static_cast<JudgeType>(0);

		while (x != lastX)
		{
			lastX = x;
			x = (x + value / x) / 2;
		}
		return x;
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType sqrt(JudgeType value) { static_assert(false, "JudgeType Fraud Type"); }

	// 引数の値の絶対値を計算します（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType abs(JudgeType value)
	{
		if (value > static_cast<JudgeType>(value)) return value;
		return value * static_cast<JudgeType>(-1);
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType abs(JudgeType value) { static_assert(false, "JudgeType Fraud Type"); }

	// 2つの値の差の絶対値を計算します（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType distance(JudgeType value1, JudgeType value2)
	{
		return abs(value1 - value2);
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType distance(JudgeType value1, JudgeType value2) { static_assert(false, "JudgeType Fraud Type"); }

	// ２つの値が大体同じだったら真を返す（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline bool equals(JudgeType value1, JudgeType value2)
	{
		return (static_cast<JudgeType>(distance(value1, value2)) <= static_cast<JudgeType>(kEpsilon));
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline bool equals(JudgeType value1, JudgeType value2) { static_assert(false, "JudgeType Fraud Type"); }

	// 引数の値が正の数なら1、負の数なら-1を返します（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType sign(JudgeType value)
	{
		if (abs(value) < static_cast<JudgeType>(kEpsilon)) return static_cast<JudgeType>(1);

		return (value / abs(value));
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType sign(JudgeType value) { static_assert(false, "JudgeType Fraud Type"); }

	// 値を指定された範囲内に制限します（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType clamp(JudgeType value, JudgeType min, JudgeType max)
	{
		return std::max(min, std::min(value, max));
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType clamp(JudgeType value, JudgeType min, JudgeType max) { static_assert(false, "JudgeType Fraud Type"); }

	// 2つの値の間を線形補間します（amountの値がClampされない）（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType lerpUnclamped(JudgeType value1, JudgeType value2, float amount)
	{
		return (value1 * (1.0f - amount)) + (value2 * amount);
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType lerpUnclamped(JudgeType value1, JudgeType value2, float amount) { static_assert(false, "JudgeType Fraud Type"); }

	// 2つの値の間を線形補間します（amountの値が0.0f～1.0fの間にClampされる）（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType lerp(JudgeType value1, JudgeType value2, float amount)
	{
		amount = clamp(amount, 0.0f, 1.0f);

		return lerpUnclamped(value1, value2, amount);
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType lerp(JudgeType value1, JudgeType value2, float amount) { static_assert(false, "JudgeType Fraud Type"); }

	// currentからtargetへ向けて移動します（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType moveTowards(JudgeType current, JudgeType target, JudgeType maxDistanceDelta)
	{
		JudgeType toTarget = target - current;
		JudgeType sqdist = toTarget * toTarget;

		if (sqdist < static_cast<JudgeType>(kEpsilon) || sqdist <= (maxDistanceDelta * maxDistanceDelta))
		{
			return target;
		}
		return current + toTarget / sqrt(sqdist) * maxDistanceDelta;
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType moveTowards(JudgeType current, JudgeType target, JudgeType maxDistanceDelta) { static_assert(false, "JudgeType Fraud Type"); }

	// ラジアンを度に変換します（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType toDegrees(JudgeType radian)
	{
		return radian * static_cast<JudgeType>(180.0f / pi);
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType toDegrees(JudgeType radian) { static_assert(false, "JudgeType Fraud Type"); }

	// 度をラジアンに変換します（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType toRadians(JudgeType degree)
	{
		return degree * static_cast<JudgeType>(pi / 180.0f);
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType toRadians(JudgeType degree) { static_assert(false, "JudgeType Fraud Type"); }

	// 度数法で指定した角度のサインを計算する（Accuracyを大きくする程精度が上がる）（数字を表す型が引数に渡された場合のみビルド可）
	template<int Accuracy, class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType sin(JudgeType degree)
	{
		// 戻り値の符号
		int dir = 1;

		JudgeType radians = toRadians(degree) / static_cast<JudgeType>(pi);

		// 正の値にする
		if (radians < static_cast<JudgeType>(0))
		{
			radians = -radians;
			dir = -dir;
		}

		// 0～2πの値にする
		radians -= static_cast<JudgeType>(static_cast<int>(radians / static_cast<JudgeType>(2)) * 2);

		// 0～πの値にする
		if (radians > static_cast<JudgeType>(1))
		{
			radians--;
			dir = -dir;
		}

		// 0～π/2の値にする
		if (radians > static_cast<JudgeType>(0.5)) radians = static_cast<JudgeType>(1) - radians;

		// 引数の値を0～sinTableDataNumの値にする
		radians *= static_cast<JudgeType>(sinTableDataNum * 2);
		int a = static_cast<int>(radians);

		// テーブル引き
		JudgeType si = static_cast<JudgeType>(sinTable[a]);
		JudgeType co = static_cast<JudgeType>(sinTable[sinTableDataNum - a]);
		JudgeType lx = static_cast<JudgeType>((radians - a) * pi / sinTableDataNum * 2);

		// テイラー展開による近似補間
		JudgeType sumSi = static_cast<JudgeType>(1);
		JudgeType sumCo = lx;
		JudgeType t = lx;

		for (int i = 1; i <= Accuracy; i++)
		{
			t *= -lx / (i * 2);
			sumSi += t;

			t *= lx / (i * 2 + 1);
			sumCo += t;
		}

		return static_cast<JudgeType>(dir * (si * sumSi + (co * sumCo / pi)));
	}
	template<int Accuracy, class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType sin(JudgeType degree) { static_assert(false, "JudgeType Fraud Type"); }

	// 度数法で指定した角度のサインを計算する（固定精度版 ※Accuracy=3 ）（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType sin(JudgeType degree)
	{
		return sin<3>(degree);
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType sin(JudgeType degree) { static_assert(false, "JudgeType Fraud Type"); }

	// 度数法で指定した角度のコサインを計算する（Accuracyを大きくする程精度が上がる）（数字を表す型が引数に渡された場合のみビルド可）
	template<int Accuracy, class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType cos(JudgeType degree)
	{
		return sin<Accuracy>(static_cast<JudgeType>(90 - degree));
	}
	template<int Accuracy, class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType cos(JudgeType degree) { static_assert(false, "JudgeType Fraud Type"); }

	// 度数法で指定した角度のコサインを計算する（固定精度版 ※Accuracy=3 ）（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType cos(JudgeType degree)
	{
		return sin<3>(static_cast<JudgeType>(90 - degree));
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType cos(JudgeType degree) { static_assert(false, "JudgeType Fraud Type"); }

	// 度数法で指定した角度のタンジェントを計算する（Accuracyを大きくする程精度が上がる）（数字を表す型が引数に渡された場合のみビルド可）
	template<int Accuracy, class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType tan(JudgeType degree)
	{
		return sin<Accuracy>(degree) / cos<Accuracy>(degree);
	}
	template<int Accuracy, class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType tan(JudgeType degree) { static_assert(false, "JudgeType Fraud Type"); }

	// 度数法で指定した角度のタンジェントを計算する（固定精度版 ※Accuracy=3 ）（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	constexpr inline JudgeType tan(JudgeType degree)
	{
		return sin<3>(degree) / cos<3>(degree);
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> constexpr inline JudgeType tan(JudgeType degree) { static_assert(false, "JudgeType Fraud Type"); }

	// TODO : 逆三角関数の関数もコンパイル時定数関数にする

	// 逆サイン（戻り値：度数法）（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	inline JudgeType asin(JudgeType s)
	{
		return toDegrees(std::asin(s));
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> inline JudgeType asin(JudgeType s) { static_assert(false, "JudgeType Fraud Type"); }

	// 逆コサイン（戻り値：度数法）（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	inline JudgeType acos(JudgeType c)
	{
		return toDegrees(std::acos(c));
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> inline JudgeType acos(JudgeType c) { static_assert(false, "JudgeType Fraud Type"); }

	// 逆タンジェント（戻り値：度数法）（数字を表す型が引数に渡された場合のみビルド可）
	template<class JudgeType, std::enable_if_t<is_number_v<JudgeType>>* = nullptr>
	inline JudgeType atan(JudgeType y, JudgeType x)
	{
		return toDegrees(std::atan2(y, x));
	}
	template<class JudgeType, std::enable_if_t<!is_number_v<JudgeType>>* = nullptr> inline JudgeType atan(JudgeType y, JudgeType x) { static_assert(false, "JudgeType Fraud Type"); }
}
#endif