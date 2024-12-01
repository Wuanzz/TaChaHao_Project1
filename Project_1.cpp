#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<map>
#include<Windows.h>
#include<thread>
#include<chrono>

using namespace std;

bool g_bXoa = false;
bool g_bThem = false;
bool kiemTraChuoi(string strTam) {
    for (int i = 0; i < strTam.size(); i++)
    {
        if (strTam[i] < 48 || strTam[i] > 57)
            return false;
    }
    return true;
}

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void goTo(int iPosX, int iPosY, int iColor);
void viTriXY(string strText, int iPos, int iColor, int iPosX, int iPosY);
void textColor(int iColor);

class Admin {
private:
    string _strUser;
    string _strPin;
public:
    bool testLogin(string strUser, string strPin);
    string getId();
    string getPin();
    void setUser(string strUser);
    void setPin(string strPin);
};

class User {
private:
    string _strId;
    string _strPin;
    string _strName;
    long _lBal;
    string _strType;
    int _iCnt;
public:
    bool testLogin(string strId, string strPin);
    void setInformation(string strFileName);
    void inFileUser();
    bool Xoa(string strId);
    int getCnt();
    string getId();
    long getBal();
    void setBal(long lBal);
    string getPin();
    string getName();
    string getType();
    void setPin(string strPin);
    void setId(string strId);
    void setName(string strName);
    void setType(string strType);
    void setCnt(int iCnt);
};

template<typename T>
class Node {
public:
    T _tData;
    Node<T>* _pNext;
    Node(T tData);
};

template<typename T>
class TaiKhoan {
private:
    Node<T>* _pHead;
    Node<T>* _pTail;
public:
    TaiKhoan();
    ~TaiKhoan();
    void addTaiKhoan(T tData);
    void loadFileAdmin();
    void loadFileUser();
    void doDisplay();
    bool testLogin(string strId, string strPin);
    void inFileUser();
    void addUser(string strId, string strName, string strType);
    void xoaUser(string strId);
    void duyetMoKhoa();
    void moKhoa(string strId);

    void xemThongTin(string strId);
    void rutTien(string strId);
    void chuyenTien(string strId);
    void xemGiaoDich(string strId);
    void doiMaPin(string strId);
};

void giaoDienDangNhap();
void giaoDienForm(string strText);
void giaoDienForm(string strText, string strId);
void dangNhap();
void thoatForm();
void dangNhapAdmin();
void dangNhapUser();
void giaoDienAdmin();
void giaoDienUser(string strId);
void themTaiKhoan();
void xoaTaiKhoan();
void diChuyen(map<int, string> mViTri, int iPos, int iPosMax, int iPosX, int iPosY);
void diChuyenDangNhap(map<int, string> mDangNhap, int iPosX, int iPosY);
void diChuyenChucNang(map<int, string> mViTri, int iPos, int iPosMax, int iPosX, int& iPosY);
void diChuyenThemVaXoa(map<int, string> mViTri, int iPos, int iPosMax, int iPosX, int iPosY);
void diChuyenMoKhoa(map<int, string> mMoKhoa, int iPos, int iPosMax, int iPosX, int iPosY);
bool kiemTraTien(string strType, long lBal, long lSoTien);
bool tinhBoiSo(string strType, long lSoTien, long lBal);
long chuyenLoaiTien(string strTypeNhan, string strTypeChuyen, long lBal, long lTienNhan);
void nhapIDXacNhan(string& strText, int iPosX, int iPosY);
void nhapPINXacNhan(string& strText, int iPosX, int iPosY);

TaiKhoan<Admin> Ad;
TaiKhoan<User> Us;

bool Admin::testLogin(string strUser, string strPin) {
    if (this->_strUser == strUser && this->_strPin == strPin) {
        goTo(1, 5, 2);
        cout << "Dang nhap thanh cong     ";
        return true;
    }
    if (this->_strUser == strUser && this->_strPin != strPin) {
        goTo(1, 5, 12);
        cout << "Sai ma Pin!         ";
        return false;
    }
    else {
        goTo(1, 5, 4);
        cout << "Sai thong tin!         ";
        return false;
    }
}

void Admin::setUser(string strUser) { _strUser = strUser; }
void Admin::setPin(string strPin) { _strPin = strPin; }
string Admin::getPin() { return _strPin; }

bool User::testLogin(string strId, string strPin) {
    if (this->_strId == strId && this->_strPin == strPin) {
        if (this->_iCnt > 0) {
            goTo(1, 5, 2);
            cout << "Dang nhap thanh cong!                  ";

            this->setCnt(3);
            return true;
        }
        else {
            goTo(1, 5, 4);
            cout << "Tai khoan da bi khoa!                  ";

            return false;
        }
    }
    else if (this->_strId == strId && this->_strPin != strPin) {
        this->setCnt(this->_iCnt - 1);
        if (this->_iCnt > 0) {
            goTo(1, 5, 12);
            cout << "Ban con " << this->_iCnt << " lan dang nhap!               ";

        }
        else {
            goTo(1, 5, 4);
            cout << "Tai khoan da bi khoa!                  ";
        }
        Us.inFileUser();
        return false;
    }
    else {
        return false;
    }
}

void User::setInformation(string strFileName) {
    ifstream Fin(strFileName);
    string strID;
    string strName;
    long lBal;
    string strType;
    int iCnt;

    Fin >> strID;
    Fin.ignore();
    getline(Fin, strName);
    Fin >> lBal;
    Fin >> strType;
    Fin >> iCnt;


    if (iCnt > 0)
        iCnt = 3;
    else
        iCnt = 0;

    _strName = strName;
    _lBal = lBal;
    _strType = strType;
    _iCnt = iCnt;

    Fin.close();
}

void User::inFileUser() {
    string strFileName = "[" + this->_strId + "].txt";
    ofstream Fout(strFileName);
    Fout << _strId << endl;
    Fout << _strName << endl;
    Fout << _lBal << endl;
    Fout << _strType << endl;
    if (_iCnt <= 0) _iCnt = 0;
    Fout << _iCnt << endl;
}

bool User::Xoa(string strId) { return _strId != strId; }
int User::getCnt() { return _iCnt; }
string User::getId() { return _strId; }
long User::getBal() { return _lBal; }
void User::setBal(long lBal) { _lBal = lBal; }
string User::getPin() { return _strPin; }
void User::setPin(string strPin) { _strPin = strPin; }
string Admin::getId() { return _strUser; }
void User::setId(string strId) { _strId = strId; }
void User::setName(string strName) { _strName = strName; }
void User::setType(string strType) { _strType = strType; }
void User::setCnt(int iCnt) { _iCnt = iCnt; }
string User::getName() { return _strName; }
string User::getType() { return _strType; }

