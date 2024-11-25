// Win.cpp --- VeySickのWindows関連コード

#ifndef NOMINMAX
    #define NOMINMAX // We don't use Windows min/max macros
#endif
#define _USE_MATH_DEFINES // We use <cmath>'s M_PI
#define _CRT_SECURE_NO_WARNINGS // We use old API for compatibility

#ifdef _WIN32 // Win32コンパイラの場合
    #include <windows.h>        // Windows API
    #include <windowsx.h>       // Windows 拡張マクロ
    #include <commctrl.h>       // コモンコントロール
    #include <commdlg.h>        // コモンダイアログ
    #include <shellapi.h>       // シェルAPI
    #include <shlobj.h>         // シェルオブジェクト
    #include <shlwapi.h>        // シェル軽量API
    #include <tchar.h>          // ジェネリック テキスト マッピング
    #include <strsafe.h>        // 安全に文字列バッファを操作
#endif

#include "VeySicK.h"            // VeySick
#include <imm.h>                // 日本語入力システム（IME/IMM）用
#include "AntiRE.h"             // 逆工学対策
#include "MCenterWindow.h"      // ウィンドウを中央寄せ
#include "MImageViewEx.h"       // イメージを表示するコントロール
#include "resource.h"           // リソースID群

#define VSK_ONE_SECOND 1000         // 一秒間の長さ（ミリ秒）

#define VSK_TIMER_ID_BLINK 999      // 点滅（blink）のタイマー
#define VSK_TIMER_ID_FPS_CHECK 888  // FPSチェックのタイマー

#define VSK_IDEAL_FPS 20            // 理想的なFPS
#define VSK_FPS_CHECK_INTERVAL (2 * VSK_ONE_SECOND) // FPSチェックの間隔（ミリ秒）

static DWORD s_dwFpsCounter = 0; // FPSチェック用の変数

CRITICAL_SECTION vsk_cs_lock; // クリティカルセクション（排他制御用）

// ロックする
void vsk_lock(void)
{
    ::EnterCriticalSection(&vsk_cs_lock);
}

// ロックを解除
void vsk_unlock(void)
{
    ::LeaveCriticalSection(&vsk_cs_lock);
}

// ミリ秒待つ
void vsk_sleep(uint32_t wait)
{
    ::Sleep(wait);
}

////////////////////////////////////////////////////////////////////////////////////
// 設定実装

#define VEYSICK_REGKEY TEXT("SOFTWARE\\Katayama Hirofumi MZ\\VeySicK")

// 設定を読み込む
bool VskSettings::load()
{
    reset();

    HKEY hKey;
    LSTATUS error = ::RegOpenKeyEx(HKEY_CURRENT_USER, VEYSICK_REGKEY, 0, KEY_READ, &hKey);
    if (error)
        return false;

    DWORD cbValue = sizeof(m_move_caret_by_mouse_click);
    ::RegQueryValueEx(hKey, TEXT("MoveCaretByMouseClick"), NULL, NULL, (BYTE*)&m_move_caret_by_mouse_click, &cbValue);

    cbValue = sizeof(m_remember_window_pos);
    ::RegQueryValueEx(hKey, TEXT("RememberWindowPos"), NULL, NULL, (BYTE*)&m_remember_window_pos, &cbValue);

    if (m_remember_window_pos)
    {
        cbValue = sizeof(m_x);
        ::RegQueryValueEx(hKey, TEXT("WinX"), NULL, NULL, (BYTE*)&m_x, &cbValue);
        cbValue = sizeof(m_y);
        ::RegQueryValueEx(hKey, TEXT("WinY"), NULL, NULL, (BYTE*)&m_y, &cbValue);
        cbValue = sizeof(m_cx);
        ::RegQueryValueEx(hKey, TEXT("WinCX"), NULL, NULL, (BYTE*)&m_cx, &cbValue);
        cbValue = sizeof(m_cy);
        ::RegQueryValueEx(hKey, TEXT("WinCY"), NULL, NULL, (BYTE*)&m_cy, &cbValue);
        cbValue = sizeof(m_zoomed);
        ::RegQueryValueEx(hKey, TEXT("WinZoomed"), NULL, NULL, (BYTE*)&m_zoomed, &cbValue);
        cbValue = sizeof(m_unlimited_mode);
        ::RegQueryValueEx(hKey, TEXT("Unlimited"), NULL, NULL, (BYTE*)&m_unlimited_mode, &cbValue);
        cbValue = sizeof(m_machine_mode);
        ::RegQueryValueEx(hKey, TEXT("MachineMode"), NULL, NULL, (BYTE*)&m_machine_mode, &cbValue);
        cbValue = sizeof(m_text_mode);
        ::RegQueryValueEx(hKey, TEXT("TextMode"), NULL, NULL, (BYTE*)&m_text_mode, &cbValue);
        cbValue = sizeof(m_field_width);
        ::RegQueryValueEx(hKey, TEXT("FieldWidth"), NULL, NULL, (BYTE*)&m_field_width, &cbValue);
    }

    ::RegCloseKey(hKey);
    return true;
}

