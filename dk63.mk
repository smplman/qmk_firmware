# Upload firware

# Put device into bootloader mode
openocd:
	"openocd.exe" "-c" "gdb_port 3333" "-s" "C:\Users\smplman\projects\qmk_firmware-19" "-f" "C:\Users\smplman\projects\dk63\stlink.cfg" "-f" "C:\Users\smplman\projects\dk63\vs11k09a-1.cfg"

openocd-stop:
	pkill openocd

dfu:
	python3 C:\Users\smplman\projects\qmk_firmware-19\util\dk63\dfu.py

# run python script to upload the firmware
upload:
	python3 C:\Users\smplman\projects\qmk_firmware-19\util\dk63\flash-firmware.py C:\Users\smplman\projects\qmk_firmware-19\.build\kmove_dk63_default.bin --vid 0x0c45 --pid 0x7040

gdb:
	arm-none-eabi-gdb.exe ./.build/kmove_dk63_default.elf -ex "target remote :3333" -ex "set confirm off" -ex "set pagination off"
