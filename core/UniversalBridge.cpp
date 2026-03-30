#include "avmplus.h"
#include <dlfcn.h> // For dynamic loading

namespace avmplus {
    // This is the ONLY function you will ever need to register in Toplevel.cpp
    NativeID UniversalNativeCall(MethodEnv, uint32_t argc, AvmBox* argv) {
        if (argc < 2) return nullObjectAtom;

        // argv[0] = Library Name (e.g., "libeos_gfx.so")
        // argv[1] = Function Name (e.g., "draw_rect")
        // argv[2+] = Arguments
        
        Stringp libName = avm_box_to_string(argv[0]);
        Stringp funcName = avm_box_to_string(argv[1]);

        // Dynamically load the external hardware library
        void* handle = dlopen(libName->toUTF8()->data(), RTLD_LAZY);
        if (!handle) return nullObjectAtom;

        // Find the symbol
        typedef void (*hw_func)(AvmBox*);
        hw_func f = (hw_func)dlsym(handle, funcName->toUTF8()->data());

        if (f) {
            f(&argv[2]); // Execute the external library code
        }

        return nullObjectAtom;
    }
}