template<typename T>
Node<T>::Node(T tData) {
    _tData = tData;
    _pNext = nullptr;
}

template<typename T>
TaiKhoan<T>::TaiKhoan() {
    _pHead = nullptr;
    _pTail = nullptr;
}

template<typename T>
TaiKhoan<T>::~TaiKhoan() {
    Node<T>* pHead = _pHead;
    while (pHead) {
        Node<T>* pTam = pHead->_pNext;
        delete pHead;
        pHead = pTam;
    }
}

template<typename T>
void TaiKhoan<T>::addTaiKhoan(T tData) {
    Node<T>* pNewTaiKhoan = new Node<T>(tData);
    if (_pHead == nullptr) {
        _pHead = _pTail = pNewTaiKhoan;
    }
    else {
        _pTail->_pNext = pNewTaiKhoan;
        _pTail = pNewTaiKhoan;
    }
}

template<typename T>
void TaiKhoan<T>::loadFileAdmin() {
    ifstream Fin("Admin.txt");
    string strUser;
    string strPin;
    while (Fin >> strUser >> strPin) {
        T tAccount;
        tAccount.setUser(strUser);
        tAccount.setPin(strPin);
        addTaiKhoan(tAccount);
    }
    Fin.close();
}

template<typename T>
void TaiKhoan<T>::loadFileUser() {
    ifstream Fin("TheTu.txt");
    string strId;
    string strPin;
    while (Fin >> strId >> strPin) {
        T tAccount;
        tAccount.setId(strId);
        tAccount.setPin(strPin);
        string strFileName;
        strFileName = "[" + tAccount.getId() + "].txt";
        tAccount.setInformation(strFileName);
        addTaiKhoan(tAccount);
    }
    Fin.close();
}

template<typename T>
void TaiKhoan<T>::doDisplay() {
    goTo(0, 9, 14);
    cout << "* * * * * DANH SACH CAC TAI KHOAN * * * * * *" << endl;
    viTriXY("DANH SACH CAC TAI KHOAN", 0, 3, 10, 9);
    int iPosY = 10, iThuTu = 1;
    for (Node<T>* pTam = _pHead; pTam != NULL; pTam = pTam->_pNext) {
        if (iThuTu < 10) {
            goTo(0, iPosY, 14);
            cout << "* ";
            textColor(11);
            cout << iThuTu << ". ID: " << pTam->_tData.getId() << "                     ";
            textColor(14);
            cout << "*" << endl;
            iPosY++;
            goTo(0, iPosY, 14);
            cout << "*    ";
            textColor(11);
            cout << "PIN: " << pTam->_tData.getPin() << "                            ";
            textColor(14);
            cout << "*" << endl;
        }
        else {
            goTo(0, iPosY, 14);
            cout << "* ";
            textColor(11);
            cout << iThuTu << ".ID: " << pTam->_tData.getId() << "                     ";
            textColor(14);
            cout << "*" << endl;
            iPosY++;
            goTo(0, iPosY, 14);
            cout << "*    ";
            textColor(11);
            cout << "PIN: " << pTam->_tData.getPin() << "                            ";
            textColor(14);
            cout << "*" << endl;
        }
        iPosY++;
        iThuTu++;
    }
    goTo(0, iPosY, 14);
    cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
}

template<typename T>
bool TaiKhoan<T>::testLogin(string strId, string strPin) {
    Node<T>* pTam = _pHead;
    while (pTam != NULL) {
        if (pTam->_tData.getId() == strId)
        {
            if (pTam->_tData.testLogin(strId, strPin))
                return true;
            else
                return false;
        }
        pTam = pTam->_pNext;
    }
    goTo(1, 5, 4);
    cout << "Tai khoan khong ton tai!        ";
    return false;
}

template<typename T>
void TaiKhoan<T>::inFileUser() {
    ofstream Fout("TheTu.txt");
    for (Node<T>* pTam = _pHead; pTam != NULL; pTam = pTam->_pNext) {
        pTam->_tData.inFileUser();
        Fout << pTam->_tData.getId() << endl;
        Fout << pTam->_tData.getPin() << endl;
    }
    Fout.close();
}

template<typename T>
void TaiKhoan<T>::addUser(string strId, string strName, string strType) {
    for (Node<T>* pTam = _pHead; pTam != NULL; pTam = pTam->_pNext) {
        if (pTam->_tData.getId() == strId) {
            g_bThem = true;
            break;
        }
    }

    if (!g_bThem) {
        T tAccount;
        tAccount.setId(strId);
        tAccount.setPin("123456");
        tAccount.setName(strName);
        tAccount.setBal(0);
        tAccount.setType(strType);
        tAccount.setCnt(3);
        addTaiKhoan(tAccount);
        string strFileName = "[" + strId + "].txt";
        ofstream Fout;
        Fout.open(strFileName);
        Fout << strId << endl;
        Fout << strName << endl;
        Fout << 0 << endl;
        Fout << strType << endl;
        Fout << 3 << endl;
        Fout.close();
        strFileName = "[LichSu" + strId + "].txt";
        Fout.open(strFileName);
        Fout.close();
        Us.inFileUser();
    }
}

template<typename T>
void TaiKhoan<T>::xoaUser(string strId) {
    for (Node<T>* pTam = _pHead; pTam != NULL; pTam = pTam->_pNext) {
        if (pTam->_tData.getId() == strId) {
            if (pTam == _pHead) {
                Node<T>* pCur = _pHead;
                _pHead = _pHead->_pNext;
                delete pCur;
                g_bXoa = true;
                break;
            }
            if (pTam == _pTail) {
                for (Node<T>* pCur = _pHead; pCur != NULL; pCur = pCur->_pNext) {
                    if (pCur->_pNext == _pTail) {
                        Node<T>* pTmp = _pTail;
                        pCur->_pNext = NULL;
                        _pTail = pCur;
                        delete pTmp;
                    }
                }
                g_bXoa = true;
                break;
            }
            if (pTam != NULL) {
                for (Node<T>* pCur = _pHead; pCur != NULL; pCur = pCur->_pNext) {
                    if (pCur->_pNext == pTam) {
                        Node<T>* pTmp = pTam;
                        pCur->_pNext = pTam->_pNext;
                        delete pTmp;
                    }
                }
                g_bXoa = true;
                break;
            }
        }
    }
    string strFileName = "[" + strId + "].txt";
    remove(strFileName.c_str());
    Us.inFileUser();
}

