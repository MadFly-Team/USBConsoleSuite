/**----------------------------------------------------------------------------

    @file       USB-HID.h
    @defgroup   USBHIDConsoleApplication USB HID Console USBHIDConsoleApplication
    @brief      USB HID Console Functionality

    @copyright  Blackstar Amplification 2023

Notes:
        See the source file for more information

Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <cinttypes>

// HIDAPI includes
#include "../../hidapi.h"

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------

namespace USB_HID
{

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#define HIDMSGHEADERLEN ( 5 )
#define HIDMSGDATALEN   ( 60 )
#define HIDMSGLEN       ( HIDMSGHEADERLEN + HIDMSGDATALEN )

//-----------------------------------------------------------------------------
// Class definitions
//-----------------------------------------------------------------------------

union HIDMESSHEADER
{
    struct
    {
        uint8_t ReportNum; //!< Internal use, will be overwritten
        uint8_t ID;        //!< Message IsConnected
        uint8_t PID;       //!< Product
        uint8_t Res;       //!< Reserved
        uint8_t Len;       //!< Length
    };

    uint8_t Data[ HIDMSGHEADERLEN ];
};

union HIDMESSAGE
{
    struct
    {
        HIDMESSHEADER Header;               //!< Header structure
        uint8_t       Msg[ HIDMSGDATALEN ]; //!< HID message buffer
    };

    uint8_t Data[ HIDMSGLEN ]; //!< Raw HID Data
};

/**---------------------------------------------------------------------------
    @ingroup    USBHIDConsoleApplication USB HID Console Application
    @brief      MAin USB Console class
  --------------------------------------------------------------------------*/
class USBHID
{

  private:
    enum
    {
        eHIDRead_Blocking = 0, //!< 0 - hid_set_nonblocking parameter
        eHIDRead_NonBlocking,  //!< 1 - hid_set_nonblocking parameter
    };

  private:
    // Data
    bool        mIsInitialized; //!< true if initialized
    bool        mIsConnected;   //!< true if connected
    uint32_t    mPID;           //!< Product ID
    uint32_t    mVID;           //!< Vendor ID
    hid_device* mHandle;        //!< HIDAPI Handle for the USB device

  public:
    // constructors etc
    /**---------------------------------------------------------------------------
        @ingroup    USBHIDConsoleApplication USB HID Console Application
        @brief      Basic Constructor
      --------------------------------------------------------------------------*/
    USBHID()
    {
        // initialize the private variables
        mIsInitialized = false;
        mIsConnected   = false;
        mPID           = 0;
        mVID           = 0;
        mHandle        = nullptr;
    }
    /**---------------------------------------------------------------------------
        @ingroup    USBHIDConsoleApplication USB HID Console Application
        @brief      Basic destructor
      --------------------------------------------------------------------------*/
    ~USBHID()
    {
    }

    // Getters and setters
    /**---------------------------------------------------------------------------
        @ingroup    USBHIDConsoleApplication USB HID Console Application
        @brief      Set the Product ID
        @param      pid - the new Product ID
      --------------------------------------------------------------------------*/
    void SetPID( uint32_t pid )
    {
        mPID = pid;
    }
    /**---------------------------------------------------------------------------
        @ingroup    USBHIDConsoleApplication USB HID Console Application
        @brief      Set the Vendor ID
        @param      vid - the new Vendor ID
      --------------------------------------------------------------------------*/
    void SetVID( uint32_t vid )
    {
        mVID = vid;
    }
    /**---------------------------------------------------------------------------
        @ingroup    USBHIDConsoleApplication USB HID Console Application
        @brief      returns the Product ID
        @return     pid - the product ID
      --------------------------------------------------------------------------*/
    uint32_t GetPID()
    {
        return mPID;
    }
    /**---------------------------------------------------------------------------
        @ingroup    USBHIDConsoleApplication USB HID Console Application
        @brief      returns the vender ID
        @return     vid - the new venor ID
      --------------------------------------------------------------------------*/
    uint32_t GetVID()
    {
        return mVID;
    }

    /**---------------------------------------------------------------------------
        @ingroup    USBHIDConsoleApplication USB HID Console Application
        @brief      Returns if the USBHID is initialized
        @return     bool - true if initialized
      --------------------------------------------------------------------------*/
    bool IsInitialized()
    {
        return mIsInitialized;
    }
    /**---------------------------------------------------------------------------
        @ingroup    USBHIDConsoleApplication USB HID Console Application
        @brief      Returns if the USBHID is connected to the device
        @return     bool - true if connected
      --------------------------------------------------------------------------*/
    bool IsConnected()
    {
        return mIsConnected;
    }
    /**---------------------------------------------------------------------------
        @ingroup    USBHIDConsoleApplication USB HID Console Application
        @brief      Sets the Device VID and PID
        @param      vid - the vendor ID
        @param      pid - the product ID
      --------------------------------------------------------------------------*/
    void SetDevice( uint32_t vid, uint32_t pid )
    {
        mVID = vid;
        mPID = pid;
    }

    // Core Functionality
    bool Init();
    bool DeInit();
    bool Connect();
    bool Disconnect();

    bool Send( const HIDMESSAGE& msg );
    bool Read( HIDMESSAGE& msg );
    bool Poll( HIDMESSAGE& msg );
};

//-----------------------------------------------------------------------------

} // namespace USB_HID

//-----------------------------------------------------------------------------
// End of file: USB-HID.h
//-----------------------------------------------------------------------------
