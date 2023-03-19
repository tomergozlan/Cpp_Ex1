#include <stdio.h>
#include "AdptArray.h"
#include <stdlib.h>
#include <string.h>

typedef struct AdptArray_ {
    int ArrSize;
    PElement* pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_) {
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
    if (!pArr)
        printf("Error ! Memory allocations failed");
        return NULL;
    pArr->ArrSize = 0;
    pArr->pElemArr = NULL;
    pArr->delFunc = delFunc_;
    pArr->copyFunc = copyFunc_;
    pArr->printFunc = printFunc_;
    return pArr;
}

void DeleteAdptArray(PAdptArray pArr) {
    int i;
    if (!pArr) return;
    for(i = 0; i < pArr->ArrSize; ++i)
    {
        pArr->delFunc((pArr->pElemArr)[i]);
    }
    free(pArr->pElemArr);
    free(pArr);
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem) {
    PElement* newpElemArr;
    if (!pArr) return FAIL;
    if (idx >= pArr->ArrSize) {
        if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
        free(pArr->pElemArr);
        pArr->pElemArr = newpElemArr;
    }
    pArr->delFunc((pArr->pElemArr)[idx]);
    (pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);
    pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pArr, int idx){
    if (!pArr || idx < 0 || idx >= pArr->ArrSize) {
        return NULL;
    }
    PElement pElem = pArr->pElemArr[idx];
    if (!pElem) {
        printf(Error! no element stored at that particular index)
        return NULL;
    }
    return pArr->copyFunc(pElem);
}

int GetAdptArraySize(PAdptArray pArr) {
    if (!pArr || pArr->ArrSize < 1) {
        return -1;
    }
    return pArr->ArrSize;
}

void PrintDB(PAdptArray pArr) {
    int i;
    if (!pArr) {
        printf("Error! Array is not initialized successfully\n");
        return;
    }
    for (i = 0; i < pArr->ArrSize; i++) {
        printf("[%d]: ", i);
        pArr->printFunc(pArr->pElemArr[i]);
        printf("\n");
    }
}