template<typename T>
void TaiKhoan<T>::duyetMoKhoa() {
    goTo(0, 9, 14);
    cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "*          MO KHOA TAI KHOAN USER           *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
    viTriXY("MO KHOA TAI KHOAN USER", 0, 3, 11, 10);
    map<int, string> mUser;
    int iPosY = 15, iThuTu = 0;
    Node<T>* pTam = _pHead;
    while (pTam) {
        if (pTam->_tData.getCnt() == 0) {
            goTo(0, iPosY, 14);
            iThuTu++;
            cout << "* ";
            textColor(2);
            cout << iThuTu << ". ";
            viTriXY(pTam->_tData.getId(), 0, 3, 5, iPosY);
            cout << "                         " << endl;
            viTriXY("*", 0, 14, 44, iPosY);
            mUser[iThuTu] = pTam->_tData.getId();
            iPosY++;
        }
        pTam = pTam->_pNext;
    }
    if (iThuTu > 0) {
        goTo(0, iPosY, 14);
        cout << "*                                           *" << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
        diChuyenMoKhoa(mUser, 0, iThuTu, 5, 14);
    }
    else {
        viTriXY("*                                           *", 0, 14, 0, 12);
        viTriXY("Khong co tai khoan bi khoa!                ", 0, 2, 1, 12);
        goTo(0, 13, 14);
        cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
        goTo(4, 14, 0);
    }
}

template<typename T>
void TaiKhoan<T>::moKhoa(string strId) {
    Node<T>* pTam = _pHead;
    while (pTam->_tData.getId() != strId) {
        pTam = pTam->_pNext;
    }
    pTam->_tData.setCnt(3);
    Us.inFileUser();
}

template<typename T>
void TaiKhoan<T>::xemThongTin(string strID) {
    Node<T>* pTam = _pHead;
    while (pTam) {
        if (pTam->_tData.getId() == strID) {
            string strId;
            string strName;
            long lBal;
            string strType;
            string strFileName = "[" + strID + "].txt";
            ifstream Fin(strFileName);
            goTo(0, 9, 14);
            cout << "* * * * * * THONG TIN NGUOI DUNG* * * * * * *" << endl;
            cout << "*ID:                                        *" << endl;
            cout << "*Ho ten:                                    *" << endl;
            cout << "*So du:                                     *" << endl;
            cout << "*Loai tien te:                              *" << endl;
            cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
            viTriXY("THONG TIN NGUOI DUNG", 0, 2, 12, 9);
            viTriXY("ID:", 0, 3, 1, 10);
            viTriXY("Ho ten:", 0, 3, 1, 11);
            viTriXY("SO du:", 0, 3, 1, 12);
            viTriXY("Loai tien te:", 0, 3, 1, 13);
            Fin >> strId;
            Fin.ignore();
            getline(Fin, strName);
            Fin >> lBal;
            Fin >> strType;
            goTo(5, 10, 7);
            cout << strId;
            goTo(9, 11, 7);
            cout << strName;
            goTo(8, 12, 7);
            cout << lBal;
            goTo(15, 13, 7);
            cout << strType;
            goTo(3, 15, 0);
            system("PAUSE");
        }
        pTam = pTam->_pNext;
    }
}

template<typename T>
void TaiKhoan<T>::rutTien(string strId) {
    Node<T>* pTam = _pHead;
    while (pTam->_tData.getId() != strId) {
        pTam = pTam->_pNext;
    }
    goTo(0, 9, 14);
    cout << "* * * * * * * * * RUT TIEN* * * * * * * * * *" << endl;
    cout << "*                                           *" << endl;
    cout << "*Nhap so tien can rut:                      *" << endl;
    cout << "*So du tai khoan:                           *" << endl;
    cout << "*Nhap ma PIN de xac nhan:                   *" << endl;
    goTo(18, 12, 7);
    cout << pTam->_tData.getBal() << pTam->_tData.getType() << endl;
    textColor(14);
    cout << "*                                           *" << endl;
    cout << "*                                           *" << endl;
    cout << "*                                           *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
    viTriXY("RUT TIEN", 0, 2, 18, 9);
    viTriXY("Nhap so tien can rut:", 0, 3, 1, 11);
    viTriXY("So du tai khoan:", 0, 3, 1, 12);
    viTriXY("Nhap ma PIN de xac nhan:", 0, 3, 1, 13);

    goTo(26, 11, 7);
    long lSoTien;
    cin >> lSoTien;
    if (!kiemTraTien(pTam->_tData.getType(), pTam->_tData.getBal(), lSoTien)) {
        this_thread::sleep_for(chrono::seconds(2));
        giaoDienUser(strId);
    }
    goTo(27, 13, 7);
    string strPin;
    nhapPINXacNhan(strPin, 27, 13);

    if (strPin == "Thoat" || strPin != pTam->_tData.getPin()) {
        viTriXY("Sai ma PIN", 0, 4, 1, 14);
        this_thread::sleep_for(chrono::seconds(2));
        giaoDienUser(strId);
    }

    long lSoDu = pTam->_tData.getBal() - lSoTien;
    pTam->_tData.setBal(lSoDu);
    string strFileName = "[LichSu" + strId + "].txt";
    ofstream Fout(strFileName, ios::app);
    Fout << strId << endl;
    Fout << "Rut tien" << endl;
    Fout << lSoTien << pTam->_tData.getType() << endl;
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    if (ltm.tm_hour < 10) {
        Fout << "0" << ltm.tm_hour << ":";
        if (ltm.tm_min < 10) {
            Fout << "0" << ltm.tm_min << ":";
            if (ltm.tm_sec < 10) {
                Fout << "0" << ltm.tm_sec << endl;
            }
            else {
                Fout << ltm.tm_sec << endl;
            }
        }
        else {
            Fout << ltm.tm_min << ":";
            if (ltm.tm_sec < 10) {
                Fout << "0" << ltm.tm_sec << endl;
            }
            else {
                Fout << ltm.tm_sec << endl;
            }
        }
    }
    else {
        Fout << ltm.tm_hour << ":";
        if (ltm.tm_min < 10) {
            Fout << "0" << ltm.tm_min << ":";
            if (ltm.tm_sec < 10) {
                Fout << "0" << ltm.tm_sec << endl;
            }
            else {
                Fout << ltm.tm_sec << endl;
            }
        }
        else {
            Fout << ltm.tm_min << ":";
            if (ltm.tm_sec < 10) {
                Fout << "0" << ltm.tm_sec << endl;
            }
            else {
                Fout << ltm.tm_sec << endl;
            }
        }
    }
    if (ltm.tm_mday < 10) {
        Fout << "0" << ltm.tm_wday << "/";
        if (ltm.tm_mon + 1 < 10) {
            Fout << "0" << 1 + ltm.tm_mon << "/" << 1900 + ltm.tm_year << endl;
        }
    }
    else {
        Fout << ltm.tm_wday << "/";
        if (ltm.tm_mon + 1 < 10) {
            Fout << "0" << 1 + ltm.tm_mon << "/" << 1900 + ltm.tm_year << endl;
        }
    }
    Fout.close();
    Us.inFileUser();
    viTriXY("Xac nhan rut tien thanh cong!              ", 0, 2, 1, 15);
    goTo(3, 17, 0);
    this_thread::sleep_for(chrono::seconds(2));
    giaoDienUser(strId);
}

