#include <stdio.h>
#include <sys/stat.h>

void dump_buffer(unsigned char *buffer, off_t buffer_size)
{
    off_t i;
    for(i = 0;i < buffer_size; ++i) { printf("%02x \n", (int)buffer[i]); }
    printf("\n");
}

off_t fileSize(std::string fn)
{
	struct stat64 fsStatBuf;
	stat64(fn.c_str(), &fsStatBuf);
	off_t fileLen = fsStatBuf.st_size;
    return fileLen;
}
