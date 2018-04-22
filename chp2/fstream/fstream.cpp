#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <bitset>
#include <fstream>

class GTest : public ::testing::Test {

protected:
  virtual void SetUp(){
  }
  
  virtual void TearDown(){
  }
};

TEST_F(GTest, GetLine_GTest) {
  std::ifstream in = std::ifstream("fstream.cpp");
  std::ofstream out = std::ofstream("fstream.copy.cpp");
  std::string s;
  std::cout << "copy file line by line" << std::endl;
  while (getline(in, s)) {
    s += "\n";
    std::cout << s ;
    out << s ;
  }
}

TEST_F(GTest, Word_GTest) {
  std::ifstream in = std::ifstream("fstream.cpp");
  std::ofstream out = std::ofstream("fstream.copy_word.cpp");
  std::string s;
  std::cout << "copy file line by line" << std::endl;
  std::vector<std::string> words;
  while (in >> s) {
    words.push_back(s);
  }
  std::cout << words.size() << " words in the file." << std::endl;
}

TEST_F(GTest, ReadFileLineByLine_GTest) {
  std::ifstream in = std::ifstream("fstream.cpp");
  std::string s;
  int a = 0;
  int &b = a;
  std::cout << a++ << std::endl;
  std::cout << &a << std::endl;
  std::cout << b << std::endl;
  std::cout << &b << std::endl;
  while (getline(in, s)) {
    std::cout << s <<std::endl;
    std::string input;
    std::cin >> input;
  }
  std::cout << 1e2 << std::endl;
}

void print_hex(const unsigned char &val) {
  std::bitset<8> bits = val;
  std::cout << bits.to_string() << std::endl;
}
int main(int argc, char *argv[])
{
  std::cout << "hex format of 3.14159" << std::endl;
  double d_num = atof("3.14159");
  unsigned char *uc_ptr = reinterpret_cast<unsigned char *>(&d_num);
  for(int i=sizeof(d_num)-1; i>0; i-=2) {
    print_hex(*(uc_ptr+i));
    print_hex(*(uc_ptr+i-1));
  }
  std::cout << std::endl;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