// 設定を保存する
bool VskSettings::save() const
{
    HKEY hKey;
    LSTATUS error = ::RegCreateKeyEx(HKEY_CURRENT_USER, VEYSICK_REGKEY, 0, NULL, 0, KEY_WRITE, NULL,
                                     &hKey, NULL);
    if (error)
        return false;

    DWORD cbValue;

    cbValue = sizeof(m_move_caret_by_mouse_click);
    ::RegSetValueEx(hKey, TEXT("MoveCaretByMouseClick"), 0, REG_DWORD, (BYTE*)&m_move_caret_by_mouse_click, cbValue);

    cbValue = sizeof(m_remember_window_pos);
    ::RegSetValueEx(hKey, TEXT("RememberWindowPos"), 0, REG_DWORD, (BYTE*)&m_remember_window_pos, cbValue);

    if (m_remember_window_pos)
    {
        cbValue = sizeof(m_x);
        ::RegSetValueEx(hKey, TEXT("WinX"), 0, REG_DWORD, (BYTE*)&m_x, cbValue);
        cbValue = sizeof(m_y);
        ::RegSetValueEx(hKey, TEXT("WinY"), 0, REG_DWORD, (BYTE*)&m_y, cbValue);
        cbValue = sizeof(m_cx);
        ::RegSetValueEx(hKey, TEXT("WinCX"), 0, REG_DWORD, (BYTE*)&m_cx, cbValue);
        cbValue = sizeof(m_cy);
        ::RegSetValueEx(hKey, TEXT("WinCY"), 0, REG_DWORD, (BYTE*)&m_cy, cbValue);
        cbValue = sizeof(m_zoomed);
        ::RegSetValueEx(hKey, TEXT("WinZoomed"), 0, REG_DWORD, (BYTE*)&m_zoomed, cbValue);
        cbValue = sizeof(m_unlimited_mode);
        ::RegSetValueEx(hKey, TEXT("Unlimited"), 0, REG_DWORD, (BYTE*)&m_unlimited_mode, cbValue);
        cbValue = sizeof(m_machine_mode);
        ::RegSetValueEx(hKey, TEXT("MachineMode"), 0, REG_DWORD, (BYTE*)&m_machine_mode, cbValue);
        cbValue = sizeof(m_text_mode);
        ::RegSetValueEx(hKey, TEXT("TextMode"), 0, REG_DWORD, (BYTE*)&m_text_mode, cbValue);
        cbValue = sizeof(m_field_width);
        ::RegSetValueEx(hKey, TEXT("FieldWidth"), 0, REG_DWORD, (BYTE*)&m_field_width, cbValue);
    }

    ::RegCloseKey(hKey);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////

// 日本語ロケールID
#define LCID_JAPANESE MAKELCID(MAKELANGID(LANG_JAPANESE, SUBLANG_DEFAULT), SORT_DEFAULT)

// 半角文字を全角文字に変換する
VskString vsk_ank_to_kanji(const VskString& str)
{
    char buf[512];
    buf[0] = 0;
    ::LCMapStringA(LCID_JAPANESE, LCMAP_FULLWIDTH, str.c_str(), int(str.size() + 1), buf, _countof(buf));
    return buf;
}

// 全角文字を半角文字に変換する
VskString vsk_kanji_to_ank(const VskString& str)
{
    char buf[512];
    buf[0] = 0;
    ::LCMapStringA(LCID_JAPANESE, LCMAP_HALFWIDTH, str.c_str(), int(str.size() + 1), buf, _countof(buf));
    return buf;
}

////////////////////////////////////////////////////////////////////////////////////

// ファイル
struct VskWin32File : VskFile
{
public:
    HANDLE m_hFile;
    int m_x = 0;

    VskWin32File() = delete;
    VskWin32File(HANDLE hFile, MODE mode, TYPE type) : VskFile(type, mode), m_hFile(hFile) { }
    ~VskWin32File() { close(); }

    void close() override;
    bool eof() const override;

    int  get_x() const override;
    bool get_pos(VskDword *poffset) const override;
    bool set_pos(VskDword pos) override;
    bool get_size(VskDword *psize) const override;

    VskError read_bin(void *ptr, VskDword size) override;
    VskError read_line(std::string& data) override;
    VskError write_bin(const void *ptr, VskDword size) override;
    VskError write_str(const std::string& str) override;
    VskError write_line(const std::string& data) override;
    void flush() override;

    bool set_com_params(VskString params) override;

protected:
    friend struct VskFileManager;
};

VskError vsk_error_from_last_error(DWORD dwError)
{
    switch (dwError)
    {
    case ERROR_ALREADY_EXISTS:
        return VSK_ERR_FILE_ALREADY_EXIST;
    case ERROR_FILE_NOT_FOUND:
    case ERROR_PATH_NOT_FOUND:
        return VSK_ERR_FILE_NOT_FOUND;
    case ERROR_BAD_PATHNAME:
        return VSK_ERR_BAD_FILE_NAME;
    default:
        return VSK_ERR_DISK_IO_ERROR;
    }
}

VskError VskFileManager::open_host_file(VskFilePtr& file, const VskString& raw_path, VskFile::MODE mode, VskFile::TYPE type)
{
    HANDLE hFile = INVALID_HANDLE_VALUE;
    switch (mode)
    {
    case VskFile::MODE_INPUT:
        if (!vsk_is_safe_zone_pathname(raw_path, false))
            return VSK_ERR_WRITE_PROTECTED;
        if (!::PathFileExistsA(raw_path.c_str()))
            return VSK_ERR_FILE_NOT_FOUND;
        if (::PathIsDirectoryA(raw_path.c_str()))
            return VSK_ERR_BAD_OPERATION;
        hFile = ::CreateFileA(raw_path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, 0, NULL);
        break;
    case VskFile::MODE_OUTPUT:
        if (!vsk_is_safe_zone_pathname(raw_path, true))
            return VSK_ERR_WRITE_PROTECTED;
        hFile = ::CreateFileA(raw_path.c_str(), GENERIC_WRITE, FILE_SHARE_READ, nullptr,
                              CREATE_ALWAYS, 0, NULL);
        break;
    case VskFile::MODE_APPEND:
        if (!vsk_is_safe_zone_pathname(raw_path, true))
            return VSK_ERR_WRITE_PROTECTED;
        if (!::PathFileExistsA(raw_path.c_str()))
            return VSK_ERR_FILE_NOT_FOUND;
        if (::PathIsDirectoryA(raw_path.c_str()))
            return VSK_ERR_BAD_OPERATION;
        hFile = ::CreateFileA(raw_path.c_str(), GENERIC_WRITE, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, 0, NULL);
        if (hFile != INVALID_HANDLE_VALUE)
            ::SetFilePointer(hFile, 0, nullptr, FILE_END);
        break;
    case VskFile::MODE_DEFAULT:
        if (!vsk_is_safe_zone_pathname(raw_path, true))
            return VSK_ERR_WRITE_PROTECTED;
        hFile = ::CreateFileA(raw_path.c_str(), GENERIC_READ | GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_ALWAYS, 0, NULL);
        break;
    }

    if (hFile == INVALID_HANDLE_VALUE)
    {
        return vsk_error_from_last_error(::GetLastError());
    }

    file = std::make_shared<VskWin32File>(hFile, mode, type);
    return VSK_NO_ERROR;
}

VskError VskFileManager::open_com_file(VskFilePtr& file, VskString device, const VskString& params)
{
    vsk_upper(device);

    if (device == "COM")
        device = "COM1";

    // RS-232C 通信ファイルを開く
    // NOTE: 管理者権限が必要かもしれません
    HANDLE hComFile = ::CreateFileA(
        device.c_str(),                 // COM1, COM2, or COM3
        GENERIC_READ | GENERIC_WRITE,   // 読み書き可能
        0,                              // 共有モードなし
        NULL,                           // セキュリティ属性
        OPEN_EXISTING,                  // 既存のデバイスを開く
        0,                              // 非同期動作なし
        NULL                            // テンプレートなし
    );
    if (hComFile == INVALID_HANDLE_VALUE)
        return vsk_error_from_last_error(::GetLastError());

    file = std::make_shared<VskWin32File>(hComFile, VskFile::MODE_DEFAULT, VskFile::TYPE_COM);
    file->set_com_params(params);
    return VSK_NO_ERROR;
}

bool VskWin32File::set_com_params(VskString params)
{
    // 空白を削除し、大文字にする
    auto str = params;
    mstr_replace_all(str, " ", "");
    mstr_replace_all(str, "\t", "");
    vsk_upper(str);

    // COMの設定を取得する
    DCB config = { sizeof(config) };
    if (!::GetCommState(m_hFile, &config))
    {
        mdbg_traceA("GetCommState failed: 0x%08lX\n", ::GetLastError());
        return false;
    }

    // COMポートの設定
    config.BaudRate = CBR_1200;      // ボーレート
    config.ByteSize = 7;             // データビット
    config.Parity   = ODDPARITY;     // パリティ
    config.StopBits = ONESTOPBIT;    // ストップビット

    // パラメータを取得する
    size_t ich = 0;
    for (auto ch : str)
    {
        switch (ich)
        {
        case 0:
            switch (ch) // パリティチェック
            {
            case 'E': config.Parity = EVENPARITY; break; // 偶数パリティ
            case 'O': config.Parity = ODDPARITY; break; // 奇数パリティ
            case 'N': config.Parity = NOPARITY; break; // パリティなし
            }
            break;
        case 1:
            switch (ch) // データビット
            {
            case '7': config.ByteSize = 7; break; // データビット7
            case '8': config.ByteSize = 8; break; // データビット8
            }
            break;
        case 2:
            switch (ch) // ストップビット
            {
            case '1': config.StopBits = ONESTOPBIT;     break; // 1ビット
            case '2': config.StopBits = ONE5STOPBITS;   break; // 1.5ビット
            case '3': config.StopBits = TWOSTOPBITS;    break; // 2ビット
            }
            break;
        case 3:
            switch (ch) // XON/XOFF制御
            {
            case 'X':
                config.fInX = config.fOutX = TRUE;
                config.XonChar = 0x11;  // XONキャラクタ
                config.XoffChar = 0x13; // XOFFキャラクタ
                break;
            case 'N':
                break;
            }
            break;
        case 4:
            switch (ch) // SI/SO制御
            {
            case 'S':
                config.fInX = config.fOutX = TRUE;
                config.XonChar = 0x0F;  // XONキャラクタ
                config.XoffChar = 0x0E; // XOFFキャラクタ
                break;
            case 'N':
                break;
            }
            break;
        }
        ++ich;
    }

    // パラメータを設定する
    if (!::SetCommState(m_hFile, &config))
    {
        mdbg_traceA("SetCommState failed: 0x%08lX\n", ::GetLastError());
        return false;
    }

    // タイムアウト設定
    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 5000;
    timeouts.ReadTotalTimeoutConstant = 5000;
    timeouts.ReadTotalTimeoutMultiplier = 1000;
    timeouts.WriteTotalTimeoutConstant = 5000;
    timeouts.WriteTotalTimeoutMultiplier = 1000;

    if (!::SetCommTimeouts(m_hFile, &timeouts))
    {
        mdbg_traceA("SetCommTimeouts failed: 0x%08lX\n", ::GetLastError());
        return false;
    }

    return true;
}

void VskWin32File::close()
{
    if (m_hFile != INVALID_HANDLE_VALUE)
    {
        ::CloseHandle(m_hFile);
        m_hFile = INVALID_HANDLE_VALUE;
    }
}

bool VskWin32File::eof() const
{
    if (m_hFile == INVALID_HANDLE_VALUE)
        return true;
    DWORD dwPos = ::SetFilePointer(m_hFile, 0, NULL, FILE_CURRENT);
    DWORD dwSize = ::GetFileSize(m_hFile, nullptr);
    return dwPos == dwSize;
}

bool VskWin32File::get_pos(VskDword *poffset) const
{
    if (m_hFile == INVALID_HANDLE_VALUE)
        return false;
    *poffset = ::SetFilePointer(m_hFile, 0, NULL, FILE_CURRENT);
    return *poffset != 0xFFFFFFFF;
}

bool VskWin32File::set_pos(VskDword pos)
{
    if (m_hFile == INVALID_HANDLE_VALUE)
        return false;
    return ::SetFilePointer(m_hFile, pos, NULL, FILE_BEGIN) != 0xFFFFFFFF;
}

bool VskWin32File::get_size(VskDword *psize) const
{
    if (m_hFile == INVALID_HANDLE_VALUE)
        return false;
    *psize = ::GetFileSize(m_hFile, nullptr);
    return *psize != 0xFFFFFFFF;
}

VskError VskWin32File::read_bin(void *ptr, VskDword size)
{
    if (m_hFile == INVALID_HANDLE_VALUE)
        return VSK_ERR_FILE_NOT_OPEN;
    if (eof())
        return VSK_ERR_INPUT_PAST_END;
    DWORD cbRead;
    if (::ReadFile(m_hFile, ptr, size, &cbRead, nullptr) && cbRead == size)
        return VSK_NO_ERROR;
    return VSK_ERR_DISK_IO_ERROR;
}

int VskWin32File::get_x() const
{
    return m_x;
}

VskError VskWin32File::read_line(std::string& data)
{
    data.clear();

    for (;;)
    {
        // 1バイトごと読み込む
        VskByte byte;
        auto error = read_bin(&byte, 1);
        if (error)
            return error;
        if (byte == '\r')
            continue; // CRは読み捨て
        if (byte == '\n')
            break; // LFは改行
        data += byte;
    }

    return VSK_NO_ERROR;
}

VskError VskWin32File::write_bin(const void *ptr, VskDword size)
{
    if (m_hFile == INVALID_HANDLE_VALUE)
        return VSK_ERR_FILE_NOT_OPEN;
    DWORD cbWritten;
    if (!::WriteFile(m_hFile, ptr, size, &cbWritten, nullptr) || cbWritten != size)
        return VSK_ERR_DISK_IO_ERROR;
    auto pb = (const uint8_t *)ptr;
    for (VskDword ib = 0; ib < size; ++ib)
    {
        if (pb[ib] == '\n' || pb[ib] == '\r')
            m_x = 0;
        else
            ++m_x;
    }
    return VSK_NO_ERROR;
}

VskError VskWin32File::write_str(const std::string& str)
{
    for (auto ch : str)
    {
        if (ch == '\r')
            continue;
        if (ch == '\n')
            write_bin("\r\n", 2);
        else
            write_bin(&ch, 1);
    }
    return VSK_NO_ERROR;
}

VskError VskWin32File::write_line(const std::string& data)
{
    return write_str(data + "\r\n");
}

void VskWin32File::flush()
{
    if (m_hFile != INVALID_HANDLE_VALUE)
        ::FlushFileBuffers(m_hFile);
}

////////////////////////////////////////////////////////////////////////////////////

// VeySicK.exeのあるフォルダを返す
VskString vsk_get_root(void)
{
    // EXEファイルのパスと"README.txt"を使ってルートフォルダを探す
    char szPath[MAX_PATH];
    ::GetModuleFileNameA(nullptr, szPath, _countof(szPath));
    for (int i = 0; i < 3; ++i)
    {
        ::PathRemoveFileSpecA(szPath); // ファイル名の部分を削除
        ::PathAppendA(szPath, "README.txt");
        if (::PathFileExistsA(szPath)) // ファイルが存在するか？
        {
            ::PathRemoveFileSpecA(szPath); // ファイル名の部分を削除
            ::PathAddBackslashA(szPath); // バックスラッシュを追加
            return szPath;
        }
        ::PathRemoveFileSpecA(szPath); // ファイル名の部分を削除
    }
    // "README.txt"が見つからなかった。ユーザーが消したのなら本番環境のはず
    ::GetModuleFileNameA(nullptr, szPath, _countof(szPath));
    ::PathRemoveFileSpecA(szPath); // ファイル名の部分を削除
    return szPath;
}

// ドライブのパスを取得
VskString vsk_get_drive_path(int drive_no)
{
    if (0 <= drive_no && drive_no <= 10)
    {
        auto ret = vsk_get_root();
        ret += VskString("drive") + vsk_to_string(drive_no);
        ret += '\\';
        return ret;
    }
    return "";
}

VskString vsk_path_remove_filename(const VskString& pathname)
{
    char buf[MAX_PATH];
    ::lstrcpynA(buf, pathname.c_str(), MAX_PATH);
    PathRemoveFileSpecA(buf);
    return buf;
}

// 現在のディレクトリを取得する
VskString vsk_getcwd(void)
{
    char buf[MAX_PATH];
    ::GetCurrentDirectoryA(MAX_PATH, buf);
    ::PathAddBackslashA(buf);
    return buf;
}

// ディレクトリを変更する
VskError vsk_chdir(const char *dirname)
{
    if (!::SetCurrentDirectoryA(dirname))
    {
        auto error = ::GetLastError();
        mdbg_traceA("%s: %d\n", dirname, error);
        return VSK_ERR_BAD_OPERATION;
    }
    return VSK_NO_ERROR;
}

// ディレクトリを作成する
VskError vsk_mkdir(const char *dirname)
{
    if (!::CreateDirectoryA(dirname, nullptr))
    {
        auto error = ::GetLastError();
        mdbg_traceA("%s: %d\n", dirname, error);
        return VSK_ERR_BAD_OPERATION;
    }
    return VSK_NO_ERROR;
}

// 空のディレクトリを削除する
VskError vsk_rmdir(const char *dirname)
{
    if (!::RemoveDirectoryA(dirname))
    {
        auto error = ::GetLastError();
        mdbg_traceA("%s: %d\n", dirname, error);
        return VSK_ERR_BAD_OPERATION;
    }
    return VSK_NO_ERROR;
}

// ファイルを削除する
VskError vsk_delete_file(const char *filename)
{
    if (!::DeleteFileA(filename))
    {
        auto error = ::GetLastError();
        mdbg_traceA("%s: %d\n", filename, error);
        return VSK_ERR_BAD_OPERATION;
    }
    return VSK_NO_ERROR;
}

// 子プロセスを作成する
bool vsk_child(const char *str)
{
    char szComSpec[MAX_PATH];
    if (!::GetEnvironmentVariableA("COMSPEC", szComSpec, _countof(szComSpec)))
        lstrcpynA(szComSpec, "cmd.exe", _countof(szComSpec));

    auto cwd = vsk_getcwd();

    VskString cmdline = "/K " + VskString(str);
    auto ret = ::ShellExecuteA(nullptr, nullptr, szComSpec, cmdline.c_str(), cwd.c_str(), SW_SHOWNORMAL);
    return (INT_PTR)ret > 32;
}

// ファイル名群を取得する
VskError vsk_files_helper(std::vector<VskString>& files, VskString& device, VskString path)
{
    // ファイル記述子（file descriptor）をパースする
    VskFile::TYPE type;
    VskString raw_path;
    if (!vsk_parse_file_descriptor(path, type, device, raw_path))
        return VSK_ERR_FILE_NOT_FOUND;

    path = raw_path;
    if (::PathIsDirectoryA(path.c_str()))
    {
        if (path.size() && path[path.size() - 1] != '\\' && path[path.size() - 1] != '/')
            path += '\\';
        path += "*";
    }

    // 列挙を開始
    WIN32_FIND_DATAA find;
    HANDLE hFind = ::FindFirstFileA(path.c_str(), &find);
    if (hFind == INVALID_HANDLE_VALUE)
        return VSK_ERR_FILE_NOT_FOUND;

    do
    {
        // "." or ".."を無視する
        if (lstrcmpiA(find.cFileName, ".") == 0 || lstrcmpiA(find.cFileName, "..") == 0)
            continue;

        // ファイル名を取得
        VskString item;
        if (find.cAlternateFileName[0])
            item = find.cAlternateFileName;
        else
            item = find.cFileName;

        // フォルダならファイル名の最後にスラッシュを付ける
        if (find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            item += '/';

        // filesに追加
        files.push_back(item);
    } while (::FindNextFileA(hFind, &find));

    // 後始末
    ::FindClose(hFind);

    return VSK_NO_ERROR;
}

// ファイル名群を取得する
VskError vsk_files_helper(std::vector<VskString>& files, VskString& device, VskInt drive_no)
{
    // 列挙の準備
    return vsk_files_helper(files, device, vsk_get_drive_path(drive_no));
}

// スラッシュをバックスラッシュに置き換える
void vsk_replace_slashes(VskString& descriptor)
{
#ifdef _WIN32 // Windowsのみ
    VskString ret;
    VskString& str = descriptor;
    bool was_lead = false;
    for (size_t ich = 0; ich < str.size(); ++ich)
    {
        if (was_lead)
        {
            was_lead = false;
            continue;
        }
#ifdef JAPAN
        // SJISの全角文字は特別な処理が必要
        if (vsk_is_sjis_code(str[ich], str.c_str()[ich + 1]))
        {
            was_lead = true;
            continue;
        }
#endif
        if (str[ich] == '/')
            str[ich] = '\\';
    }
#endif // def _WIN32
}

// ファイル記述子（file descriptor）をパースする
bool vsk_parse_file_descriptor(VskString descriptor, VskFile::TYPE& type, VskString& device, VskString& raw_path)
{
    // 前後の空白を取り除く
    mstr_trim(descriptor, " \t\r\n");

    // 必要ならばスラッシュをバックスラッシュに置き換える
    vsk_replace_slashes(descriptor);

    // 普通のファイルと仮定する
    type = VskFile::TYPE_HOST_FILE;

    // コロンを探す
    auto i0 = descriptor.find(':');
    if (i0 == descriptor.npos)
    {
        // デバイス未定
        device.clear();
        raw_path = descriptor;
    }
    else
    {
        device = descriptor.substr(0, i0); // コロンまでの文字列を取得
        // "1:", "COM:", "LPT:" などを取り除いたのをraw_pathに代入
        raw_path = descriptor.substr(i0 + 1);
    }

    // 前後の空白を削除
    mstr_trim(raw_path, " \t\r\n");
    mstr_trim(device, " \t\r\n");

    vsk_upper(device); // 大文字にする

    if (device.size() == 1 && "A" <= device && device <= "Z") // これはドライブ文字
    {
        // Windowsのフルパスと仮定
        raw_path = descriptor;
        device.clear();
        return true;
    }

    if (!::PathIsRelativeA(raw_path.c_str()) || ::PathIsUNCA(raw_path.c_str()))
    {
        // Windowsのフルパス
        raw_path = descriptor;
        device.clear();
        return true;
    }

    // 空文字列かドライブ番号か？
    if (device.empty() || (device.size() == 1 && "0" <= device && device <= "9") || device == "10")
    {
        // raw_pathの先頭にスラッシュ群があれば取り除く
        while (raw_path.size() && (raw_path[0] == '\\' || raw_path[0] == '/'))
            raw_path = raw_path.substr(1);

        // ドライブパスを先頭に追加
        if (device.empty())
            raw_path = vsk_getcwd() + raw_path;
        else
            raw_path = vsk_get_drive_path(std::atoi(device.c_str())) + raw_path;

        // バックスラッシュを取り除く
        if (raw_path.size() && raw_path[raw_path.size() - 1] == '\\')
            raw_path.resize(raw_path.size() - 1);

        return true;
    }

    if (device == "COM")
        device = "COM1";

    if (device == "COM1" || device == "COM2" || device == "COM3") // RS-232C 通信ファイル
    {
        type = VskFile::TYPE_COM;
        return true;
    }
    if (device == "SCRN") // スクリーン
    {
        type = VskFile::TYPE_SCREEN;
        return true;
    }
    if (device == "KYBD") // キーボード
    {
        type = VskFile::TYPE_KEYBOARD;
        return true;
    }
    if (device == "LPT") // ラインプリンタ
    {
        type = VskFile::TYPE_LINE_PRINTER;
        return true;
    }
    if (device == "CAS1" || device == "CAS2") // カセット
    {
        type = VskFile::TYPE_CASETTE;
        return true;
    }

    return false; // その他は無効とする
}

// 安全地帯のパスファイル名か？
bool vsk_is_safe_zone_pathname(VskString pathname, bool for_write)
{
    // 書き込み用でなければ許可
    if (!for_write)
        return true;

    // 前後の空白を取り除く
    mstr_trim(pathname, " \t\r\n");

    // \\?\ を取り除く
    if (pathname.find("\\\\?\\") == 0)
        pathname = pathname.substr(4);

    // フルパスの大文字にする
    char szPath2[MAX_PATH];
    GetFullPathNameA(pathname.c_str(), _countof(szPath2), szPath2, NULL);
    ::CharUpperA(szPath2);
    pathname = szPath2;

    // EXEファイルのフォルダを取得
    auto root_path = vsk_get_root();
    ::CharUpperA(&root_path[0]);

    // EXEファイルのフォルダ内部にあるか？
    return pathname.find(root_path) == 0;
}

// Shiftキーが押されているか？
bool vsk_is_shift_pressed(void)
{
    return ::GetKeyState(VK_SHIFT) < 0;
}

// Ctrlキーが押されているか？
bool vsk_is_ctrl_pressed(void)
{
    return ::GetKeyState(VK_CONTROL) < 0;
}

// Altキーが押されているか？
bool vsk_is_alt_pressed(void)
{
    return ::GetKeyState(VK_MENU) < 0;
}

// キーが押されているか？
bool vsk_is_pressed(int vk)
{
    return ::GetKeyState(vk) < 0;
}

// キーボード情報（ASCII文字から仮想キーへの写像に、Shiftキーの状態を加えたもの）
static VskWord vsk_keyboard_info_0[2][256]; // character to virtual key
// キーボード情報（仮想キーからASCII文字への写像に、Shiftキーの状態を加えたもの）
static VskWord vsk_keyboard_info_1[2][256]; // virtual key to character

// キーボード情報を初期化
static void vsk_init_keyboard_info(void)
{
    static bool s_init = false;
    if (s_init)
        return;
    s_init = true;
    std::memset(&vsk_keyboard_info_0, 0, sizeof(vsk_keyboard_info_0));
    std::memset(&vsk_keyboard_info_1, 0, sizeof(vsk_keyboard_info_1));
    for (int ch = 0; ch < 256; ++ch)
    {
        WORD w = ::VkKeyScan(ch);
        bool shift = (HIBYTE(w) & 1);
        vsk_keyboard_info_0[shift][ch] = LOBYTE(w);
        vsk_keyboard_info_1[shift][LOBYTE(w)] = VskByte(ch);
    }
}

// 仮想キーを文字コードに変換する
VskByte vsk_map_key_code(VskWord key, bool shift, bool ctrl, bool caps)
{
    vsk_init_keyboard_info();

    if (ctrl)
    {
        if (('A' <= key) && (key <= 'Z'))
        {
            return key - 0x40;
        }
        return 0;
    }
    else if (shift)
    {
        if (('A' <= key) && (key <= 'Z'))
        {
            if (caps)
                return VskByte(vsk_tolower(VskByte(key)));
            else
                return VskByte(key);
        }
        return (VskByte)vsk_keyboard_info_1[shift][key];
    }
    else
    {
        if (('A' <= key) && (key <= 'Z'))
        {
            if (caps)
                return VskByte(key);
            else
                return VskByte(vsk_tolower(VskByte(key)));
        }
        if (('0' <= key) && (key <= '9'))
            return VskByte(key);
        switch (key)
        {
        case VK_UP:             return 0x1E;
        case VK_DOWN:           return 0x1F;
        case VK_LEFT:           return 0x1D;
        case VK_RIGHT:          return 0x1C;
        case VK_BACK:           return 0x7F;
        case VK_DELETE:         return 0x08;
        case VK_HOME:           return 0x0C;
        case VK_END:            return 0x01;
        case VK_PRIOR:          return 0xF9;
        case VK_NEXT:           return 0xF8;
        case VK_TAB:            return 0x09;
        case VK_ESCAPE:         return 0x1B;
        case VK_INSERT:         return 0x12;
        case VK_RETURN:         return 0x0D;
        case VK_ADD:            return 0x3B;
        case VK_SUBTRACT:       return 0x2D;
        case VK_MULTIPLY:       return 0x2A;
        case VK_DIVIDE:         return 0x2F;
        case VK_DECIMAL:        return 0x2E;
        default:                return (VskByte)vsk_keyboard_info_1[shift][key];
        }
    }
} // vsk_map_key_code

// 入力ポートの値を取得
VskInt vsk_inport_8801(VskInt port)
{
    // キーボード情報を初期化
    vsk_init_keyboard_info();

    // キーボードの状態を取得
    VskInt ret = 0;
    int ibit = 0;
    switch (port)
    {
    case 0x00: // ポート 0
        if (!vsk_is_pressed(VK_NUMPAD0)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD1)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD2)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD3)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD4)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD5)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD6)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD7)) ret |= (1 << ibit); ++ibit;
        break;
    case 0x01: // ポート 1
        if (!vsk_is_pressed(VK_NUMPAD8)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD9)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_MULTIPLY)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_ADD)) ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_DECIMAL)) ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_RETURN)) ret |= (1 << ibit); ++ibit;
        break;
    case 0x02: // ポート 2
        if (!vsk_is_pressed(vsk_keyboard_info_0[1]['`'])) ret |= (1 << ibit); ++ibit; // VK_OEM_3
        if (!vsk_is_pressed('A')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('B')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('C')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('D')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('E')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('F')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('G')) ret |= (1 << ibit); ++ibit;
        break;
    case 0x03: // ポート 3
        if (!vsk_is_pressed('H')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('I')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('J')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('K')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('L')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('M')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('N')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('O')) ret |= (1 << ibit); ++ibit;
        break;
    case 0x04: // ポート 4
        if (!vsk_is_pressed('P')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('Q')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('R')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('S')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('T')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('U')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('V')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('W')) ret |= (1 << ibit); ++ibit;
        break;
    case 0x05: // ポート 5
        if (!vsk_is_pressed('X')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('Y')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('Z')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(vsk_keyboard_info_0[0]['['])) ret |= (1 << ibit); ++ibit; // VK_OEM_4
        if (!vsk_is_pressed(vsk_keyboard_info_0[0]['\\'])) ret |= (1 << ibit); ++ibit; // VK_OEM_5
        if (!vsk_is_pressed(vsk_keyboard_info_0[0][']'])) ret |= (1 << ibit); ++ibit; // VK_OEM_6
        if (!vsk_is_pressed(vsk_keyboard_info_0[0]['^'])) ret |= (1 << ibit); ++ibit; // VK_OEM_7
        if (!vsk_is_pressed(vsk_keyboard_info_0[0]['-'])) ret |= (1 << ibit); ++ibit; // VK_OEM_MINUS
        break;
    case 0x06: // ポート 6
        if (!vsk_is_pressed('0')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('1')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('2')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('3')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('4')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('5')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('6')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('7')) ret |= (1 << ibit); ++ibit;
        break;
    case 0x07: // ポート 7
        if (!vsk_is_pressed('8')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('9')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(vsk_keyboard_info_0[0][':'])) ret |= (1 << ibit); ++ibit; // VK_OEM_1
        if (!vsk_is_pressed(vsk_keyboard_info_0[0][';'])) ret |= (1 << ibit); ++ibit; // VK_OEM_PLUS
        if (!vsk_is_pressed(vsk_keyboard_info_0[0][','])) ret |= (1 << ibit); ++ibit; // VK_OEM_COMMA
        if (!vsk_is_pressed(vsk_keyboard_info_0[0]['.'])) ret |= (1 << ibit); ++ibit; // VK_OEM_PERIOD
        if (!vsk_is_pressed(vsk_keyboard_info_0[0]['/'])) ret |= (1 << ibit); ++ibit; // VK_OEM_2
        if (!vsk_is_pressed(vsk_keyboard_info_0[1]['_'])) ret |= (1 << ibit); ++ibit; // VK_OEM_102
        break;
    case 0x08: // ポート 8
        if (!vsk_is_pressed(VK_HOME)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_UP)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_RIGHT)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_DELETE)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_MENU)) ret |= (1 << ibit); ++ibit;
        if (!(vsk_is_pressed(VK_KANA) || vsk_is_pressed(VK_OEM_COPY))) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_SHIFT)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_CONTROL)) ret |= (1 << ibit); ++ibit;
        break;
    case 0x09: // ポート 9
        if (!(vsk_is_pressed(VK_CONTROL) && vsk_is_pressed('C'))) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F1)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F2)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F3)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F4)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F5)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_SPACE)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_ESCAPE)) ret |= (1 << ibit); ++ibit;
        break;
    case 0x0A: // ポート 10
        if (!vsk_is_pressed(VK_TAB)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_DOWN)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_LEFT)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_END)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_PRINT)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_SUBTRACT)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_DIVIDE)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_CAPITAL)) ret |= (1 << ibit); ++ibit;
        break;
    case 0x0B: // ポート 11
        if (!vsk_is_pressed(VK_PRINT)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NEXT)) ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        break;
    case 0x0C: // ポート 12
        if (!vsk_is_pressed(VK_F6)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F7)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F8)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F9)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F10)) ret |= (1 << ibit); ++ibit;
        if (!(vsk_is_pressed(VK_BACK) || (vsk_is_ctrl_pressed() && vsk_is_pressed('H')))) ret |= (1 << ibit); ++ibit;
        if (!(vsk_is_pressed(VK_INSERT) || (vsk_is_shift_pressed() && vsk_is_pressed(VK_DELETE)))) ret |= (1 << ibit); ++ibit;
        if (!(vsk_is_pressed(VK_DELETE) || (vsk_is_ctrl_pressed() && vsk_is_pressed('H')))) ret |= (1 << ibit); ++ibit;
        break;
    case 0x0D: // ポート 13
        if (!vsk_is_pressed(VK_CONVERT)) ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_KANJI)) ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        break;
    case 0x0E: // ポート 14
        if (!vsk_is_pressed(VK_RETURN)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_RETURN)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_LSHIFT)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_RSHIFT)) ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        break;
    default:
        // 未実装
        assert(0);
        break;
    }
    assert(ibit == 0 || ibit == 8);
    return ret;
}

