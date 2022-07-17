#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/stat.h>

#define err_handle(m)                                                          \
    do {                                                                       \
        perror(m);                                                             \
        exit(-1);                                                              \
    }while(0)

int main(int argc, char **argv) {
    struct stat st;
    bzero(&st, sizeof(st));
    stat("makefile", &st);
    printf("dev:%ld\n", st.st_dev);
    printf("ino:%ld\n", st.st_ino);
    printf("mode:%d\n", st.st_mode);
    printf("nlink:%ld\n", st.st_nlink);
    printf("uid:%d\n", st.st_uid);
    printf("gid:%d\n", st.st_gid);
    printf("size:%ld\n", st.st_size);
    if(S_ISREG(st.st_mode))
        printf("makefile is [-]\n");
    return 0;
}
//  struct stat {
//     dev_t st_dev;         /* ID of device containing file */ 设备号
//     ino_t st_ino;         /* Inode number */ inode号
//     mode_t st_mode;       /* File type and mode */   权限和文件类型
//     nlink_t st_nlink;     /* Number of hard links */
//     uid_t st_uid;         /* User ID of owner */
//     gid_t st_gid;         /* Group ID of owner */
//     dev_t st_rdev;        /* Device ID (if special file) */
//     off_t st_size;        /* Total size, in bytes */
//     blksize_t st_blksize; /* Block size for filesystem I/O */
//     blkcnt_t st_blocks;   /* Number of 512B blocks allocated */
//     struct timespec st_atim; /* Time of last access */
//     struct timespec st_mtim; /* Time of last modification */
//     struct timespec st_ctim; /* Time of last status change */
// };
//stat判断文件类型的方法 sb.st_mode & S_IFMT
// #define	__S_IFMT	0170000	/* These bits determine file type.  */
// /* File types.  */
// #define	__S_IFDIR	0040000	/* Directory.  */
// #define	__S_IFCHR	0020000	/* Character device.  */
// #define	__S_IFBLK	0060000	/* Block device.  */
// #define	__S_IFREG	0100000	/* Regular file.  */
// #define	__S_IFIFO	0010000	/* FIFO.  */
// #define	__S_IFLNK	0120000	/* Symbolic link.  */
// #define	__S_IFSOCK	0140000	/* Socket.  */
// s_IFCHR:  printf("character device\n");        break;
// S_IFDIR:  printf("directory\n");               break;
// S_IFIFO:  printf("FIFO/pipe\n");               break;
// S_IFLNK:  printf("symlink\n");                 break;
// S_IFREG:  printf("regular file\n");            break;
// S_IFSOCK: printf("socket\n");                  break;