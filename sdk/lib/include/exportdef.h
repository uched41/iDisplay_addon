#ifndef EXPORTDEF_H
#define EXPORTDEF_H

#ifdef _WIN32
    #if defined(IDISPLAYSDKLIB_BUTTONDISPLAY_LIBRARY)
        #define LIB_API_CALL __declspec(dllexport)
    #else
        #define LIB_API_CALL __declspec(dllimport)
    #endif

#else
      #define LIB_API_CALL
#endif


#endif // EXPORTDEF_H
