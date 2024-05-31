# VeilFlow: A real-time mosaic tool for video

## Build

1. Install OpenCV
2. Pull `nlohmann_json` from git submodule
```bash
git submodule update --init --recursive
```
3. Set `OpenCV_DIR` in PATH
4. Build with CMake

## Usage

```bash
.\VeilFlow.exe <input>
```

Make sure that you have the `config.json` file in the same directory as the executable.

## Configuration

```json
{
  "mosaicRegion": {
    "x": 800,
    "y": 600,
    "width": 300,
    "height": 300
  },
  "mosaicSize": 20
}
```
