# Upload firware

# Put device into bootloader mode
openocd:
	openocd -s ../dk63/ -f stlink.cfg &

openocd-stop:
	pkill openocd

dfu:
	python3 ./util/dk63/dfu.py

# run python script to upload the firmware
upload:
	python3 ./util/dk63/flash-firmware-hid.py ./.build/kmove_dk63_default.bin --vid 0x0c45 --pid 0x7040
	# python3 ../dk63/files/RCData4000.bin ./.build/kmove_dk63_default.bin --vid 0x0c45 --pid 0x7040

gdb:
	arm-none-eabi-gdb ./.build/kmove_dk63_default.elf -ex "target remote :3333" -ex "set confirm off" -ex "set pagination off"