// 入力ポートの値を取得
VskInt vsk_inport_9801(VskInt port)
{
    // キーボード情報を初期化
    vsk_init_keyboard_info();

    // キーボードの状態を取得
    VskInt ret = 0;
    int ibit = 0;
    switch (port)
    {
    case 0xE0:
        if (!vsk_is_pressed(VK_NUMPAD0)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD1)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD2)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD3)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD4)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD5)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD6)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD7)) ret |= (1 << ibit); ++ibit;
        break;
    case 0xE1:
        if (!vsk_is_pressed(VK_NUMPAD8)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NUMPAD9)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_MULTIPLY)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_ADD)) ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_DECIMAL)) ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_RETURN)) ret |= (1 << ibit); ++ibit;
        break;
    case 0xE2:
        if (!vsk_is_pressed(vsk_keyboard_info_0[1]['`'])) ret |= (1 << ibit); ++ibit; // VK_OEM_3
        if (!vsk_is_pressed('A')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('B')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('C')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('D')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('E')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('F')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('G')) ret |= (1 << ibit); ++ibit;
        break;
    case 0xE3:
        if (!vsk_is_pressed('H')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('I')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('J')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('K')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('L')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('M')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('N')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('O')) ret |= (1 << ibit); ++ibit;
        break;
    case 0xE4:
        if (!vsk_is_pressed('P')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('Q')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('R')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('S')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('T')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('U')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('V')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('W')) ret |= (1 << ibit); ++ibit;
        break;
    case 0xE5:
        if (!vsk_is_pressed('X')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('Y')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('Z')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(vsk_keyboard_info_0[0]['['])) ret |= (1 << ibit); ++ibit; // VK_OEM_4
        if (!vsk_is_pressed(vsk_keyboard_info_0[0]['\\'])) ret |= (1 << ibit); ++ibit; // VK_OEM_5
        if (!vsk_is_pressed(vsk_keyboard_info_0[0][']'])) ret |= (1 << ibit); ++ibit; // VK_OEM_6
        if (!vsk_is_pressed(vsk_keyboard_info_0[0]['^'])) ret |= (1 << ibit); ++ibit; // VK_OEM_7
        if (!vsk_is_pressed(vsk_keyboard_info_0[0]['-'])) ret |= (1 << ibit); ++ibit; // VK_OEM_MINUS
        break;
    case 0xE6:
        if (!vsk_is_pressed('0')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('1')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('2')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('3')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('4')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('5')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('6')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('7')) ret |= (1 << ibit); ++ibit;
        break;
    case 0xE7:
        if (!vsk_is_pressed('8')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed('9')) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(vsk_keyboard_info_0[0][':'])) ret |= (1 << ibit); ++ibit; // VK_OEM_1
        if (!vsk_is_pressed(vsk_keyboard_info_0[0][';'])) ret |= (1 << ibit); ++ibit; // VK_OEM_PLUS
        if (!vsk_is_pressed(vsk_keyboard_info_0[0][','])) ret |= (1 << ibit); ++ibit; // VK_OEM_COMMA
        if (!vsk_is_pressed(vsk_keyboard_info_0[0]['.'])) ret |= (1 << ibit); ++ibit; // VK_OEM_PERIOD
        if (!vsk_is_pressed(vsk_keyboard_info_0[0]['/'])) ret |= (1 << ibit); ++ibit; // VK_OEM_2
        if (!vsk_is_pressed(vsk_keyboard_info_0[1]['_'])) ret |= (1 << ibit); ++ibit; // VK_OEM_102
        break;
    case 0xE8:
        if (!vsk_is_pressed(VK_HOME)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_UP)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_RIGHT)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_DELETE)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_MENU)) ret |= (1 << ibit); ++ibit;
        if (!(vsk_is_pressed(VK_KANA) || vsk_is_pressed(VK_OEM_COPY))) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_SHIFT)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_CONTROL)) ret |= (1 << ibit); ++ibit;
        break;
    case 0xE9:
        if (!(vsk_is_pressed(VK_CONTROL) && vsk_is_pressed('C'))) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F1)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F2)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F3)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F4)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F5)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_SPACE)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_ESCAPE)) ret |= (1 << ibit); ++ibit;
        break;
    case 0xEA:
        if (!vsk_is_pressed(VK_TAB)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_DOWN)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_LEFT)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_END)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_PRINT)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_SUBTRACT)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_DIVIDE)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_CAPITAL)) ret |= (1 << ibit); ++ibit;
        break;
    case 0xEB:
        if (!vsk_is_pressed(VK_PRINT)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_NEXT)) ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        break;
    case 0xEC:
        if (!vsk_is_pressed(VK_F6)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F7)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F8)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F9)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_F10)) ret |= (1 << ibit); ++ibit;
        if (!(vsk_is_pressed(VK_BACK) || (vsk_is_ctrl_pressed() && vsk_is_pressed('H')))) ret |= (1 << ibit); ++ibit;
        if (!(vsk_is_pressed(VK_INSERT) || (vsk_is_shift_pressed() && vsk_is_pressed(VK_DELETE)))) ret |= (1 << ibit); ++ibit;
        if (!(vsk_is_pressed(VK_DELETE) || (vsk_is_ctrl_pressed() && vsk_is_pressed('H')))) ret |= (1 << ibit); ++ibit;
        break;
    case 0xED:
        if (!vsk_is_pressed(VK_CONVERT)) ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_KANJI)) ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        break;
    case 0xEE:
        if (!vsk_is_pressed(VK_RETURN)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_RETURN)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_LSHIFT)) ret |= (1 << ibit); ++ibit;
        if (!vsk_is_pressed(VK_RSHIFT)) ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        ret |= (1 << ibit); ++ibit;
        break;
    default:
        // 未実装
        assert(0);
        break;
    }
    assert(ibit == 0 || ibit == 8);
    return ret;
}

// 仮想キーからGRPH文字を取得する
VskByte vsk_map_grph_code(VskWord key)
{
    // キーボード情報を初期化
    vsk_init_keyboard_info();
    // Shiftキーが押されているか
    BOOL shift = vsk_is_shift_pressed();
    // キーに応じてGRPH文字を計算する
    switch (key)
    {
    case VK_NUMPAD0:        return 0x9A;
    case VK_NUMPAD1:        return 0x93;
    case VK_NUMPAD2:        return 0x8F;
    case VK_NUMPAD3:        return 0x92;
    case VK_NUMPAD4:        return 0xE1;
    case VK_NUMPAD5:        return 0xE2;
    case VK_NUMPAD6:        return 0xE3;
    case VK_NUMPAD7:        return 0x98;
    case VK_NUMPAD8:        return 0x91;
    case VK_NUMPAD9:        return 0x99;
    case VK_ADD:            return 0xE0;
    case VK_SUBTRACT:       return 0x9B;
    case VK_MULTIPLY:       return 0x95;
    case VK_DIVIDE:         return 0x90;
    case VK_DECIMAL:        return 0x9B;

    case '1':               return 0x93;
    case '2':               return 0x8F;
    case '3':               return 0x92;
    case '4':               return 0xE1;
    case '5':               return shift ? 0xE2 : 0xF2;
    case '6':               return shift ? 0xE3 : 0xF3;
    case '7':               return shift ? 0x98 : 0xF4;
    case '8':               return shift ? 0x91 : 0xF5;
    case '9':               return shift ? 0x99 : 0xF6;
    case '0':               return shift ? 0x9A : 0xF7;

    case 'A':               return 0x9E;
    case 'B':               return 0x84;
    case 'C':               return 0x82;
    case 'D':               return 0xE6;
    case 'E':               return 0xE4;
    case 'F':               return 0xE7;
    case 'G':               return 0xEC;
    case 'H':               return 0xED;
    case 'I':               return 0xE8;
    case 'J':               return 0xEA;
    case 'K':               return 0xEB;
    case 'L':               return 0x8E;
    case 'M':               return 0x86;
    case 'N':               return 0x85;
    case 'O':               return 0xE9;
    case 'P':               return 0x8D;
    case 'Q':               return 0x9C;
    case 'R':               return 0xE5;
    case 'S':               return 0x9F;
    case 'T':               return 0xEE;
    case 'U':               return 0xF0;
    case 'V':               return 0x83;
    case 'W':               return 0x9D;
    case 'X':               return 0x81;
    case 'Y':               return 0xEF;
    case 'Z':               return 0x80;

    case VK_SPACE:          return ' ';
    case VK_RETURN:         return '\r';
    default:
        // キーを分析
        if (key == vsk_keyboard_info_0[0][':']) // VK_OEM_1
            return shift ? 0x95 : 0x94;
        if (key == vsk_keyboard_info_0[0]['/']) // VK_OEM_2
            return shift ? 0x90 : 0x97;
        if (key == vsk_keyboard_info_0[1]['`']) // VK_OEM_3
            return 0x8A;
        if (key == vsk_keyboard_info_0[0]['[']) // VK_OEM_4
            return 0;
        if (key == vsk_keyboard_info_0[0]['\\']) // VK_OEM_5
            return 0xF1;
        if (key == vsk_keyboard_info_0[0][']']) // VK_OEM_6
            return 0;
        if (key == vsk_keyboard_info_0[0]['^']) // VK_OEM_7
            return 0x8B;
        if (key == vsk_keyboard_info_0[0][';']) // VK_OEM_PLUS
            return shift ? 0xE0 : 0x89;
        if (key == vsk_keyboard_info_0[0]['-']) // VK_OEM_MINUS
            return shift ? 0x96 : 0x8C;
        if (key == vsk_keyboard_info_0[0][',']) // VK_OEM_COMMA
            return shift ? 0x90 : 0x87;
        if (key == vsk_keyboard_info_0[0]['.']) // VK_OEM_PERIOD
            return shift ? 0x9B : 0x88;
        if (key == vsk_keyboard_info_0[1]['_']) // VK_OEM_102
            return 0;
        return 0;
    }
} // vsk_map_grph_code

