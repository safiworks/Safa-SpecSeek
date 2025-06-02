// intel_cpu_models.h
#ifndef INTEL_CPU_MODELS_H
#define INTEL_CPU_MODELS_H

#include <stdint.h>
#include <stdio.h>

typedef struct {
    unsigned int family;
    unsigned int model;
    unsigned int ext_model;
    const char* microarch;
} intel_cpu_microarch_t;


/// @brief Intel CPU Microarch lookup table
static const intel_cpu_microarch_t intel_cpu_table[] = {
    {6, 0x3A, 0, "Ivy Bridge"},
    {6, 0x3C, 0, "Haswell"},
    {6, 0x3D, 0, "Broadwell"},
    {6, 0x3F, 0, "Broadwell EP"},
    {6, 0x45, 0, "Haswell"},
    {6, 0x46, 0, "Haswell"},
    {6, 0x4E, 0, "Skylake"},
    {6, 0x4F, 0, "Broadwell EP+"},
    {6, 0x5E, 0, "Cannon Lake"},
    {6, 0x6A, 0, "Skylake-X"},
    {6, 0x6C, 0, "Skylake-X"},
    {6, 0x7D, 0, "Ice Lake"},
    {6, 0x7E, 0, "Ice Lake"},
    {6, 0x8E, 0, "Kaby Lake"},
    {6, 0x8F, 0, "Coffee Lake"},
    {6, 0x9E, 0, "Coffee Lake"},
    {6, 0xA5, 0, "Comet Lake"},
    {6, 0xA6, 0, "Comet Lake"},
    {6, 0xA7, 0, "Alder Lake"},
    {6, 0xAF, 0, "Alder Lake"},
    {6, 0xBE, 0, "Alder Lake"},
    {6, 0xBF, 0, "Raptor Lake"},
    {6, 0xB7, 0, "Rocket Lake"},
    {6, 0xB8, 0, "Rocket Lake"},
};

static const size_t intel_cpu_table_size = sizeof(intel_cpu_table) / sizeof(intel_cpu_microarch_t);

// it gets better about here to be fair

/// @brief returns the name of the microarch from the lookup table
/// @param family cpu family
/// @param model full model tag
/// @param ext_model Extended Model on its own
/// @return 
static const char* intel_cpu_get_microarch(unsigned int family, unsigned int model, unsigned int ext_model) {
    for (size_t i = 0; i < intel_cpu_table_size; i++) {
        const intel_cpu_microarch_t* entry = &intel_cpu_table[i];
        if (entry->family == family &&
            entry->model == model &&
            (entry->ext_model == 0 || entry->ext_model == ext_model)) {
            return entry->microarch;
        }
    }
    return "Unknown CPU (Intel)";
}

#endif
