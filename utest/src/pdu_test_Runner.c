/* AUTOGENERATED FILE. DO NOT EDIT. */

//=======Test Runner Used To Run Each Test Below=====
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  if (TEST_PROTECT()) \
  { \
      setUp(); \
      TestFunc(); \
  } \
  if (TEST_PROTECT() && !TEST_IS_IGNORED) \
  { \
    tearDown(); \
  } \
  UnityConcludeTest(); \
}

//=======Automagically Detected Files To Include=====
#include "unity.h"
#include <setjmp.h>
#include <stdio.h>

//=======External Functions This Runner Calls=====
extern void setUp(void);
extern void tearDown(void);
extern void test_ReadCoil();
extern void test_ReadCoilsER();
extern void test_ReadHold();
extern void test_ReadHoldER();
extern void test_WriteHold();


//=======Test Reset Option=====
void resetTest()
{
  tearDown();
  setUp();
}


//=======MAIN=====
int main(void)
{
  Unity.TestFile = "C:\Work\ModBus\utest\src\pdu_test.c";
  UnityBegin();
  RUN_TEST(test_ReadCoil, 36);
  RUN_TEST(test_ReadCoilsER, 50);
  RUN_TEST(test_ReadHold, 81);
  RUN_TEST(test_ReadHoldER, 111);
  RUN_TEST(test_WriteHold, 131);

  return (UnityEnd());
}
