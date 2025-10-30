#include "common.h"

#include <libmc.h>

#include <stdbool.h>

typedef void (*OperationFinalizer)(int* result);

typedef struct GetInfoOperation {
    int* type;
    int* free;
    int* format;
} GetInfoOperation;

static GetInfoOperation get_info_operation = { 0 };
static int registered_operation = 0;

static void finalize_get_info(int* result) {
    // *get_info_operation.type = sceMcTypePS2;
    // *get_info_operation.free = 0x1F03;
    // *get_info_operation.format = 1;

    // For now we just report absence of a memory card
    *get_info_operation.type = sceMcTypeNoCard;
    *get_info_operation.free = 0;
    *get_info_operation.format = 0;
    *result = sceMcResSucceed;
}

static OperationFinalizer finalizers[21] = { NULL, finalize_get_info,
                                             NULL, NULL,
                                             NULL, NULL,
                                             NULL, NULL,
                                             NULL, NULL,
                                             NULL, NULL,
                                             NULL, NULL,
                                             NULL, NULL,
                                             NULL, NULL,
                                             NULL, NULL,
                                             NULL };

int sceMcInit(void) {
    return sceMcIniSucceed;
}

int sceMcSync(int mode, int* cmd, int* result) {
    if (registered_operation > 0) {
        *cmd = registered_operation;
        finalizers[registered_operation](result);
        registered_operation = 0;
        return sceMcExecFinish;
    } else {
        return sceMcExecIdle;
    }
}

int sceMcGetInfo(int port, int slot, int* type, int* free, int* format) {
    registered_operation = sceMcFuncNoCardInfo;
    get_info_operation.type = type;
    get_info_operation.free = free;
    get_info_operation.format = format;
    return 0;
}

int sceMcOpen(int p1, int p2, const char* p3, int p4) {
    not_implemented(__func__);
}

int sceMcClose(int p1) {
    not_implemented(__func__);
}

int sceMcRead(int p1, void* p2, int p3) {
    not_implemented(__func__);
}

int sceMcWrite(int p1, const void* p2, int p3) {
    not_implemented(__func__);
}

int sceMcMkdir(int p1, int p2, const char* p3) {
    not_implemented(__func__);
}

int sceMcDelete(int p1, int p2, const char* p3) {
    not_implemented(__func__);
}

int sceMcFormat(int p1, int p2) {
    not_implemented(__func__);
}

int sceMcUnformat(int p1, int p2) {
    not_implemented(__func__);
}

int sceMcGetDir(int port, int slot, const char* name, unsigned int mode, int maxent, sceMcTblGetDir* table) {
    not_implemented(__func__);
}
