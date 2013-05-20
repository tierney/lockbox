#include "rsync.h"

#include <librsync.h>
#include <stdio.h>

namespace lockbox {

static size_t block_len = RS_DEFAULT_BLOCK_LEN;
static size_t strong_len = RS_DEFAULT_STRONG_LEN;


Rsync::Rsync(int blocksize) : blocksize_(blocksize) {
}

Rsync::~Rsync() {
}

void Rsync::GenerateDelta(const string& first, const string& second,
                          string* output) {
  char *cfirst;
  size_t fsize;
  FILE* ffirst = open_memstream(&cfirst, &fsize);
  fprintf(ffirst, first.c_str());
  fflush(ffirst);

  char *csig;
  size_t sigsize;
  FILE* fsig = open_memstream(&csig, &sigsize);
  rs_stats_t sigstats;
  rs_result sigresult;
  sigresult = rs_sig_file(ffirst, fsig, block_len, strong_len, &sigstats);

  char *csecond;
  size_t ssize;
  FILE* fsecond = open_memstream(&csecond, &ssize);
  fprintf(fsecond, second.c_str());
  fflush(fsecond);

  char *coutput;
  size_t osize;
  FILE* foutput = open_memstream(&coutput, &osize);

  rs_result       result;
  rs_signature_t  *sumset;
  rs_stats_t      stats;
  result = rs_loadsig_file(fsig, &sumset, &stats);
  if (result != RS_DONE)
    return result;

  if (show_stats)
    rs_log_stats(&stats);

  if ((result = rs_build_hash_table(sumset)) != RS_DONE)
    return result;

  result = rs_delta_file(sumset, new_file, delta_file, &stats);

  rs_free_sumset(sumset);

  delta_file->seek(0);

  char buf[1 << 16];
  size_t len;
  while ((len = fread(buf, 1, sizeof(buf), delta_file)) > 0) {
    if (output)
      output->append(buf, len);
  }

  // rs_file_close(delta_file);
  // rs_file_close(new_file);
  // rs_file_close(sig_file);
}

void Rsync::ApplyDelta(const string& first, const string& delta,
                       string* output) {
}


} // namespace lockbox
