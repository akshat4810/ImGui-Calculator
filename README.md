# ImGui Calculator
 This repository contains a simple calculator application built using ImGui (Immediate Mode Graphical User Interface) and C++. The calculator supports basic arithmetic operations including addition, subtraction, multiplication, and division.

## Features
- **Basic Arithmetic Operations**: Perform addition, subtraction, multiplication, and division.
- **Immediate Feedback**: Results are calculated and displayed immediately upon pressing the "Calculate" button.
- **Cross-Platform**: Includes support for Android using JNI and OpenGL ES.
- **User-Friendly Interface**: Clean and simple GUI built with ImGui.

## Prerequisites
- Android Studio
- Android NDK (Native Development Kit)
- A physical Android device or emulator

## Installation
1. **Open the project in Android Studio:**
   - Launch Android Studio.
   - Click on `File > Open` and navigate to the cloned repository directory.
   - Select the project and click `OK`.
2. **Set up the Android NDK:**
   - Install the Android NDK from the SDK Manager if not already installed.
   - Configure the NDK path in your project settings if necessary.
3. **Build the project:**
   - Sync the Gradle files by clicking on the `Sync Now` prompt that appears in Android Studio.
   - Build the project by clicking on `Build > Make Project`.
4. **Run the project:**
   - Connect your Android device or start an emulator.
   - Run the project by clicking on the `Run` button or pressing `Shift + F10`.

## Usage
- Launch the app on your Android device or emulator.
- Enter numbers into the input fields.
- Select the desired operation by clicking one of the operation buttons (+, -, *, /).
- Click the "Calculate" button to see the result.

## Contributing
Contributions are welcome! Please feel free to submit a pull request or open an issue to discuss potential changes.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Acknowledgements
- [ImGui](https://github.com/ocornut/imgui) for the wonderful GUI library
- Android and OpenGL ES for enabling cross-platform support