template<typename T>
void TaiKhoan<T>::chuyenTien(string strId) {
    Node<T>* pTam = _pHead;
    Node<T>* pCur = _pHead;
    while (pTam->_tData.getId() != strId) {
        pTam = pTam->_pNext;
    }
    goTo(0, 9, 14);
    cout << "* * * * * * * * CHUYEN TIEN * * * * * * * * *" << endl;
    cout << "*                                           *" << endl;
    cout << "*Nhap so tien can chuyen:                   *" << endl;
    cout << "*Nhap ID tai khoan nhan:                    *" << endl;
    cout << "*So du tai khoan:                           *" << endl;
    cout << "*Nhap ma PIN de xac nhan:                   *" << endl;
    cout << "*                                           *" << endl;
    cout << "*                                           *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
    viTriXY("CHUYEN TIEN", 0, 2, 16, 9);
    viTriXY("Nhap so tien can chuyen:", 0, 3, 1, 11);
    viTriXY("Nhap ID tai khoan nhan:", 0, 3, 1, 12);
    viTriXY("So du tai khoan:", 0, 3, 1, 13);
    viTriXY("Nhap ma PIN de xac nhan:", 0, 3, 1, 14);
    goTo(18, 13, 7);
    cout << pTam->_tData.getBal() << pTam->_tData.getType() << endl;
    goTo(26, 11, 7);
    long lSoTien;
    cin >> lSoTien;

    if (!kiemTraTien(pTam->_tData.getType(), pTam->_tData.getBal(), lSoTien)) {
        this_thread::sleep_for(chrono::seconds(2));
        giaoDienUser(strId);
    }

    string strIdNhan;
    goTo(25, 12, 7);
    nhapIDXacNhan(strIdNhan, 25, 12);
    if (strIdNhan == "Thoat") {
        this_thread::sleep_for(chrono::seconds(2));
        giaoDienUser(strId);
    }
    while (pCur != NULL && pCur->_tData.getId() != strIdNhan) {
        pCur = pCur->_pNext;
    }
    if (pCur == NULL) {
        goTo(1, 15, 4);
        cout << "Tai khoan nhan tien khong ton tai!         ";
        this_thread::sleep_for(chrono::seconds(2));
        goTo(3, 17, 0);
        giaoDienUser(strId);
    }
    goTo(27, 14, 7);
    string strPin;
    nhapPINXacNhan(strPin, 27, 14);
    if (strPin == "Thoat" || strPin != pTam->_tData.getPin()) {
        goTo(1, 15, 4);
        cout << "Sai ma PIN!                                ";
        this_thread::sleep_for(chrono::seconds(2));
        giaoDienUser(strId);
    }
    long lSoDu = pTam->_tData.getBal() - lSoTien;
    pTam->_tData.setBal(lSoDu);
    string strFileName = "[LichSu" + strId + "].txt";
    ofstream Fout(strFileName, ios::app);
    Fout << strId << endl;
    Fout << "Chuyen tien den " << strIdNhan << endl;
    Fout << lSoTien << pTam->_tData.getType() << endl;

    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    if (ltm.tm_hour < 10) {
        Fout << "0" << ltm.tm_hour << ":";
        if (ltm.tm_min < 10) {
            Fout << "0" << ltm.tm_min << ":";
            if (ltm.tm_sec < 10) {
                Fout << "0" << ltm.tm_sec << endl;
            }
            else {
                Fout << ltm.tm_sec << endl;
            }
        }
        else {
            Fout << ltm.tm_min << ":";
            if (ltm.tm_sec < 10) {
                Fout << "0" << ltm.tm_sec << endl;
            }
            else {
                Fout << ltm.tm_sec << endl;
            }
        }
    }
    else {
        Fout << ltm.tm_hour << ":";
        if (ltm.tm_min < 10) {
            Fout << "0" << ltm.tm_min << ":";
            if (ltm.tm_sec < 10) {
                Fout << "0" << ltm.tm_sec << endl;
            }
            else {
                Fout << ltm.tm_sec << endl;
            }
        }
        else {
            Fout << ltm.tm_min << ":";
            if (ltm.tm_sec < 10) {
                Fout << "0" << ltm.tm_sec << endl;
            }
            else {
                Fout << ltm.tm_sec << endl;
            }
        }
    }

    if (ltm.tm_mday < 10) {
        Fout << "0" << ltm.tm_wday << "/";
        if (ltm.tm_mon + 1 < 10) {
            Fout << "0" << 1 + ltm.tm_mon << "/" << 1900 + ltm.tm_year << endl;
        }
    }
    else {
        Fout << ltm.tm_wday << "/";
        if (ltm.tm_mon + 1 < 10) {
            Fout << "0" << 1 + ltm.tm_mon << "/" << 1900 + ltm.tm_year << endl;
        }
    }

    Fout.close();
    lSoDu = chuyenLoaiTien(pCur->_tData.getType(), pTam->_tData.getType(), pCur->_tData.getBal(), lSoTien);
    lSoTien = chuyenLoaiTien(pCur->_tData.getType(), pTam->_tData.getType(), 0, lSoTien);

    pCur->_tData.setBal(lSoDu);
    strFileName = "[LichSu" + strIdNhan + "].txt";
    Fout.open(strFileName, ios::app);
    Fout << strId << endl;
    Fout << "Nhan tien tu " << strId << endl;
    Fout << lSoTien << pCur->_tData.getType() << endl;
    if (ltm.tm_hour < 10) {
        Fout << "0" << ltm.tm_hour << ":";
        if (ltm.tm_min < 10) {
            Fout << "0" << ltm.tm_min << ":";
            if (ltm.tm_sec < 10) {
                Fout << "0" << ltm.tm_sec << endl;
            }
            else {
                Fout << ltm.tm_sec << endl;
            }
        }
        else {
            Fout << ltm.tm_min << ":";
            if (ltm.tm_sec < 10) {
                Fout << "0" << ltm.tm_sec << endl;
            }
            else {
                Fout << ltm.tm_sec << endl;
            }
        }
    }
    else {
        Fout << ltm.tm_hour << ":";
        if (ltm.tm_min < 10) {
            Fout << "0" << ltm.tm_min << ":";
            if (ltm.tm_sec < 10) {
                Fout << "0" << ltm.tm_sec << endl;
            }
            else {
                Fout << ltm.tm_sec << endl;
            }
        }
        else {
            Fout << ltm.tm_min << ":";
            if (ltm.tm_sec < 10) {
                Fout << "0" << ltm.tm_sec << endl;
            }
            else {
                Fout << ltm.tm_sec << endl;
            }
        }
    }
    Fout << ltm.tm_mday << "/" << 1 + ltm.tm_mon << "/" << 1900 + ltm.tm_year << endl;
    Fout.close();


    Us.inFileUser();
    viTriXY("Xac nhan chuyen tien thanh cong!           ", 0, 2, 1, 16);
    goTo(3, 17, 0);
    this_thread::sleep_for(chrono::seconds(2));
    giaoDienUser(strId);

}

