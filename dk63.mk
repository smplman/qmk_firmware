# Upload firware

# Put device into bootloader mode
openocd:
	"openocd.exe" "-c" "gdb_port 50000" "-s" "C:\Users\smplman\projects\qmk_firmware-19" "-f" "../dk63/stlink.cfg" "-f" "../dk63/vs11k09a-1.cfg"
dfu:
	python3 ./util/dk63/dfu.py

# run python script to upload the firmware
upload:
	python3 ./util/dk63/flash-firmware.py ./.build/kmove_dk63_default.bin --vid 0x0c45 --pid 0x7040
