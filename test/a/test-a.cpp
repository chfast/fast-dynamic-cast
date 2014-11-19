
#include "a.h"

#include <chf/type_info.hpp>
#include <test/helper.hpp>

#include <stdexcept>
#include <string>

namespace fdctest {
namespace a {

void test_gen();

void test()
{
	#define TEST(OBJECT, CLASS) chf::test::test_isa<OBJECT, CLASS>()

	test_gen();

	chf::test::test_classes<A0, B0, B2>();

	TEST(Root, Root);   // TODO: Create template test generation 

	TEST(A0, Root);
	TEST(A1, Root);
	TEST(A2, Root);
	TEST(A3, Root);
	TEST(A4, Root);

	TEST(B0, Root);
	TEST(B1, Root);
	TEST(B2, Root);
	TEST(B3, Root);
	TEST(B4, Root);

	TEST(C0, Root);
	TEST(C1, Root);
	TEST(C2, Root);
	TEST(C3, Root);
	TEST(C4, Root);

	TEST(D0, Root);
	TEST(D1, Root);
	TEST(D2, Root);
    TEST(D3, Root);
    TEST(D4, Root);

	TEST(A0, A0);
	TEST(A1, A0);
	TEST(A2, A0);
	TEST(A3, A0);
	TEST(A4, A0);

	TEST(B0, A0);
	TEST(B1, A0);
	TEST(B2, A0);
	TEST(B3, A0);
	TEST(B4, A0);

	TEST(C0, A0);
	TEST(C1, A0);
	TEST(C2, A0);
	TEST(C3, A0);
	TEST(C4, A0);

	TEST(D0, B0);
	TEST(D1, B0);
	TEST(D2, B0);
	TEST(D3, B0);
	
	TEST(A0, B0);
	TEST(A1, B0);
	TEST(A2, B0);
	TEST(A3, B0);
	TEST(A4, B0);

	TEST(B0, B0);
	TEST(B1, B0);
	TEST(B2, B0);
	TEST(B3, B0);
	TEST(B4, B0);

	TEST(C0, B0);
	TEST(C1, B0);
	TEST(C2, B0);
	TEST(C3, B0);
	TEST(C4, B0);

	TEST(D0, B0);
	TEST(D1, B0);
	TEST(D2, B0);
	TEST(D3, B0);

	TEST(A0, C0);
	TEST(A1, C0);
	TEST(A2, C0);
	TEST(A3, C0);
	TEST(A4, C0);

	TEST(B0, C0);
	TEST(B1, C0);
	TEST(B2, C0);
	TEST(B3, C0);
	TEST(B4, C0);

	TEST(C0, C0);
	TEST(C1, C0);
	TEST(C2, C0);
	TEST(C3, C0);
	TEST(C4, C0);

	TEST(D0, C0);
	TEST(D1, C0);
	TEST(D2, C0);
	TEST(D3, C0);

	TEST(A0, D0);
	TEST(A1, D0);
	TEST(A2, D0);
	TEST(A3, D0);
	TEST(A4, D0);

	TEST(B0, D0);
	TEST(B1, D0);
	TEST(B2, D0);
	TEST(B3, D0);
	TEST(B4, D0);

	TEST(C0, D0);
	TEST(C1, D0);
	TEST(C2, D0);
	TEST(C3, D0);
	TEST(C4, D0);

	TEST(D0, D0);
	TEST(D1, D0);
	TEST(D2, D0);
    TEST(D3, D0);
    TEST(D4, D0);
}


}}