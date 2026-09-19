#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <llvm-c/Core.h>
#include <llvm-c/BitReader.h>
#include <llvm-c/BitWriter.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <input.bc> <output.bc>\\n", argv[0]);
        return 1;
    }

    LLVMContextRef context = LLVMContextCreate();
    LLVMModuleRef module;
    LLVMMemoryBufferRef mem_buf;
    char *error_msg = NULL;
    
    if (LLVMCreateMemoryBufferWithContentsOfFile(argv[1], &mem_buf, &error_msg)) {
        fprintf(stderr, "Error: %s\\n", error_msg);
        return 1;
    }

    if (LLVMParseBitcodeInContext(context, mem_buf, &module, &error_msg)) {
        fprintf(stderr, "Error parsing: %s\\n", error_msg);
        return 1;
    }

    LLVMDisposeMemoryBuffer(mem_buf);

    LLVMValueRef func = LLVMGetFirstFunction(module);
    int counter = 0;
    while (func != NULL) {
        char new_name[64];
        snprintf(new_name, sizeof(new_name), "jocky_obf_%d", counter++);
        LLVMSetValueName(func, new_name);
        func = LLVMGetNextFunction(func);
    }

    if (LLVMWriteBitcodeToFile(module, argv[2])) {
        fprintf(stderr, "Error writing bitcode\\n");
        return 1;
    }

    printf("[JOCKY] Obfuscation complete!\\n");
    LLVMDisposeModule(module);
    LLVMContextDispose(context);
    return 0;
}
