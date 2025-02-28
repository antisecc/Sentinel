# Linux Antivirus System

This project implements a Linux antivirus system using a Loadable Kernel Module (LKM) to provide real-time scanning and execution control of executable files. The system is designed to monitor newly created executables, scan them for known viruses, and prevent the execution of any unscanned files.

## Features

- **File Monitoring**: Utilizes fanotify or inotify to track newly created executable files and alert the user if a virus is detected.
- **Execution Control**: Hooks into the `execve` system call to prevent the execution of executables that have not been scanned.
- **Scanning**: Scans the filesystem for ELF executables and checks them against a database of known virus signatures.
- **Signature Management**: Loads and matches virus signatures to ensure effective detection.
- **Logging**: Records events and alerts for monitoring purposes.
- **User-space Daemon**: Runs in the background to handle alerts and user interactions.

## Project Structure

- `src/kernel/lkm/`: Contains the kernel module source files for file monitoring and execution control.
- `src/scanner/`: Implements the scanning functionality and virus signature management.
- `src/daemon/`: Contains the user-space daemon for handling alerts and interactions.
- `src/utils/`: Provides utility functions for logging and configuration management.
- `tests/`: Includes unit tests for both the scanner and kernel module functionalities.
- `tools/`: Contains tools for generating virus signatures and controlling the antivirus system.
- `config/`: Configuration file for system settings.
- `Makefile`: Build scripts for compiling the project.

## Setup Instructions

1. **Clone the Repository**: 
   ```
   git clone <repository-url>
   cd linux-antivirus
   ```

2. **Build the Project**: 
   ```
   make
   ```

3. **Load the Kernel Module**: 
   ```
   sudo insmod <module-name>.ko
   ```

4. **Start the Daemon**: 
   ```
   ./src/daemon/avd &
   ```

5. **Run Scans**: 
   Use the command-line interface provided in `tools/av_control.c` to start manual scans or configure the daemon.

## Usage

- The system will automatically monitor for new executables and scan them.
- Users can manually trigger scans and view logs for detected threats.

## Contributing

Contributions are welcome! Please submit a pull request or open an issue for any enhancements or bug fixes.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.