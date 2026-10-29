v1.6.0 adds a light/dark theme selector to the GUI, fixes the preferences that were never actually saved, and recovers EXIF from PNGs that store it in the non-standard JPEG-style form.
v1.6.0 为 GUI 增加浅色/深色主题选择，修复一直没能真正生效的设置记忆，并能从"非规范形式"存放 EXIF 的 PNG 里把元数据捞回来。

## What's new | 新增

- **Light / dark theme in the GUI**: a `Theme:` dropdown sits next to the language selector (add order: theme first), switches instantly, and covers the window, file list, log view and every control.  Light keeps the native platform style untouched; dark switches to Fusion with a custom palette, because the native Windows style ignores most palette entries
  **GUI 浅色/深色主题**：`主题：` 下拉框位于语言选择器左侧（新增顺序：主题在前），切换即时生效，覆盖窗口、文件列表、日志区与所有控件。浅色保持原生平台风格不变；深色改用 Fusion + 自定义调色板 —— 原生 Windows 风格会忽略调色板的大部分项
- **Preferences now actually persist** (bug fix): `QSettings` was a silent no-op because the application never set an organisation name — its file name came back empty and every write failed with an access error.  As a result the language choice was never remembered either, despite what the README claimed.  Both language and theme are now stored and restored
  **设置现在真的会记住**（缺陷修复）：`QSettings` 一直是静默空操作 —— 程序从未设置组织名，其 fileName 为空、每次写入都是访问错误。因此语言选择其实也从未被记住（尽管 README 一直这么写）。现在语言与主题都会保存并恢复
- **EXIF recovered from non-conformant `eXIf` chunks**: some writers put the JPEG-style `Exif\0\0` identifier inside a PNG `eXIf` chunk.  That is not what the PNG spec says, and libpng drops such a chunk with a warning, so the metadata used to be lost silently.  The decoder now rescues the payload from the raw chunk stream and writes a conformant chunk back out
  **从非规范 `eXIf` 块中恢复 EXIF**：有些写入器会在 PNG 的 `eXIf` 块里带上 JPEG 风格的 `Exif\0\0` 标识。这不符合 PNG 规范，libpng 会带警告丢弃该块，导致元数据被静默丢失。解码器现在会从原始分块流中把载荷捞回来，并在写回时恢复为规范形式
- **Self-test: 362 → 371 checks**, adding the non-conformant eXIf case with an explicit baseline assertion that libpng alone drops it
  **自测试：362 → 371 项**，新增非规范 eXIf 场景，并显式断言"libpng 单独处理会丢"这一基线

## Downloads | 下载

| File | For |
|---|---|
| `img2png-v1.6.0-windows-x64.zip` | Windows users — extract and run, no installation needed<br>Windows 用户 —— 解压即用，无需安装 |
| `img2png-v1.6.0-linux-x64.tar.gz` | Linux x64 — includes a launcher script with bundled Qt libraries<br>Linux x64 —— 附带启动脚本与 Qt 运行库 |
| `img2png_1.6.0_amd64.deb` | Linux x64 Debian/Ubuntu package — installs to `/opt/img2png` with `img2png` / `img2png-gui` on PATH<br>Linux x64 的 Debian/Ubuntu 安装包 —— 安装到 `/opt/img2png`，`img2png` / `img2png-gui` 直接可用 |
| `img2png-v1.6.0-macos.tar.gz` | macOS — includes the .app bundle<br>macOS —— 包含 .app 应用包 |
| `img2png-v1.6.0-macos.dmg` | macOS disk image — drag the .app to Applications (unsigned: first launch needs right-click → Open)<br>macOS 磁盘镜像 —— 把 .app 拖进 Applications（未签名：首次打开需右键 → 打开） |
| `img2png-1.6.0.zip` | Source code — builds offline on all three platforms (dependencies vendored)<br>源代码 —— 三平台均可离线构建（依赖已内置） |

## Notes | 说明

- Windows x64 tested locally; the Linux/macOS builds and the full self-test (371 checks) were verified in CI
  Windows x64 已本地实测；Linux/macOS 的构建与完整自测试（371 项）已在 CI 验证
- **Repository moved**: the project now lives at `github.com/Hanson418/img2png` (the old account name still redirects).  GUI settings are stored under `HKCU\Software\Hanson418\img2png` — the key changed with the rename, so the first launch after upgrading starts at the defaults (light theme, Chinese)
  **仓库地址变更**：项目现在位于 `github.com/Hanson418/img2png`（旧账号名仍会跳转）。GUI 设置存放于 `HKCU\Software\Hanson418\img2png` —— 键名随改名变化，因此升级后首次启动为默认状态（浅色主题、中文）
- The dark theme leaves the OS title bar as the system draws it: Qt palettes do not reach the non-client area
  深色主题下窗口标题栏仍由系统绘制：Qt 调色板作用不到非客户区
- **New package formats**: Linux now also ships a `.deb` (Debian/Ubuntu, installs under `/opt/img2png` with a `.desktop` entry) and macOS also ships a `.dmg` with the standard drag-to-Applications layout.  Neither the `.dmg` nor the `.app` is code-signed, so macOS Gatekeeper needs a right-click → Open on first launch
  **新增包格式**：Linux 额外提供 `.deb`（Debian/Ubuntu，装到 `/opt/img2png` 并带 `.desktop` 项），macOS 额外提供 `.dmg`（标准「拖进 Applications」布局）。`.dmg`/`.app` 均未代码签名，因此 macOS 首次打开需右键 → 打开
- Metadata preservation is unchanged from v1.5.0 (EXIF / ICC / XMP / resolution / text chunks) and stays independent of `--auto`
  元数据保留与 v1.5.0 一致（EXIF / ICC / XMP / 分辨率 / 文本块），且与 `--auto` 无关
- See the README for the per-format metadata table and the bit-depth rules (English / 中文)
  逐格式的元数据与位深对照表见 README（English / 中文）
