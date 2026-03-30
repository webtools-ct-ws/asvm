#include "avmplus.h"
#include "asvm.h" // Your HAL headers for hal_fb_clear

namespace avmplus {
    // This is the actual C++ logic for the ActionScript call
    // argv[0] will be the color passed from ActionScript
    NativeID EOS_fb_clear(MethodEnv, uint32_t argc, AvmBox* argv) {
        if (argc < 1) return nullObjectAtom;
        
        // Convert the ActionScript Boxed value to a C++ integer
        int32_t color = AvmCore::integer(argv[0]);
        
        // Call your existing HAL function
        hal_fb_clear((uint32_t)color);
        
        return nullObjectAtom;
    }
}