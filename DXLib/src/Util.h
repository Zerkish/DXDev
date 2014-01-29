#ifndef DXLIB_PRIVATEUTIL_H
#define DXLIB_PRIVATEUTIL_H

template<typename COMTYPE>
inline void ReleaseCom(COMTYPE *&ptr) {
    if (ptr) ptr->Release();
    ptr = nullptr;
}

#endif // !DXLIB_PRIVATEUTIL_H