////////////////////////////////////////////////////////////////////////////////////
// イメージ関連

// 4BPP用のBITMAPINFO
struct BITMAPINFO_4BPP : BITMAPINFO
{
    RGBQUAD bmiColorsExtra[(1 << 4) - 1];
};

// モノクロの色情報
static const VskWebColor vsk_colors_mono[2] =
{             //                       GRB
    0x000000, //  #0: Black         (&H000)
    0xFFFFFF, //  #1: White         (&HFFF)
};

// １バイト中のビット群を逆順にしたものを返す関数
VskByte vsk_reverse_byte(VskByte x)
{
    static const VskByte table[] =
    {
        0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
        0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
        0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
        0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
        0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
        0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
        0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
        0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
        0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
        0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
        0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
        0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
        0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
        0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
        0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
        0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
        0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
        0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
        0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
        0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
        0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
        0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
        0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
        0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
        0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
        0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
        0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
        0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
        0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
        0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
        0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
        0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
    };
    return table[x];
}

// XBMからビットの深さが1BPPのDIBビットマップを作成
VskImageHandle vsk_create_1bpp_image_from_xbm(int width, int height, const void *bits)
{
    assert(width % CHAR_BIT == 0);
    size_t size = width / CHAR_BIT * height;
    std::vector<VskByte> bytes;
    bytes.resize(size);
    memcpy(bytes.data(), bits, size);
    for (auto& byte : bytes)
        byte = vsk_reverse_byte(byte);
    return CreateBitmap(width, height, 1, 1, bytes.data());
}

// ビットの深さが1BPPのDIBビットマップを作成
VskImageHandle vsk_create_1bpp_image(int width, int height)
{
    BITMAPINFO_4BPP bmi;
    ZeroMemory(&bmi, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 1;
    size_t iColor = 0;
    bmi.bmiColors[iColor].rgbBlue       = vsk_web_color_blue(vsk_colors_mono[iColor]);
    bmi.bmiColors[iColor].rgbGreen      = vsk_web_color_green(vsk_colors_mono[iColor]);
    bmi.bmiColors[iColor].rgbRed        = vsk_web_color_red(vsk_colors_mono[iColor]);
    bmi.bmiColors[iColor].rgbReserved   = 0;
    ++iColor;
    bmi.bmiColors[iColor].rgbBlue       = vsk_web_color_blue(vsk_colors_mono[iColor]);
    bmi.bmiColors[iColor].rgbGreen      = vsk_web_color_green(vsk_colors_mono[iColor]);
    bmi.bmiColors[iColor].rgbRed        = vsk_web_color_red(vsk_colors_mono[iColor]);
    bmi.bmiColors[iColor].rgbReserved   = 0;
    ++iColor;
    bmi.bmiHeader.biClrUsed = DWORD(iColor);

    HDC hDC = CreateCompatibleDC(nullptr);
    LPVOID pvBits;
    HBITMAP hbm = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, &pvBits, nullptr, 0);
    DeleteDC(hDC);
    return hbm;
}

// ビットの深さが32BPPのDIBビットマップを作成
VskImageHandle vsk_create_32bpp_image(int width, int height, void **ppvBits)
{
    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    HDC hDC = CreateCompatibleDC(nullptr);
    LPVOID pvBits;
    HBITMAP hbm = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, &pvBits, nullptr, 0);
    if (ppvBits)
        *ppvBits = pvBits;
    DeleteDC(hDC);
    return hbm;
}

// ビットマップをクリップボードにコピーする
bool vsk_copy_image_to_clipboard(HWND hwnd, HBITMAP hBitmap)
{
    BITMAP bm;
    if (!GetObject(hBitmap, sizeof(bm), &bm))
    {
        assert(0);
        return false;
    }

    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = bm.bmWidth;
    bmi.bmiHeader.biHeight = bm.bmHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;

    SIZE_T cb = sizeof(BITMAPINFOHEADER) + bm.bmWidthBytes * bm.bmHeight;
    HANDLE hDIB = GlobalAlloc(GHND | GMEM_SHARE, cb);
    if (!hDIB)
    {
        assert(0);
        return false;
    }

    BYTE *pb = (BYTE *)GlobalLock(hDIB);
    if (!pb)
    {
        assert(0);
        GlobalFree(hDIB);
        return false;
    }

    CopyMemory(pb, &bmi, sizeof(BITMAPINFOHEADER));

    HDC hDC = CreateCompatibleDC(NULL);
    GetDIBits(hDC, hBitmap, 0, bm.bmHeight, pb + sizeof(BITMAPINFOHEADER), &bmi, DIB_RGB_COLORS);
    DeleteDC(hDC);

    GlobalUnlock(hDIB);

    BOOL bOK = FALSE;
    if (OpenClipboard(hwnd))
    {
        if (EmptyClipboard())
        {
            bOK = (SetClipboardData(CF_DIB, hDIB) != NULL);
            assert(bOK);
        }
        else
        {
            assert(0);
        }
        CloseClipboard();
    }
    else
    {
        assert(0);
    }

    if (!bOK)
        GlobalFree(hDIB);

    return !!bOK;
}

////////////////////////////////////////////////////////////////////////////////////
// VskImage

// VskImageの内部実装VskImageImpl
struct VskImageImpl
{
    VskImageHandle m_image = nullptr;
    BITMAP m_bm = { 0 };
};

// イメージのハンドル
VskImage::operator VskImageHandle() const
{
    return m_pimpl->m_image;
}

// コンストラクタ
VskImage::VskImage()
{
    m_pimpl = new VskImageImpl;
}

// コンストラクタ
VskImage::VskImage(VskImageHandle image)
{
    m_pimpl = new VskImageImpl;
    attach(image);
}

// デストラクタ
VskImage::~VskImage()
{
    destroy();
    delete m_pimpl;
}

// 幅（ピクセル単位）
int VskImage::width() const
{
    return m_pimpl->m_bm.bmWidth;
}

// 高さ（ピクセル単位）
int VskImage::height() const
{
    return m_pimpl->m_bm.bmHeight;
}

// ビットの深さ
int VskImage::bpp() const
{
    return m_pimpl->m_bm.bmBitsPixel;
}

// イメージの横幅（バイト数）
int VskImage::pitch() const
{
    return m_pimpl->m_bm.bmWidthBytes;
}

// イメージハンドルを取り付ける
void VskImage::attach(VskImageHandle image)
{
    destroy();
    if (GetObject(image, sizeof(m_pimpl->m_bm), &m_pimpl->m_bm))
        m_pimpl->m_image = image;
}

// イメージハンドルを取りはずす
VskImageHandle VskImage::detach()
{
    VskImageHandle old_image = m_pimpl->m_image;
    m_pimpl->m_image = nullptr;
    return old_image;
}

// イメージハンドルを破棄
void VskImage::destroy()
{
    if (m_pimpl->m_image)
    {
        DeleteObject(m_pimpl->m_image);
        m_pimpl->m_image = nullptr;
    }
}

// イメージのデータを取得する
VskByte *VskImage::bits(size_t offset)
{
    assert(m_pimpl->m_image);
    assert(m_pimpl->m_bm.bmBits);
    return reinterpret_cast<VskByte *>(m_pimpl->m_bm.bmBits) + offset;
}

// イメージのデータを取得する
const VskByte *VskImage::bits(size_t offset) const
{
    assert(m_pimpl->m_image);
    assert(m_pimpl->m_bm.bmBits);
    return reinterpret_cast<VskByte *>(m_pimpl->m_bm.bmBits) + offset;
}

// 座標(x, y)はイメージの内側か？
bool VskImage::inside(int x, int y) const
{
    return x >= 0 && y >= 0 && x < width() && y < height();
}

////////////////////////////////////////////////////////////////////////////////////
// Vsk1BppImage

// コンストラクタ
Vsk1BppImage::Vsk1BppImage()
{
}

// コンストラクタ
Vsk1BppImage::Vsk1BppImage(VskImageHandle image) : VskImage(image)
{
}

// コンストラクタ
Vsk1BppImage::Vsk1BppImage(int width, int height, const void *bits)
{
    attach(vsk_create_1bpp_image_from_xbm(width, height, bits));
}

////////////////////////////////////////////////////////////////////////////////////
// Vsk32BppImage

// コンストラクタ
Vsk32BppImage::Vsk32BppImage()
{
}

// コンストラクタ
Vsk32BppImage::Vsk32BppImage(VskImageHandle image) : VskImage(image)
{
}

// コンストラクタ
Vsk32BppImage::Vsk32BppImage(int width, int height)
{
    attach(vsk_create_32bpp_image(width, height, nullptr));
}

// ピクセルを取得
VskSystemColor Vsk32BppImage::get_pixel(int x, int y) const
{
    if (!inside(x, y))
        return 0;
    auto line = bits(y * pitch());
    return reinterpret_cast<const VskSystemColor&>(line[4 * x]);
}

// ピクセルをセット
void Vsk32BppImage::set_pixel(int x, int y, VskSystemColor color)
{
    if (!inside(x, y))
        return;
    auto line = bits(y * pitch());
    reinterpret_cast<VskSystemColor&>(line[4 * x]) = color;
}

// イメージをクリアする
void Vsk32BppImage::clear()
{
    auto pdw = reinterpret_cast<VskDword *>(bits());
    auto cdw = width() * height();
    while (cdw-- > 0)
        *pdw++ = 0;
}

////////////////////////////////////////////////////////////////////////////////////
// VskWin32App --- Win32アプリのクラス

struct VskWin32App : VskObject
{
    VskMachineState m_state;                    // マシン状態
    HINSTANCE m_hInst = nullptr;                // アプリのインスタンス ハンドル
    HWND m_hWnd = nullptr;                      // メインウィンドウのハンドル
    MImageViewEx<true> m_imageView;             // イメージを表示するためのコントロール
    BOOL m_bShowCursor = TRUE;                  // マウスカーソルを表示するか？
    HIMC m_hIMC = nullptr;                      // 日本語入力のハンドル
    char m_filename[MAX_PATH] = "";             // BASICプログラムのファイル名
    char m_disk_images[10][MAX_PATH] = { "" };  // ディスク イメージ群
    char m_disk_folders[10][MAX_PATH] = { "" }; // ディスク フォルダー群
    HANDLE m_hWorkingThread = nullptr;          // 仕事をするスレッドのハンドル
    VskSettings m_settings;                     // 設定

    VskWin32App();
    bool init_app(void *hInst, int argc, WCHAR **argv, int nCmdShow);
    void exit_app();
    int run();
    void error(const _TCHAR *msg);

protected:
    void render();
    void OnIdle();
    bool do_load(HWND hwnd, const char *file, bool do_run);
    bool do_save(HWND hwnd, const char *file, bool protect);
    void show_popup_menu(HWND hwnd, INT iSubMenu);
    void start_stop_timers(HWND hwnd, bool do_start);
    VskString get_disk_image(HWND hwnd, int number);
    VskString get_drive_folder(HWND hwnd, int number);
    VskString load_string(int id);
    void reset_settings();
    bool load_settings();
    bool save_settings();
    void ime_on_off_real(bool on);
    void update_caret_position();

protected:
    // メッセージ ハンドラ
    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
    void OnDestroy(HWND hwnd);
    void OnMove(HWND hwnd, int x, int y);
    void OnSize(HWND hwnd, UINT state, int cx, int cy);
    void OnTimer(HWND hwnd, UINT id);
    void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
    void OnInitMenuPopup(HWND hwnd, HMENU hMenu, UINT item, BOOL fSystemMenu);
    BOOL OnEraseBkgnd(HWND hwnd, HDC hdc);
    void OnPaint(HWND hwnd);
    void OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);
    void OnKeyLocked(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);
    void OnSysKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);
    void OnChar(HWND hwnd, TCHAR ch, int cRepeat);
    void OnSysChar(HWND hwnd, TCHAR ch, int cRepeat);
    BOOL OnSetCursor(HWND hwnd, HWND hwndCursor, UINT codeHitTest, UINT msg);
    void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
    void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
    void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
    void OnRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
    void OnRButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
    void OnContextMenu(HWND hwnd, HWND hwndContext, UINT xPos, UINT yPos);
    void OnZoom(HWND hwnd, INT nZoom);
    void OnAbout(HWND hwnd);
    bool OnLoad(HWND hwnd, bool do_run);
    bool OnSave(HWND hwnd);
    bool OnSaveAs(HWND hwnd);
    void OnEjectDisk(HWND hwnd, int number);
    void OnDiskImage(HWND hwnd, int number);
    void OnDriveFolder(HWND hwnd, int number);

    void OnCopy(HWND hwnd);
    void OnPaste(HWND hwnd);
    void OnOpenReadMe(HWND hwnd);
    void OnScreenshot(HWND hwnd, BOOL bFile);
    void OnSettings(HWND hwnd);

    // ウィンドウプロシージャ
    static LRESULT CALLBACK
    WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // ウィンドウプロシージャの仮想関数
    virtual LRESULT CALLBACK
    WndProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

VskWin32App *vsk_pMainWnd = nullptr;

#define VSK_APP() vsk_pMainWnd

// アプリを終了する
void vsk_app_quit(void)
{
    // スレッドが違うかもしれないので、PostMessageを経由
    ::PostMessage(VSK_APP()->m_hWnd, WM_DESTROY, 0, 0);
}

// コンストラクタ
VskWin32App::VskWin32App()
{
    // ポインタを保持する
    vsk_pMainWnd = this;
}

// 設定をリセットする
void VskWin32App::reset_settings()
{
    m_settings.reset();
}

// 設定を読み込む
bool VskWin32App::load_settings()
{
    if (!m_settings.load())
        return false;

    return true;
}

// 設定を保存する
bool VskWin32App::save_settings()
{
    return m_settings.save();
}

// 終了フラグ
bool vsk_exiting = false;

// 仕事をするスレッド
static DWORD WINAPI vsk_working_thread(LPVOID arg)
{
    // ループ
    while (!vsk_exiting)
    {
        vsk_lock();
        if (vsk_machine)
            vsk_step();
        vsk_unlock();
    }

    return 0;
}

// WM_CREATE
// ウィンドウ作成時の処理
BOOL VskWin32App::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
    // ウィンドウ ハンドルをセット
    m_hWnd = hwnd;
    m_imageView.m_hWnd = hwnd;

    // アプリオブジェクトをウィンドウハンドルに関連付ける
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    // マシンと接続できなければ失敗
    if (!vsk_connect_machine(&m_state, &m_settings, true))
        return FALSE; // 失敗

    // テストパターンを表示。
    vsk_machine->test_pattern(0);

    // IMEを一時的に無効化する。
    HIMC hIMC = ::ImmGetContext(hwnd);
    ::ImmAssociateContext(hwnd, nullptr);
    ::ImmDestroyContext(hIMC);
    m_hIMC = ::ImmCreateContext();

    // タイマーを開始
    start_stop_timers(hwnd, true);

    // 可能ならばドライブ 1を現在のディレクトリにする
    auto path = vsk_get_drive_path(1);
    if (::PathIsDirectoryA(path.c_str()))
        ::SetCurrentDirectoryA(path.c_str());

