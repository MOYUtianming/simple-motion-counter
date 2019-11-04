## definition of FIL
>
    /* File object structure (FIL) */

    typedef struct {
        FATFS*	fs;				/* Pointer to the related file system object (**do not change order**) */
        WORD	id;				/* Owner file system mount ID (**do not change order**) */
        BYTE	flag;			/* Status flags */
        BYTE	err;			/* Abort flag (error code) */
        DWORD	fptr;			/* File read/write pointer (Zeroed on file open) */
        DWORD	fsize;			/* File size */
        DWORD	sclust;			/* File start cluster (0:no cluster chain, always 0 when fsize is 0) */
        DWORD	clust;			/* Current cluster of fpter (not valid when fprt is 0) */
        DWORD	dsect;			/* Sector number appearing in buf[] (0:invalid) */
    #if !_FS_READONLY
        DWORD	dir_sect;		/* Sector number containing the directory entry */
        BYTE*	dir_ptr;		/* Pointer to the directory entry in the win[] */
    #endif
    #if _USE_FASTSEEK
        DWORD*	cltbl;			/* Pointer to the cluster link map table (Nulled on file open) */
    #endif
    #if _FS_LOCK
        UINT	lockid;			/* File lock ID origin from 1 (index of file semaphore table Files[]) */
    #endif
    #if !_FS_TINY
        BYTE	buf[_MAX_SS];	/* File private data read/write window */
    #endif
    } FIL;
## other macro-functions
>
    #define f_eof(fp) (((fp)->fptr == (fp)->fsize) ? 1 : 0)
        find the end of a file;
    #define f_error(fp) ((fp)->err)
        get error message;
    #define f_tell(fp) ((fp)->fptr)
        get file read/write pointer;
    #define f_size(fp) ((fp)->fsize)
        get size of a file;
## FRESULT f_open (FIL* fp, const TCHAR* path, BYTE mode);				/* Open or create a file */
>
    FRESULT f_open (
        FIL* fp,			/* Pointer to the blank file object */
        const TCHAR* path,	/* Pointer to the file name */
        BYTE mode			/* Access mode and file open mode flags */
    )
## FRESULT f_close (FIL* fp);											/* Close an open file object */
>
    FRESULT f_close (
        FIL *fp		/* Pointer to the file object to be closed */
    )
## FRESULT f_read (FIL* fp, void* buff, UINT btr, UINT* br);			/* Read data from a file */
>
    FRESULT f_read (
        FIL* fp, 		/* Pointer to the file object */
        void* buff,		/* Pointer to data buffer */
        UINT btr,		/* Number of bytes to read */
        UINT* br		/* Pointer to number of bytes read */
    )
## FRESULT f_write (FIL* fp, const void* buff, UINT btw, UINT* bw);	/* Write data to a file */
> 
    FRESULT f_write (
	FIL* fp,			/* Pointer to the file object */
	const void *buff,	/* Pointer to the data to be written */
	UINT btw,			/* Number of bytes to write */
	UINT* bw			/* Pointer to number of bytes written */
    )
## FRESULT f_lseek (FIL* fp, DWORD ofs);								/* Move file pointer of a file object */
>
    FRESULT f_lseek (
	FIL* fp,		/* Pointer to the file object */
	DWORD ofs		/* File pointer from top of file */
    )
## FRESULT f_opendir (DIR* dp, const TCHAR* path);						/* Open a directory */
>
    FRESULT f_opendir (
	DIR* dp,			/* Pointer to directory object to create */
	const TCHAR* path	/* Pointer to the directory path */
    )
## FRESULT f_closedir (DIR* dp);										/* Close an open directory */
>
    FRESULT f_closedir (
        DIR *dp		/* Pointer to the directory object to be closed */
    )
## FRESULT f_readdir (DIR* dp, FILINFO* fno);							/* Read a directory item */
>
    FRESULT f_readdir (
        DIR* dp,			/* Pointer to the open directory object */
        FILINFO* fno		/* Pointer to file information to return */
    )
## FRESULT f_mkdir (const TCHAR* path);								/* Create a sub directory */
>
    FRESULT f_mkdir (
	const TCHAR* path		/* Pointer to the directory path */
    )
## FRESULT f_getlabel (const TCHAR* path, TCHAR* label, DWORD* vsn);	/* Get volume label */
>
    FRESULT f_getlabel (
        const TCHAR* path,	/* Path name of the logical drive number */
        TCHAR* label,		/* Pointer to a buffer to return the volume label */
        DWORD* vsn			/* Pointer to a variable to return the volume serial number */
    )
## FRESULT f_truncate (FIL* fp);										/* Truncate file */
## FRESULT f_sync (FIL* fp);											/* Flush cached data of a writing file */
## FRESULT f_unlink (const TCHAR* path);								/* Delete an existing file or directory */
## FRESULT f_rename (const TCHAR* path_old, const TCHAR* path_new);	/* Rename/Move a file or directory */
## FRESULT f_stat (const TCHAR* path, FILINFO* fno);					/* Get file status */
## FRESULT f_chmod (const TCHAR* path, BYTE value, BYTE mask);			/* Change attribute of the file/dir */
## FRESULT f_utime (const TCHAR* path, const FILINFO* fno);			/* Change times-tamp of the file/dir */
## FRESULT f_chdir (const TCHAR* path);								/* Change current directory */
## FRESULT f_chdrive (const TCHAR* path);								/* Change current drive */
## FRESULT f_getcwd (TCHAR* buff, UINT len);							/* Get current directory */
## FRESULT f_getfree (const TCHAR* path, DWORD* nclst, FATFS** fatfs);	/* Get number of free clusters on the drive */
## FRESULT f_setlabel (const TCHAR* label);							/* Set volume label */
## FRESULT f_mount (FATFS* fs, const TCHAR* path, BYTE opt);			/* Mount/Unmount a logical drive */
## FRESULT f_mkfs (const TCHAR* path, BYTE sfd, UINT au);				/* Create a file system on the volume */
## FRESULT f_fdisk (BYTE pdrv, const DWORD szt[], void* work);			/* Divide a physical drive into some partitions */
## int f_putc (TCHAR c, FIL* fp);										/* Put a character to the file */
## int f_puts (const TCHAR* str, FIL* cp);								/* Put a string to the file */
## int f_printf (FIL* fp, const TCHAR* str, ...);						/* Put a formatted string to the file */
## TCHAR* f_gets (TCHAR* buff, int len, FIL* fp);						/* Get a string from the file */
## FRESULT f_forward (FIL* fp, UINT(*func)(const BYTE*,UINT), UINT btf, UINT* bf);	/* Forward data to the stream */
