#include "../../header/MineObject.hpp"

MineObject::MineObject(): type("DIAMOND"), opened(false) {}

MineObject::MineObject(string type): type(type), opened(false) {}

MineObject::~MineObject() {}

void MineObject::setClose() {
    opened = false;
}
void MineObject::setOpen() {
    opened = true;
}

string MineObject::getType() {
    return type;
}

void MineObject::setDiamond() {
    type = "DIAMOND";
}

void MineObject::setBomb() {
    type = "BOMB";
}

bool MineObject::isOpened() {
    return opened;
}

ostream& operator<<(ostream& os, const MineObject& mo) {
    if (mo.opened) {
        if (mo.type == "BOMB") {
            os << "000";
        } else {
            string output = "$$$";
            for (int i = 0; i < (int) output.length(); i++) {
                print_green(output[i]);
            }
        }
    } else {
        if (mo.type == "BOMB") {
            os << "OO0";
        } else {
            os << "OOO";
        }
        // os << "OOO";
    }
    return os;
}

