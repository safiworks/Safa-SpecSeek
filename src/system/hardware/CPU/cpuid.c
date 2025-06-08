void cpuid(
    unsigned int leaf,
    unsigned int subleaf,
    unsigned int* eax,
    unsigned int* ebx,
    unsigned int* ecx,
    unsigned int* edx
){
    __asm__ volatile("cpuid"
                    : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
                    : "a"(leaf), "c"(subleaf));
}

unsigned int max_supported_leaf(){
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x00000000, 0, &eax, &ebx, &ecx, &edx);
    return eax;
}

unsigned int max_supported_extended_leaf(){
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x80000000, 0, &eax, &ebx, &ecx, &edx);
    return eax;
}