template<typename T>
void TaiKhoan<T>::xemGiaoDich(string strID) {
    goTo(0, 9, 14);
    int iPosY = 9;
    cout << "* * * * * * *LICH SU GIAO DICH* * * * * * * *" << endl;
    viTriXY("LICH SU GIAO DICH", 0, 2, 13, 9);
    goTo(0, 10, 11);
    string strFileName = "[LichSu" + strID + "].txt";
    ifstream Fin;
    Fin.open(strFileName);
    if (Fin.peek() != ifstream::traits_type::eof()) {
        string strId;
        string strLoaiGiaoDich;
        string strSoTien;
        string strGio;
        string strNgay;
        while (Fin >> strId) {
            Fin.ignore();
            getline(Fin, strLoaiGiaoDich);
            Fin >> strSoTien;
            Fin >> strGio;
            Fin >> strNgay;

            cout << strId << endl;
            cout << strLoaiGiaoDich << endl;
            cout << strSoTien << endl;
            cout << strGio << endl;
            cout << strNgay << endl << endl;
            iPosY += 6;
        }
    }
    else {
        iPosY++;
        textColor(14);
        cout << "*                                           *" << endl;
        goTo(1, iPosY, 4);
        cout << "Khong co du lieu giao dich!                " << endl;
        iPosY++;
    }
    goTo(0, iPosY, 14);
    cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
    goTo(0, iPosY + 2, 0);
    system("PAUSE");
    giaoDienUser(strID);
}

template<typename T>
void TaiKhoan<T>::doiMaPin(string strId) {
    Node<T>* pTam = _pHead;
    while (pTam->_tData.getId() != strId) {
        pTam = pTam->_pNext;
    }
    goTo(0, 9, 14);
    cout << "* * * * * * * * DOI MA PIN* * * * * * * * * *" << endl;
    cout << "*Nhap ma PIN cu:                            *" << endl;
    cout << "*Nhap ma PIN moi:                           *" << endl;
    cout << "*Xac nhan lai ma PIN moi:                   *" << endl;
    cout << "*                                           *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
    viTriXY("DOI MA PIN", 0, 3, 16, 9);
    viTriXY("Nhap ma PIN cu:", 0, 2, 1, 10);
    viTriXY("Nhap ma PIN moi:", 0, 2, 1, 11);
    viTriXY("Xac nhan lai ma PIN moi:", 0, 2, 1, 12);
    goTo(17, 10, 7);
    string strOldPin;
    cin >> strOldPin;
    if (pTam->_tData.getPin() == strOldPin)
    {
        goTo(18, 11, 7);
        string strNewPin;
        cin >> strNewPin;
        if (strNewPin.size() == 6 && kiemTraChuoi(strNewPin))
        {
            goTo(26, 12, 7);
            string strXacNhan;
            cin >> strXacNhan;
            if (strXacNhan.size() == 6 && strXacNhan == strNewPin)
            {
                pTam->_tData.setPin(strNewPin);
                Us.inFileUser();
                goTo(1, 13, 2);
                cout << "Doi ma pin thanh cong!                     *";

                goTo(1, 15, 0);
                this_thread::sleep_for(chrono::seconds(1));
                giaoDienUser(strId);
            }
            else
            {
                goTo(1, 13, 4);
                cout << "Nhap lai ma pin khong khop voi ma pin moi! *";

                doiMaPin(strId);
            }
        }
        else
        {
            goTo(1, 13, 4);
            cout << "Ma pin moi gom 6 chu so!                   *";

            doiMaPin(strId);
        }
    }
    else {
        goTo(1, 13, 4);
        cout << "Ma pin cu sai!                             *";

        doiMaPin(strId);
    }

}

void giaoDienDangNhap() {
    system("CLS");
    textColor(14);//yellow
    cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "*           Ta Cha Hao Bank             *" << endl;
    cout << "*                                       *" << endl;
    cout << "*   Chao mung ban da den voi chung toi  *" << endl;
    cout << "*                                       *" << endl;
    cout << "*   Dang nhap                           *" << endl;
    cout << "*   Thoat                               *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
    viTriXY("Ta Cha Hao Bank", 0, 1, 12, 1);
    viTriXY("Chao mung ban da den voi chung toi", 0, 2, 4, 3);
    map<int, string> mTCHB;
    mTCHB[1] = "Dang nhap";
    //MapTCHB[2] = "Dang ki";
    mTCHB[2] = "Thoat";
    diChuyen(mTCHB, 1, 2, 4, 4);

}

void giaoDienForm(string strText) {
    goTo(0, 9, 0);
    this_thread::sleep_for(chrono::seconds(1));
    textColor(14);
    if (strText == "Ta Cha Hao Bank") {
        giaoDienDangNhap();
    }
    if (strText == "Dang nhap") {
        dangNhap();
    }
    if (strText == "Dang nhap Admin") {
        dangNhapAdmin();
    }
    if (strText == "Dang nhap User") {
        dangNhapUser();
    }
    if (strText == "Admin") {
        giaoDienAdmin();
    }
    if (strText == "Thoat") {
        thoatForm();
    }
}

void dangNhap() {
    system("CLS");
    textColor(14);
    cout << "* * * * * * * * *DANG NHAP* * * * * * * *" << endl;
    cout << "*                                       *" << endl;
    cout << "*   1.Dang nhap Admin                   *" << endl;
    cout << "*   2.Dang nhap User                    *" << endl;
    cout << "*                                       *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
    viTriXY("DANG NHAP", 0, 5, 17, 0);
    map<int, string> mDangNhap;
    mDangNhap[1] = "Dang nhap Admin";
    mDangNhap[2] = "Dang nhap User";
    diChuyen(mDangNhap, 1, 2, 6, 1);
}

