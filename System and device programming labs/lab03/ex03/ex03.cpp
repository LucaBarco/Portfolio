#if 1
#define UNICODE
#define _UNICODE
#endif
#ifndef UNICODE
#define TCHAR CHAR
#endif
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#define TYPE_FILE 1
#define TYPE_DIR 2
#define TYPE_DOT 3

#define M 100
#define L 500

typedef struct info {
	TCHAR name[L];
	LARGE_INTEGER size;
};
static void TraverseAndCreate(LPTSTR SourcePathName, LPTSTR DestPathName);
static DWORD FileType(LPWIN32_FIND_DATA pFileData);
static BOOL myCopyFile(LPTSTR SourcePathName, LPTSTR DestPathName);

int _tmain(int argc, LPTSTR argv[]){

	TCHAR startPath[L], NewPath[L], myPath[L];
	
	if (argc != 4) {
		fprintf(stderr, "Pars error!\n");
	}
	//argv[3]==1 -> relative paths ; else -> absolute paths

	//supposing argv[2] is a relative path
	if (atoi((const char*)argv[3]) == 1) {
		GetCurrentDirectory(L, myPath);
		_stprintf(NewPath, _T("%s\\%s"), myPath, argv[2]);
		_stprintf(startPath, _T("%s\\%s"), myPath, argv[1]);
	}
	else {
		//supposing argv[2] is an absolute path
		_stprintf(NewPath, _T("%s"), argv[2]);
		_stprintf(startPath, _T("%s"), argv[1]);
	}
	
	TraverseAndCreate(startPath, NewPath);
	Sleep(5000);
	
	return 0;

}
static void TraverseAndCreate(LPTSTR SourcePathName, LPTSTR DestPathName) {
	HANDLE SearchHandle;
	WIN32_FIND_DATA FindData;
	DWORD FType, l;
	TCHAR NewPath[L],myPath[L];
	BOOL status;
	_tprintf(_T("--> Create dir: %s\n"), DestPathName);
	status=CreateDirectory(DestPathName, NULL);
	status=SetCurrentDirectory(SourcePathName);
	SearchHandle = FindFirstFile(_T("*"), &FindData);
	do {
		FType = FileType(&FindData);
		l = _tcslen(DestPathName);
		//build the complete destination path (absolute)
		if (DestPathName[l - 1] == '\\') {
			_stprintf(NewPath, _T("%s%s"), DestPathName, FindData.cFileName);
		}
		else {
			_stprintf(NewPath, _T("%s\\%s"), DestPathName, FindData.cFileName);
		}
		if (FType == TYPE_FILE) {
			//insert new 2 data fields: name (C String) + size (DWORD or LargeInteger)
			//CopyFile(FindData.cFileName, NewPath, FALSE); or create a new file 
		
			myCopyFile(FindData.cFileName, NewPath);
		}
		if (FType == TYPE_DIR) {
			TraverseAndCreate(FindData.cFileName, NewPath); //recurr
			SetCurrentDirectory(_T("..")); //backtrack
		}
	} while (FindNextFile(SearchHandle, &FindData));
	FindClose(SearchHandle);
	return;
}
static DWORD FileType(LPWIN32_FIND_DATA pFileData) {
	BOOL IsDir;
	DWORD FType;
	FType = TYPE_FILE;
	IsDir = (pFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
	if (IsDir) {
		if (lstrcmp(pFileData->cFileName, _T(".")) == 0 || lstrcmp(pFileData->cFileName, _T("..")) == 0) {
			FType = TYPE_DOT;
		}
		else {
			FType = TYPE_DIR;
		}
		
	}
	return FType;
}
static BOOL myCopyFile(LPTSTR SourcePathName, LPTSTR DestPathName) {
	HANDLE hSrc, hDst;
	DWORD nWrt, nRd;
	struct info myInfo;
	TCHAR Path[L],completePath[L];
	TCHAR c;
	GetCurrentDirectory(L, Path);
	_stprintf(completePath, _T("%s\\%s"), Path, SourcePathName);
	hSrc = CreateFile(SourcePathName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hSrc == INVALID_HANDLE_VALUE) {
		
		_tprintf(_T("Error opening file %s\n"), completePath);
		return FALSE;
	}
	hDst = CreateFile(DestPathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hDst == INVALID_HANDLE_VALUE) {
		_tprintf(_T("Error creating file %s\n"), DestPathName);
		return FALSE;
	}
	GetFileSizeEx(hSrc, &myInfo.size);
	_stprintf(myInfo.name, _T("%s"), SourcePathName);
	WriteFile(hDst, &myInfo, sizeof(struct info), &nWrt, NULL);
	while (ReadFile(hSrc, &c, sizeof(TCHAR), &nRd, NULL)&& nRd>0) {
		WriteFile(hDst, &c, sizeof(TCHAR), &nWrt, NULL);
	}
	CloseHandle(hSrc);
	CloseHandle(hDst);
	return TRUE;
}