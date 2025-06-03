// amd_cpu.h
#ifndef _AMD_MICROARCH_H
#define _AMD_MICROARCH_H    1

/// this is much less bullshit that whatever Intel is pulling over at ../intel/microarch.h

/// @brief Returns the AMD microarchitecture name based on family and model, the Linux src code was huge for this
/// @param family CPU family
/// @param model CPU model
/// @return const char* string describing the microarchitecture
const char* amd_cpu_get_microarch(unsigned int family, unsigned int model) {
    switch(family){
        case 0x17:
            switch (model){
                case 0x00 ... 0x2F:
                case 0x50 ... 0x5F:
                    return "Zen";
                case 0x30 ... 0x4F:
                case 0x60 ... 0x7f:
                case 0x90 ... 0x91:
                case 0xA0 ... 0xAF:
                    return "Zen+";
                default:
                    return "Unknown Zen/Zen+ Processor"; 
            }
        case 0x19:
            switch (model){
                case 0x00 ... 0x0F:
                case 0x20 ... 0x5F:
                    return "Zen 3";
                case 0x10 ... 0x1F:
                case 0x60 ... 0xAF:
                    return "Zen 4";
                default:
                    return "Unknown Zen 3 / Zen 4 Processor";
            }
        case 0x1A:
            switch (model){
                case 0x00 ... 0x2F:
                case 0x40 ... 0x4F:
                case 0x60 ... 0x7F:
                    return "Zen 5";
                case 0x50 ... 0x5F:
                case 0x90 ... 0xAF:
                case 0xC0 ... 0xCF:
                    return "Zen 6";
                default:
                    return "Unknown Zen 5 / Zen 6 Processor";
            }
        default:
            return "Unknown AMD Microarch";
    }
}

#endif
