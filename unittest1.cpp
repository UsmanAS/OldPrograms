#include "stdafx.h"
#include "CppUnitTest.h"
#include "myvector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace myvectorUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		

		TEST_METHOD(usiddi4_Test1)
		{
			myvector<int> V(10);

			V.push_back(1);
			V.push_back(2);
			V.push_back(3);
			
			Assert::IsTrue(V[0] == 1);
			Assert::IsTrue(V[1] == 2);
			Assert::IsTrue(V[2] == 3);
		}

		TEST_METHOD(usiddi4_Test2)
		{
			myvector<int> V(10);
			Assert::IsTrue(V.capacity() == 10);

			V.push_back(4);
			Assert::IsTrue(V.capacity() == 10);


		}

		TEST_METHOD(usiddi4_Test3)
		{
			myvector<int> V1(5);
			Assert::IsTrue(V1.capacity() == 5);
		}

		TEST_METHOD(usiddi4_Test4)
		{
			myvector<int> V(10);

			V.push_back(1);
			Assert::IsTrue(V.front() == 1);

			V.push_back(2);
			Assert::IsTrue(V.back() == 2);

			V.push_back(3);

			Assert::IsTrue(V.front() == 1);
			Assert::IsTrue(V.back() == 3);

		}

		TEST_METHOD(usiddi4_Test5)
		{
			myvector<int> V(5);
			V.push_back(2);
			V.push_back(3);
			V.push_back(4);
			Assert::IsTrue(V.size() == 3);
			Assert::IsTrue(V.capacity() == 5);
		}

		TEST_METHOD(usiddi4_Test6)
		{
			myvector<int> V(3);
			V.push_back(1);
			Assert::IsTrue(V.size() == 1);
			V.push_back(1);
			Assert::IsTrue(V.size() == 2);
			V.push_back(1);
			Assert::IsTrue(V.size() == 3);
		}

		TEST_METHOD(usiddi4_Test7)
		{
			myvector<int> V;
			Assert::IsTrue(V.capacity() == 100);
		}

		TEST_METHOD(usiddi4_Test8)
		{
			myvector<int> V(10);
			V.push_back(0);
			Assert::IsTrue(V[0] == 0);
			Assert::IsTrue(V.size() == 1);
		}

		TEST_METHOD(usiddi4_Test9)
		{
			myvector<double> V(10);
			V.push_back(3.2);
			Assert::IsTrue(V[0] == 3.2);
			V.push_back(4.41);
			Assert::IsTrue(V[1] == 4.41);

		}

		TEST_METHOD(usiddi4_Test10)
		{
			myvector<string> V(10);
			V.push_back("Hello");
			Assert::IsTrue(V[0] == "Hello");
			V.push_back("Hi");
			Assert::IsTrue(V[1] == "Hi");
		}
	};
}