void thoatForm() {
    system("CLS");
    cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "*           Ta Cha Hao Bank             *" << endl;
    cout << "*                                       *" << endl;
    cout << "*     Cam on ban da su dung dich vu     *" << endl;
    cout << "*                                       *" << endl;
    cout << "*                                       *" << endl;
    cout << "*                                       *" << endl;
    cout << "*                                       *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
    viTriXY("Ta Cha Hao Bank", 0, 1, 12, 1);
    viTriXY("Cam on ban da su dung dich vu", 0, 5, 6, 3);
    goTo(0, 10, 0);

    Us.inFileUser();
    exit(0);
}

void dangNhapAdmin() {
    system("CLS");
    map<int, string>mDangNhap;
    cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "*           DANG NHAP ADMIN             *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "*User:                                  *" << endl;
    cout << "*Pin:                                   *" << endl;
    cout << "*                                       *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
    viTriXY("DANG NHAP ADMIN", 0, 2, 12, 1);
    viTriXY("User:", 0, 3, 1, 3);
    viTriXY("Pin:", 0, 3, 1, 4);
    mDangNhap[1] = "User:";
    mDangNhap[2] = "Pin:";
    diChuyenDangNhap(mDangNhap, 6, 2);
}

void dangNhapUser() {
    system("CLS");
    map<int, string>mDangNhap;
    cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "*           DANG NHAP USER              *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "*ID:                                    *" << endl;
    cout << "*Pin:                                   *" << endl;
    cout << "*                                       *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
    viTriXY("DANG NHAP USER", 0, 2, 12, 1);
    viTriXY("ID:", 0, 3, 1, 3);
    viTriXY("Pin:", 0, 3, 1, 4);
    mDangNhap[1] = "ID:";
    mDangNhap[2] = "Pin:";
    diChuyenDangNhap(mDangNhap, 6, 2);
}

void giaoDienForm(string strText, string strId) {
    goTo(0, 9, 14);
    this_thread::sleep_for(chrono::seconds(1));
    giaoDienUser(strId);
}

void giaoDienAdmin() {
    textColor(14);
    system("CLS");
    cout << "                Chao mung Admin              " << endl;
    cout << "* * * * * * * * * * *MENU * * * * * * * * * *" << endl;
    cout << "    1.Xem danh sach tai khoan" << endl;
    cout << "    2.Them tai khoan" << endl;
    cout << "    3.Xoa tai khoan" << endl;
    cout << "    4.Mo khoa tai khoan" << endl;
    cout << "    5.Thoat" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
    viTriXY("Chao mung Admin", 0, 2, 16, 0);
    map<int, string> mAdmin;
    //MapViTri[0] = "Admin";
    mAdmin[1] = "Xem danh sach tai khoan";
    mAdmin[2] = "Them tai khoan";
    mAdmin[3] = "Xoa tai khoan";
    mAdmin[4] = "Mo khoa tai khoan";
    mAdmin[5] = "Thoat";
    int iPosY = 1;
    diChuyenChucNang(mAdmin, 1, 5, 6, iPosY);
    switch (iPosY) {
    case 1:
        Us.doDisplay();
        textColor(0);
        system("PAUSE");
        break;
    case 2:
        themTaiKhoan();
        this_thread::sleep_for(chrono::seconds(2));
        break;
    case 3:
        xoaTaiKhoan();
        goTo(0, 15, 14);
        this_thread::sleep_for(chrono::seconds(2));
        break;
    case 4:
        Us.duyetMoKhoa();
        this_thread::sleep_for(chrono::seconds(2));
        break;
    case 5:
        giaoDienForm("Ta Cha Hao Bank");
        break;
    }

    giaoDienAdmin();
}

void themTaiKhoan() {
    this_thread::sleep_for(chrono::seconds(1));
    goTo(0, 9, 14);
    cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "*            THEM TAI KHOAN USER            *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "*ID:                                        *" << endl;
    cout << "*Ho ten:                                    *" << endl;
    cout << "*Loai tien te:                              *" << endl;
    cout << "*                                           *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
    viTriXY("THEM TAI KHOAN USER", 0, 2, 13, 10);
    viTriXY("ID:", 0, 3, 1, 12);
    viTriXY("Ho ten:", 0, 3, 1, 13);
    viTriXY("Loai tien te:", 0, 3, 1, 14);
    map<int, string> mThemUser;
    mThemUser[0] = "Them";
    mThemUser[1] = "ID:";
    mThemUser[2] = "Ho ten:";
    mThemUser[3] = "Loai tien te:";
    diChuyenThemVaXoa(mThemUser, 1, 3, 2, 11);
}

void xoaTaiKhoan() {
    this_thread::sleep_for(chrono::seconds(1));
    goTo(0, 9, 14);
    cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "*            XOA TAI KHOAN USER             *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "*ID:                                        *" << endl;
    cout << "*                                           *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
    viTriXY("XOA TAI KHOAN USER", 0, 2, 13, 10);
    viTriXY("ID:", 0, 3, 1, 12);
    map<int, string>mXoaUser;
    mXoaUser[0] = "Xoa";
    mXoaUser[1] = "ID:";
    diChuyenThemVaXoa(mXoaUser, 1, 1, 2, 11);
}

void giaoDienUser(string strId) {
    textColor(14);
    goTo(0, 0, 14);
    system("CLS");
    cout << "                Chao mung User               " << endl;
    cout << "* * * * * * * * * * *MENU * * * * * * * * * *" << endl;
    cout << "    1.Xem thong tin tai khoan" << endl;
    cout << "    2.Rut tien" << endl;
    cout << "    3.Chuyen tien" << endl;
    cout << "    4.Xem noi dung giao dich" << endl;
    cout << "    5.Doi ma pin" << endl;
    cout << "    6.Thoat" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
    viTriXY("Chao mung User", 0, 3, 16, 0);
    map<int, string> mUser;
    mUser[1] = "Xem thong tin tai khoan";
    mUser[2] = "Rut tien";
    mUser[3] = "Chuyen tien";
    mUser[4] = "Xem noi dung giao dich";
    mUser[5] = "Doi ma pin";
    mUser[6] = "Thoat";
    int iPosY = 1;
    diChuyenChucNang(mUser, 1, 6, 6, iPosY);
    switch (iPosY) {
    case 1:
        Us.xemThongTin(strId);
        break;
    case 2:
        Us.rutTien(strId);
        break;
    case 3:
        Us.chuyenTien(strId);
        break;
    case 4:
        Us.xemGiaoDich(strId);
        break;
    case 5:
        Us.doiMaPin(strId);
        break;
    case 6:
        giaoDienForm("Ta Cha Hao Bank");
        break;
    }
    this_thread::sleep_for(chrono::seconds(1));
    giaoDienUser(strId);
}

void textColor(int iColor) {
    SetConsoleTextAttribute(hConsole, iColor);
}

