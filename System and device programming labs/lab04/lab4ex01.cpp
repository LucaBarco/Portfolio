
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

struct thread_pars {
	LPSTR filename;
	INT32 id;
	PINT32 vect;
	INT32 n;
	BOOL error;
};
typedef struct thread_pars *LPTHREADPARS;
void MergeVectors(PINT32 A, PINT32 B, INT32 NA, INT32 NB, INT32 Ntot);
DWORD WINAPI ThreadFunction(LPVOID pars);
void MergeSort(PINT32 A, INT32 N);
int _tmain(int argc, LPTSTR argv[])
{
	if (argc < 3) {
		fprintf(stderr, "Usage: cp filein_1 filein_2 ... fileout\n");
		Sleep(3000);
		return 1;
	}
	INT32 n,nt=0,ntot=0;
	n = argc-2; //the last one is the name of the output file
	LPTHREADPARS parameters;
	LPHANDLE handles;
	DWORD exitStatus,nwrite;
	HANDLE hOut;
	INT32 i,j;
	PINT32  res;
	hOut = CreateFile(argv[argc - 1], GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hOut == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "Cannot open output file. Error: %x\n", GetLastError());
		Sleep(2000);
		CloseHandle(hOut);
		return 3;
	}
	for (i = 0; i < argc; i++) {
		_tprintf(_T("argv[%d]= %s\n"), i, argv[i]);
	}

	parameters = (LPTHREADPARS)malloc(n * sizeof(struct thread_pars));
	handles = (LPHANDLE)malloc(n * sizeof(HANDLE));

	for ( i = 0; i < n; i++) {
		parameters[i].id = i;
		parameters[i].filename = argv[i + 1];
		parameters[i].error =false;
		handles[i] = CreateThread(NULL,0, ThreadFunction,(LPVOID)&parameters[i],0,NULL);
	}
	
	exitStatus = WaitForMultipleObjects(n,handles,TRUE,INFINITE);
	if (exitStatus != WAIT_OBJECT_0) {
		//error
		fprintf(stderr, "WFMO failed\n");
		Sleep(3000);
		return 1;
	}
	
	for (i = 0; i < n; i++) {
		if (parameters[i].error) {
			fprintf(stderr, "Cannot open file input %s\n",parameters[i].filename);
			Sleep(3000);
			return 4;
		}
	}
	//merge
	nt = parameters[0].n;
	for ( i = 0; i < n; i++) {
		ntot += parameters[i].n;
		_tprintf(_T("\nvect %d = \t"), i);
		for (j = 0; j < parameters[i].n; j++) {
				_tprintf(_T("\nvect%d[%d] = %d\n"), i,j, parameters[i].vect[j]);
		}
	}
	res = (PINT32)malloc(ntot * sizeof(INT32));
	for (i = 0; i < parameters[0].n; i++) {
		res[i] = parameters[0].vect[i];
	}
	for (i = 0; i < n - 1; i++) {
		MergeVectors(res, parameters[i + 1].vect, nt, parameters[i+1].n,ntot);
		nt = nt + parameters[i + 1].n;
	}
	WriteFile(hOut, &ntot, sizeof(INT32), &nwrite, NULL);
	for (i = 0; i < ntot; i++) {
		_tprintf(_T("\tres[%d] = %d\n"),i,res[i]);
		WriteFile(hOut, &res[i], sizeof(INT32), &nwrite, NULL);
	}

	return 0;
}
DWORD WINAPI ThreadFunction(LPVOID pars) {
	LPTHREADPARS parameters = (LPTHREADPARS)pars;
	HANDLE hIn;
	INT32 buffer;
	DWORD nread;
	DWORD i,n;
	hIn = CreateFile(parameters->filename, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hIn == INVALID_HANDLE_VALUE) {
		parameters->error = true;
		fprintf(stderr, "Thread %d: Cannot open input file %s. Error: %x\n", parameters->id,parameters->filename, GetLastError());
		Sleep(2000);
		return 2;
	}

	if (!ReadFile(hIn, &buffer, sizeof(INT32), &nread, NULL)) {
		fprintf(stderr, "Thread %d: Cannot read from input file %s. Error: %x\n", parameters->id, parameters->filename, GetLastError());
		Sleep(2000);
		return 3;
	}
	
	parameters->n = buffer;
	parameters->vect = (PINT32)malloc(buffer * sizeof(INT32));
	
	for (i = 0; i < buffer && ReadFile(hIn, &parameters->vect[i], sizeof(INT32), &nread, NULL); i++);
	MergeSort(parameters->vect, parameters->n);
	return 0;
}

void Merge(PINT32 A, PINT32 B,INT32 l, INT32 q, INT32 r ) {
	INT32 i, j, k;
	i = l;
	j = q + 1;
	for (k = l; k <= r; k++) {
		if (i > q) {
			B[k] = A[j++];
		}
		else {
			if (j > r) {
				B[k] = A[i++];
			}
			else {
				if ((A[i] < A[j]) || (A[i] == A[j])) {
					B[k] = A[i++];
				}
				else {
					B[k] = A[j++];
				}
			}
		}
	}
	for (k = l; k <= r; k++) {
		A[k] = B[k];
	}
	return;
}
void MergeSortR(PINT32 A, PINT32 B, INT32 l, INT32 r) {
	INT32 q, i;
	if (r <= l) {
		return;
	}
	q = (l + r) / 2;
	MergeSortR(A, B, l, q);
	MergeSortR(A, B, q + 1, r);
	Merge(A, B, l, q, r);
}
void MergeSort(PINT32 A, INT32 N) {
	INT32 l = 0, r = N - 1;
	PINT32 B = (PINT32)malloc(N * sizeof(INT32));
	MergeSortR(A, B, l, r);
}
void MergeVectors(PINT32 A, PINT32 B, INT32 NA, INT32 NB,INT32 Ntot) {
	INT32 a=0, b=0, c=0, NC = NA + NB;
	PINT32 C = (PINT32)malloc(NC * sizeof(INT32));
	if (NC > Ntot) {
		NC = Ntot;
	}
	for (c = 0; c < NC; c++) {
		if (a >= NA) {
			C[c] = B[b++];
		}
		else {
			if (b >= NB) {
				C[c] = A[a++];
			}
			else {
				if (A[a] <= B[b]) {
					C[c] = A[a++];
				}
				else {
					C[c] = B[b++];
				}
			}
		}
	}
	for (c = 0; c < NC; c++) {
		A[c] = C[c];
	}
	free(C);

}