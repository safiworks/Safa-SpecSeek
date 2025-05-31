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