#include <iostream>
#include <boost/filesystem.hpp>
#include "src/countlines.h"


#include <stdio.h>
#include <sys/stat.h>
using namespace std;
void dump_buffer(unsigned char *buffer, off_t buffer_size)
{
    // off_t buffer_size = sizeof(buffer)/sizeof(buffer[0]);
    // cout << "buffer size: " << buffer_size << endl;
    off_t i;
    for(i = 0;i < buffer_size; ++i)
    {
     printf("%02x \n", ((unsigned char *)buffer)[i]);
    }
    printf("\n");
}

void ReadFile(std::string fn)
{
	FILE *file;
	file = fopen(fn.c_str(), "rb");
	if (!file)
	{
		fprintf(stderr, "Unable to open file %s", fn.c_str());
		return;
	}
	// struct stat64 fsStatBuf;
	// stat64(fn.c_str(), &fsStatBuf);
	// off_t fileLen = fsStatBuf.st_size;
    unsigned char buffer[1];
	if (!buffer)
	{
		fprintf(stderr, "Memory error!");
        fclose(file);
		return;
	}
    fseeko(file, 3, SEEK_SET);
	fread(buffer, 1, 1, file);
	fclose(file);
    dump_buffer(buffer, 1);
}

void readOnePerson(std::string fn) {
    boost::filesystem::path fpath(fn);
    auto fstem = fpath.stem();
    auto fbranch = fpath.branch_path();
    auto fbed = fbranch / (fstem.string() + ".bed");
    auto fbim = fbranch / (fstem.string() + ".bim");
    auto ffam = fbranch / (fstem.string() + ".fam");
    auto bedfn = fbed.string();
    auto bimfn = fbim.string();
    auto famfn = ffam.string();
    int nsnp = ctline(bimfn);
    int nindiv = ctline(famfn);
    using namespace std;
    cout << "nsnp: " << nsnp << endl;
    cout << "nindiv: " << nindiv << endl;
}

int main(int argc, char const* argv[])
{
    using namespace std;
    readOnePerson("test");
    std::string fn = "test.bed";
    ReadFile(fn);
    return 0;
}