void goTo(int iPosX, int iPosY, int iColor) {
    COORD Position;
    Position.X = iPosX;
    Position.Y = iPosY;
    textColor(iColor);
    SetConsoleCursorPosition(hConsole, Position);
}

void viTriXY(string strText, int iPos, int iColor, int iPosX, int iPosY) {
    goTo(iPosX, iPosY + iPos, iColor);
    cout << strText;
}

void diChuyen(map<int, string>mViTri, int iPos, int iPosMax, int iPosX, int iPosY) {

    viTriXY(mViTri[iPos], iPos, 139, iPosX, iPosY);

    string strText = "";
    char cNhap;
    while ((cNhap = _getch()) != 27) {
        switch (cNhap) {
        case 13:
            giaoDienForm(mViTri[iPos]);
        case 72://UP
            viTriXY(mViTri[iPos], iPos, 14, iPosX, iPosY);

            if (iPos > 1) {
                strText = mViTri[iPos];
                viTriXY(strText, iPos--, 14, iPosX, iPosY);
                iPos--;
            }

        case 80://DOWN
            viTriXY(mViTri[iPos], iPos, 14, iPosX, iPosY);
            if (iPos < iPosMax) {
                iPos++;
                strText = mViTri[iPos];
                viTriXY(mViTri[iPos], iPos, 139, iPosX, iPosY);
            }
            break;
        }
    }
    if (strText == "Dang nhap User" || strText == "Dang nhap Admin") {
        giaoDienForm("Ta Cha Hao Bank");
    }
    if (strText == "Thoat") {
        giaoDienForm("Thoat");
    }
}

void nhapIDXacNhan(string& strText, int iPosX, int iPosY) {
    char cNhap;
    while ((cNhap = _getch()) != 27) {
        if (cNhap == 13) {
            return;
        }
        if (cNhap == 8 && strText.length() > 0) {
            strText.pop_back();
            cout << "\b \b";
        }
        else {
            if (cNhap >= 48 && cNhap <= 57) {
                if (strText.size() == 14) {
                    viTriXY("Ma ID gom 14 chu so!                   ", 0, 4, 1, iPosY + 3);
                }
                else {
                    strText += cNhap;
                    viTriXY(strText, 0, 7, iPosX, iPosY);
                }
            }
            else {
                viTriXY("Ma ID chi bao gom cac chu so!          ", 0, 4, 1, iPosY + 3);
            }
        }
    }
    strText = "Thoat";
}

void nhapPINXacNhan(string& strText, int iPosX, int iPosY) {
    char cNhap;
    while ((cNhap = _getch()) != 27) {
        if (cNhap == 13) {
            return;
        }
        if (cNhap == 8 && strText.length() > 0) {
            strText.pop_back();
            cout << "\b \b";
        }
        else {
            if (cNhap >= 48 && cNhap <= 57) {
                if (strText.size() == 6) {
                    viTriXY("Ma PIN gom 6 chu so!                   ", 0, 4, 1, iPosY + 1);
                }
                else {
                    strText += cNhap;
                    viTriXY(strText, 0, 7, iPosX, iPosY);
                }
            }
            else {
                viTriXY("Ma PIN chi bao gom cac chu so!         ", 0, 4, 1, iPosY + 1);
            }
        }
    }
    strText = "Thoat";
}

void nhapID(string& strText, int iPosX, int iPosY) {
    char cNhap;
    while ((cNhap = _getch()) != 27) {
        if (cNhap == 13) {
            return;
        }
        if (cNhap == 8 && strText.length() > 0) {
            strText.pop_back();
            cout << "\b \b";
        }
        else {
            if (cNhap >= 48 && cNhap <= 57) {
                if (strText.size() == 14) {
                    viTriXY("Ma ID gom 14 chu so!                   ", 0, 4, 1, iPosY + 2);
                    goTo(7 + strText.size(), 3, 14);
                }
                else {
                    strText += cNhap;
                    viTriXY(strText, 0, 7, iPosX, iPosY);
                }
            }
            else {
                viTriXY("Ma ID chi bao gom cac chu so!          ", 0, 4, 1, iPosY + 2);
                goTo(7 + strText.size(), 3, 14);
            }
        }
    }
    strText = "Thoat";
}

void nhapPIN(string& strText, int iPosX, int iPosY) {
    string strTam = "";
    char cNhap;
    while ((cNhap = _getch()) != 27) {
        if (cNhap == 13) {
            return;
        }
        if (cNhap == 8 && strText.length() > 0) {
            strText.pop_back();
            strTam.pop_back();
            cout << "\b \b";
            viTriXY(strTam, 0, 7, iPosX, iPosY);
        }
        else {
            if (cNhap >= 48 && cNhap <= 57) {
                if (strText.size() == 6) {
                    viTriXY("Ma PIN gom 6 chu so!                   ", 0, 4, 1, iPosY + 1);
                    goTo(13, 4, 14);
                }
                else {
                    strText += cNhap;
                    strTam += "*";
                    viTriXY(strTam, 0, 7, iPosX, iPosY);
                }
            }
            else {
                viTriXY("Ma PIN chi bao gom cac chu so!         ", 0, 4, 1, iPosY + 1);
                goTo(13 + strText.size(), 4, 14);
            }
        }
    }
    strText = "Thoat";
}

void diChuyenDangNhap(map<int, string>mDangNhap, int iPosX, int iPosY) {
    string strId;
    string strPin;
    char cNhap;
    string strText = "";
    goTo(7, 3, 14);
    nhapID(strId, 7, 3);
    if (strId == "Thoat") {
        Us.inFileUser();
        giaoDienForm("Dang nhap");
    }
    goTo(7, 4, 14);
    nhapPIN(strPin, 7, 4);
    if (strPin == "Thoat") {
        Us.inFileUser();
        giaoDienForm("Dang nhap");
    }
    if (mDangNhap[1] == "User:") {
        if (Ad.testLogin(strId, strPin)) {
            this_thread::sleep_for(chrono::seconds(2));
            giaoDienForm("Admin");
        }
        goTo(7 + strPin.size(), 4, 0);
        this_thread::sleep_for(chrono::seconds(2));
        giaoDienForm("Dang nhap Admin");
    }
    else {
        if (Us.testLogin(strId, strPin)) {
            if (strPin == "123456") {
                Us.doiMaPin(strId);
            }
            else {
                Us.inFileUser();
                giaoDienForm("User", strId);
            }
        }
        Us.inFileUser();
        goTo(7 + strPin.size(), 4, 0);
        this_thread::sleep_for(chrono::seconds(2));
        giaoDienForm("Dang nhap User");
    }
}

