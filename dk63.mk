# Upload firmware

# start openocd
openocd-run:
	"openocd.exe" "-c" "gdb_port 3333" "-s" "C:\Users\smplman\projects\qmk_firmware-19" "-f" "C:\Users\smplman\projects\dk63\stlink.cfg" "-f" "C:\Users\smplman\projects\dk63\vs11k09a-1.cfg"
	# openocd -c "gdb_port 3333" -s /qmk_firmware -f /qmk_firmware/util/dk63/stlink.cfg -f /qmk_firmware/util/dk63/vs11k09a-1.cfg

openocd-remote:
	docker run -it --privileged --rm -w /qmk_firmware -p 3333:3333 -v /dev:/dev qmk make -f dk63.mk openocd-run
	# docker run -it --rm --privileged -w /qmk_firmware -p 3333:3333 -v /dev:/dev -v /Users/speery/projects/personal/qmk_firmware-9:/qmk_firmware qmk make -f dk63.mk openocd-run

openocd-start:
	openocd -c "gdb_port 3333" -s /qmk_firmware -f /qmk_firmware/util/dk63/stlink.cfg -f /qmk_firmware/util/dk63/vs11k09a-1.cfg &

# stop openocd
openocd-stop:
	pkill openocd

# Put device into bootloader mode
dfu:
	# python3 /qmk_firmware/util/dk63/dfu.py
	# python3 "C:\Users\smplman\projects\qmk_firmware-19\util\dk63\dfu.py"
	python3 util/dk63/dfu.py


# run python script to upload the firmware
upload:
	# python3 C:\Users\smplman\projects\qmk_firmware-19\util\dk63\flash-firmware.py C:\Users\smplman\projects\qmk_firmware-19\.build\kemove_dk63_default.bin --vid 0x0c45 --pid 0x7040
	# python3 /qmk_firmware/util/dk63/flash-firmware.py /qmk_firmware/.build/kemove_dk63_default.bin --vid 0x0c45 --pid 0x7040
	python3 ./util/dk63/flash-firmware.py ./.build/kemove_dk63_default.bin --vid 0x0c45 --pid 0x7040


# start gdb session
gdb:
	arm-none-eabi-gdb.exe ./.build/kemove_dk63_default.elf -ex "target remote :3333" -ex "set confirm off" -ex "set pagination off"
	# arm-none-eabi-gdb .build/kemove_dk63_default.elf -ex "target remote :3333" -ex "set confirm off" -ex "set pagination off"

# deploy using docker
deploy:
	./util/dk63/docker_build.sh kmove/dk63:default:flash

# dfu-remote: docker run -it --rm --privileged -w /qmk_firmware -p 3333:3333 -v /dev:/dev qmk make -f dk63.mk dfu

gdb-remote:
	arm-none-eabi-gdb.exe ./.build/kemove_dk63_default.elf -ex "target remote 192.168.99.101:3333" -ex "set confirm off" -ex "set pagination off"

remote-debug:
	docker run --rm -it --rm --privileged -v /dev:/dev \
		--user=1000:50 \
		-w /qmk_firmware \
		# -v /mnt/c/Users/smplman/projects/qmk_firmware-19:/qmk_firmware \
		-e ALT_GET_KEYBOARDS=true \
		-e SKIP_GIT="$SKIP_GIT" \
		-e MAKEFLAGS="$MAKEFLAGS" \
		-p 3333:3333 \
		qmk \
		openocd -c "gdb_port 3333" -s /qmk_firmware -f /qmk_firmware/util/dk63/stlink.cfg -f /qmk_firmware/util/dk63/vs11k09a-1.cfg

remote-gdb:
	arm-none-eabi-gdb.exe ./.build/kemove_dk63_default.elf -ex "target remote 192.168.99.102:3333" -ex "set confirm off" -ex "set pagination off"
	# arm-none-eabi-gdb ../qmk_firmware-9/.build/kemove_dk63_default.elf -ex "target remote 192.168.99.102:3333" -ex "set confirm off" -ex "set pagination off"

upload-remote:
	docker run -it --rm --privileged -w /qmk_firmware -p 3333:3333 -v /dev:/dev qmk make -f dk63.mk upload

all-remote:
	docker run -it --rm --privileged -v /mnt/c/Users/smplman/projects/qmk_firmware-19:/qmk_firmware -w /qmk_firmware -p 3333:3333 -v /dev:/dev qmk make -f dk63.mk all

# dfu and upload
all: openocd-start dfu openocd-stop upload
