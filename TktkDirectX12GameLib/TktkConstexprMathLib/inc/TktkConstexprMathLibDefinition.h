#ifndef TKTK_CONSTEXPR_MATH_LIB_DEFINITION_H_
#define TKTK_CONSTEXPR_MATH_LIB_DEFINITION_H_

#if defined(NDEBUG) || !defined(_DEBUG)
#pragma comment( lib, "TktkConstexprMathLib_mt.lib" )
#else
#pragma comment( lib, "TktkConstexprMathLib_mtd.lib" )
#endif
#endif // !TKTK_CONSTEXPR_MATH_LIB_DEFINITION_H_