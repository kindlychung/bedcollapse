#include <iostream>
#include <boost/filesystem.hpp>
#include <math.h>
#include "src/countlines.h"
#include "src/collgen_memo.h"
#include "src/util.h"

using namespace std;

void bedColl(std::string fn, std::string outfn, off_t nshift) {
    boost::filesystem::path fpath(fn);
    auto fstem = fpath.stem();
    auto fbranch = fpath.branch_path();
    auto fbed = fbranch / (fstem.string() + ".bed");
    auto fbim = fbranch / (fstem.string() + ".bim");
    auto ffam = fbranch / (fstem.string() + ".fam");
    auto bedfn = fbed.string();
    auto bimfn = fbim.string();
    auto famfn = ffam.string();

    off_t nsnp = countlines(bimfn);
    off_t nindiv = countlines(famfn);
    off_t bytes_snp = ceil(nindiv / 4.0);
    off_t bytes_read = bytes_snp * nsnp;
    // see the documentation picture on flickr
    off_t bytes_shift = bytes_snp * nshift;
    if(bytes_shift > bytes_read) {throw "Shift too large!";}
    off_t bytes_left = bytes_read - bytes_shift;

    // read snps into buffer, from the bed file
	FILE *file;
	file = fopen(bedfn.c_str(), "rb"); if (!file) { fprintf(stderr, "Unable to open file %s", fn.c_str()); }
    unsigned char buffer[bytes_read]; if (!buffer) { fprintf(stderr, "Memory error!"); fclose(file); }
    fseeko(file, 3, SEEK_SET);
	fread(buffer, bytes_read, 1, file);

    unsigned char collres[bytes_read];
    // initialize with NA
    std::fill_n(collres, bytes_read, 0x55);
    for(off_t i=0; i<bytes_left; i++)
    {
        // collapse genotype using the memoization array
        collres[i] = collgen[buffer[i]][buffer[i+bytes_shift]];
    }

    FILE *outfile = fopen(outfn.c_str(), "w+");
    fwrite(magicbits, 3, 1, outfile);
    fwrite(collres, bytes_read, 1, outfile);
    fclose(outfile);
}

int main(int argc, char const* argv[])
{
    bedColl("test", "/tmp/out.bed", 1);
    // std::string fn = "test.bed";
    // ReadFile(fn);
    // srand(time(NULL));
    // testcollgenarray();
    return 0;
}
