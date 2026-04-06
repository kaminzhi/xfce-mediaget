# xfce-mediaget

A tool for **XFCE Generic Monitor (GenMon)** that displays media information for multiple players and automatic album art processing.

<img width="1435" height="147" alt="2026-04-05-135129_hyprshot" src="https://github.com/user-attachments/assets/68968b5e-f841-49cd-a8d2-cc0aa7ba8d0d" />

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
