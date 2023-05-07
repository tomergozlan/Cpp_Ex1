/**
* @file AdptArray.c
* @brief This is a implementation file for a dynamic array that adapts to the element type given by the user.
*
* The array can store any type of element and allows the user to perform basic operations
* such as insert, get, and delete.
* The array dynamically allocates memory to adapt to the required size and elements,
* which are identified by a unique index.
*
* @author Tomer Gozlan
* @date 22/11/2022
*/

#include <stdio.h>
#include "AdptArray.h"
#include <stdlib.h>
#include <string.h>

typedef struct AdptArray_ {
    int ArrSize;
    PElement *pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
} AdptArray, *PAdptArray;

/**
@brief Creates a new dynamic array that adapts to the element type
@param[in] copyFunc_ - Pointer to a copy function for an element
@param[in] delFunc_ - Pointer to a delete function for an element
@param[in] printFunc_ - Pointer to a print function for an element
@return Pointer to the newly created dynamic array
*/

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_) {
    PAdptArray pArr = (PAdptArray) malloc(sizeof(AdptArray));
    if (!pArr) {
        printf("Error ! Memory allocations failed");
        return NULL;
    }
    pArr->ArrSize = 0;
    pArr->pElemArr = NULL;
    pArr->delFunc = delFunc_;
    pArr->copyFunc = copyFunc_;
    pArr->printFunc = printFunc_;
    return pArr;
}

/**
@brief Deletes a dynamic array and all of its elements
@param[in] pArr - Pointer to the dynamic array to delete
@return void
*/
void DeleteAdptArray(PAdptArray pArr) {
    int i;
    if (!pArr) return;
    for (i = 0; i < pArr->ArrSize; ++i) {
        if ((pArr->pElemArr)[i] == NULL)
            continue;
        pArr->delFunc((pArr->pElemArr)[i]);
    }
    free(pArr->pElemArr);
    free(pArr);
}

/**
@brief Sets an element at a specific index of the dynamic array
@param[in] pArr - Pointer to the dynamic array
@param[in] idx - The index at which to set the element
@param[in] pNewElem - Pointer to the new element to set
@return SUCCESS if successful, FAIL otherwise
*/
Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem) {
    PElement *newpElemArr;
    if (!pArr)
        return FAIL;
    if (idx >= pArr->ArrSize) {
        if ((newpElemArr = (PElement *) calloc((idx + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
        free(pArr->pElemArr);
        pArr->pElemArr = newpElemArr;
    }
    if ((pArr->pElemArr)[idx] != NULL)
        pArr->delFunc((pArr->pElemArr)[idx]);
    (pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);
    pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
    return SUCCESS;
}

/**
@brief Gets the element at a given index in the adaptive array.
@param pArr Pointer to the adaptive array.
@param idx The index of the element to be retrieved.
@return A copy of the element at the specified index if successful; otherwise, NULL.
*/

PElement GetAdptArrayAt(PAdptArray pArr, int idx) {
    if (!pArr || idx < 0 || idx >= pArr->ArrSize) {
        return NULL;
    }
    PElement pElem = pArr->pElemArr[idx];
    if (!pElem)
        return NULL;
    return pArr->copyFunc(pElem);
}

/**
@brief Get the current size of the adaptive array.
@param pArr Pointer to the adaptive array structure.
@return int The current size of the adaptive array. Returns -1 if pArr is NULL.
*/
int GetAdptArraySize(PAdptArray pArr) {
    if (!pArr)
        return -1;
    return pArr->ArrSize;
}

/**
@brief Prints the elements in the array using the provided print function.
@param pArr Pointer to the adaptive array to be printed
This function prints the elements in the adaptive array by iterating over each element
and calling the provided print function on non-null elements. If the provided array
pointer is NULL, an error message will be printed to the console.
*/
void PrintDB(PAdptArray pArr) {
    int i;
    if (!pArr) {
        printf("Error! Array is not initialized successfully\n");
        return;
    }
    for (i = 0; i < pArr->ArrSize; i++) {
        if ((pArr->pElemArr)[i] == NULL)
            continue;
        pArr->printFunc(pArr->pElemArr[i]);
    }
}
