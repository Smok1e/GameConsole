#pragma once

#ifdef __FUNCSIG__

	#define _FUNC_ __FUNCSIG__

#else

	#define _FUNC_ __func__

#endif

#define _TRC printf ("%s\n", _FUNC_); 