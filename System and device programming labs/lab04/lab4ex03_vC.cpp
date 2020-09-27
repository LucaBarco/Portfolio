#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#define TYPE_FILE 1
#define TYPE_DIR 2
#define TYPE_DOT 3
#define L 500

struct log_entry {
	TCHAR message[1024];
	DWORD thread_id;
	struct log_entry *child;
	struct log_entry *parent;
};
typedef struct log_entry *LPLOGENTRY;

struct outputthread_pars {
	LPLOGENTRY head;
	LPDWORD thread_ids;
	DWORD n;
};
typedef struct outputthread_pars *LPOUTPUTTHREADPARS;
struct thread_pars {
	DWORD id;
	BOOL error;
	TCHAR dirName[L];
	LPLOGENTRY headLogList;
};
typedef struct thread_pars *LPTHREADPARS;

//CRITICAL_SECTION CriticalSection, CriticalSection2;
CRITICAL_SECTION CSsaveLog;
HANDLE mutex;

LPLOGENTRY initLogList();
LPLOGENTRY addLog(LPLOGENTRY head, LPSTR message, DWORD thread_id);
void printLog(LPLOGENTRY head, DWORD id);
DWORD WINAPI ThreadFunction(LPVOID pars);
DWORD WINAPI OutputThreadFunction(LPVOID pars);
static void TraverseDirectoryRecursive(LPTSTR PathName, DWORD level, LPTHREADPARS parameters);
static DWORD FileType(LPWIN32_FIND_DATA pFileData);

int _tmain(int argc, LPTSTR argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: dir1 dir2 dir3 ....\n");
		Sleep(3000);
		return 1;
	}
	HANDLE hOutThread;
	LPHANDLE handles;
	DWORD i, n, j;
	LPTHREADPARS parameters;
	struct outputthread_pars Outputparameter;
	FILE *fp;
	TCHAR line[1024], myDir[L], myCurPath[L], myParentPath[L];

	GetCurrentDirectory(L, myDir);

	n = argc - 1;

	parameters = (LPTHREADPARS)malloc(n * sizeof(struct thread_pars));
	handles = (LPHANDLE)malloc(n * sizeof(HANDLE));
	Outputparameter.thread_ids = (LPDWORD)malloc(n * sizeof(DWORD));
	Outputparameter.n = n;

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
	InitializeCriticalSection(&CSsaveLog);
	Outputparameter.head = initLogList();

	for (i = 0; i < n; i++) {
		parameters[i].headLogList = Outputparameter.head;
		handles[i] = CreateThread(NULL, 0, ThreadFunction, (void *)&parameters[i], 0, &parameters[i].id);
		Outputparameter.thread_ids[i] = parameters[i].id;
	}
	WaitForMultipleObjects(n, handles, TRUE, INFINITE);
	hOutThread = CreateThread(NULL, 0, OutputThreadFunction, (void *)&Outputparameter, 0, NULL);
	WaitForSingleObject(hOutThread, INFINITE);
	CloseHandle(mutex);
	DeleteCriticalSection(&CSsaveLog);

	return 0;
}
DWORD WINAPI ThreadFunction(LPVOID pars) {
	mutex = CreateMutex(NULL, TRUE, NULL);
	LPTHREADPARS parameters = (LPTHREADPARS)pars;
	TCHAR message[1024];

	//_tprintf(_T("Thread id : %d\tlevel=0 DIR:%s\n"), parameters->id, parameters->dirName);
	_stprintf(message, _T("Thread id : %d\tlevel=0 DIR:%s\n"), parameters->id, parameters->dirName);
	EnterCriticalSection(&CSsaveLog);
	parameters->headLogList=addLog(parameters->headLogList,message,parameters->id);
	LeaveCriticalSection(&CSsaveLog);

	TraverseDirectoryRecursive(parameters->dirName, 1, parameters);
	
	ExitThread(0);
}

static void TraverseDirectoryRecursive(LPTSTR PathName, DWORD level, LPTHREADPARS parameters) {
	HANDLE SearchHandle;
	WIN32_FIND_DATA FindData;
	DWORD FType, i;
	TCHAR myPath[L], log[L],message[1024];
	
	WaitForSingleObject(mutex, INFINITE);
	SetCurrentDirectory(PathName);
	SearchHandle = FindFirstFile(_T("*"), &FindData);
	ReleaseMutex(mutex);
	
	do {
		FType = FileType(&FindData);
		if (FType == TYPE_DIR) {
			
			//		_tprintf(_T("Thread id : %d\tlevel=%d DIR:%s\n"), GetCurrentThreadId(), level, FindData.cFileName);
			_stprintf(myPath, _T("%s\\%s"), PathName, FindData.cFileName);
			_stprintf(message, _T("Thread id : %d\tlevel=%d DIR:%s\n"), GetCurrentThreadId(), level, FindData.cFileName);
			EnterCriticalSection(&CSsaveLog);
			parameters->headLogList=addLog(parameters->headLogList, message, parameters->id);
			LeaveCriticalSection(&CSsaveLog);
			TraverseDirectoryRecursive(myPath, level + 1, parameters);

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

DWORD WINAPI OutputThreadFunction(LPVOID pars) {
	LPOUTPUTTHREADPARS parameters = (LPOUTPUTTHREADPARS)pars;
	DWORD i;
	for (i = 0; i < parameters->n; i++) {
		_tprintf(_T("Thread %d: \n"),parameters->thread_ids[i]);
		printLog(parameters->head,parameters->thread_ids[i]);
	}
	ExitThread(0);
}
LPLOGENTRY initLogList() {
	LPLOGENTRY head = (LPLOGENTRY)malloc(sizeof(struct log_entry));
	head->parent = NULL;
	head->child = NULL;
	return head;
}
LPLOGENTRY addLog(LPLOGENTRY head, LPSTR message,DWORD thread_id) {

	if (head == NULL) {
		head= (LPLOGENTRY)malloc(sizeof(struct log_entry));
		head->child = NULL;
		_stprintf(head->message, _T("%s"), message);
		head->thread_id = thread_id;
		return head;
	}
	head->child = addLog(head->child, message, thread_id);
	head->child->parent = head;
	return head;
/*
	if (head->child == NULL) {
		head->child = (LPLOGENTRY)malloc(sizeof(struct log_entry));
		_stprintf(head->child->message, _T("%s"), message);
		head->child->thread_id = thread_id;
		head->child->child = NULL;
		head->child->parent = head;
		return head->child;
	}
	head->child=addLog(head->child,message,thread_id);
	return head->child;*/
}
void printLog(LPLOGENTRY head, DWORD id) {
	if (head== NULL) {
		return;
	}
	if (head->thread_id == id) {
		_tprintf(_T("%s\n"), head->message);
	}
	printLog(head->child,id);
	return;
}