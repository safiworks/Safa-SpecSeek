/// @brief Returns the AMD microarchitecture name based on family and model, the Linux src code was huge for this
/// @param family CPU family
/// @param model CPU model
/// @return const char* string describing the microarchitecture
const char* amd_cpu_get_microarch(unsigned int family, unsigned int model);

/// @brief get the Micro archetecture for the Current CPU [INTEL ONLY]
/// @param family CPU Family Value
/// @param model the CPUs BASE model
/// @param ext_model the CPUs Extended Model
/// @param stepping revision?
/// @return Microarchetecture string.
const char* intel_get_cpu_microarch(unsigned int family,
    unsigned int model,
    unsigned int ext_model,
    unsigned int stepping);