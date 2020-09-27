#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#define TYPE_FILE 1
#define TYPE_DIR 2
#define TYPE_DOT 3
#define L 500
struct thread_pars {
	TCHAR dirName[L];
	DWORD id;
	BOOL error;
};
typedef struct thread_pars *LPTHREADPARS;

struct path_entry {
	LPSTR path;
	DWORD level;
	struct path_entry *child;
	struct path_entry *parent;
};
typedef struct path_entry *LPPATHENTRY;



CRITICAL_SECTION CriticalSection, CriticalSection2;

DWORD WINAPI ThreadFunction(LPVOID pars);
static void TraverseDirectoryRecursive(LPTSTR PathName, DWORD level);
static DWORD FileType(LPWIN32_FIND_DATA pFileData);

int _tmain(int argc, LPTSTR argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: dir1 dir2 dir3 ....\n");
		Sleep(3000);
		return 1;
	}
	LPHANDLE handles;
	DWORD i, n,j;
	LPTHREADPARS parameters;
	TCHAR line[1024], myDir[L], myCurPath[L], myParentPath[L];

	GetCurrentDirectory(L, myDir);
	n = argc - 1;
	parameters = (LPTHREADPARS)malloc(n * sizeof(struct thread_pars));
	handles = (LPHANDLE)malloc(n * sizeof(HANDLE));
	InitializeCriticalSection(&CriticalSection);
	InitializeCriticalSection(&CriticalSection2);

	for (i = 0; i < n; i++) {
		if (argv[i + 1][0] == '.' && argv[i + 1][1] == '.') {
			SetCurrentDirectory(_T(".."));
			GetCurrentDirectory(L, myParentPath);
			SetCurrentDirectory(myDir);

			for (j = 3; j < strlen(argv[i + 1]); j++) {
				myCurPath[j - 3] = argv[i + 1][j];
			}
			myCurPath[j - 3] = '\0';

			_stprintf(parameters[i].dirName, _T("%s\\%s"), myParentPath, myCurPath);
			_tprintf("correct directory:%s\n", parameters[i].dirName);
		}
		else if (argv[i + 1][0] == '.' && argv[i + 1][1] != '.') {
			GetCurrentDirectory(L, myParentPath);
			for (j = 2; j < strlen(argv[i + 1]); j++) {
				myCurPath[j - 2] = argv[i + 1][j];
			}
			myCurPath[j - 2] = '\0';
			_stprintf(parameters[i].dirName, _T("%s\\%s"), myParentPath, myCurPath);
			_tprintf("correct directory:%s\n", parameters[i].dirName);
		}
		else {
			_stprintf(parameters[i].dirName, _T("%s"), argv[i + 1]);
		}
	}



	
	for (i = 0; i < n; i++) {
		handles[i] = CreateThread(NULL, 0, ThreadFunction, (void *)&parameters[i], 0, &parameters[i].id);
	}
	WaitForMultipleObjects(n, handles, TRUE, INFINITE);
	DeleteCriticalSection(&CriticalSection);
	DeleteCriticalSection(&CriticalSection2);
	return 0;
}
DWORD WINAPI ThreadFunction(LPVOID pars) {
	
	LPTHREADPARS parameters = (LPTHREADPARS)pars;
	
	_tprintf(_T("Thread id : %d\tlevel=0 DIR:%s\n"), parameters->id, parameters->dirName);

	TraverseDirectoryRecursive(parameters->dirName, 1);


	ExitThread(0);
}

static void TraverseDirectoryRecursive(LPTSTR PathName, DWORD level) {
	HANDLE SearchHandle;
	WIN32_FIND_DATA FindData;
	DWORD FType, i;
	TCHAR myPath[L];
	EnterCriticalSection(&CriticalSection2);
	SetCurrentDirectory(PathName);
	SearchHandle = FindFirstFile(_T("*"), &FindData);
	LeaveCriticalSection(&CriticalSection2);

	do {
		FType = FileType(&FindData);
		if (FType == TYPE_DIR) {
			/*for (i = 0; i < level; i++) {
				_tprintf(_T(" "));
			}*/
			_tprintf(_T("Thread id : %d\tlevel=%d DIR:%s\n"), GetCurrentThreadId(), level, FindData.cFileName);
			_stprintf(myPath, _T("%s\\%s"), PathName, FindData.cFileName);

			TraverseDirectoryRecursive(myPath, level + 1);

		}

	} while (FindNextFile(SearchHandle, &FindData));
	FindClose(SearchHandle);
	return;
}

static DWORD FileType(LPWIN32_FIND_DATA pFileData) {
	BOOL isDir;
	DWORD FType;
	FType = TYPE_FILE;
	isDir = (pFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
	if (isDir) {
		if (lstrcmp(pFileData->cFileName, _T(".")) == 0 || lstrcmp(pFileData->cFileName, _T("..")) == 0) {
			FType = TYPE_DOT;
		}
		else {
			FType = TYPE_DIR;
		}
	}
	return FType;
}