#ifndef VSK_SINGLE_THREAD
    // 別スレッドで処理
    m_hWorkingThread = ::CreateThread(nullptr, 0, vsk_working_thread, this, 0, nullptr);
#endif

    return TRUE; // 成功
}

#define MYWM_IME_ON_OFF (WM_USER + 100)

// IMEをオンまたはオフにする(メインスレッドにゆだねる)
void vsk_ime_on_off(bool on)
{
    HWND hwnd = VSK_APP()->m_hWnd;
    ::PostMessage(hwnd, MYWM_IME_ON_OFF, (BOOL)on, 0);
}

// IMEをオンまたはオフにする(本物、実体)
void VskWin32App::ime_on_off_real(bool on)
{
    mdbg_traceA("ime_on_off_real: %d\n", on);
    if (on)
    {
        ::ImmAssociateContext(m_hWnd, m_hIMC);
        ::ImmSetOpenStatus(m_hIMC, TRUE);
        DWORD dwConversion, dwSentence;
        ::ImmGetConversionStatus(m_hIMC, &dwConversion, &dwSentence);
        ::ImmSetConversionStatus(m_hIMC, IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE, dwSentence);
        update_caret_position();
    }
    else
    {
        ::ImmSetOpenStatus(m_hIMC, FALSE);
        ::ImmAssociateContext(m_hWnd, nullptr);
    }
    m_state.m_kanji_mode = on;
}

// WM_DESTROY
// ウィンドウの破棄前の処理
void VskWin32App::OnDestroy(HWND hwnd)
{
#ifndef VSK_SINGLE_THREAD
    if (m_hWorkingThread)
    {
        ::CloseHandle(m_hWorkingThread);
        m_hWorkingThread = nullptr;
    }
#endif

    // 行儀よくIMEの後始末。
    ::ImmAssociateContext(hwnd, nullptr);
    ImmDestroyContext(m_hIMC);
    m_hIMC = nullptr;

    // タイマーを破棄
    start_stop_timers(hwnd, false);

    // マシンとの接続を切断
    vsk_connect_machine(&m_state, &m_settings, false);

    // MImageViewExの終了処理
    m_imageView.OnDestroy(hwnd);

    // WM_QUITメッセージを投函し、メッセージループを終了
    PostQuitMessage(0);
}

// タイマーを開始または停止
void VskWin32App::start_stop_timers(HWND hwnd, bool do_start)
{
    if (do_start)
    {
        // タイマーを開始
        ::SetTimer(hwnd, VSK_TIMER_ID_BLINK, m_state.m_blink_interval, nullptr);
        ::SetTimer(hwnd, VSK_TIMER_ID_FPS_CHECK, VSK_FPS_CHECK_INTERVAL, nullptr);
    }
    else
    {
        // タイマーを破棄
        ::KillTimer(hwnd, VSK_TIMER_ID_BLINK);
        ::KillTimer(hwnd, VSK_TIMER_ID_FPS_CHECK);
    }
}

// WM_MOVE
void VskWin32App::OnMove(HWND hwnd, int x, int y)
{
    if (!::IsZoomed(hwnd) && !::IsIconic(hwnd))
    {
        // 位置を覚えておく
        RECT rc;
        ::GetWindowRect(hwnd, &rc);
        VSK_SETTINGS()->m_x = rc.left;
        VSK_SETTINGS()->m_y = rc.top;
    }
}

// WM_SIZE
// ウィンドウのサイズが変化した
void VskWin32App::OnSize(HWND hwnd, UINT state, int cx, int cy)
{
    // サイズを覚えておく
    VSK_SETTINGS()->m_zoomed = ::IsZoomed(hwnd);
    if (!::IsZoomed(hwnd) && !::IsIconic(hwnd))
    {
        RECT rc;
        ::GetWindowRect(hwnd, &rc);
        VSK_SETTINGS()->m_cx = rc.right - rc.left;
        VSK_SETTINGS()->m_cy = rc.bottom - rc.top;
    }

    // 再描画
    InvalidateRect(hwnd, nullptr, TRUE);
}

// ボーダーカラーをセット
void vsk_reset_border_color(int border_color)
{
    if (border_color == -1)
    {
        VSK_APP()->m_imageView.SetBorderColor(CLR_INVALID);
        return;
    }

    VskWebColor web_color;
    if (!vsk_web_color_from_digital_8_color_code(web_color, border_color))
        return;

    auto red = vsk_web_color_red(web_color);
    auto green = vsk_web_color_green(web_color);
    auto blue = vsk_web_color_blue(web_color);
    VSK_APP()->m_imageView.SetBorderColor(RGB(red, green, blue));
}

// キャレット位置を更新
void VskWin32App::update_caret_position()
{
    HIMC hImc = ::ImmGetContext(m_hWnd);
    if (!hImc)
        return;

    double x = m_state.m_text_wider ? m_state.m_caret_x * 16 : m_state.m_caret_x * 8;
    double y = m_state.m_text_longer ? m_state.m_caret_y * 20 : m_state.m_caret_y * 16;
    m_imageView.image_to_client(x, y);

    COMPOSITIONFORM comp_form = { CFS_POINT };
    comp_form.ptCurrentPos = { LONG(x), LONG(y) };

    ::ImmSetCompositionWindow(hImc, &comp_form);
    ::ImmReleaseContext(m_hWnd, hImc);
}

/// マウスクリックでキャレット位置を移動する
void vsk_caret_move_by_mouse_click(int text_x, int text_y)
{
    if (VSK_SETTINGS()->m_move_caret_by_mouse_click)
    {
        VSK_STATE()->m_caret_x = text_x;
        VSK_STATE()->m_caret_y = text_y;
        vsk_machine->fix_caret_pos(false); // キャレット位置を補正
        VSK_STATE()->m_blink_flag = 3; // すぐに表示
    }
}

// マウスの位置と表示・非表示
void vsk_set_mouse_pos(int x0, int y0, bool visible)
{
    POINT pt;
    ::GetCursorPos(&pt);
    ::ScreenToClient(VSK_APP()->m_hWnd, &pt);

    double cx0 = x0, cy0 = y0;
    VSK_APP()->m_imageView.image_to_client(cx0, cy0);

    if (x0 != -1)
        pt.x = LONG(cx0);

    if (y0 != -1)
    {
        pt.y = LONG(cy0);
        if (VSK_STATE()->m_screen_height == 200)
            pt.y *= 2;
    }

    ::ClientToScreen(VSK_APP()->m_hWnd, &pt);
    ::SetCursorPos(pt.x, pt.y);

    VSK_APP()->m_bShowCursor = visible;
    ::SetCursor(visible ? ::LoadCursor(nullptr, IDC_ARROW) : nullptr);
}

// マウスをクリッピングする
void vsk_mouse_clip(int x0, int y0, int x1, int y1)
{
    if (x0 == -1 && y0 == -1)
    {
        ::ClipCursor(NULL);
        return;
    }

    double cx0 = x0, cy0 = y0, cx1 = x1, cy1 = y1;
    VSK_APP()->m_imageView.image_to_client(cx0, cy0);
    VSK_APP()->m_imageView.image_to_client(cx1, cy1);

    if (VSK_STATE()->m_screen_height == 200)
    {
        cy0 *= 2;
        cy1 *= 2;
    }

    POINT pt0 = { LONG(cx0), LONG(cy0) };
    POINT pt1 = { LONG(cx1), LONG(cy1) };

    ::MapWindowPoints(VSK_APP()->m_hWnd, nullptr, &pt0, 1);
    ::MapWindowPoints(VSK_APP()->m_hWnd, nullptr, &pt1, 1);
    RECT rc = { pt0.x, pt0.y, pt1.x + 1, pt1.y + 1 };
    ::ClipCursor(&rc);
}

// WM_TIMER
// タイマー処理
void VskWin32App::OnTimer(HWND hwnd, UINT id)
{
    if (id == VSK_TIMER_ID_BLINK) // キャレットの点滅処理
    {
        // 0, 1, 2, 3, 0, 1, 2, 3, ... を繰り返す
        m_state.m_blink_flag++;
        m_state.m_blink_flag %= 4;

        // キャレット位置に応じて処理
        update_caret_position();
    }
    else if (id == VSK_TIMER_ID_FPS_CHECK) // FPSチェック処理
    {
        // FPSに関するテキストを構築
        char szText[64];
        UINT nFPS = s_dwFpsCounter / (VSK_FPS_CHECK_INTERVAL / VSK_ONE_SECOND);
        if (m_filename[0]) // ファイルがあるか?
        {
            StringCchPrintfA(szText, _countof(szText), VEYSICK_TITLE_FPS_WITH_FILE,
                             ::PathFindFileNameA(m_filename), nFPS);
        }
        else // ファイルがない?
        {
            StringCchPrintfA(szText, _countof(szText), VEYSICK_TITLE_FPS, nFPS);
        }
        // メインウィンドウのタイトルにテキストをセット
        ::SetWindowTextA(hwnd, szText);
        // FPSカウントをクリア
        s_dwFpsCounter = 0;
    }
}

// WM_MOUSEMOVE
void VskWin32App::OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
    double x0 = x, y0 = y;
    if (!m_imageView.client_to_image(x0, y0))
        return;

    vsk_mouse(int(x0), int(y0), 0, 0);
}

// WM_LBUTTONDOWN / WM_LBUTTONDBLCLK
void VskWin32App::OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
    double x0 = x, y0 = y;
    if (!m_imageView.client_to_image(x0, y0))
        return;

    int text_x, text_y;
    if (!vsk_machine->hit_text_char(text_x, text_y, int(x0), int(y0)))
        return;

    vsk_pen(text_x, text_y, true);
    vsk_mouse(int(x0), int(y0), +1, 0);
}

// WM_LBUTTONUP
void VskWin32App::OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
    double x0 = x, y0 = y;
    if (!m_imageView.client_to_image(x0, y0))
    {
        vsk_pen(-1, -1, false);
        return;
    }

    int text_x, text_y;
    if (!vsk_machine->hit_text_char(text_x, text_y, int(x0), int(y0)))
    {
        vsk_pen(-1, -1, false);
        return;
    }

    vsk_pen(text_x, text_y, false);
    vsk_mouse(int(x0), int(y0), -1, 0);
}

// ポップアップ メニューを表示する
void VskWin32App::show_popup_menu(HWND hwnd, INT iSubMenu)
{
    HMENU hMenu = ::LoadMenu(m_hInst, MAKEINTRESOURCE(IDR_POPUPMENU));
    HMENU hSubMenu = ::GetSubMenu(hMenu, iSubMenu);

    ::SetForegroundWindow(hwnd);

    POINT pt;
    ::GetCursorPos(&pt);

    auto flags = TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON;
    INT nCmdID = (INT)::TrackPopupMenu(hSubMenu, flags, pt.x, pt.y, 0, hwnd, nullptr);

    ::PostMessage(hwnd, WM_NULL, 0, 0);

    if (nCmdID != 0 && nCmdID != -1)
        ::PostMessage(hwnd, WM_COMMAND, nCmdID, 0);

    ::DestroyMenu(hMenu);
}

// WM_RBUTTONDOWN / WM_RBUTTONDBLCLK
void VskWin32App::OnRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
    double x0 = x, y0 = y;
    if (!m_imageView.client_to_image(x0, y0))
    {
        return;
    }

    int text_x, text_y;
    if (!vsk_machine->hit_text_char(text_x, text_y, int(x0), int(y0)))
    {
        return;
    }

    vsk_mouse(int(x0), int(y0), 0, +1);
}

// WM_RBUTTONUP
void VskWin32App::OnRButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
    double x0 = x, y0 = y;
    if (!m_imageView.client_to_image(x0, y0))
    {
        return;
    }

    int text_x, text_y;
    if (!vsk_machine->hit_text_char(text_x, text_y, int(x0), int(y0)))
    {
        return;
    }

    if (!vsk_mouse(int(x0), int(y0), 0, -1))
    {
        // For WM_CONTEXTMENU
        FORWARD_WM_RBUTTONUP(hwnd, x, y, keyFlags, DefWindowProc);
    }
}

// WM_CONTEXTMENU
void VskWin32App::OnContextMenu(HWND hwnd, HWND hwndContext, UINT xPos, UINT yPos)
{
    show_popup_menu(hwnd, 0);
}

// WM_INITMENUPOPUP
// メニューをポップアップする前にメニューの表示を更新する
void VskWin32App::OnInitMenuPopup(HWND hwnd, HMENU hMenu, UINT item, BOOL fSystemMenu)
{
    // 貼り付け可能か？
    ::EnableMenuItem(hMenu, ID_PASTE_TEXT, (IsClipboardFormatAvailable(CF_TEXT) ? MF_ENABLED : MF_GRAYED));

    // 必要ならば、メニュー項目ID_MACHINE_8801, ID_MACHINE_9801のいずれかにチェックを付ける
    {
        bool bCheck8801 = vsk_machine->is_8801_mode();
        bool bCheck9801 = vsk_machine->is_9801_mode();
        ::CheckMenuItem(hMenu, ID_MACHINE_8801, (bCheck8801 ? MF_CHECKED : MF_UNCHECKED));
        ::CheckMenuItem(hMenu, ID_MACHINE_9801, (bCheck9801 ? MF_CHECKED : MF_UNCHECKED));
    }

    // 必要ならば、メニュー項目のID_GRPH_MODE, ID_SJIS_MODE, ID_JIS_MODEのいずれかにチェックを付ける
    {
        bool bCheckGRPH = vsk_machine->is_grph_mode();
        bool bCheckSJIS = vsk_machine->is_sjis_mode();
        bool bCheckJIS = vsk_machine->is_jis_mode();
        ::CheckMenuItem(hMenu, ID_GRPH_MODE, (bCheckGRPH ? MF_CHECKED : MF_UNCHECKED));
        ::CheckMenuItem(hMenu, ID_SJIS_MODE, (bCheckSJIS ? MF_CHECKED : MF_UNCHECKED));
        ::CheckMenuItem(hMenu, ID_JIS_MODE, (bCheckJIS ? MF_CHECKED : MF_UNCHECKED));
        bool bEnableJIS = !vsk_machine->is_8801_mode();
        ::EnableMenuItem(hMenu, ID_JIS_MODE, (bEnableJIS ? MF_ENABLED : MF_GRAYED));
    }

    // 必要ならば、メニュー項目ID_ZOOM_X1、ID_ZOOM_X2、ID_ZOOM_X3のいずれかにチェックを付ける
    {
        RECT rc;
        ::GetClientRect(hwnd, &rc);
        BOOL bCheckX1 = (rc.right == VSK_SCREEN_WIDTH && rc.bottom == VSK_SCREEN_HEIGHT);
        BOOL bCheckX2 = (rc.right == 2 * VSK_SCREEN_WIDTH && rc.bottom == 2 * VSK_SCREEN_HEIGHT);
        BOOL bCheckX3 = (rc.right == 3 * VSK_SCREEN_WIDTH && rc.bottom == 3 * VSK_SCREEN_HEIGHT);
        ::CheckMenuItem(hMenu, ID_ZOOM_X1, (bCheckX1 ? MF_CHECKED : MF_UNCHECKED));
        ::CheckMenuItem(hMenu, ID_ZOOM_X2, (bCheckX2 ? MF_CHECKED : MF_UNCHECKED));
        ::CheckMenuItem(hMenu, ID_ZOOM_X3, (bCheckX3 ? MF_CHECKED : MF_UNCHECKED));
    }

    // 必要ならば、メニュー項目ID_MAXIMIZEにチェックを付ける
    ::CheckMenuItem(hMenu, ID_MAXIMIZE, (IsZoomed(hwnd) ? MF_CHECKED : MF_UNCHECKED));

    // メニュー項目ID_ZOOM_X2, ID_ZOOM_X3 を有効化または無効化する
    {
        HMONITOR hMonitor = ::MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
        MONITORINFO mi = { sizeof(mi) };
        if (::GetMonitorInfoW(hMonitor, &mi))
        {
            INT cx = mi.rcWork.right - mi.rcWork.left;
            INT cy = mi.rcWork.bottom - mi.rcWork.top;

            BOOL bEnableX2 = (cx >= 2 * VSK_SCREEN_WIDTH && cy >= 2 * VSK_SCREEN_HEIGHT);
            BOOL bEnableX3 = (cx >= 3 * VSK_SCREEN_WIDTH && cy >= 3 * VSK_SCREEN_HEIGHT);
            ::EnableMenuItem(hMenu, ID_ZOOM_X2, (bEnableX2 ? MF_ENABLED : MF_GRAYED));
            ::EnableMenuItem(hMenu, ID_ZOOM_X3, (bEnableX3 ? MF_ENABLED : MF_GRAYED));
        }
        else
        {
            ::EnableMenuItem(hMenu, ID_ZOOM_X2, MF_ENABLED);
            ::EnableMenuItem(hMenu, ID_ZOOM_X3, MF_ENABLED);
        }
    }

    MENUITEMINFOA mii = { sizeof(mii), MIIM_TYPE, MFT_STRING };
    VskString filename;
    VskString str;

    // ディスクイメージ名・フォルダー名をセットする
    {
        int ids0[] = { ID_DRIVE1_IMAGE, ID_DRIVE2_IMAGE, ID_DRIVE3_IMAGE, ID_DRIVE4_IMAGE };
        int ids1[] = { ID_DRIVE1_FOLDER, ID_DRIVE2_FOLDER, ID_DRIVE3_FOLDER, ID_DRIVE4_FOLDER };
        assert(_countof(ids0) == _countof(ids1));
        for (int iDrive = 0; iDrive < _countof(ids0); ++iDrive)
        {
            // イメージ名をセットする。ついでにチェックを付けるか外す
            filename = get_disk_image(hwnd, iDrive + 1);
            if (PathIsDirectoryA(filename.c_str()))
            {
                str = load_string(IDS_OPEN_IMAGE) + " (";
                str += PathFindFileNameA(filename.c_str());
                str += ")";
                ::CheckMenuItem(hMenu, ids0[iDrive], MF_CHECKED);
            }
            else
            {
                str = load_string(IDS_OPEN_IMAGE);
                ::CheckMenuItem(hMenu, ids0[iDrive], MF_UNCHECKED);
            }
            mii.dwTypeData = const_cast<char *>(str.data());
            ::SetMenuItemInfoA(hMenu, ids0[iDrive], FALSE, &mii);

            // フォルダー名をセットする。ついでにチェックを付けるか外す
            filename = get_drive_folder(hwnd, iDrive + 1);
            if (PathIsDirectoryA(filename.c_str()))
            {
                str = load_string(IDS_FOLDER) + " (";
                str += PathFindFileNameA(filename.c_str());
                str += ")";
                ::CheckMenuItem(hMenu, ids1[iDrive], MF_CHECKED);
            }
            else
            {
                str = load_string(IDS_FOLDER);
                ::CheckMenuItem(hMenu, ids1[iDrive], MF_UNCHECKED);
            }
            mii.dwTypeData = const_cast<char *>(str.data());
            ::SetMenuItemInfoA(hMenu, ids1[iDrive], FALSE, &mii);
        }
    }
}

