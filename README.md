# TRAFFIC LIGHT CONTROL SYSTEM (IMPLEMENT ON STM32 BLUEPILL)

## Introduction

The Traffic Light Control handles three inputs from sensors representing vehicles on the South and West roads and pedestrian crossings - Walk. The system operates based on:
- Traffic lights in different directions must change from Go (green) -> Warning (yellow) -> Stop (red). When one light is in Go or Warning, the other direction's lights must be in Stop.
- priority: South-Walk-West. if the sensors in all directions are logic 1, the South's vehicles will move first, then the Walk, then the West.
- Alternate Right of Way: When multiple sensors detect a vehicle (sensor = 1), the traffic lights will turn green base on priority, alternating the right of way. For example, initially, the South direction is given priority, followed by the Walk (Pedestrian) signal and the West direction. If the South light is already Green, then if there is a vehicle in the West or Pedestrian crossings, the light in that direction will green although there's a vehicle in South direction

This project is developed by a team has four members
- Nguyễn Hoàng Hiệp
- Huỳnh Quang Đức
- Ngô Quang Đức
- Trần Anh Đức

## Objective

Implement traffic light control system on STM32 bluepill using an FSM (Finite State Machine) approach. Using button for input.

- If button is pressed or held, logic sensor = 1 represents there is car or pedestrian crossings in that direction button is pressed or held.
- If button isn't pressed or held, logic sensor = 0 represents there isn't car or pedestrian crossings in that direction button is pressed or held.
- **LCD Display:**
  - Displays the elapsed time for light states:
    - Go (Green for 10s) → Warning (Yellow for 5s) → Stop (Red).
    - Pedestrian light sequence: White (10s) → Blinking Warning (5s) → Red.
  - Shows "00" when all lights are Red.



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








