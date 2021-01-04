#!/bin/sh
# NOTE: This script uses tabs for indentation

errcho() {
	echo "$@" >&2
}

USAGE="Usage: $0 [keyboard[:keymap[:target]]]"

# Check preconditions
for arg; do
	if [ "$arg" = "--help" ]; then
		echo "$USAGE"
		exit 0
	fi
done
if [ $# -gt 1 ]; then
	errcho "$USAGE"
	exit 1
elif ! command -v docker >/dev/null 2>&1; then
	errcho "Error: docker not found"
	errcho "See https://docs.docker.com/install/#supported-platforms for installation instructions"
	exit 2
fi

# Determine arguments
if [ $# -eq 0 ]; then
	printf "keyboard=" && read -r keyboard
	[ -n "$keyboard" ] && printf "keymap=" && read -r keymap
	[ -n "$keymap"   ] && printf "target=" && read -r target
else
	IFS=':' read -r keyboard keymap target x <<-EOF
	$1
	EOF
	if [ -n "$x" ]; then
		errcho "$USAGE"
		exit 1
	fi
fi
if [ -n "$target" ]; then
	if [ "$(uname)" = "Darwin" ] || "$(docker-machine active)" >/dev/null 2>&1; then
		usb_args="--privileged -v /dev:/dev"
	else
		errcho "Error: target requires docker-machine to work on your platform"
		errcho "See http://gw.tnode.com/docker/docker-machine-with-usb-support-on-windows-macos"
		errcho "Consider flashing with QMK Toolbox (https://github.com/qmk/qmk_toolbox) instead"
		exit 3
	fi
fi
dir=$(pwd -W 2>/dev/null) || dir=$PWD  # Use Windows path if on Windows
# dir="/c/Users/smplman/projects/qmk_firmware-19"
# echo $dir

perms="1000:50"
# --user $(id -u):$(id -g) \
# Run container and build firmware
docker run --rm -it $usb_args \
    --user=$perms \
	-w /qmk_firmware \
    -v /qmk_firmware-9:/qmk_firmware \
	-e ALT_GET_KEYBOARDS=true \
	-e SKIP_GIT="$SKIP_GIT" \
	-e MAKEFLAGS="$MAKEFLAGS" \
    -p 3333:3333 \
	qmk \
	make "$keyboard${keymap:+:$keymap}${target:+:$target}"
