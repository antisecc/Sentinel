# Linux Antivirus System

This project implements a Linux antivirus system to provide real-time scanning and execution control of executable files written in C language. 

## Setup Instructions



1. **Build the Project**: 
   ```
   make
   ```

2. **Load the Kernel Module**: 
   ```
   sudo insmod <module-name>.ko
   ```

3. **Start the Daemon**: 
   ```
   ./src/daemon/avd &
   ```

4. **Run Scans**: 
   Use the command-line interface provided in `tools/av_control.c` to start manual scans or configure the daemon.

## Usage

- The system will automatically monitor for new executables and scan them.
- Users can manually trigger scans and view logs for detected threats.

## Contributing

Contributions are welcome! Please submit a pull request or open an issue for any enhancements or bug fixes.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.
