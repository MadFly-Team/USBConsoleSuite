
/**----------------------------------------------------------------------------

    @file 		main.cpp
    @defgroup   USBHIDConsoleApplication USB HID Console Application
    @brief      Main entry for the USB tool.

    @copyright	Blackstar Amplification 2023

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

// HIDAPI includes
#include "../inc/hidapi.h"

// Headers needed for sleeping.
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "../inc/USB-HID.h"

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#define DEFAULT_VENDOR_ID  ( 0x27D4 )
#define DEFAULT_PRODUCT_ID ( 0xCF )

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------

using namespace USB_HID;

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
  --------------------------------------------------------------------------*/
int main( int argc, char* argv[] )
{
    // not using the parameters
    (void)argc;
    (void)argv;

    USBHID     usb;
    HIDMESSAGE msg;

    // Init and connect to the device
    usb.SetDevice( DEFAULT_VENDOR_ID, DEFAULT_PRODUCT_ID );
    if ( usb.Init() == false )
        std::cout << "Failed to init USB" << std::endl;
    if ( usb.Connect() == false )
        std::cout << "Failed to connect USB" << std::endl;

    // recieve and send HID messages
    // Test section...
    if ( usb.IsConnected() )
    {
        std::cout << "Connected to unit [VID: " << usb.GetVID() << ",PID: " << usb.GetPID()
                  << "]" << std::endl;
        // send the handshake
        main_CreateMessage( msg, 0x81, 0, 0, 3, new byte[ 3 ]{ 0x00, 0x09, 0x04 } );
        usb.Send( msg );

        std::cout << "Sent Handshake..." << std::endl;

        Sleep( 3000 );
        usb.Read( msg );

        std::cout << "HID: Received: " << msg.Header.ID << " " << msg.Header.PID << " " << msg.Header.Res << " " << msg.Header.Len
                  << std::endl;

        main_CreateMessage( msg, 0x04, 0, 0, 0, nullptr );
        usb.Send( msg );

        std::cout << "Sent switch to firmware updater..." << std::endl;

        Sleep( 3000 );

        std::cout << "Finished, terminating." << std::endl;
    }

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