void diChuyenChucNang(map<int, string> mViTri, int iPos, int iPosMax, int iPosX, int& iPosY) {
    goTo(iPosX, 3, 0);
    viTriXY(mViTri[iPos], iPos, 139, iPosX, iPosY);
    int _iPosY = iPosY;
    string strText;
    char cNhap;
    while ((cNhap = _getch()) != 'k') {
        switch (cNhap) {
        case 13:
            iPosY = _iPosY;
            return;
        case 72://UP
            viTriXY(mViTri[iPos], iPos, 14, iPosX, iPosY);
            if (iPos > 0) {
                strText = mViTri[iPos];
                viTriXY(strText, iPos--, 14, iPosX, iPosY);
                iPos--;
                _iPosY = _iPosY - 1;
            }
        case 80://DOWN
            viTriXY(mViTri[iPos], iPos, 14, iPosX, iPosY);
            if (iPos < iPosMax) {
                iPos++;
                strText = mViTri[iPos];
                viTriXY(strText, iPos, 139, iPosX, iPosY);
                _iPosY = _iPosY + 1;
            }
            break;
        case 27:
            if (strText == "Thoat") {
                giaoDienForm("Thoat");
            }
            else giaoDienForm("Ta Cha Hao Bank");
        }
    }
}

void diChuyenThemVaXoa(map<int, string> mViTri, int iPos, int iPosMax, int iPosX, int iPosY) {
    goTo(5, 12, 7);
    if (mViTri[0] == "Them") {
        string strId;
        string strName;
        string strType;
        cin >> strId;
        if (strId.size() == 14 && kiemTraChuoi(strId)) {
            goTo(9, 13, 7);
            cin.ignore();
            getline(cin, strName);
            goTo(15, 14, 7);
            cin >> strType;
            if (strType == "VND" || strType == "USD") {
                Us.addUser(strId, strName, strType);
                if (!g_bThem) {
                    goTo(1, 15, 2);
                    cout << "Them tai khoan thanh cong!           ";
                    goTo(3, 17, 0);
                }
                else {
                    goTo(1, 15, 4);
                    cout << "ID da ton tai!              ";
                    g_bThem = false;
                }
            }
            else {
                goTo(1, 15, 4);
                cout << "Loai tien te la VND hoac USD!           ";
                themTaiKhoan();
            }
        }
        else {
            goTo(1, 15, 4);
            cout << "ID gom 14 chu so!               ";
            themTaiKhoan();
        }
    }
    else {
        string strId;
        goTo(5, 12, 14);
        cin >> strId;
        if (strId.size() == 14) {
            Us.xoaUser(strId);
            if (g_bXoa) {
                goTo(1, 13, 2);
                cout << "Xoa tai khoan thanh cong!           ";
                g_bXoa = false;
            }
            else {
                goTo(1, 13, 4);
                cout << "ID khong ton tai!            ";

                xoaTaiKhoan();
            }
        }
        else {
            goTo(1, 13, 4);
            cout << "ID gom 14 chu so!            ";
            xoaTaiKhoan();
        }
    }
}

void diChuyenMoKhoa(map<int, string> mMoKhoa, int iPos, int iPosMax, int iPosX, int iPosY) {
    viTriXY("* * * * * Chon tai khoan can mo khoa* * * * *", 0, 14, 0, 13);
    cout << endl << "*                                           *" << endl;
    viTriXY("Chon tai khoan can mo khoa", 0, 3, 10, 13);
    iPos++;
    viTriXY(mMoKhoa[iPos], iPos, 139, iPosX, iPosY);
    string strText = "";
    char cNhap;
    while ((cNhap = _getch()) != 'k') {
        switch (cNhap) {
        case 13:
            Us.moKhoa(mMoKhoa[iPos]);
            goTo(1, iPosY + iPosMax + 1, 2);
            cout << "Da mo khoa tai khoan!";
            this_thread::sleep_for(chrono::seconds(3));
            giaoDienAdmin();
        case 72:
            viTriXY(mMoKhoa[iPos], iPos, 3, iPosX, iPosY);
            if (iPos > 1) {
                strText = mMoKhoa[iPos];
                viTriXY(strText, iPos--, 3, iPosX, iPosY);
                iPos--;
            }
        case 80:
            viTriXY(mMoKhoa[iPos], iPos, 3, iPosX, iPosY);
            if (iPos < iPosMax) {
                iPos++;
                strText = mMoKhoa[iPos];
                viTriXY(mMoKhoa[iPos], iPos, 139, iPosX, iPosY);
            }
            break;
        case 27:
            return;
        }
    }
}

bool tinhBoiSo(string strType, long lSoTien, long lBal) {
    if (strType == "VND") {
        if (lSoTien % 50000 != 0) {
            return false;
        }
        return true;
    }
    if (strType == "USD") {
        if (lSoTien % 2 != 0) {
            return false;
        }
        return true;
    }
    return false;
}

bool kiemTraTien(string strType, long lBal, long lSoTien) {
    if (strType == "VND") {
        if (lSoTien < 50000) {
            goTo(1, 15, 4);
            cout << "So tien khong duoc it hon 50000 VND        ";
            return false;
        }
        if ((lSoTien + 50000) > lBal) {
            goTo(1, 15, 4);
            cout << "So du khong duoc it hon 50000 VND          ";
            return false;
        }
        if (!tinhBoiSo(strType, lSoTien, lBal)) {
            goTo(1, 15, 4);
            cout << "So tien phai la boi so cua 50000 VND       ";
            return false;
        }
        return true;
    }
    if (strType == "USD") {
        if (lSoTien < 2) {
            goTo(1, 15, 4);
            cout << "So tien khong duoc it hon 2 USD            ";
            return false;
        }
        if ((lSoTien + 2) > lBal) {
            goTo(1, 15, 4);
            cout << "So du khong duoc it hon 2 USD              ";
            return false;
        }
        if (!tinhBoiSo(strType, lSoTien, lBal)) {
            goTo(1, 15, 4);
            cout << "So tien phai la boi so cua 2 USD           ";
            return false;
        }
        return true;
    }
    return false;
}

long chuyenLoaiTien(string strTypeNhan, string strTypeChuyen, long lBal, long lTienNhan) {
    map<string, long>mChuyenDoi;
    mChuyenDoi["VND"] = 25000;
    mChuyenDoi["USD"] = 1;
    if (strTypeNhan != strTypeChuyen) {
        lBal += (mChuyenDoi[strTypeNhan] * lTienNhan) / mChuyenDoi[strTypeChuyen];
    }
    else {
        lBal += lTienNhan;
    }
    return lBal;
}

int main() {
    Ad.loadFileAdmin();
    Us.loadFileUser();
    giaoDienDangNhap();
}
