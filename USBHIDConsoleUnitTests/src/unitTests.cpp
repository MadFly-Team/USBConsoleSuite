/**----------------------------------------------------------------------------

    @file       unitTests.cpp
    @defgroup   USBHIDConsoleUnitTests Unit Tests for the USB HID Console Library
    @brief      Unit Tests for the USB HID Console Library

    @copyright  Neil Beresford 2023

Notes:

Version:

        0.0.1.0   First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

// doctest unit testing framework setup
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest/doctest/doctest.h"
#include "../../USBHIDConsoleLibrary/inc/Support_Defines.h"
#include "../../USBHIDConsoleLibrary/inc/Modules/USB/USBHIDMessage.h"
#include "../../USBHIDConsoleLibrary/inc/Modules/USB/USB-HID.h"

//-----------------------------------------------------------------------------
// Namespace access
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Unit Tests
//-----------------------------------------------------------------------------

TEST_SUITE( "USB HID Console Library Test Suite" )
{
    //-----------------------------------------------------------------------------
    TEST_CASE( "Testing 1" )
    //-----------------------------------------------------------------------------
    {
        SUBCASE( "Dummy Test" )
        {
            CHECK( 1 != 0 );
            CHECK( 1 == 1 );
        }
    }
    //-----------------------------------------------------------------------------
    //-----------------------------------------------------------------------------
} // TEST_SUITE( "USB HID Console Library Test Suite" )

//-----------------------------------------------------------------------------
// End of file: unitTests.cpp
//-----------------------------------------------------------------------------
