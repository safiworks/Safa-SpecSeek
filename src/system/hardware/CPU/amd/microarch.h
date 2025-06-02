// amd_cpu.h
#ifndef AMD_CPU_H
#define AMD_CPU_H

/// this is much less bullshit that whatever Intel is pulling over at ../intel/microarch.h

/// @brief Returns the AMD microarchitecture name based on family and model
/// @param family CPU family
/// @param model CPU model
/// @return const char* string describing the microarchitecture
static inline const char* amd_cpu_get_microarch(unsigned int family, unsigned int model) {
    switch (family) {
        case 0x17:
            switch (model) {
                case 0x1: return "Zen";
                case 0x8: return "Zen+";
                default: return "Unknown AMD Zen (Family 23)";
            }
        case 0x18:
            return "Zen 2";
        case 0x19:
            return "Zen 3";
        case 0x1A:
            if (model <= 0x3) {
                return "Zen 4";
            } else if (model == 0x4) {
                return "Zen 5"; 
            } else {
                return "Unknown AMD Zen 4/5";
            }
        default:
            return "Unknown AMD Family";
    }
}

#endif
