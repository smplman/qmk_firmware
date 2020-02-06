FROM qmkfm/base_container

VOLUME /qmk_firmware
WORKDIR /qmk_firmware
COPY . .
# RUN usermod -u 1000 /qmk_firmware

RUN apt-get update && apt-get install --no-install-recommends -y \
    usbutils \
    procps \
    evtest

WORKDIR /
RUN wget https://github.com/xpack-dev-tools/openocd-xpack/releases/download/v0.10.0-13/xpack-openocd-0.10.0-13-linux-x64.tgz
RUN tar -xvf xpack-openocd-0.10.0-13-linux-x64.tgz
RUN ln -s /xPacks/openocd/0.10.0-13/bin/openocd /usr/bin/openocd

RUN pip3 install wheel
RUN pip3 install pyusb

CMD make all:default
