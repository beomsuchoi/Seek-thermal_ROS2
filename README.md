# Seek-thermal_ROS2


먼저 필요한 의존성 패키지들을 설치합니다:
```
sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    libusb-1.0-0-dev \
    libopencv-dev \
    git
```
libseek-thermal 라이브러리 설치:

# 홈 디렉토리로 이동
```
cd ~
```
# libseek-thermal 클론
```
https://github.com/beomsuchoi/libseek-thermal.git
```

# 빌드 디렉토리 생성 및 이동
```
cd libseek-thermal
mkdir build
cd build
```
# 빌드 및 설치
```
cmake ..
make
sudo make install
```
# 라이브러리 캐시 업데이트
```
sudo ldconfig
```
udev 규칙 설정 (카메라 접근 권한을 위해 필요):

# libseek-thermal 디렉토리에서
```
sudo cp ../debian/99-seek.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules
sudo udevadm trigger
```
새로운 udev 규칙 파일을 생성합니다:
```
sudo nano /etc/udev/rules.d/99-seek-thermal.rules
```
아래 내용을 복사해서 넣습니다:
```
Copy# Seek Thermal Compact/CompactPRO
SUBSYSTEMS=="usb", ATTRS{idVendor}=="289d", ATTRS{idProduct}=="0010", MODE="0666"
SUBSYSTEMS=="usb", ATTRS{idVendor}=="289d", ATTRS{idProduct}=="0011", MODE="0666"
```
Ctrl + X를 누른 후 Y를 눌러 저장하고 나갑니다.
규칙을 적용합니다:
```
sudo udevadm control --reload-rules
sudo udevadm trigger
```
이렇게 하면 udev 규칙 설정이 완료됩니다.
