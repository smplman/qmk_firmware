# Makefile for dk63, offers some dev tools

DIR:=${CURDIR}
QMK_PATH=$(DIR)/../../../
QMK_DIR:= $(abspath $(dir $(QMK_PATH)))
UTIL_DIR=$(DIR)/util

# start openocd
openocd-run:
	openocd -c "gdb_port 3333" -s $(QMK_DIR) -f $(UTIL_DIR)/stlink.cfg -f $(UTIL_DIR)/vs11k09a-1.cfg

openocd-start:
	openocd -c "gdb_port 3333" -s $(QMK_DIR) -f ./util/stlink.cfg -f ./util/vs11k09a-1.cfg &

# stop openocd
openocd-stop:
	pkill openocd

# Put device into bootloader mode
dfu:
	python3 ./util/dfu.py

# run python script to upload the firmware
upload:
	python3 ./util/flash-firmware.py $(QMK_DIR)/.build/kemove_dk63_default.bin --vid 0x0c45 --pid 0x7040

# start gdb session
gdb:
	arm-none-eabi-gdb-py $(QMK_DIR)/.build/kemove_dk63_default.elf -ex "target remote :3333" -ex "set confirm off" -ex "set pagination off" -ex "source ./svd_gdb.py" -ex "svd_load util/SN32F240B.svd"

# Docker makefile commands
KEYBOARD_DIR=/qmk_firmware/keyboards/kemove/dk63
DOCKER_UTIL_DIR=$(KEYBOARD_DIR)/util
DOCKER_MAKEFILE=$(KEYBOARD_DIR)/dk63.mk
DOCKER_RUN=docker run -it --rm --privileged -w /qmk_firmware -p 3333:3333 -v $(QMK_DIR):/qmk_firmware -v /dev:/dev qmk
DOCKER_MAKE=$(DOCKER_RUN) make -f $(DOCKER_MAKEFILE)

# deploy using docker
deploy:
	./util/docker_build.sh kemove/dk63:default:flash

build:
	cd $(QMK_DIR); \
	make kemove/dk63:default

# dfu-remote: docker run -it --rm --privileged -w /qmk_firmware -p 3333:3333 -v /dev:/dev qmk make -f $(DOCKER_MAKEFILE) dfu

remote-debug:
	docker run --rm -it --rm --privileged -v /dev:/dev \
		--user=1000:50 \
		-w /qmk_firmware \
		-v $(QMK_DIR):/qmk_firmware \
		-e ALT_GET_KEYBOARDS=true \
		-e SKIP_GIT="$SKIP_GIT" \
		-e MAKEFLAGS="$MAKEFLAGS" \
		-p 3333:3333 \
		qmk \
		openocd -c "gdb_port 3333" -s /qmk_firmware -f $(DOCKER_UTIL_DIR)/stlink.cfg -f $(DOCKER_UTIL_DIR)/vs11k09a-1.cfg

openocd-remote:
	$(DOCKER_MAKE) openocd-run

gdb-remote:
	$(DOCKER_MAKE) gdb

build-remote:
	$(DOCKER_MAKE) build

upload-remote:
	$(DOCKER_MAKE) upload

all-remote:
	$(DOCKER_MAKE) all

dfu-remote:
	$(DOCKER_MAKE) dfu-mode

sh:
	$(DOCKER_RUN) /bin/bash


# dfu and upload
all: openocd-start dfu openocd-stop upload
dfu-mode: openocd-start dfu openocd-stop