// ドライブ番号のディスク イメージのパスファイル名を取得
VskString VskWin32App::get_disk_image(HWND hwnd, int number)
{
    int iDrive = number - 1;
    assert(0 <= iDrive && iDrive < _countof(m_disk_images));
    if (m_disk_images[iDrive][0])
        return m_disk_images[iDrive];
    return "";
}

// ドライブ フォルダのパスファイル名を取得
VskString VskWin32App::get_drive_folder(HWND hwnd, int number)
{
    int iDrive = number - 1;
    assert(0 <= iDrive && iDrive < _countof(m_disk_images));
    if (m_disk_images[iDrive][0])
        return "";
    assert(0 <= iDrive && iDrive < _countof(m_disk_folders));
    auto filename = m_disk_folders[iDrive];
    if (filename[0] && PathIsDirectoryA(filename))
        return filename;
    char szPath[MAX_PATH];
    ::GetModuleFileNameA(nullptr, szPath, _countof(szPath));
    ::PathRemoveFileSpecA(szPath);
    ::PathRemoveBackslashA(szPath);
    return VskString(szPath) + "\\Drive" + std::to_string(iDrive + 1);
}

VskString VskWin32App::load_string(int id)
{
    char szText[512];
    szText[0] = 0;
    LoadStringA(m_hInst, id, szText, _countof(szText));
    return VskString(szText);
}

// ID_DRIVE1_EJECT, ID_DRIVE2_EJECT, ID_DRIVE3_EJECT, ID_DRIVE4_EJECT
void VskWin32App::OnEjectDisk(HWND hwnd, int number)
{
    int iDrive = number - 1;
    assert(0 <= iDrive && iDrive < _countof(m_disk_images));
    assert(0 <= iDrive && iDrive < _countof(m_disk_folders));
    m_disk_images[iDrive][0] = 0;
    m_disk_folders[iDrive][0] = 0;
}

// ID_DRIVE1_IMAGE, ID_DRIVE2_IMAGE, ID_DRIVE3_IMAGE, ID_DRIVE4_IMAGE
void VskWin32App::OnDiskImage(HWND hwnd, int number)
{
    // ファイルパス名
    char szFile[MAX_PATH];
    szFile[0] = 0;

    // ユーザーにファイルの場所を問い合わせる準備をする
    OPENFILENAMEA ofn = { sizeof(ofn), hwnd };
    ofn.lpstrFilter = "D88 Files (*.d88)\0*.d88\0\0";
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = _countof(szFile);
    ofn.lpstrTitle = "Load D88 disk image";
    ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST |
                OFN_PATHMUSTEXIST | OFN_ENABLESIZING;
    ofn.lpstrDefExt = ".d88";

    // 初期ディレクトリを指定
    char szDir[MAX_PATH];
    ::GetModuleFileNameA(nullptr, szDir, _countof(szDir));
    ::PathRemoveFileSpecA(szDir);
    ::PathAppendA(szDir, "FILES");
    if (!::PathIsDirectoryA(szDir))
        ::PathRemoveFileSpecA(szDir);
    ofn.lpstrInitialDir = szDir;

    // 問い合わせる
    if (!::GetOpenFileNameA(&ofn))
        return;

    // TODO:
}

// ID_DRIVE1_FOLDER, ID_DRIVE2_FOLDER, ID_DRIVE3_FOLDER, ID_DRIVE4_FOLDER
void VskWin32App::OnDriveFolder(HWND hwnd, int number)
{
    INT iDrive = number - 1;
    assert(0 <= iDrive && iDrive < _countof(m_disk_folders));

    // TODO: 初期位置を指定
    BROWSEINFOA bi = { hwnd };
    bi.ulFlags = BIF_RETURNONLYFSDIRS;
    auto pidlRet = SHBrowseForFolderA(&bi);
    if (!pidlRet)
        return;

    // ディスクを取り出す
    OnEjectDisk(hwnd, number);
    // ドライブ フォルダのパスファイル名を取得
    SHGetPathFromIDListA(pidlRet, m_disk_folders[iDrive]);
    // 後始末
    ILFree(pidlRet);
}

// ID_LOAD / ID_LOAD_RUN
bool VskWin32App::OnLoad(HWND hwnd, bool do_run)
{
    // ファイルパス名
    char szFile[MAX_PATH];
    szFile[0] = 0;

    // ユーザーにファイルの場所を問い合わせる準備をする
    OPENFILENAMEA ofn = { sizeof(ofn), hwnd };
    ofn.lpstrFilter = "BASIC Files (*.bas)\0*.bas\0Text Files (*.txt)\0*.txt\0";
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = _countof(szFile);
    ofn.lpstrTitle = "LOAD";
    ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST |
                OFN_PATHMUSTEXIST | OFN_ENABLESIZING;
    ofn.lpstrDefExt = ".bas";

    // 初期ディレクトリを指定
    char szDir[MAX_PATH];
    ::GetModuleFileNameA(nullptr, szDir, _countof(szDir));
    ::PathRemoveFileSpecA(szDir);
    ::PathAppendA(szDir, "FILES");
    if (!::PathIsDirectoryA(szDir))
        ::PathRemoveFileSpecA(szDir);
    ofn.lpstrInitialDir = szDir;

    // 問い合わせる
    if (!::GetOpenFileNameA(&ofn))
        return false;

    return do_load(hwnd, szFile, do_run);
}

bool VskWin32App::do_load(HWND hwnd, const char *file, bool do_run)
{
    lstrcpynA(m_filename, file, _countof(m_filename));
    return false; // 未実装
}

bool VskWin32App::do_save(HWND hwnd, const char *file, bool protect)
{
    lstrcpynA(m_filename, file, _countof(m_filename));
    return false; // 未実装
}

// ID_SAVE
bool VskWin32App::OnSave(HWND hwnd)
{
    if (!m_filename[0])
        return OnSaveAs(hwnd);
    return do_save(hwnd, m_filename, false);
}

// ID_SAVE_AS
bool VskWin32App::OnSaveAs(HWND hwnd)
{
    // ファイルパス名
    char szFile[MAX_PATH];
    szFile[0] = 0;

    // ユーザーにファイルの場所を問い合わせる準備をする
    OPENFILENAMEA ofn = { sizeof(ofn), hwnd };
    ofn.lpstrFilter = "BASIC Files (*.bas)\0*.bas\0";
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = _countof(szFile);
    ofn.lpstrTitle = "SAVE";
    ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST |
                OFN_PATHMUSTEXIST | OFN_ENABLESIZING | OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = ".bas";

    // 初期ディレクトリを指定
    char szDir[MAX_PATH];
    ::GetModuleFileNameA(nullptr, szDir, _countof(szDir));
    ::PathRemoveFileSpecA(szDir);
    ::PathAppendA(szDir, "FILES");
    if (!::PathIsDirectoryA(szDir))
        ::PathRemoveFileSpecA(szDir);
    ofn.lpstrInitialDir = szDir;

    // 問い合わせる
    if (!::GetSaveFileNameA(&ofn))
        return false;

    return do_save(hwnd, szFile, false);
}

// WM_COMMAND
// コマンドを実行する
void VskWin32App::OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case ID_EXIT: // アプリの終了
        ::DestroyWindow(hwnd);
        break;
    case ID_RESET: // リセット
        vsk_connect_machine(&m_state, &m_settings, false);
        vsk_connect_machine(&m_state, &m_settings, true);
        vsk_machine->test_pattern(0);
        break;
    case ID_MACHINE_8801: // 8801モード
        vsk_connect_machine(&m_state, &m_settings, false);
        m_settings.m_machine_mode = VSK_MACHINE_MODE_8801;
        vsk_connect_machine(&m_state, &m_settings, true);
        vsk_machine->test_pattern(0);
        break;
    case ID_MACHINE_9801: // 9801モード
        vsk_connect_machine(&m_state, &m_settings, false);
        m_settings.m_machine_mode = VSK_MACHINE_MODE_9801;
        vsk_connect_machine(&m_state, &m_settings, true);
        vsk_machine->test_pattern(0);
        break;
    case ID_LOAD: // 読み込む
        OnLoad(hwnd, false);
        break;
    case ID_LOAD_RUN: // 読み込んで実行
        OnLoad(hwnd, true);
        break;
    case ID_SAVE: // 保存
        OnSave(hwnd);
        break;
    case ID_SAVE_AS: // 名前を付けて保存
        OnSaveAs(hwnd);
        break;
    case ID_DRIVE1_EJECT: // ドライブを取り出す
        OnEjectDisk(hwnd, 1);
        break;
    case ID_DRIVE2_EJECT: // ドライブを取り出す
        OnEjectDisk(hwnd, 2);
        break;
    case ID_DRIVE3_EJECT: // ドライブを取り出す
        OnEjectDisk(hwnd, 3);
        break;
    case ID_DRIVE4_EJECT: // ドライブを取り出す
        OnEjectDisk(hwnd, 4);
        break;
    case ID_DRIVE1_FOLDER: // ドライブフォルダをセット
        OnDriveFolder(hwnd, 1);
        break;
    case ID_DRIVE2_FOLDER: // ドライブフォルダをセット
        OnDriveFolder(hwnd, 2);
        break;
    case ID_DRIVE3_FOLDER: // ドライブフォルダをセット
        OnDriveFolder(hwnd, 3);
        break;
    case ID_DRIVE4_FOLDER: // ドライブフォルダをセット
        OnDriveFolder(hwnd, 4);
        break;
    case ID_DRIVE1_IMAGE: // イメージを開く
        OnDiskImage(hwnd, 1);
        break;
    case ID_DRIVE2_IMAGE: // イメージを開く
        OnDiskImage(hwnd, 2);
        break;
    case ID_DRIVE3_IMAGE: // イメージを開く
        OnDiskImage(hwnd, 3);
        break;
    case ID_DRIVE4_IMAGE: // イメージを開く
        OnDiskImage(hwnd, 4);
        break;
    case ID_NEW_DISK:
        assert(0); // 未実装
        break;
    case ID_ABOUT: // このアプリについて
        OnAbout(hwnd);
        break;
    case ID_ZOOM_X1: // 1倍拡大
        OnZoom(hwnd, 1);
        break;
    case ID_ZOOM_X2: // 2倍拡大
        OnZoom(hwnd, 2);
        break;
    case ID_ZOOM_X3: // 3倍拡大
        OnZoom(hwnd, 3);
        break;
    case ID_MAXIMIZE: // 最大化
        ::ShowWindow(hwnd, (IsZoomed(hwnd) ? SW_RESTORE : SW_MAXIMIZE));
        break;
    case ID_OPEN_README: // ReadMeを開く
        OnOpenReadMe(hwnd);
        break;
    case ID_SAVE_SCREENSHOT: // スクリーンショットを保存する
        OnScreenshot(hwnd, TRUE);
        break;
    case ID_COPY_SCREENSHOT: // スクリーンショットをコピーする
        OnScreenshot(hwnd, FALSE);
        break;
    case ID_SETTINGS: // 設定
        OnSettings(hwnd);
        break;
    case ID_PASTE_TEXT:
        OnPaste(hwnd);
        break;
    case ID_COPY_TEXT:
        OnCopy(hwnd);
        break;
    case ID_GRPH_MODE:
        VSK_SETTINGS()->m_text_mode = VSK_TEXT_MODE_GRPH;
        break;
    case ID_SJIS_MODE:
        VSK_SETTINGS()->m_text_mode = VSK_TEXT_MODE_SJIS;
        break;
    case ID_JIS_MODE:
        VSK_SETTINGS()->m_text_mode = VSK_TEXT_MODE_JIS;
        break;
    }
}

// ID_ABOUT
// このアプリについて、バージョン情報
void VskWin32App::OnAbout(HWND hwnd)
{
    MSGBOXPARAMS params = { sizeof(params), hwnd, m_hInst };
    params.lpszText = TEXT(VEYSICK_TITLE) TEXT("\r\n") TEXT(VEYSICK_COPYRIGHT);
    params.lpszCaption = TEXT(VEYSICK_CLASSNAME);
    params.dwStyle = MB_USERICON;
    params.lpszIcon = MAKEINTRESOURCE(IDI_MAINICON);
    _hookCenterMsgBoxDx(TRUE);
    ::MessageBoxIndirect(&params);
    _hookCenterMsgBoxDx(FALSE);
}

using std::max;
using std::min;

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

