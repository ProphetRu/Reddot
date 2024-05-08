#include "TestLogger/TestLogger.h"
#include "TestHashes/TestHashes.h"
#include "TestConfig/TestConfig.h"
#include "TestWebSecurityFilters/TestWebSecurityFilters.h"
#include "TestSessionManager/TestSessionManager.h"
#include "TestWebPageFactory/TestWebPageFactory.h"
#include "TestDBManager/TestDBManager.h"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
