# Upload firmware

# start openocd
openocd:
	# "openocd.exe" "-c" "gdb_port 3333" "-s" "C:\Users\smplman\projects\qmk_firmware-19" "-f" "C:\Users\smplman\projects\dk63\stlink.cfg" "-f" "C:\Users\smplman\projects\dk63\vs11k09a-1.cfg"
	openocd -c "gdb_port 3333" -s /qmk_firmware -f /qmk_firmware/util/dk63/stlink.cfg -f /qmk_firmware/util/dk63/vs11k09a-1.cfg

openocd-remote:
	docker run -it --privileged -w /qmk_firmware -p 3333:3333 -v /dev:/dev -v /c/Users/smplman/projects/qmk_firmware-19:/qmk_firmware qmk make -f dk63.mk openocd

openocd-start:
	openocd -c "gdb_port 3333" -s /qmk_firmware -f /qmk_firmware/util/dk63/stlink.cfg -f /qmk_firmware/util/dk63/vs11k09a-1.cfg &

# stop openocd
openocd-stop:
	pkill openocd

# Put device into bootloader mode
dfu:
	# python3 C:\Users\smplman\projects\qmk_firmware-19\util\dk63\dfu.py
	python3 /qmk_firmware/util/dk63/dfu.py

# run python script to upload the firmware
upload:
	# python3 C:\Users\smplman\projects\qmk_firmware-19\util\dk63\flash-firmware.py C:\Users\smplman\projects\qmk_firmware-19\.build\kmove_dk63_default.bin --vid 0x0c45 --pid 0x7040
	python3 /qmk_firmware/util/dk63/flash-firmware.py /qmk_firmware/.build/kmove_dk63_default.bin --vid 0x0c45 --pid 0x7040

# start gdb session
gdb:
	# arm-none-eabi-gdb.exe ./.build/kmove_dk63_default.elf -ex "target remote :3333" -ex "set confirm off" -ex "set pagination off"
	arm-none-eabi-gdb .build/kmove_dk63_default.elf -ex "target remote :3333" -ex "set confirm off" -ex "set pagination off"

gdb-remote:
	arm-none-eabi-gdb.exe ./.build/kmove_dk63_default.elf -ex "target remote 192.168.99.101:3333" -ex "set confirm off" -ex "set pagination off"

# dfu and upload
all: openocd-start dfu openocd-stop upload
