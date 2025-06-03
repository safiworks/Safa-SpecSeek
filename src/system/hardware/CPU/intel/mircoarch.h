#ifndef INTEL_MICROARCH_H
#define INTEL_MICROARCH_H   1

/// @brief get the Micro archetecture for the Current CPU [INTEL ONLY]
/// @param family CPU Family Value
/// @param model the CPUs BASE model
/// @param ext_model the CPUs Extended Model
/// @param stepping revision?
/// @return MicroArchetecture string.
const char* intel_get_cpu_microarch(unsigned int family,
    unsigned int model,
    unsigned int ext_model,
    unsigned int stepping){
    switch (family){
        case 0x4:
            return "Intel 486";
        case 0x5:
            switch (model){
                case 0x01 ... 0x08:
                    return "P5";
                case 0x09 ... 0x0A:
                    return "Lakemont";
                default:
                    break;
            }
            break;
        case 0x6:
            switch (model){
                case 0x1 ... 0x8:
                    if (model == 0x5 && ext_model == 0x0) return "P6";
                    if (model == 0x5 && ext_model == 0x1) return "Pentium M";
                    if (model == 0x5 && ext_model == 0x2) return "Westmere";
                    if (model == 0x5 && ext_model == 0x4) return "Haswell";
                    if (model == 0x5 && ext_model == 0x5 && stepping == 11) return "Cooper Lake";
                    if (model == 0x5 && ext_model == 0x5 &&
                        (stepping == 5 || stepping == 6 || stepping == 7)) return "Cascade Lake"; 
                    if (model == 0x5 && ext_model == 0x5) return "Skylake";                   
                    if (model == 0x5 && ext_model == 0xA) return "Comet Lake";
                    if (model == 0x5 && ext_model == 0xB) return "Arrow Lake";
                    if (model == 0x5 && ext_model == 0xC) return "Arrow Lake";
                    if (model == 0x6 && ext_model == 0x1) return "Core";
                    if (model == 0x6 && ext_model == 0x4) return "Haswell";
                    if (model == 0x6 && ext_model == 0x5) return "Broadwell (EP +)";
                    if (model == 0x6 && ext_model == 0x6) return "Cannon Lake";
                    if (model == 0x6 && ext_model == 0xA) return "Comet Lake";
                    if (model == 0x6 && ext_model == 0xC) return "Arrow Lake";
                    if (model == 0x7 && ext_model == 0x1) return "Penryn";
                    if (model == 0x7 && ext_model == 0x4) return "Broadwell";
                    if (model == 0x7 && ext_model == 0x9) return "Alder Lake";
                    if (model == 0x7 && ext_model == 0xA) return "Rocket Lake";
                    if (model == 0x7 && ext_model == 0xB) return "Raptor Lake or Barlett Lake";
                    break;
                case 0xA:
                    switch (ext_model){
                        case 0x0:
                            return "P6";
                        case 0x1:
                            return "Nehalem";
                        case 0x2:
                            return "Sandy Bridge";
                        case 0x3:
                            return "Ivy Bridge";
                        case 0x6:
                            return "Ice Lake";
                        case 0x9:
                            return "Alder Lake";
                        case 0xA:
                            return "Meteor Lake";
                        case 0xB:
                            return "Raptor Lake or Barlett Lake";
                        default:
                            break;
                    }
                    break;
                case 0xB:
                    switch (ext_model){
                        case 0x0:
                            return "P6";
                        case 0xA:
                            return "Meteor Lake";
                        default:
                            break;
                    }
                    break;
                case 0x9:
                case 0xC:
                    switch (ext_model){
                        case 0x3:
                            return "Haswell";
                        case 0x2:
                            return "Westmere";
                        case 0x6:
                            return "Ice Lake";
                        case 0x8:
                            return "Tiger Lake";
                        case 0xA:
                            return "Meteor Lake";
                        case 0xB:
                            return "Lunar Lake";
                        case 0xC:
                            return "Panther Lake";
                        default:
                            break;
                    }
                    break;
                case 0xD:
                    switch (ext_model){
                        case 0x0:
                            return "Modified Pentium M";
                        case 0x1:
                            return "Penryn";
                        case 0x2:
                            return "Sandy Bridge";
                        case 0x3:
                            return "Broadwell";
                        case 0x7:
                            return "Ice Lake";
                        case 0x8:
                            return "Tiger Lake";
                        case 0xA:
                            return "Granite Rapids";
                        case 0xB:
                            return "Lunar Lake";
                        case 0xC:
                            return "Wildcat Lake";
                        case 0xD:
                            return "Clearwater Forest";
                        default:
                            break;
                    }
                    break;
                case 0xE:
                    switch (ext_model){
                        case 0x0:
                            return "Modified Pentium M";
                        case 0x1:
                        case 0x2:
                            return "Nehalem";
                        case 0x3:
                            return "Ivy Bridge";
                        case 0x4:
                        case 0x5:
                            return "Skylake";
                        case 0x7:
                            return "Ice Lake";
                        case 0x8:
                            if (stepping == 9) return "Amber Lake";
                            if (stepping == 10) return "Coffee Lake";
                            if (stepping == 11 || stepping == 12) return "Whiskey Lake";
                            return "Kaby Lake";
                        case 0x9:
                            return "Kaby Lake or Coffee Lake";
                        case 0xA:
                            return "Granite Rapids";
                        case 0xB:
                            return "Raptor Lake or Barlett Lake";
                        default:
                            break;
                    }
                    break;
                case 0xF:
                    switch (ext_model){
                        case 0x0:
                            return "Core";
                        case 0x1:
                            return "Nehalem";
                        case 0x2:
                            return "Westmere";
                        case 0x3:
                            return "Haswell";
                        case 0x4:
                            return "Broadwell";
                        case 0x8:
                            return "Sapphire Rapids";
                        case 0xA:
                            return "Sierra Forest";
                        case 0xC:
                            return "Emerald Rapids";
                        case 0xB:
                            return "Raptor Lake or Barlett Lake";
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        case 0xF:
            switch (model){
                case 0x1 ... 0x4:
                    return "Netburst";
                case 0x6:
                    return "Modified Pentium M";
                default:
                    break;
            }
            break;
        default:
            return "Unknown Intel Microarch";
    }
    return "Unknown Intel Microarch";
}

#endif