// GDI+用。エンコーダーのCLSIDを取得する
BOOL GetEncoderClsid(CLSID* pClsid, LPCWSTR mime_type)
{
    // エンコーダーのサイズ情報を取得
    UINT cItems = 0, cbEncoders = 0;
    Gdiplus::GetImageEncodersSize(&cItems, &cbEncoders);
    if (!cbEncoders)
        return FALSE; // 失敗

    // エンコーダーを格納するメモリーを確保
    auto pEncoders = (Gdiplus::ImageCodecInfo *)malloc(cbEncoders);
    if (!pEncoders)
        return FALSE; // 失敗

    // エンコーダーを格納
    Gdiplus::GetImageEncoders(cItems, cbEncoders, pEncoders);

    // MIMEの種類に一致するエンコーダーのCLSIDを取得
    for (UINT iItem = 0; iItem < cItems; ++iItem)
    {
        if (wcscmp(pEncoders[iItem].MimeType, mime_type) == 0)
        {
            *pClsid = pEncoders[iItem].Clsid;
            free(pEncoders); // 解放
            return TRUE; // 成功
        }
    }

    free(pEncoders); // 解放
    return FALSE; // 失敗
}

// HBITMAPを画像ファイルとして保存する関数
BOOL SaveHBITMAPToFile(HBITMAP hBitmap, LPCWSTR filename, LPCWSTR mime_type = L"image/png")
{
    // GDI+ BitmapオブジェクトをHBITMAPから作成
    auto bitmap = new Gdiplus::Bitmap(hBitmap, NULL);
    if (!bitmap)
        return FALSE; // 失敗
    std::shared_ptr<Gdiplus::Bitmap> pBitmap(bitmap);

    // PNGエンコーダのCLSIDを取得
    CLSID clsid;
    if (!GetEncoderClsid(&clsid, mime_type))
        return FALSE; // 失敗

    // PNGとして保存
    if (pBitmap->Save(filename, &clsid, NULL) != Gdiplus::Ok)
        return FALSE; // 失敗

    return TRUE; // 成功
}

BOOL Settings_OnOK(HWND hwnd)
{
    VSK_SETTINGS()->m_move_caret_by_mouse_click = (IsDlgButtonChecked(hwnd, chx1) == BST_CHECKED);
    VSK_SETTINGS()->m_remember_window_pos = (IsDlgButtonChecked(hwnd, chx2) == BST_CHECKED);
    VSK_SETTINGS()->m_unlimited_mode = (IsDlgButtonChecked(hwnd, chx3) == BST_CHECKED);
    VSK_SETTINGS()->m_field_width = GetDlgItemInt(hwnd, edt1, nullptr, TRUE);
    return TRUE;
}

// 「設定」ダイアログ
INT_PTR CALLBACK
Settings_DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
        if (VSK_SETTINGS()->m_move_caret_by_mouse_click)
            ::CheckDlgButton(hwnd, chx1, BST_CHECKED);
        if (VSK_SETTINGS()->m_remember_window_pos)
            ::CheckDlgButton(hwnd, chx2, BST_CHECKED);
        if (VSK_SETTINGS()->m_unlimited_mode)
            ::CheckDlgButton(hwnd, chx3, BST_CHECKED);
        ::SetDlgItemInt(hwnd, edt1, VSK_SETTINGS()->m_field_width, TRUE);
        ::SendDlgItemMessage(hwnd, scr1, UDM_SETRANGE, 0, MAKELONG(1024, -1));
        return TRUE; // オートフォーカス
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case chx1:
        case chx2:
        case chx3:
            PropSheet_Changed(::GetParent(hwnd), hwnd);
            break;
        }
        break;
    case WM_NOTIFY:
        {
            auto pnmhdr = reinterpret_cast<NMHDR *>(lParam);
            switch (pnmhdr->code)
            {
            case PSN_APPLY: // 適用
                if (!Settings_OnOK(hwnd))
                {
                    return SetDlgMsgResult(hwnd, WM_NOTIFY, PSNRET_INVALID_NOCHANGEPAGE);
                }
                break;
            }
        }
        break;
    }
    return 0;
}

// ID_SETTINGS
// 設定
void VskWin32App::OnSettings(HWND hwnd)
{
    PROPSHEETPAGE psp = { sizeof(psp) };
    HPROPSHEETPAGE hpsp[1];
    INT iPage = 0, nStartPage = 0;

    // ページを追加する
    psp.pszTemplate = MAKEINTRESOURCE(IDD_SETTINGS);
    psp.pfnDlgProc = Settings_DlgProc;
    psp.dwFlags = PSP_DEFAULT;
    psp.hInstance = m_hInst;
    hpsp[iPage++] = ::CreatePropertySheetPage(&psp);

    assert(iPage <= _countof(hpsp));
    assert(nStartPage < _countof(hpsp));

    // タイトル
    TCHAR szTitle[128];
    ::LoadString(m_hInst, IDS_SETTINGS, szTitle, _countof(szTitle));

    // プロパティシートを表示する
    PROPSHEETHEADER psh = { sizeof(psh) };
    psh.dwFlags = 0;
    psh.hInstance = m_hInst;
    psh.hwndParent = hwnd;
    psh.nPages = iPage;
    psh.phpage = hpsp;
    psh.pszCaption = szTitle;
    psh.nStartPage = nStartPage;
    ::PropertySheet(&psh);
}

// ミリ秒を返す
VskLong vsk_get_tick_count(void)
{
    return ::GetTickCount();
}

// スクリーンショットを保存する
bool vsk_save_screenshot(HBITMAP hbm)
{
    // ファイルパス名
    WCHAR szFile[MAX_PATH];
    ::LoadStringW(nullptr, IDS_SCREENSHOT, szFile, _countof(szFile));

    // スクリーンショットの保存用のフィルター
    WCHAR szFilter[MAX_PATH];
    ::LoadStringW(nullptr, IDS_SAVESHOTFILTER, szFilter, _countof(szFilter));
    for (size_t ich = 0; szFilter[ich]; ++ich)
    {
        if (szFilter[ich] == L'|')
            szFilter[ich] = 0;
    }

    // タイトル
    WCHAR szTitle[MAX_PATH];
    ::LoadStringW(nullptr, IDS_SAVESHOTTITLE, szTitle, _countof(szTitle));

    // ユーザーにファイルの場所を問い合わせる準備をする
    OPENFILENAMEW ofn = { sizeof(ofn), VSK_APP()->m_hWnd };
    ofn.lpstrFilter = szFilter;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = _countof(szFile);
    ofn.lpstrTitle = szTitle;
    ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST |
                OFN_PATHMUSTEXIST | OFN_ENABLESIZING | OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = L".png";

    // スクリーンショットの保存先をユーザーに問い合わせる
    if (::GetSaveFileNameW(&ofn))
    {
        // GDI+を初期化
        Gdiplus::GdiplusStartupInput gdiplusStartupInput;
        ULONG_PTR gdiplusToken;
        Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

        // 画像ファイルとして保存
        if (ofn.nFilterIndex == 2)
            SaveHBITMAPToFile(hbm, szFile, L"image/bmp");
        else
            SaveHBITMAPToFile(hbm, szFile, L"image/png");

        // GDI+を解放
        Gdiplus::GdiplusShutdown(gdiplusToken);
    }

    // HBITMAPを破棄
    ::DeleteObject(hbm);

    return true;
}

// スクリーンショットを保存する
bool vsk_save_screenshot_real(bool text, bool graphics, bool half)
{
    bool old_text = VSK_STATE()->m_show_text;
    bool old_graphics = VSK_STATE()->m_show_graphics;
    VSK_STATE()->m_show_text = text;
    VSK_STATE()->m_show_graphics = graphics;
    vsk_machine->render();
    VSK_STATE()->m_show_text = old_text;
    VSK_STATE()->m_show_graphics = old_graphics;

    HBITMAP hbm = (HBITMAP)::CopyImage(*vsk_machine->get_screen_image(), IMAGE_BITMAP,
        0, 0, LR_COPYRETURNORG | LR_CREATEDIBSECTION);
    if (!hbm)
        return false;

    if (half)
    {
        BITMAP bm;
        ::GetObject(hbm, sizeof(bm), &bm);

        HBITMAP hbmHalf = (HBITMAP)::CopyImage(hbm, IMAGE_BITMAP,
            bm.bmWidth, bm.bmHeight / 2,
            LR_CREATEDIBSECTION);
        bool ret = false;
        if (hbmHalf)
        {
            ret = vsk_save_screenshot(hbmHalf);
            ::DeleteObject(hbmHalf);
        }
        ::DeleteObject(hbm);
        return ret;
    }
    else
    {
        bool ret = vsk_save_screenshot(hbm);
        ::DeleteObject(hbm);
        return ret;
    }
}

#define MYWM_SCREENSHOT (WM_USER + 101)

// スクリーンショットを保存する
bool vsk_save_screenshot(bool text, bool graphics, bool half)
{
    if (!vsk_machine || !vsk_pMainWnd)
        return false;

    // スレッドが違うかもしれないので、PostMessageを経由
    DWORD flags = 0;
    flags |= !!text;
    flags |= (graphics << 1);
    flags |= (half << 2);
    ::PostMessage(vsk_pMainWnd->m_hWnd, MYWM_SCREENSHOT, flags, 0);
    return true;
}

// ID_SAVE_SCREENSHOT, ID_COPY_SCREENSHOT
void VskWin32App::OnScreenshot(HWND hwnd, BOOL bFile)
{
    if (!vsk_machine)
        return;

    // スクリーンショットのコピーを作成
    start_stop_timers(hwnd, false);
    HBITMAP hbm = (HBITMAP)::CopyImage(*vsk_machine->get_screen_image(), IMAGE_BITMAP,
                                       0, 0, LR_COPYRETURNORG | LR_CREATEDIBSECTION);
    start_stop_timers(hwnd, true);
    if (!hbm)
        return;

    if (!bFile) // ファイルではなくクリップボード？
    {
        // クリップボードにコピー
        vsk_copy_image_to_clipboard(hwnd, hbm);
        // HBITMAPを破棄
        ::DeleteObject(hbm);
        return;
    }

    // スクリーンショットを保存する
    vsk_save_screenshot(hbm);

    // HBITMAPを破棄
    ::DeleteObject(hbm);
}

// ID_ZOOM_X1, ID_ZOOM_X2, ID_ZOOM_X3
void VskWin32App::OnZoom(HWND hwnd, INT nZoom)
{
    // 最大化・最小化を解除する
    ::ShowWindow(hwnd, SW_RESTORE);

    // スタイルを取得
    DWORD style = GetWindowStyle(hwnd), exstyle = GetWindowExStyle(hwnd);

    // クライアント領域のサイズからウィンドウのサイズを取得する
    RECT rc = { 0, 0, VSK_SCREEN_WIDTH, VSK_SCREEN_HEIGHT };
    rc.right *= nZoom;
    rc.bottom *= nZoom;
    ::AdjustWindowRectEx(&rc, style, TRUE, exstyle);

    // ウィンドウのサイズを変更する
    RECT rcWnd;
    ::GetWindowRect(hwnd, &rcWnd);
    ::MoveWindow(hwnd, rcWnd.left, rcWnd.top, (rc.right - rc.left), (rc.bottom - rc.top), TRUE);
}

// クリップボードにテキストをコピー
BOOL vsk_copy_text_to_clipboard(HWND hwnd, const std::string& text)
{
    if (!::OpenClipboard(hwnd))
        return false;

    ::EmptyClipboard();

    BOOL bOK = FALSE;
    size_t cbText = (text.size() + 1) * sizeof(char);
    if (HANDLE hText = ::GlobalAlloc(GHND | GMEM_SHARE, cbText))
    {
        if (char *psz = (char *)::GlobalLock(hText))
        {
            ::CopyMemory(psz, text.c_str(), cbText);
            bOK = !!::SetClipboardData(CF_TEXT, hText);
            ::GlobalUnlock(hText);
        }
        if (!bOK)
            ::GlobalFree(hText);
    }

    ::CloseClipboard();
    return !!bOK;
}

// クリップボードからテキストを取得
BOOL vsk_get_text_from_clipboard(HWND hwnd, std::string& text)
{
    if (!::IsClipboardFormatAvailable(CF_TEXT) || !::OpenClipboard(hwnd))
        return FALSE;

    BOOL bOK = FALSE;
    if (HANDLE hText = ::GetClipboardData(CF_OEMTEXT))
    {
        if (char *psz = (char *)::GlobalLock(hText))
        {
            text = psz;
            bOK = TRUE;
            ::GlobalUnlock(hText);
        }
    }

    ::CloseClipboard();
    return !!bOK;
}

// ID_COPY_TEXT
void VskWin32App::OnCopy(HWND hwnd)
{
    if (!vsk_machine)
    {
        assert(0);
        return;
    }

    VskString text = vsk_machine->copy_text_screen();
    vsk_copy_text_to_clipboard(hwnd, text);
}

// ID_PASTE_TEXT
// テキストをクリップボードから貼り付け
void VskWin32App::OnPaste(HWND hwnd)
{
    std::string text;
    if (!vsk_machine || !vsk_get_text_from_clipboard(hwnd, text))
    {
        assert(0);
        return;
    }

    vsk_machine->keyboard_str(text);
}

// ID_OPEN_README
void VskWin32App::OnOpenReadMe(HWND hwnd)
{
    TCHAR szPath[MAX_PATH];
    ::GetModuleFileName(nullptr, szPath, _countof(szPath));
    PathRemoveFileSpec(szPath);
    PathAppend(szPath, TEXT("README.txt"));
    if (!PathFileExists(szPath))
    {
        PathRemoveFileSpec(szPath);
        PathRemoveFileSpec(szPath);
        PathAppend(szPath, TEXT("README.txt"));
    }
    ::ShellExecute(hwnd, nullptr, szPath, nullptr, nullptr, SW_SHOWNORMAL);
}

// WM_ERASEBKGND
// WM_PAINTの前に背景を消す
BOOL VskWin32App::OnEraseBkgnd(HWND hwnd, HDC hdc)
{
    // MImageViewExを使って描画
    return m_imageView.OnEraseBkgnd(hwnd, hdc);
}

// WM_PAINT
// クライアント領域を描画
void VskWin32App::OnPaint(HWND hwnd)
{
    // MImageViewExを使って描画
    m_imageView.OnPaint(hwnd);
}

// INKEY$ 用
VskByte vsk_inkey = 0;
VskDword vsk_vk = 0;
bool vsk_shift = false;
bool vsk_ctrl = false;

// VK_PROCESSKEYの処理前の仮想キーコード
UINT vsk_vkey = 0;

