# TRAFFIC LIGHT CONTROL SYSTEM (IMPLEMENT ON STM32 BLUEPILL)

## Introduction

The Traffic Light Control handles three inputs from sensors representing vehicles on the South and West roads and pedestrian crossings - Walk.
In this project we use button for input. 
- If button is pressed or held, logic sensor = 1 represents there is car or pedestrian crossings in that direction button is pressed or held.
- If button isn't pressed or held, logic sensor = 0 represents there isn't car or pedestrian crossings in that direction button is pressed or held.  

This project is developed by a team has four members
- Nguyễn Hoàng Hiệp
- Huỳnh Quang Đức
- Ngô Quang Đức
- Trần Anh Đức

## Objective

Test and Maximize the communication capabilities of the LoRaWAN protocol used Arduino under different real-world conditions: straight transmission (no obstacles), transmission through tree canopies, rain, and obstacles such as walls or buildings.

## Measurements method

## Hardware Requirements
- STM32 blue pill: 1 units
- button: 3 units
- LCD 1602: 1 units 
- LED (red, green, yellow): 3 units

## Connections
| Module LoRa | Arduino Uno R3 |
|-------------|----------------|
| VCC         | 3.3V           |
| GND         | GND            |
| RST         | 9              |
| DIO0        | 2              |
| NSS         | 10             |
| MOSI        | 11             |
| MISO        | 12             |
| SCK         | 13             |

## Measurement Scenarios
- Straight transmission: Measurement across both sides of West Lake (Hồ Tây)
- Transmission through tree canopies: The transmitter will be placed on top of a high-rise building while the receiver is under the tree canopy.
- Transmission with obstacles such as walls or buildings: Measurements will be taken across different floors of Nhà Xinh residential complex in Yên Hòa, Hanoi.

## Contact

- Facebook: [Nguyễn Hoàng Hiệp](https://www.facebook.com/profile.php?id=100009669068016)
- Gmail: kzhiep@gmail.com

## Demo

- Youtube: [demo vi xử lý nhóm 18](https://www.youtube.com/watch?v=T2hlrNRj5pM)








