namespace YY
{
	namespace Thunks
	{

#ifndef YY_Thunks_Defined
		namespace internal
		{
			template<class Char>
			static
			BOOL
			WINAPI
			StrToInt64ExT(
				_In_ const Char* pszString,
				STIF_FLAGS dwFlags,
				_Out_ LONGLONG* pllRet
				)
			{
				if (!pszString)
					return FALSE;


				for (; ; ++pszString)
				{
					const auto ch = *pszString;
				
					if (ch == Char(' ') || ch == Char('\n') || ch == Char('\t'))
					{
						continue;
					}

					break;
				}

				bool Sign = true;
				if (*pszString == Char('+'))
				{
					++pszString;
				}
				else if (*pszString == Char('-'))
				{
					++pszString;
					Sign = false;
				}

				ULONGLONG result = 0;

				if (dwFlags & STIF_SUPPORT_HEX)
				{
					//������ʽ0x????, 0X?????
					if (*pszString == Char('0') && (pszString[1] == Char('x') || pszString[1] == Char('X')))
					{
						pszString += 2;

						for (auto String = pszString; ; ++String)
						{
							const auto ch = *String;
							if (ch >= Char('0') && ch <= Char('9'))
							{
								result = (result << 4) | ((ULONGLONG)ch - Char('0'));
							}
							else if (ch >= Char('a') && ch <= Char('f'))
							{
								result = (result << 4) | ((ULONGLONG)ch - Char('a') + 10);
							}
							else if (ch >= Char('A') && ch <= Char('F'))
							{
								result = (result << 4) | ((ULONGLONG)ch - Char('A') + 10);
							}
							else
							{
								if (String == pszString)
								{
									return FALSE;
								}

								if (pllRet)
								{
									*pllRet = result;
								}

								return TRUE;
							}
						}
					}
				}

				for (auto String = pszString; ; ++String)
				{
					const auto ch = *String;
					if (ch >= Char('0') && ch <= ('9'))
					{
						result = (result * 10) + ((ULONGLONG)ch - Char('0'));
					}
					else
					{
						if (String == pszString)
						{
							return FALSE;
						}

						if (pllRet)
						{
							if (!Sign)
							{
								result = ~result + 1;
							}

							*pllRet = result;
						}

						return TRUE;
					}
				}

				return FALSE;
			}
		}
#endif

#if (YY_Thunks_Support_Version < NTDDI_WINXP)
// Windows 2000 Professional, Windows XP [desktop apps only] 
// Windows 2000 Server [desktop apps only]
// ��ȻWindows 2000֧�֣�������IE6�����IE6��һ������Windows 2000���У���˵���5.1���Ǿ;�̬���롣

EXTERN_C
BOOL
WINAPI
StrToInt64ExA(
	_In_ PCSTR pszString,
	STIF_FLAGS dwFlags,
	_Out_ LONGLONG* pllRet
	)
#ifdef YY_Thunks_Defined
;
#else
{
	if (const auto pStrToInt64ExA = try_get_StrToInt64ExA())
	{
		return pStrToInt64ExA(pszString, dwFlags, pllRet);
	}

	return internal::StrToInt64ExT(pszString, dwFlags, pllRet);
}
#endif

__YY_Thunks_Expand_Function(shlwapi, StrToInt64ExA, 12);

#endif //YY_Thunks_Support_Version < NTDDI_WINXP

#if (YY_Thunks_Support_Version < NTDDI_WINXP)
// Windows 2000 Professional, Windows XP [desktop apps only] 
// Windows 2000 Server [desktop apps only]
// ��ȻWindows 2000֧�֣�������IE6�����IE6��һ������Windows 2000���У���˵���5.1���Ǿ;�̬���롣

EXTERN_C
BOOL
WINAPI
StrToInt64ExW(
	_In_ PCWSTR pszString,
	STIF_FLAGS dwFlags,
	_Out_ LONGLONG* pllRet
	)
#ifdef YY_Thunks_Defined
;
#else
{
	if (const auto pStrToInt64ExW = try_get_StrToInt64ExW())
	{
		return pStrToInt64ExW(pszString, dwFlags, pllRet);
	}

	return internal::StrToInt64ExT(pszString, dwFlags, pllRet);
}
#endif

__YY_Thunks_Expand_Function(shlwapi, StrToInt64ExW, 12);

#endif //YY_Thunks_Support_Version < NTDDI_WINXP
	}
}