void VskWin32App::OnKeyLocked(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
    if (!fDown)
    {
        vsk_inkey = 0;
        if (vk == VK_F11) // F11 キー
        {
            // メニューに移動
            ::DefWindowProc(hwnd, WM_SYSCOMMAND, SC_KEYMENU, 0);
        }
        return;
    }

    mdbg_traceA("OnKeyLocked: vk: 0x%X\n", vk);

    // Ctrlキーを押したらマウスクリッピングを解除
    if (vk == VK_CONTROL)
        ::ClipCursor(nullptr);

    const bool caps = (::GetKeyState(VK_CAPITAL) < 0);
    bool shift = vsk_is_shift_pressed(), ctrl = vsk_is_ctrl_pressed();
    if (!(vk == vsk_vk && shift == vsk_shift && ctrl == vsk_ctrl))
        vsk_inkey = vsk_map_key_code(vk, vsk_is_shift_pressed(), vsk_is_ctrl_pressed(), caps);
    vsk_vk = vk;
    vsk_shift = shift;
    vsk_ctrl = ctrl;

#ifdef JAPAN
    if (vk == VK_KANJI || vk == VK_OEM_ENLW) // 漢字のON/OFFを変えようとした？
    {
        ime_on_off_real(!m_state.m_kanji_mode);
        return;
    }
    if (vk == VK_PROCESSKEY) // IMEで何らかの処理が行われた？
    {
        mdbg_traceA("vsk_vkey: 0x%X\n", vsk_vkey);
        if (vsk_vkey == VK_OEM_AUTO) // IMEをOFFにしようとした？
        {
            mdbg_traceA("VK_PROCESSKEY:VK_OEM_AUTO\n");
            ime_on_off_real(false);
        }
        return;
    }
    if (vk == VK_OEM_COPY) // かなキー（IMEがOFFのときのみ）か？
    {
        vsk_ime_on_off(false); // IMEをOFFにする
        m_state.m_kana_mode = !m_state.m_kana_mode; // かなモードを切り替える。
        return;
    }
#endif

    // Ctrlキーと一緒にアルファベットが押されたら制御コード
    if (vsk_is_ctrl_pressed() && 'A' <= vk && vk <= 'Z')
    {
        vsk_machine->control_code(VskByte(vk));
        return;
    }

    // Altキーと一緒に押されたらGRPH文字
    if (vsk_is_alt_pressed())
    {
        vsk_machine->keyboard_ch(vsk_map_grph_code(vk));
        return;
    }

    // 仮想キーに応じて処理を行う
    switch (vk)
    {
    case VK_LEFT: // ←
        if (vsk_is_ctrl_pressed())
            vsk_machine->control_code('B');
        else
            vsk_machine->control_code(']');
        break;
    case VK_UP: // ↑
        vsk_machine->print_control('^');
        break;
    case VK_RIGHT: // →
        if (vsk_is_ctrl_pressed())
            vsk_machine->control_code('F');
        else
            vsk_machine->control_code('\\');
        break;
    case VK_DOWN: // ↓
        vsk_machine->control_code('_');
        break;
    case VK_RETURN: // Enterキー
        vsk_machine->control_code('M');
        break;
    case VK_BACK: // BackSpaceキー
        vsk_machine->control_code('H');
        break;
    case VK_DELETE: // Delキー
        if (vsk_is_shift_pressed())
            vsk_machine->control_code('R'); // Shift+DelはInsertとして扱う
        else
            vsk_machine->control_code('H'); // それ以外はBackSpaceとして扱う
        break;
    case VK_TAB: // Tabキー
        vsk_machine->control_code('I');
        break;
    case VK_PRIOR: // PageUp キー
        vsk_page_up();
        break;
    case VK_NEXT: // PageDownキー
        vsk_page_down();
        break;
    case VK_HOME: // Homeキー
        if (vsk_is_shift_pressed())
            vsk_machine->control_code('K'); // Shift+Homeはホームポジションに移動
        else
            vsk_machine->control_code('L'); // それ以外は画面消去
        break;
    case VK_END: // Endキー
        vsk_machine->control_code('A'); // EndキーはPC-8801/PC-9801のHELPとして扱う
        break;
    case VK_INSERT: // Insertキー
        vsk_machine->control_code('R');
        break;
    case VK_PRINT: // Printキー
        assert(0); // 未実装
        break;
    case VK_F1: // F1キー
        vsk_machine->function_key(0, vsk_is_shift_pressed());
        break;
    case VK_F2: // F2キー
        vsk_machine->function_key(1, vsk_is_shift_pressed());
        break;
    case VK_F3: // F3キー
        vsk_machine->function_key(2, vsk_is_shift_pressed());
        break;
    case VK_F4: // F4キー
        vsk_machine->function_key(3, vsk_is_shift_pressed());
        break;
    case VK_F5: // F5キー
        vsk_machine->function_key(4, vsk_is_shift_pressed());
        break;
    case VK_F6: // F6キー
        vsk_machine->function_key(5);
        break;
    case VK_F7: // F7キー
        vsk_machine->function_key(6);
        break;
    case VK_F8: // F8キー
        vsk_machine->function_key(7);
        break;
    case VK_F9: // F9キー
        vsk_machine->function_key(8);
        break;
    case VK_F10: // F10キー
        vsk_machine->function_key(9);
        break;
    case VK_F11: // F11キー
        // (上を参照)
        break;
    case VK_F12: // メインウィンドウのカーソルを消す、または再表示
        m_bShowCursor = !m_bShowCursor;
        ::SetCursor(m_bShowCursor ? ::LoadCursor(nullptr, IDC_ARROW) : nullptr);
        break;
    }
}

// WM_KEYDOWN / WM_KEYUP
// キーが押されたか離された
void VskWin32App::OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
    vsk_lock();
    OnKeyLocked(hwnd, vk, fDown, cRepeat, flags);
    vsk_unlock();
}

// WM_SYSKEYDOWN / WM_SYSKEYUP
// Altと共に何かキーが押されたか、離された
void VskWin32App::OnSysKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
    // 離された場合は無視
    if (!fDown)
        return;

    if (vk == VK_F4)
    {
        ::DestroyWindow(hwnd); // Alt+F4でメインウィンドウを閉じる
        return;
    }

    // 通常のキー処理を呼び出す
    OnKey(hwnd, vk, fDown, cRepeat, flags);
}

// WM_CHAR
// 文字が入力された
void VskWin32App::OnChar(HWND hwnd, TCHAR ch, int cRepeat)
{
    if (0x20 <= ch && ch <= 0x7F) // 普通のASCII文字か？
    {
        // Ctrlが押されていたら無視
        if (vsk_is_ctrl_pressed())
            return;

#ifdef JAPAN
        // かなモードなら英数字を半角カナに変換
        if (!m_state.m_kanji_mode && m_state.m_kana_mode)
            ch = vsk_abc_to_kana(VskByte(ch), vsk_is_shift_pressed());
#endif

        // キーボード入力を処理
        vsk_lock();
        vsk_machine->keyboard_ch(ch);
        vsk_unlock();
        return;
    }

#ifdef JAPAN
    if (ch > 0xFF) // マルチバイト文字？
    {
        // SJIS （コードページ923）に変換
        WCHAR szW[2] = { ch, 0 };
        CHAR szA[3];
        if (!WideCharToMultiByte(932, 0, szW, -1, szA, _countof(szA), nullptr, nullptr))
            return;

        // バッファオーバーランを避ける
        szA[_countof(szA) - 1] = 0;

        auto w = vsk_make_word(szA[1], szA[0]); // ワード値を組み立て

        vsk_lock();
        if (vsk_is_sjis_code(w)) // SJISの全角文字なら
        {
            vsk_machine->keyboard_ch(w); // キーボード入力を処理
        }
        else if (szA[0] && !szA[1]) // 半角カナ？
        {
            vsk_machine->keyboard_ch(szA[0]); // キーボード入力を処理
        }
        vsk_unlock();
    }
#endif
}

// WM_SYSCHAR
void VskWin32App::OnSysChar(HWND hwnd, TCHAR ch, int cRepeat)
{
    // 余計な音を出さないようにWM_SYSCHARメッセージを食べる
}

// WM_SETCURSOR
BOOL VskWin32App::OnSetCursor(HWND hwnd, HWND hwndCursor, UINT codeHitTest, UINT msg)
{
    if (codeHitTest == HTCLIENT)
    {
        ::SetCursor(m_bShowCursor ? ::LoadCursor(nullptr, IDC_ARROW) : nullptr);
        return TRUE;
    }
    return FORWARD_WM_SETCURSOR(hwnd, hwndCursor, codeHitTest, msg, ::DefWindowProc);
}

LRESULT CALLBACK
VskWin32App::WndProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
        HANDLE_MSG(hwnd, WM_ERASEBKGND, OnEraseBkgnd);
        HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
        HANDLE_MSG(hwnd, WM_KEYDOWN, OnKey);
        HANDLE_MSG(hwnd, WM_KEYUP, OnKey);
        HANDLE_MSG(hwnd, WM_SYSKEYDOWN, OnSysKey);
        HANDLE_MSG(hwnd, WM_SYSKEYUP, OnSysKey);
        HANDLE_MSG(hwnd, WM_CHAR, OnChar);
        HANDLE_MSG(hwnd, WM_SYSCHAR, OnSysChar);
        HANDLE_MSG(hwnd, WM_SETCURSOR, OnSetCursor);
        HANDLE_MSG(hwnd, WM_MOUSEMOVE, OnMouseMove);
        HANDLE_MSG(hwnd, WM_LBUTTONDOWN, OnLButtonDown);
        HANDLE_MSG(hwnd, WM_LBUTTONDBLCLK, OnLButtonDown);
        HANDLE_MSG(hwnd, WM_LBUTTONUP, OnLButtonUp);
        HANDLE_MSG(hwnd, WM_RBUTTONDOWN, OnRButtonDown);
        HANDLE_MSG(hwnd, WM_RBUTTONDBLCLK, OnRButtonDown);
        HANDLE_MSG(hwnd, WM_RBUTTONUP, OnRButtonUp);
        HANDLE_MSG(hwnd, WM_CONTEXTMENU, OnContextMenu);
        HANDLE_MSG(hwnd, WM_INITMENUPOPUP, OnInitMenuPopup);
        HANDLE_MSG(hwnd, WM_MOVE, OnMove);
        HANDLE_MSG(hwnd, WM_SIZE, OnSize);
        HANDLE_MSG(hwnd, WM_TIMER, OnTimer);
        HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
    case MYWM_IME_ON_OFF:
        ime_on_off_real((bool)wParam);
        break;
    case MYWM_SCREENSHOT:
        vsk_save_screenshot_real((wParam & 1), (wParam & 2), (wParam & 4));
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// アプリを初期化する
bool VskWin32App::init_app(void *hInst, int argc, WCHAR **argv, int nCmdShow)
{
    // インスタンスハンドルを保存する
    m_hInst = (HINSTANCE)hInst;

    // コモンコントロールを初期化
    ::InitCommonControls();

    // クリティカルセクションを初期化
    ::InitializeCriticalSection(&vsk_cs_lock);

    // メインウィンドウのクラスを登録する
    WNDCLASSEX wcx = { sizeof(wcx) };
    wcx.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcx.lpfnWndProc = WindowProc;
    wcx.hInstance = m_hInst;
    wcx.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_MAINICON));
    wcx.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)UlongToHandle(COLOR_3DFACE + 1);
    wcx.lpszMenuName = MAKEINTRESOURCE(IDR_MAINMENU);
    wcx.lpszClassName = TEXT(VEYSICK_CLASSNAME);
    if (!RegisterClassEx(&wcx))
    {
        // 失敗
        error(TEXT("RegisterClassEx failed"));
        return false;
    }

    // 設定を読み込む
    load_settings();

    enum
    {
        style = WS_OVERLAPPEDWINDOW,
        exstyle = 0,
    };

    // クライアント領域のサイズからウィンドウのサイズを取得する
    RECT rc = { 0, 0, VSK_SCREEN_WIDTH, VSK_SCREEN_HEIGHT };
    if (m_settings.m_cx == CW_USEDEFAULT)
    {
        ::AdjustWindowRectEx(&rc, style, TRUE, exstyle);
    }
    else
    {
        rc.left = rc.top = 0;
        rc.right = m_settings.m_cx;
        rc.bottom = m_settings.m_cy;
    }

    // メインウィンドウを作成
    HWND hwnd = CreateWindowEx(exstyle, TEXT(VEYSICK_CLASSNAME), TEXT(VEYSICK_TITLE), style,
                               m_settings.m_x, m_settings.m_y,
                               rc.right - rc.left, rc.bottom - rc.top,
                               nullptr, nullptr, m_hInst, this);
    if (!hwnd)
    {
        // 失敗
        error(TEXT("CreateWindowEx failed"));
        return false;
    }

    // 必要なら最大化する
    if (VSK_SETTINGS()->m_zoomed && VSK_SETTINGS()->m_remember_window_pos)
        nCmdShow = SW_SHOWMAXIMIZED;

    // ウィンドウを表示
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    return true; // 成功
}

// アプリを走らせる
int VskWin32App::run()
{
    MSG msg;
    for (;;)
    {
        if (!::PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE))
        {
            DWORD dwTick0 = GetTickCount();
            OnIdle();
            DWORD dwTick1 = GetTickCount();
            DWORD dwDiff = dwTick1 - dwTick0;
            if (dwDiff < VSK_ONE_SECOND / VSK_IDEAL_FPS)
                ::Sleep((VSK_ONE_SECOND / VSK_IDEAL_FPS) - dwDiff);
            continue;
        }

        if (!::GetMessage(&msg, nullptr, 0, 0))
            break;

        // VK_PROCESSKEYの処理前の仮想キーコードを取得する
        if (msg.message == WM_KEYDOWN)
            vsk_vkey = ::ImmGetVirtualKey(m_hWnd);

        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

// アプリの終了時の処理
void VskWin32App::exit_app()
{
    // 終了フラグ
    vsk_exiting = true;

    // 設定を保存する
    save_settings();

    // クリティカルセクションを破棄
    ::DeleteCriticalSection(&vsk_cs_lock);

    // メモリーモデルを破棄する
    m_state.m_memory = nullptr;
    // マシンを破棄する
    vsk_machine = nullptr;
}

// 描画
void VskWin32App::render()
{
    if (vsk_machine)
    {
        vsk_machine->render();
        m_imageView.setImage((HBITMAP)(VskImageHandle)*vsk_machine->get_screen_image());
#ifdef VSK_SINGLE_THREAD
        vsk_lock();
        vsk_machine->step();
        vsk_unlock();
#endif
    }
    else
    {
        m_imageView.setImage(nullptr);
    }
}

// アイドル時にする処理
void VskWin32App::OnIdle()
{
    ++s_dwFpsCounter;
    if (IsWindowVisible(m_hWnd) && !IsIconic(m_hWnd))
    {
        vsk_lock();
        render();
        vsk_unlock();
    }
}

void VskWin32App::error(const _TCHAR *msg)
{
    MessageBox(m_hWnd, msg, nullptr, MB_ICONERROR);
}

// ウィンドウ プロシージャ
LRESULT CALLBACK
VskWin32App::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    VskWin32App *pApp = reinterpret_cast<VskWin32App *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (!pApp)
    {
        if (uMsg == WM_CREATE)
        {
            CREATESTRUCT *pCS = reinterpret_cast<CREATESTRUCT *>(lParam);
            pApp = reinterpret_cast<VskWin32App *>(pCS->lpCreateParams);
        }
        else
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    return pApp->WndProcDx(hwnd, uMsg, wParam, lParam);
}

////////////////////////////////////////////////////////////////////////////////////

// アプリのメイン関数２
INT VeySicK_Main(HINSTANCE hInstance, INT argc, WCHAR **argv, INT nCmdShow)
{
    // アプリオブジェクトを作成、初期化
    std::shared_ptr<VskWin32App> pApp(new VskWin32App());
    if (!pApp->init_app(hInstance, argc, argv, nCmdShow))
        return 1;

    // アプリを走らせる
    int ret = pApp->run();

    // 終了
    pApp->exit_app();
    return ret; // 終了コード
}

////////////////////////////////////////////////////////////////////////////////////

// Windowsアプリのメイン関数
INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    // 逆工学対策ルーチン
#ifdef NDEBUG // On Release time only
    AntiRE_StopWatch();
    AntiRE_DetectDebugger(); // Detect debugger
    AntiRE_CheckDebugRegs(); // Check CPU debug registers
    //AntiRE_DetectVirtualMachine(); // Detect virtual machine (WARNING: License compliant?)
    if (AntiRE_StopWatch() >= 3 * 1000) // 3-count death
    {
        ::ExitProcess(0);
        return 0;
    }
#endif

    // 引数付きでアプリを呼び出す
    assert(VskObject::s_cAliveObjects == 0); // オブジェクトの生存数確認
    INT argc;
    assert(VskObject::s_cAliveObjects == 0);
    LPWSTR *wargv = CommandLineToArgvW(GetCommandLineW(), &argc);
    INT ret = VeySicK_Main(hInstance, argc, wargv, nCmdShow);
    LocalFree(wargv);
    assert(VskObject::s_cAliveObjects == 0); // オブジェクトの生存数確認

    // ハンドルリークの検出。ときどきハンドルの個数をチェックすること
#if (_WIN32_WINNT >= 0x0500) && !defined(NDEBUG)
    TCHAR szText[MAX_PATH];
    wnsprintf(szText, _countof(szText), TEXT("GDI Objects: %ld, User Objects: %ld\n"),
              GetGuiResources(GetCurrentProcess(), GR_GDIOBJECTS),
              GetGuiResources(GetCurrentProcess(), GR_USEROBJECTS));
    OutputDebugString(szText);
#endif

    // メモリーリークの検出（Visual C++のみ）
#if defined(_MSC_VER) && !defined(NDEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    return ret;
}
