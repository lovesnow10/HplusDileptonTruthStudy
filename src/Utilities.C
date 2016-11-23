#include "Utilities.h"
#include <regex>

TFile *OpenFile(const char *FileName) {
  TFile *fFile = NULL;
  fFile = TFile::Open(FileName, "READONLY");

  if (!fFile->IsZombie()) {
    return fFile;
  } else {
    std::cout << "WARNING: Cannot find file " << FileName << ", please check. ";
    std::cout << "Return nullptr..." << std::endl;
    return NULL;
  }
}

TFile *CreateNewFile(const char *FileName) {
  std::cout << "WARNING: You are creating new file, will overwrite exist file "
               "with the same name"
            << std::endl;
  return new TFile(FileName, "RECREATE");
}

TTree *GetTTree(const char *fTreeName, TFile *fFile) {
  TTree *fTree = NULL;
  TKey *fKey = fFile->FindKey(fTreeName);
  if (fKey != nullptr) {
    fTree = (TTree *)fKey->ReadObj();
  } else {
    std::cout << "WARNING: Cannot find TTree with name " << fTreeName
              << ", please check. ";
    std::cout << "Return nullptr..." << std::endl;
  }
  return fTree;
}

std::string GenerateTimeSuffix() {
  time_t timenow;
  timenow = time(NULL);
  struct tm *local = localtime(&timenow);
  char *buf = new char;
  strftime(buf, 80, "%Y%m%d_%H%M", local);
  return std::string(buf);
}

std::string GetNameSuffix(const char *fInputName) {
  std::string path = fInputName;
  const std::regex pattern(".*\\/(.*)\\.root");
  std::match_results<std::string::const_iterator> result;
  bool valid = std::regex_match(path, result, pattern);
  std::string res = "";
  if (valid) {
    res = result[1];
  }
  return res;
}

std::vector<std::vector<int>> GetCombinations(int n, int r)
{
  std::vector<std::vector<int>> mCombinations;
  mCombinations.clear();

  std::vector<bool> v(n);
  std::fill(v.begin(), v.begin() + r, true);

  std::vector<int> tmp;
  tmp.clear();
  do {
    for (int i = 0; i < n; ++i)
    {
      if(v[i]) tmp.push_back(i);
    }
    mCombinations.push_back(tmp);
    tmp.clear();
  } while(std::prev_permutation(v.begin(), v.end()));
  return mCombinations;
}

std::vector<std::vector<int>> GetPermutations(int n, int r)
{
  std::vector<std::vector<int>> mPermutations;
  mPermutations.clear();

  std::vector<std::vector<int>> mCombinations = GetCombinations(n, r);
  for (auto comb : mCombinations)
  {
    std::sort(comb.begin(), comb.end());
    do {
      mPermutations.push_back(comb);
    } while(std::next_permutation(comb.begin(), comb.end()));
  }
  return mPermutations;
}
