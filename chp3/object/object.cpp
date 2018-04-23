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


class A{
  int a;
};

class B{
  B() {
    std::cout << "B" <<std::endl;
  }
  void Greeting() {
    std::cout << "Hello" <<std::endl;
  }
};

class C:public A{
  C() {
    std::cout << "C" <<std::endl;
  }
  void Greeting() {
    std::cout << "Hello" << std::endl;
  }
};

struct Stash {
  Stash(unsigned elem_size, unsigned elem_max_cnt):\
    elem_max_cnt_(elem_max_cnt), \
    elem_size_(elem_size), \
    next_(0), \
    data_(nullptr){
    data_ = new unsigned char[elem_size*elem_max_cnt];
  }

  int Add(void *elem){
    if(next_== elem_max_cnt_) {
      std::cout << "Add elem out of index" << std::endl;
      return -1;
    }
    unsigned char *ptr = data_ + next_*elem_size_;
    memcpy((void*)ptr, elem, elem_size_);
    ++next_;
    return next_-1;
  }

  void *Fetch(unsigned index) {
    if(index >= next_) {
      std::cout << "Fetch elem out of range" << std::endl;
      return nullptr;
    }
    unsigned char *ptr = data_ + index*elem_size_;
    return (void*)ptr;
  }

  bool Inflate(unsigned size) {
    if(size < elem_max_cnt_) {
      return false;
    }
    unsigned char *data_tmp = new unsigned char[size*elem_size_];
    memcpy((void*)data_tmp, data_, next_*elem_size_);
    delete data_;
    data_ = data_tmp;
    return true;
  }

  void Cleanup() {
    delete data_;
    data_ = nullptr;
    elem_size_= 0;
    elem_max_cnt_ = 0;
    next_ = 0;
  }

  unsigned Count() {
    return next_;
  }

  unsigned elem_max_cnt_;
  unsigned elem_size_;
  unsigned next_;
  unsigned char *data_;
};

struct Link {
  unsigned char *data_;
  Link *next_;
  Link(void *data) {
    data_ = new unsigned char[mem_size_];
    memcpy(data_, data, mem_size_);
    // std::cout <<"Push :" <<  *(double*)data_ << std::endl;
  }
  ~Link() {
    delete data_;
    data_ = nullptr;
  }

  static void Preset(unsigned size) {
    mem_size_ = size;
  }
  static unsigned mem_size_;
};
unsigned Link::mem_size_ = 0;

struct Stack {

  Stack(unsigned mem_size):mem_size_(mem_size), head_(nullptr) {
    Link::Preset(mem_size_);
  }

  void Push(void *data) {
    Link *tmp = head_;
    Link *node = new Link(data);
    if(tmp) {
      node->next_ = head_;
      head_ = node;
    } else {
      head_ = node;
    }
  }

  void *Peek() {
    if(head_) {
      return (void*)(head_->data_);
    }
    return nullptr;
  }

  void Pop() {
    if(head_) {
      Link *tmp = head_;
      head_ = head_->next_;
      delete tmp;
    }
  }

  unsigned mem_size_;
  Link *head_;
};

TEST_F(GTest, Objec_GTest) {
  std::cout << sizeof(A) << std::endl;
  std::cout << sizeof(B) << std::endl;
  std::cout << sizeof(C) << std::endl;
}

TEST_F(GTest, Stash_GTest) {

  Stash stash_int(sizeof(int), 10);
  Stash stash_double(sizeof(double), 10);
  for(int i=0; i<10; i++) {
    stash_int.Add((void*)&i);
  }

  for(double d=0; d<20.0; d+=2.0) {
    stash_double.Add(&d);
  }

  int val = *(int*)stash_int.Fetch(5);
  EXPECT_EQ(val, 5);

  double dval = *(double*)stash_double.Fetch(5);
  EXPECT_EQ(dval, 10.0);

  stash_int.Inflate(20);
  val = *(int*)stash_int.Fetch(5);
  EXPECT_EQ(val, 5);

  stash_double.Inflate(20);
  dval = *(double*)stash_double.Fetch(5);
  EXPECT_EQ(dval, 10.0);

}

TEST_F(GTest, Stack_GTest) {

  Stack stack_int(sizeof(int));
  Stack stack_double(sizeof(double));
  for(int i=0; i<10; i++) {
    stack_int.Push((void*)&i);
  }

  for(double d=0; d<20.0; d+=2.0) {
    stack_double.Push(&d);
  }

  for(int i=0; i<10; i++) {
    int val = *(int*)stack_int.Peek();
    stack_int.Pop();
    EXPECT_EQ(val, 9-i);
  }

  for(int d=0; d<20.0; d+=2.0) {
    double val = *(double*)stack_double.Peek();
    stack_double.Pop();
    EXPECT_EQ(val, 18.0-d);
  }
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
