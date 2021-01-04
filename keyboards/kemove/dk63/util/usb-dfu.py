import struct

import hid
import time


def main():
    with hid.Device(0x0c45, 0x766b) as h:
        print(f'Device manufacturer: {h.manufacturer}')
        print(f'Product: {h.product}')
        print(f'Serial Number: {h.serial}')

        data = struct.pack("<II", 0x5A8942AA, 0xCC6271FF)
        print(h.send_feature_report(data))


if __name__ == "__main__":
    main()
