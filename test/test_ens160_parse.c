// tests/test_ens160_parse.c
#include "unity.h"
#include "ens160.h"

int main(void){
  UNITY_BEGIN();
  ens160_raw_t raw = { .eco2_l=0x34, .eco2_h=0x12, .tvoc_l=0x78, .tvoc_h=0x56, .status=0x10 };
  ens160_data_t out;
  TEST_ASSERT_EQUAL_INT(0, ens160_parse(&raw, &out));
  TEST_ASSERT_EQUAL_UINT16(0x1234, out.eco2);
  TEST_ASSERT_EQUAL_UINT16(0x5678, out.tvoc);
  return UNITY_END();
}
