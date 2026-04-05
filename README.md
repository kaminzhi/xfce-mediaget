# xfce-mediaget

A tool for **XFCE Generic Monitor (GenMon)** that displays current media information with support for multiple players and automatic album art processing.

---

## Dependencies

- `playerctl` (Media control)
- `curl` (Image downloading)
- `ffmpeg` (Image processing/scaling)

## How To Use

```bash
git clone https://github.com/kaminzhi/xfce-mediaget.git
cd xfce-mediaget
make
sudo make install
```

```bash
# Default (150x83)
xfce-mediaget

# Custom Square (e.g., 32x32)
xfce-mediaget -w 32 -h 32
```
