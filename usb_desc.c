#include <usb_names.h>

#define MANUFACTURER_NAME    {'L','i','t','r','u','v'}
#define MANUFACTURER_NAME_LEN 6
#define PRODUCT_NAME    {'J','6',' ', 'B', 'i', 'g', 'k', 'n', 'o', 'b'}
#define PRODUCT_NAME_LEN 10

struct usb_string_descriptor_struct usb_string_manufacturer_name = {
        2 + MANUFACTURER_NAME_LEN * 2,
        3,
        MANUFACTURER_NAME
};

struct usb_string_descriptor_struct usb_string_product_name = {
        2 + PRODUCT_NAME_LEN * 2,
        3,
        PRODUCT_NAME
};
