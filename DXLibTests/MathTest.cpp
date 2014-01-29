#include "stdafx.h"
#include "CppUnitTest.h"

#include <DXMath.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DXLibTests
{		
	TEST_CLASS(MathTest)
	{
	public:
		
		TEST_METHOD(Conversions)
		{
			// TODO: Your test code here
            dx::Radians rad1(dx::Pi);
            dx::Degrees deg = dx::ToDegrees(rad1);
            
            Assert::AreEqual(180.0f, (float)deg, FLT_EPSILON);
            deg = dx::Degrees(180.0f);
            Assert::AreEqual(dx::Pi, dx::ToRadians(deg), FLT_EPSILON);

            rad1 = dx::Radians(dx::PiOver2);
            Assert::AreEqual(90.0f, (float)dx::ToDegrees(rad1), FLT_EPSILON);
		}

        TEST_METHOD(Comparing) {
            dx::Radians rad(dx::Pi);

            Assert::IsTrue(rad == dx::Pi);
            Assert::IsTrue(dx::Pi == rad);

            Assert::IsTrue(rad != 1.0f);
            Assert::IsTrue(1.0f != rad);

            Assert::IsTrue(!dx::InRange(1.0f + FLT_EPSILON, 1.0f, FLT_EPSILON));
            Assert::IsTrue(dx::InRange(1.0f + FLT_EPSILON, 1.0f, FLT_EPSILON + 0.0001f));

            Assert::IsTrue(dx::FloatEquals(rad, dx::Pi));
            Assert::IsTrue(!dx::FloatEquals(rad, 1.0f));
        }

        TEST_METHOD(Arithmetic) {
            dx::Radians rad(dx::Pi);
            
            Assert::AreEqual(dx::TwoPi, rad * 2.0f, FLT_EPSILON);
            Assert::AreEqual(dx::Pi, rad * 1.0f, FLT_EPSILON);

            Assert::AreEqual(dx::PiOver2, rad / 2.0f, FLT_EPSILON);
            Assert::AreEqual(dx::PiOver2, rad * 0.5f, FLT_EPSILON);

            Assert::AreEqual(dx::TwoPi, rad + dx::Pi, FLT_EPSILON);

            dx::Degrees deg(dx::Pi);
            
            Assert::AreEqual(dx::TwoPi, deg * 2.0f, FLT_EPSILON);
            Assert::AreEqual(dx::Pi, deg * 1.0f, FLT_EPSILON);

            Assert::AreEqual(dx::PiOver2, deg / 2.0f, FLT_EPSILON);
            Assert::AreEqual(dx::PiOver2, deg * 0.5f, FLT_EPSILON);

            Assert::AreEqual(dx::TwoPi, deg + dx::Pi, FLT_EPSILON);
        }
	};
}
