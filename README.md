# Lumina Inventory System

A desktop companion tool for [Snipe-IT](https://snipeitapp.com/) that provides bulk check-in and check-out of inventory items across warehouse zones.

## Purpose

Snipe-IT does not natively support bulk zone-based check-in/check-out. This application connects directly to the Snipe-IT MySQL database and updates asset assignments by zone, allowing operators to check in or check out all items in one or more zones with a single action.

## Features

- **Zone selection** — 11 configurable zones (0–9 plus Zone 4.5) with a "Select All" toggle
- **Bulk check-out** — assigns items to a location based on their zone
- **Bulk check-in** — clears assignment and resets status for all items in selected zones
- **Dark themed UI** — modern Catppuccin Mocha-inspired interface

## Tech Stack

- **C++17** with **Qt5** (Widgets)
- **MySQL/MariaDB** via the C API
- **CMake 3.27+** build system
- Cross-platform (Linux, macOS, Windows)

## Building

```bash
cmake -B build
cmake --build build
```

### Dependencies

- Qt5 (Core, Gui, Widgets)
- libmariadb / MySQL client library
- CMake 3.27+

On Debian/Ubuntu:
```bash
sudo apt install qt5-default libmariadb-dev cmake
```

On Arch:
```bash
sudo pacman -S qt5-base mariadb-libs cmake
```

## Usage

1. Launch the application
2. Go to **File > Connect To Database**
3. Enter the MySQL server URL, username, and password
4. Select the zones you want to operate on
5. Click **CheckOut** or **CheckIn**
