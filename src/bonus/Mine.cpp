#include "../../header/Mine.hpp"

Mine::Mine(): mine(MINE_SIZE, MINE_SIZE) {
    for (int i = 0; i < MINE_SIZE * MINE_SIZE; i++) {
        mine.add(make_shared<MineObject>());
    }
}

void Mine::displayMine() {
    mine.print("");
}

int Mine::countDiamond() {
    int count = 0;
    for (int i = 0; i < MINE_SIZE; i++) {
        for (int j = 0; j < MINE_SIZE; j++) {
            auto object = mine.get(i, j);
            if (object->getType() == "DIAMOND") {
                count++;
            }
        }
    }
    return count;
}

void Mine::refreshMine() {
    for (int i = 0; i < MINE_SIZE; i++) {
        for (int j = 0; j < MINE_SIZE; j++) {
            auto object = mine.get(i, j);
            if (rand() % 10 < 7) {
                object->setDiamond();
            } else {
                object->setBomb();
            }
            object->setClose();
        }
    }
}

void Mine::openAllSlot() {
    for (int i = 0; i < MINE_SIZE; i++) {
        for (int j = 0; j < MINE_SIZE; j++) {
            mine.get(i, j)->setOpen();
        }
    }
}

void Mine::playMine(shared_ptr<Player>& player) {
    refreshMine();
    cout << endl << "Selamat datang ke Tambang Berlian!" << endl;
    cout << "Kamu dapat menggandakan guldenmu disini!" << endl;
    cout << "Hati - hati karna guldenmu bisa hilang juga!" << endl << endl;

    int capital;
    while (true) {
        cout << "Masukkan gulden yang kamu ingin gunakan untuk menambang (0 = Tidak jadi menambang): ";
        if (cin >> capital) {
            if (capital >= 0 && capital <= player->getGulden()) break;
            else cout << "Masukkan jumlah yang valid (>= 0 dan <= " << player->getGulden() << ")!" << endl;
        } else {
            cout << "Masukkan nilai numerik yang valid!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    if (capital == 0) {
        return;
    }
    player->setGulden(player->getGulden() - capital);

    int collected = 0;
    cout << "Menambang dimulai!" << endl;
    int tryCount = 0;
    int diamondCount = countDiamond();
    while (tryCount < diamondCount) {
        try {
            displayMine();
            cout << "> Gulden yang telah terkumpul: " << collected << " [Modal: " << capital << "]" << endl;
            string location;
            cout << "Masukkan petak yang ingin ditambang ('STOP' = Berhenti bermain dan ambil gulden yang terkumpul): ";
            cin >> location;
            if (location == "STOP") {
                break;
            }
            if (mine.isValid(location)) {
                auto object = mine.get(location);
                if (object->isOpened()) {
                    cout << endl << "WARNING: Petak sudah ditambang!" << endl;
                    continue;
                }
                object->setOpen();
                if (object->getType() == "BOMB") {
                    collected = 0;
                    break;
                } else {
                    if (collected == 0) {
                        collected += capital * 0.5;
                    } else {
                        collected += collected * 0.5;
                    }
                }
            }
            tryCount++;
        } catch (const exception& e) {
            cout << endl << "WARNING: " << e.what() << endl;
        }
    }
    cout << endl;
    openAllSlot();
    displayMine();
    finalizeGame(collected, capital, tryCount, diamondCount, player);
}

void Mine::finalizeGame(int collected, int capital, int tryCount, int diamondCount, shared_ptr<Player>& player) {
    cout << "Menambang selesai: berikut seluruh petak tambang terbuka!" << endl;
    if (collected == 0) {
        cout << "Yah, kamu menambang batu yang sangat keras, menambang berhenti!" << endl
             << "Tidak mendapat gulden apapun!" << endl;
    } else if (tryCount == diamondCount) {
        cout << "Selamat kamu telah menambang semuanya!" << endl;
    }
    int result = collected - capital;
    float profit = ((float) result / capital) * 100;
    cout << "Total gulden yang didapat: " << collected << "  [P/L: ";
    cout << (result > 0 ? "+" : "") << result << " (";
    cout << (profit > 0 ? "+" : "") << static_cast<int>(profit) << "%)]" << endl << endl;
    player->setGulden(player->getGulden() + collected);
}
