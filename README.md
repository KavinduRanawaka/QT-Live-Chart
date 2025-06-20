
# Qt Serial Data Visualizer

A Qt-based desktop application designed for connecting to a serial device (such as an Arduino), reading streaming data, and visualizing it in real time. It also includes features like device configuration, firmware updates, and multi-window MDI (Multiple Document Interface) support.

---

## ✨ Features

* 📊 **Live Data Graphing** using `QtCharts`
* 🧭 **Multi-Window Interface** (Data Graphs, 3D Visualizer, Data View, Device Status)
* 🔌 **Serial Port Connection** and Device Discovery
* ⏺ **Data Recording** toggle support
* ⚙️ **Device Configuration**, Calibration, and Firmware Update
* 🧰 **Toolbar and Menu Bar** with full control options
* 📁 **Data Export and Print Support**
* 🪟 **Window Layout Management** (Tile, Cascade, Minimize, Restore)

---


## 🚀 Getting Started

### Prerequisites

* Qt 5.12+ (with `QtCharts` module)
* C++17 compatible compiler
* Supported OS: Windows / Linux / macOS

### Building the Project

```bash
git clone https://github.com/yourusername/qt-serial-visualizer.git
cd qt-serial-visualizer
qmake
make
./QtSerialVisualizer
```

Or use **Qt Creator** to open the `.pro` file and build the project.

---

## 🔧 Usage Guide

1. **Connect a Serial Device**

   * Go to `Device > Open Port`
   * Select your serial port (e.g., COM3, /dev/ttyUSB0)
2. **Start Reading**

   * Use `Device > Start Reading Data / Stop`
3. **View Data**

   * Open `View > Data View Window` to see real-time charts.
4. **Record Data**

   * Toggle recording via `Reading Data > Start Recording Data / Stop`
5. **Export**

   * Use `File > Export Data` to save collected data.

---

## 🧩 Project Structure

* `mainwindow.cpp / .h`: Core UI and logic controller
* `portdialog.cpp / .h`: Serial port selection dialog
* `main.cpp`: Entry point of the application
* `resources/`: Icons and static assets (if any)

---

## 📦 Dependencies

* [Qt](https://www.qt.io/) (Core, Widgets, Charts, SerialPort)
* C++ Standard Library

---

## 🧪 Future Improvements

* Save chart data to CSV
* Load and replay historical data
* Add 3D data visualization in the 3D Visualizer window
* Improve UI with dynamic resizing and animations

---


**Your Name**
[GitHub](https://github.com/yourusername) | [LinkedIn](https://linkedin.com/in/yourprofile)

---

Would you like me to help generate a LICENSE file or add the project structure in Markdown format with file descriptions too?
