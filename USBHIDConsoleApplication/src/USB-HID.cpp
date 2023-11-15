/**----------------------------------------------------------------------------

    @file       USB-HID.cpp
    @defgroup   USBHIDConsoleApplication USB HID Console USBHIDConsoleApplication
    @brief      USB HID Console Functionality

    @copyright  Blackstar Amplification 2023

Notes:

    USBHID class is a wrapper for the HIDAPI library. This library is used
    as it's cross platform and can be used for Windows, Linux, and OSX.
    The internal HID read function is non blocking, Poll() is to be used
    and its results are returned as and when. For blocking reads, use Read().

    HID messages within tyhis implementation are one byte bigger as they
    contain a status or report byte at the start. This is set internally,
    and should be ignored. Please be aware of this when setting the data
    of the

    USBHID is simplied, with the following functionality grouped -

    USB Connection, disconnection etc.

    USBHID::Init()          - Initializes the device
    USBHID::Connect()       - Connects to the device, setting reads to non-blocking
    USBHID::Disconnect()    - Disconnects from the device
    USBHID::DeInit()        - Uninitializes the device

    USB HID Message handling

    USBHID::Read()          - Reads from the device
    USBHID::Send()          - Sends to the device
    USBHID::Poll()          - Polls the device, returns HID Msg when recieved.

    Misc and getters and setters.

    USBHID::SetDevice()     - Sets the VID and PID for the device to connect to.
    USBHID::GetVID()        - returns the VID
    USBHID::GetPID()        - returns the PID
    USBHID::SetVID()        - sets the VID
    USBHID::SetPID()        - sets the PID
    USBHID::IsInitialized   - Checks if the device is initialized
    USBHID::IsConnected     - Checks if the device is connected


Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include "../inc/USB-HID.h"

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------

namespace USB_HID
{

//-----------------------------------------------------------------------------
// Class
//-----------------------------------------------------------------------------

/**---------------------------------------------------------------------------
    @ingroup    USBHIDConsoleApplication USB HID Console Application
    @brief      Initializes the device
    @return     bool - true if successful
  --------------------------------------------------------------------------*/
bool USBHID::Init()
{
    bool bRet = false;

    if ( mIsInitialized == false )
    {
        if ( hid_init() == false )
        {
            mIsInitialized = true;
            bRet           = true;
        }
    }

    return bRet;
}

/**---------------------------------------------------------------------------
    @ingroup    USBHIDConsoleApplication USB HID Console Application
    @brief      Connects to the device, setting reads to non-blocking
    @return     bool - true if successful
  --------------------------------------------------------------------------*/
bool USBHID::Connect()
{
    bool bRet = false;

    if ( mIsInitialized == true && mIsConnected == false )
    {
        // Open the USB HID device (change VID and PID based on your device)
        mHandle = hid_open( mVID, mPID, nullptr );

        if ( mHandle != nullptr )
        {
            hid_set_nonblocking( mHandle, eHIDRead_NonBlocking );
            mIsConnected = true;
            bRet         = true;
        }
    }

    return bRet;
}

/**---------------------------------------------------------------------------
    @ingroup    USBHIDConsoleApplication USB HID Console Application
    @brief      Uninitializes the device, freeing up resources
    @return     bool - true if successful
  --------------------------------------------------------------------------*/
bool USBHID::DeInit()
{
    bool bRet = false;

    if ( mIsInitialized == true )
    {
        hid_exit();
        mIsInitialized = false;
        bRet           = true;
    }

    return bRet;
}

/**---------------------------------------------------------------------------
    @ingroup    USBHIDConsoleApplication USB HID Console Application
    @brief      Disonnects the device
    @return     bool - true if successful
  --------------------------------------------------------------------------*/
bool USBHID::Disconnect()
{
    bool bRet = false;

    if ( mIsInitialized == true && mIsConnected == true )
    {
        hid_close( mHandle );
        mHandle      = nullptr;
        mIsConnected = false;
        bRet         = true;
    }

    return bRet;
}

/**---------------------------------------------------------------------------
    @ingroup    USBHIDConsoleApplication USB HID Console Application
    @brief      Sends a HID message
    @param      msg - The HID message
    @return     bool - true if successful
  --------------------------------------------------------------------------*/
bool USBHID::Send( const HIDMESSAGE& msg )
{
    bool bRet = false;
    if ( mIsInitialized == true && mIsConnected == true )
    {
        bRet = hid_write( mHandle, msg.Data, sizeof( HIDMESSAGE ) ) == 0;
    }

    return bRet;
}

/**---------------------------------------------------------------------------
    @ingroup    USBHIDConsoleApplication USB HID Console Application
    @brief      Reads a HID message, blocking
    @param      msg - The HID message
    @return     bool - true if successful
  --------------------------------------------------------------------------*/
bool USBHID::Read( HIDMESSAGE& msg )
{
    bool bRet = false;

    if ( mIsInitialized == true && mIsConnected == true )
    {
        hid_set_nonblocking( mHandle, eHIDRead_Blocking );
        if ( hid_read( mHandle, msg.Data, sizeof( HIDMESSAGE ) ) == sizeof( HIDMESSAGE ) )
        {
            bRet = true;
        }
        hid_set_nonblocking( mHandle, eHIDRead_NonBlocking );
    }

    return bRet;
}

/**---------------------------------------------------------------------------
    @ingroup    USBHIDConsoleApplication USB HID Console Application
    @brief      Polls checking for a recieved HID message
    @param      msg - The HID message, set if returned true
    @return     bool - true if  message was recieved
  --------------------------------------------------------------------------*/
bool USBHID::Poll( HIDMESSAGE& msg )
{
    bool bRet = false;

    if ( mIsInitialized == true && mIsConnected == true )
    {
        if ( hid_read( mHandle, msg.Data, sizeof( HIDMESSAGE ) ) == sizeof( HIDMESSAGE ) )
        {
            bRet = true;
        };
    }

    return bRet;
}

//-----------------------------------------------------------------------------

} // namespace USB_HID

//-----------------------------------------------------------------------------
// End of file: USB-HID.cpp
//-----------------------------------------------------------------------------
