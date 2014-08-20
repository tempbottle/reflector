#pragma once

// Generated by gen_function_header.py

namespace reflection {
template <typename Return>
Return returnValueOf(Return (*)());

template <typename Return, typename Arg0>
Return returnValueOf(Return (*)(Arg0));
template <typename Return, typename Arg0>
Arg0 arg0TypeIn(Return (*)(Arg0));

template <typename Return, typename Arg0, typename Arg1>
Return returnValueOf(Return (*)(Arg0, Arg1));
template <typename Return, typename Arg0, typename Arg1>
Arg0 arg0TypeIn(Return (*)(Arg0, Arg1));
template <typename Return, typename Arg0, typename Arg1>
Arg1 arg1TypeIn(Return (*)(Arg0, Arg1));

template <typename Return, typename Arg0, typename Arg1, typename Arg2>
Return returnValueOf(Return (*)(Arg0, Arg1, Arg2));
template <typename Return, typename Arg0, typename Arg1, typename Arg2>
Arg0 arg0TypeIn(Return (*)(Arg0, Arg1, Arg2));
template <typename Return, typename Arg0, typename Arg1, typename Arg2>
Arg1 arg1TypeIn(Return (*)(Arg0, Arg1, Arg2));
template <typename Return, typename Arg0, typename Arg1, typename Arg2>
Arg2 arg2TypeIn(Return (*)(Arg0, Arg1, Arg2));

template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
Return returnValueOf(Return (*)(Arg0, Arg1, Arg2, Arg3));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
Arg0 arg0TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
Arg1 arg1TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
Arg2 arg2TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
Arg3 arg3TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3));

template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
Return returnValueOf(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
Arg0 arg0TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
Arg1 arg1TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
Arg2 arg2TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
Arg3 arg3TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
Arg4 arg4TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4));

template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
Return returnValueOf(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
Arg0 arg0TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
Arg1 arg1TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
Arg2 arg2TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
Arg3 arg3TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
Arg4 arg4TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
Arg5 arg5TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5));

template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
Return returnValueOf(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
Arg0 arg0TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
Arg1 arg1TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
Arg2 arg2TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
Arg3 arg3TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
Arg4 arg4TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
Arg5 arg5TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
Arg6 arg6TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6));

template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
Return returnValueOf(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
Arg0 arg0TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
Arg1 arg1TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
Arg2 arg2TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
Arg3 arg3TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
Arg4 arg4TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
Arg5 arg5TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
Arg6 arg6TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
Arg7 arg7TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7));

template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
Return returnValueOf(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
Arg0 arg0TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
Arg1 arg1TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
Arg2 arg2TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
Arg3 arg3TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
Arg4 arg4TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
Arg5 arg5TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
Arg6 arg6TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
Arg7 arg7TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
Arg8 arg8TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8));

template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
Return returnValueOf(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
Arg0 arg0TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
Arg1 arg1TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
Arg2 arg2TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
Arg3 arg3TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
Arg4 arg4TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
Arg5 arg5TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
Arg6 arg6TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
Arg7 arg7TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
Arg8 arg8TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9));
template <typename Return, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
Arg9 arg9TypeIn(Return (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9));

}
