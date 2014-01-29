#ifndef DXLIB_DXDEFS_H
#define DXLIB_DXDEFS_H

#define NO_COPY_ASSIGN(CLASS) CLASS(const CLASS &); const CLASS & operator=(const CLASS &);

#if defined(DEBUG) | defined(_DEBUG)
#define DEBUG_HR(EXPRESSION) \
    if (FAILED((EXPRESSION))) \
        MessageBox(NULL, TEXT(#EXPRESSION), TEXT("ERROR"), MB_OK | MB_ICONERROR)
#else
#define DEBUG_HR(EXPRESSION) (EXPRESSION)
#endif

#define ARRAY_SIZE(X) (sizeof((X)) / sizeof((X)[0]))

//#define RELEASE_COM(X) if ((X)) (X)->Release(); (X) = nullptr

#endif // !DXLIB_DXDEFS_H