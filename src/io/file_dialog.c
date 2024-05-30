#include "file_dialog.h"

#include "../../libs/tinyfiledialogs/tinyfiledialogs.h"

const char* file_dialog_pick() {
  char const* lFilterPatterns[2] = {
      "*.nes",
  };

  return tinyfd_openFileDialog("Select ROM file", "../", 1, lFilterPatterns,
                               ".NES file", 0);
}