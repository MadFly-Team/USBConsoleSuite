/**----------------------------------------------------------------------------

    @file       Support_Defines.h
    @defgroup   USBHIDConsoleApplication USB HID Console Application
    @brief      Support defines for the USB tool.

    @copyright  Blackstar Amplification 2023

Notes:

Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace Support
{

//-----------------------------------------------------------------------------

#define DEFAULT_VENDOR_ID  ( 0x27D4 ) //!< Vendor ID for the USB device
#define DEFAULT_PRODUCT_ID ( 0xCF )   //!< Product ID for the USB device

#define NOT_USED( x )      ( (void)( x ) ) //!< Macro to remove unused variable warnings

//-----------------------------------------------------------------------------

} // end namespace Support

//-----------------------------------------------------------------------------
// End of file: Support_Defines.h
//-----------------------------------------------------------------------------
