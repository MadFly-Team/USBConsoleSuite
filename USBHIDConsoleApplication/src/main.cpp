#include <iostream>
#include <hidapi/hidapi.h>

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"

using namespace std;

uint32_t Test1(void);

int main()
{

    Test1();	

    // Initialize the HIDAPI library
    if (hid_init() != 0) {
        std::cerr << "HIDAPI initialization failed." << std::endl;
        return 1;
    }

    // Open the USB HID device (change VID and PID based on your device)
    hid_device* handle = hid_open(0x1234, 0x5678, nullptr);

    if (handle == nullptr) {
        std::cerr << "Failed to open HID device." << std::endl;
        hid_exit();
        return 1;
    }

    // Read data from the HID device
    unsigned char buffer[64];
    int bytesRead = hid_read(handle, buffer, sizeof(buffer));

    if (bytesRead < 0) {
        std::cerr << "Error reading from HID device." << std::endl;
    } else {
        std::cout << "Read " << bytesRead << " bytes: ";
        for (int i = 0; i < bytesRead; ++i) {
            std::cout << static_cast<int>(buffer[i]) << " ";
        }
        std::cout << std::endl;
    }

    // Close the HID device
    hid_close(handle);

    // Finalize the HIDAPI library
    hid_exit();

    return 0;
}


uint32_t Test1(void)
{
    uint8_t VerStringBuffer[ 256 ];
    uint8_t key;

	if (CABRIGLIB_Version_GetString( VerStringBuffer ) == eCABRIGERROR_NoErr )
	{
		printf( "Version of library  - %s\r\n", VerStringBuffer );
	}
	else
	{
		printf( "Library failed.\r\n" );
	}

    using namespace ftxui;

    auto summary = [&] {
        auto content = vbox({
            hbox({text(L"- done:   "), text(L"3") | bold}) | color(Color::Green),
            hbox({text(L"- active: "), text(L"2") | bold}) | color(Color::RedLight),
            hbox({text(L"- queue:  "), text(L"9") | bold}) | color(Color::Red),
            });
        return window(text(L" Summary "), content);
    };

    auto document =  //
        vbox({
            hbox({
                summary(),
                summary(),
                summary() | flex,
            }),
            hbox({
                summary(),
                summary(),
                summary() | flex,
            }),
            summary(),
            summary(),
            });

    // Limit the size of the document to 80 char.
    document = document | size(WIDTH, LESS_THAN, 80);

    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
    Render(screen, document);

    std::cout << screen.ToString() << '\0' << std::endl;

    string input;
    cin >> input;

    screen.ResetPosition();
    screen.Clear();
    std::cout << screen.ToString() << '\0' << std::endl;

    auto c = Canvas(100, 90);

    c.DrawText(20, 1, "This is a canvas", [](Pixel& p) {
        p.foreground_color = Color::Black;
        p.background_color = Color::White;
        p.underlined = true;
        p.inverted = true;
        });

    // Triangle:
    c.DrawPointLine(10, 10, 80, 10, Color::Red);
    c.DrawPointLine(80, 10, 80, 40, Color::Blue);
    c.DrawPointLine(80, 40, 10, 10, Color::Green);

    // Circle, not filled and filled:
    c.DrawPointCircle(30, 50, 20);
    c.DrawPointCircleFilled(40, 40, 10);

    // Plot a function:
    std::vector<int> ys(100);
    for (int x = 0; x < 100; x++)
        ys[x] = int(60 + 20 * cos(x * 0.2));
    for (int x = 0; x < 99; x++)   
        c.DrawPointLine(x, ys[x], x + 1, ys[x + 1], Color::Red);

    document = canvas(&c) | border;

    screen = Screen::Create(Dimension::Fit(document));
    Render(screen, document);
    screen.Print();
    getchar();

    return EXIT_SUCCESS;
}

uint32_t TestMe()
{
    cout << "HELLO!" << endl;
    return(2);
}