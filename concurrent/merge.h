// =================================================================
//
// File: merge.h
// Author: Pedro Perez
// Description: This file contains the implementation of the
//				functions used to take the time and perform the
//				speed up calculation; as well as functions for
//				initializing integer arrays.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#ifndef MERGE_H
#define MERGE_H

#include <cstring>

// =================================================================
// Merge both halves of A, using B array as temporary storage.
//
// @param A, the source array.
// @param B, the destination array.
// @param low, lower index.
// @param mid, middle index.
// @param high, higher index.
// =================================================================
template <class T>
void merge(T *A, T *B, int low, int mid, int high) {
	int i, j, k;
	i = low;
	j = mid + 1;
	k = low;
	while(i <= mid && j <= high){
		if(A[i] < A[j]){
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
	for(; j <= high; j++){
		B[k++] = A[j];
	}

	for(; i <= mid; i++){
		B[k++] = A[i];
	}
}

// =================================================================
// If the minimum unit has not been reached (a single array
// position), separate the range [low, high] into two halves,
// invoking the split process again. When no more separations can be
// made, mix both halves of the arrangement.
//
// @param A, the source array.
// @param B, the temporal array.
// @param low, lower index.
// @param high, higher index.
// =================================================================
template<class T>
void split(T *A, T *B, int low, int high) {
	int  mid, size, i, j;

	if (high - low == 0) return;

	mid = low + ((high - low) / 2);
	split(A, B, low, mid);
	split(A, B, mid + 1, high);
	merge(A, B,low, mid, high);
	memcpy(A + low, B + low, (high - low + 1) * sizeof(int));
}

#endif