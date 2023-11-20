/**----------------------------------------------------------------------------

    @file       USBHIDMessage.h
    @defgroup   USBHIDConsoleApplication USB HID Console Application
    @brief      USB HID Message definitions for the USB tool.

    @copyright  Blackstar Amplification 2023

Notes:

Version:

        0.0.1.0     First Release, development phase. Draft copy

-----------------------------------------------------------------------------*/

#pragma once

//-----------------------------------------------------------------------------
// Namespace
// ----------------------------------------------------------------------------

namespace USB_HID
{

//-----------------------------------------------------------------------------
// Singleton class USAHIDMessage
// ----------------------------------------------------------------------------

class USBHIDMessage
{
  public:
    // Function to access the singleton instance
    static USBHIDMessage& getInstance()
    {
        static USBHIDMessage instance; // Created only once
        return instance;
    }

    // Other member functions and data members can be added here

  private:
    // Private constructor to prevent direct instantiation
    USBHIDMessage()
    {
    }

    // Private destructor to prevent deletion from outside the class
    ~USBHIDMessage()
    {
    }

    // Private copy constructor and copy assignment operator to prevent cloning
    USBHIDMessage( const USBHIDMessage& )            = delete;
    USBHIDMessage& operator=( const USBHIDMessage& ) = delete;

}; // end class Singleton USBHIDMessage

//-----------------------------------------------------------------------------

} // namespace USB_HID

//-----------------------------------------------------------------------------
// End of file: USBHIDMessage.h
//-----------------------------------------------------------------------------
