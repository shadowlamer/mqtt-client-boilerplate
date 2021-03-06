#include <KBDHelper.h>

int fd;
struct input_event ev;
struct pollfd fds;

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

void KBDHelper::flush() {
    if (fd<=0) return;
    getDigit();
}

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

string KBDHelper::getBuf() {
    return buf;
}

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

bool KBDHelper::checkSpecial(char special) {
    return buf.find(special) != string::npos;
}

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
