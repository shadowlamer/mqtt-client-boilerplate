/**
 * @file KBDHelper.cpp
 * @brief Реализация класса KBDHelper.
 * @author Vadim Cherenev
 * @date 21.02.2019
 * @copyright MIT License
 */

#include <KBDHelper.h>

int fd;
struct input_event ev;
struct pollfd fds;

/**
 * @param device Имя файла устройства клавиатуры
 * @throws runtime_error Не удалось открыть файл устройства клавиатуры.
 */
KBDHelper::KBDHelper(string device) {

    fd = open(device.c_str(), O_RDONLY);
    fds.fd = fd;
    fds.events = POLLIN ;
    if (fd<0)
        throw runtime_error("Can't find keypad");
}

KBDHelper::~KBDHelper() {
    close(fd);
}

/**
 * @brief Очищает буфер клавиатуры.
 */
void KBDHelper::flush() {
    if (fd<=0) return;
    getDigit();
}

/**
 * @brief Читает символы с клавиатуры.
 * Опрашивает клавиатуру, конвертирует прочитанные коды клавиш в символы.
 * @return Содержимое буфера клавиатуры
 */
string KBDHelper::getDigit() {
    if (fd<=0) return "";
    buf = "";
    while (poll(&fds, 1, 1) >0 ){
        ssize_t r = read(fd, &ev, sizeof(struct input_event));
        if (ev.type == EV_KEY && ev.code == KEY_LEFTSHIFT)
            shift = (ev.value != 0);
        else if(r > 0 && ev.type == EV_KEY && ev.value == 0) {
            __u16 scancode = ev.code;
            if (shift) scancode += 0x100;
            auto foundKeycodes = keymap.find(scancode);
            if (foundKeycodes!=keymap.end()) {
                buf += foundKeycodes->second;
            }
        }
    }
    return buf;
}

/**
 * @brief Немедленно возвращает содержимое буфера клавиатуры.
 * Опроса клавиатуры не производится.
 * @return Содержимое буфера клавиатуры
 */
string KBDHelper::getBuf() {
    return buf;
}

/**
 * @brief Читает строку символов с клавиатуры.
 * Чтение завершается по нажатию клавиши "Ввод" или при достижении максимального размера строки.
 * Можно удалять символы нажатием клавиши "Удалить"
 * @param str Буфер для сохранения введенной строки
 * @param maxSize Максимальный размер строки
 * @return true, если строка успешно прочитана
 */
bool KBDHelper::inputString(string &str, unsigned int maxSize) {
    for ( string::iterator it = buf.begin() ; it < buf.end(); it++) {
        switch (*it) {
            case '0' ... '9':
                if ( str.size() < maxSize )
                    str.push_back(*it);
                break;
            case KBD_BKSPACE:
                if (!str.empty()) str.pop_back();
                break;
            case KBD_ENTER:
                return true;
            default:break;
        }
    }
    return false;
}

/**
 * @brief Проверяет был ли введен специальный символ.
 * @param special Специальный символ, который нужно найти
 * @return true, если заданный символ был введен
 */
bool KBDHelper::checkSpecial(char special) {
    return buf.find(special) != string::npos;
}

/**
 * @brief Ищет файл устройства по имени устройства.
 * @sa INPUT_DEV_DIRECTORY
 * @param devname Имя устройства
 * @return Имя файла устройства
 */
string KBDHelper::findDeviceByName(const string &devname) {
    char buf[512];
    DIR* dirp = opendir(INPUT_DEV_DIRECTORY);
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        string name(string(INPUT_DEV_DIRECTORY) + string(dp->d_name));
        fd = open(name.c_str(), O_RDONLY);
        ioctl(fd, EVIOCGNAME(sizeof(buf)), buf);
        close(fd);
        if (devname.compare(buf) == 0) return name;
    }
    closedir(dirp);
    return "";
}
