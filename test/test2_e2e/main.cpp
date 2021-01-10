#include "tst_e2e.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    QApplication a(argc, nullptr);

    return RUN_ALL_TESTS();
}
