#include "ExtensionsTest.h"
#include "../testResource.h"
#include "TableViewTest/TableViewTestScene.h"

ExtensionsTests::ExtensionsTests()
{
    addTest("TableViewTest", [](){ return new (std::nothrow) TableViewTests; });
}
