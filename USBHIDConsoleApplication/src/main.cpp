
/**----------------------------------------------------------------------------

    @file       main.cpp
    @defgroup   USBHIDConsoleApplication USB HID Console Application
    @brief      Main entry for the USB tool.

    @copyright  Blackstar Amplification 2023

Notes:


Version:

        0.0.1.0 First Release, development phase. Draft copy


-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <iostream>
#include <stdio.h>
#include <vcruntime_string.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>

// Headers needed for sleeping.
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "../../USBHIDCOnsoleLibrary/inc/Support_Defines.h"
#include "../../USBHIDConsoleLibrary/inc/Modules/USB/USB-HID.h"

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------

using namespace USB_HID;
using namespace Support;

//-----------------------------------------------------------------------------
// Forward References
//-----------------------------------------------------------------------------

void main_CreateMessage( HIDMESSAGE& msg, uint8_t nID, uint8_t nPID, uint8_t nRes, uint8_t nLen, uint8_t* pData );

//-----------------------------------------------------------------------------
// External Functionality
//-----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    USBHIDConsoleApplication USB HID Console Application
    @brief      The main entry point
    @param      argc - The number of command line arguments
    @param      argv - The command line arguments
    @return     int  - The exit code
  --------------------------------------------------------------------------*/
int main( int argc, char* argv[] )
{
    // not currently using the parameters
    NOT_USED( argc );
    NOT_USED( argv );

    // Test section -----------------------------------------------------------
    // Simple test for connecting to the USB device and sending a message
    USBHID     usb; //!< USB HID object
    HIDMESSAGE msg; //!< USB HID message

    // Init and connect to the device
    usb.SetDevice( DEFAULT_VENDOR_ID, DEFAULT_PRODUCT_ID );
    if ( usb.Init() == false )
        std::cout << "Failed to init USB" << std::endl;
    if ( usb.Connect() == false )
        std::cout << "Failed to connect USB" << std::endl;

    // recieve and send HID messages
    if ( usb.IsConnected() )
    {
        std::cout << "Connected to unit [VID: 0x" << std::hex << usb.GetVID() << ",PID: 0x" << usb.GetPID() << "]" << std::dec << std::endl;
        // send the handshake
        main_CreateMessage( msg, 0x81, 0, 0, 3, new byte[ 3 ]{ 0x00, 0x09, 0x04 } );
        usb.Send( msg );

        std::cout << "Sent Handshake..." << std::endl;

        Sleep( 3000 );
        usb.Read( msg );

        std::cout << std::hex << "HID: Received:  0x" << msg.Header.ID << " 0x" << msg.Header.PID << " 0x" << msg.Header.Res << " 0x"
                  << msg.Header.Len << std::dec << std::endl;

        main_CreateMessage( msg, 0x04, 0, 0, 0, nullptr );
        usb.Send( msg );

        std::cout << "Sent switch to firmware updater..." << std::endl;

        Sleep( 3000 );

        std::cout << "Finished, terminating." << std::endl;
    }
    // end test section -------------------------------------------------------

    // Disconnect and deinit the device
    if ( usb.Disconnect() == false )
        std::cout << "Failed to disconnect USB" << std::endl;
    if ( usb.DeInit() == false )
        std::cout << "Failed to deinit USB" << std::endl;

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
// Internal Functionality
//-----------------------------------------------------------------------------
/**---------------------------------------------------------------------------
    @ingroup    USBHIDConsoleApplication USB HID Console Application
    @brief      Creates the HID message structure
    @param      msg   - The destination message
    @param      nID   - The new message ID
    @param      nPID  - The new message PID
    @param      nRes  - The new message response
    @param      nLen  - The new message length
    @param      pData - The new message data
      --------------------------------------------------------------------------*/
void main_CreateMessage( HIDMESSAGE& msg, uint8_t nID, uint8_t nPID, uint8_t nRes, uint8_t nLen, uint8_t* pData )
{
    // completely erase the message structure
    memset( msg.Data, 0, sizeof( msg.Data ) );

    // setup header
    msg.Header.ReportNum = 0x01;
    msg.Header.ID        = nID;
    msg.Header.PID       = nPID;
    msg.Header.Res       = nRes;
    msg.Header.Len       = nLen;

    // if needed, setup the msg data for the HID message
    if ( pData != nullptr )
        memcpy( msg.Msg, pData, nLen );
}
//-----------------------------------------------------------------------------
// End of file: main.cpp
//-----------------------------------------------------------------------------
