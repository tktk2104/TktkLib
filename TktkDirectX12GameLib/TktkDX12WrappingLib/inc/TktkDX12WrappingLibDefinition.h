#ifndef TKTK_DX12_WRAPPING_LIB_DEFINITION_H_
#define TKTK_DX12_WRAPPING_LIB_DEFINITION_H_

#if defined(NDEBUG) || !defined(_DEBUG)
#pragma comment( lib, "TktkDX12WrappingLib_mt.lib" )
#else
#pragma comment( lib, "TktkDX12WrappingLib_mtd.lib" )
#endif
#endif // !TKTK_DX12_WRAPPING_LIB_DEFINITION_H_