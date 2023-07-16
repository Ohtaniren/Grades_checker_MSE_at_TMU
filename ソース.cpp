#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

/*�N���X*/
//���ƃN���X�̒�`�i�ȖڌQ�C�Ȗڎ�ށC�Ȗږ��C�P�ʁC���сC�N�x�j
struct lecture {
public:
	string category;//�ȖڌQ�̒ǉ�
	string lecturekinds;//�Ȗڎ�ނ̒ǉ�
	string lecturenum;
	string lecturename;
	float unit;
	int value;
	int year;

	lecture(const string& c, const string& k, const string& num, const string& name, float u, int v, int y)
		: category(c), lecturekinds(k), lecturenum(num), lecturename(name), unit(u), value(v), year(y)
	{}
};
//3�N�K�v�P�ʐ��N���X�̒�`�i�v�Z�������̂������ɂ��Ă͂߂Ă����j
struct Unitnum3 {
public:
	float unit1;//���{�ȖڌQ�C��ՉȖڌQ�C�L�����A����̒P�ʐ�//(3�N:14�ȏ�C4�N:14�ȏ�)

	float unit2;//��b�[�~�i�[��//(3�N:2�C4�N:2)

	float unit3;//��񃊃e���V�[���H//(3�N:2�C4�N:2)

	float unit4;//����Ȗځi���H�p��j//(3�N:8�C4�N:8)

	float unit5;//���n���ʊ�b�Ȗ�//(3�N:20�ȏ�C4�N:20�ȏ�)

	float unit6;//�R�[�X���ʊ�b�Ȗځi�K�C�j�F//(3�N:16)

	float unit7;//�R�[�X���ʊ�b�Ȗځi�I���j�F//(3�N:10�ȏ�)

	float unit8;//�R�[�X���ʐ��C�R�[�X���ȖڌQ�F//(32�P�ʈȏざ�R�[�X���ȖڌQ�F�����R�[�X�i�m�\ / ���́j�̉ȖڂɌ���)

	float unit9;//�m�\���̉��p����//(3�N:2�C4�N:2)

	float unit10;//���C����ȖځC�ی��̈�ȖځC���n���ʊ�b�ȖځC��勳��ȖڌQ�F(3�N:86�ȏ�,4�N:104�ȏ�)

	float unit11;//���P��//(3�N:112�ȏ�C4�N:130�ȏ�)//

	float unit12;//��勳��ȖڌQ//(3�N:62)

	Unitnum3(float u1, float u2, float u3, float u4, float u5, float u6, float u7, float u8, float u9, float u10, float u11, float u12)
		: unit1(u1), unit2(u2), unit3(u3), unit4(u4), unit5(u5), unit6(u6), unit7(u7), unit8(u8), unit9(u9), unit10(u10), unit11(u11), unit12(u12)
	{}
};
//4�N�K�v�P�ʐ�(���Ɨv��)�N���X�̒�`�i�v�Z�������̂������ɂ��Ă͂߂Ă����j
struct Unitnum4 {
public:
	float unit1;//�R�[�X���ʊ�b�Ȃ�//(4�N:66�ȏ�)

	float unit2;//���ʌ���//(4�N:8)

	float unit3;//��勳��ȖڌQ//(4�N:80)

	float unit4;//���C����ȖځC�ی��̈�ȖځC���n���ʊ�b�ȖځC��勳��ȖڌQ//(4�N:104�ȏ�)

	float unit5;//���P��//(4�N:130�ȏ�)

};

/*�֐�*/
//�������͂��X�y�[�X�ŋ�؂�C��؂�ꂽ�������N���X�Ɋi�[����֐�
void splitString(const string& line, vector<string>& elements) {
	// ���p�X�y�[�X��S�p�X�y�[�X�ɒu������
	string replacedLine = line;
	for (char& c : replacedLine) {
		if (c == ' ') { // ���p�X�y�[�X��S�p�X�y�[�X�ɒu��
			c = '�@';
		}
	}

	regex re("\\s+"); // ���K�\���p�^�[��: 1�ȏ�̋󔒕����i�S�p�X�y�[�X�j�Ƀ}�b�`
	sregex_token_iterator it(replacedLine.begin(), replacedLine.end(), re, -1); // �C�e���[�^�̎g�p
	sregex_token_iterator end;
	while (it != end) {
		elements.push_back(*it++);
	}
}

//�G��4�A�D��3�A�ǂ�2�A��1�A�s��0�̐��l�ɕϊ�����֐�
int convertGradeToValue(const string& grade) {
	if (grade == "�G") return 4;
	else if (grade == "�D") return 3;
	else if (grade == "��") return 2;
	else if (grade == "��") return 1;
	else if (grade == "�s��")return 0;
	else return -1;// ����`�̐��т��n���ꂽ�ꍇ�̃f�t�H���g�l
}

//�P�ʐ��v�Z�֐�
float unitsum(const vector<lecture>& lectures, const string& category, const string& kinds) {
	float unitSum = 0.0;
	for (const auto& lec : lectures) {
		if (lec.category == category && lec.lecturekinds == kinds) {
			unitSum += lec.unit;
		}
	}
	return unitSum;
}

//�P�ʐ��v�Z�֐�(��勳��ȖڌQ��p)
float unitsum2(const vector<lecture>& lectures, const string& category, const string& kinds, const string& lecturename) {
	float unitSum = 0.0;
	for (const auto& lec : lectures) {
		if (lec.category == category && lec.lecturekinds == kinds && lec.lecturename == lecturename) {
			unitSum += lec.unit;
		}
	}
	return unitSum;
}

//�P�ʐ��v�Z�֐�(���Ɣԍ�����o�[�W����)
float unitsum3(const vector<lecture>& lectures, const string& category, const string& kinds, const string& lecturename, const string& lecturenum) {
	float unitSum = 0.0;
	for (const auto& lec : lectures) {
		if (lec.category == category && lec.lecturekinds == kinds && lec.lecturename == lecturename && lec.lecturenum == lecturenum) {
			unitSum += lec.unit;
		}
	}
	return unitSum;
}

// �擾�P�ʐ��ƕK�v�P�ʐ����r����֐�
void compareUnits(const Unitnum3& acquired, const Unitnum3& required) {
	cout << "=== �擾�P�ʐ��ƕK�v�P�ʐ��̔�r ===" << endl;
	// �e�v�f�̔�r���s���A���ʂɉ����ă��b�Z�[�W��\�����܂�
	if (acquired.unit1 >= required.unit1)
		cout << "�擾�P�ʐ�1 (" << acquired.unit1 << ") �͏\���ł��B" << endl;
	else
		cout << "�擾�P�ʐ�1 (" << acquired.unit1 << ") ���s�����Ă��܂��B�K�v�ȒP�ʐ�: " << required.unit1 << endl;

	if (acquired.unit2 >= required.unit2)
		cout << "�擾�P�ʐ�2 (" << acquired.unit2 << ") �͏\���ł��B" << endl;
	else
		cout << "�擾�P�ʐ�2 (" << acquired.unit2 << ") ���s�����Ă��܂��B�K�v�ȒP�ʐ�: " << required.unit2 << endl;

	// �e�v�f�̔�r��ǉ����܂�
	if (acquired.unit3 >= required.unit3)
		cout << "�擾�P�ʐ�3 (" << acquired.unit3 << ") �͏\���ł��B" << endl;
	else
		cout << "�擾�P�ʐ�3 (" << acquired.unit3 << ") ���s�����Ă��܂��B�K�v�ȒP�ʐ�: " << required.unit3 << endl;

	if (acquired.unit4 >= required.unit4)
		cout << "�擾�P�ʐ�4 (" << acquired.unit4 << ") �͏\���ł��B" << endl;
	else
		cout << "�擾�P�ʐ�4 (" << acquired.unit4 << ") ���s�����Ă��܂��B�K�v�ȒP�ʐ�: " << required.unit4 << endl;

	if (acquired.unit5 >= required.unit5)
		cout << "�擾�P�ʐ�5 (" << acquired.unit5 << ") �͏\���ł��B" << endl;
	else
		cout << "�擾�P�ʐ�5 (" << acquired.unit5 << ") ���s�����Ă��܂��B�K�v�ȒP�ʐ�: " << required.unit5 << endl;

	if (acquired.unit6 >= required.unit6)
		cout << "�擾�P�ʐ�6 (" << acquired.unit6 << ") �͏\���ł��B" << endl;
	else
		cout << "�擾�P�ʐ�6 (" << acquired.unit6 << ") ���s�����Ă��܂��B�K�v�ȒP�ʐ�: " << required.unit6 << endl;

	if (acquired.unit7 >= required.unit7)
		cout << "�擾�P�ʐ�7 (" << acquired.unit7 << ") �͏\���ł��B" << endl;
	else
		cout << "�擾�P�ʐ�7 (" << acquired.unit7 << ") ���s�����Ă��܂��B�K�v�ȒP�ʐ�: " << required.unit7 << endl;

	if (acquired.unit8 >= required.unit8)
		cout << "�擾�P�ʐ�8 (" << acquired.unit8 << ") �͏\���ł��B" << endl;
	else
		cout << "�擾�P�ʐ�8 (" << acquired.unit8 << ") ���s�����Ă��܂��B�K�v�ȒP�ʐ�: " << required.unit8 << endl;

	if (acquired.unit9 >= required.unit9)
		cout << "�擾�P�ʐ�9 (" << acquired.unit9 << ") �͏\���ł��B" << endl;
	else
		cout << "�擾�P�ʐ�9 (" << acquired.unit9 << ") ���s�����Ă��܂��B�K�v�ȒP�ʐ�: " << required.unit9 << endl;

	if (acquired.unit10 >= required.unit10)
		cout << "�擾�P�ʐ�10 (" << acquired.unit10 << ") �͏\���ł��B" << endl;
	else
		cout << "�擾�P�ʐ�10 (" << acquired.unit10 << ") ���s�����Ă��܂��B�K�v�ȒP�ʐ�: " << required.unit10 << endl;

	if (acquired.unit11 >= required.unit11)
		cout << "�擾�P�ʐ�11 (" << acquired.unit11 << ") �͏\���ł��B" << endl;
	else
		cout << "�擾�P�ʐ�11 (" << acquired.unit11 << ") ���s�����Ă��܂��B�K�v�ȒP�ʐ�: " << required.unit11 << endl;

	if (acquired.unit12 >= required.unit12)
		cout << "�擾�P�ʐ�12 (" << acquired.unit12 << ") �͏\���ł��B" << endl;
	else
		cout << "�擾�P�ʐ�12 (" << acquired.unit12 << ") ���s�����Ă��܂��B�K�v�ȒP�ʐ�: " << required.unit12 << endl;

	// ���ׂĂ̗v�f�̔�r���ʂɉ����������ǉ����܂�
	if (acquired.unit1 >= required.unit1 && acquired.unit2 >= required.unit2 && acquired.unit3 >= required.unit3
		&& acquired.unit4 >= required.unit4 && acquired.unit5 >= required.unit5 && acquired.unit6 >= required.unit6
		&& acquired.unit7 >= required.unit7 && acquired.unit8 >= required.unit8 && acquired.unit9 >= required.unit9
		&& acquired.unit10 >= required.unit10 && acquired.unit11 >= required.unit11 && acquired.unit12 >= required.unit12)
	{
		// ���������ׂĖ������ꂽ�ꍇ�̏���
		cout << "���ׂĂ̏����𖞂����Ă��܂��B" << endl;
	}
	else
	{
		// ��������������Ȃ������ꍇ�̏���
		cout << "�K�v�ȏ�������������Ă��܂���B" << endl;
	}
}


//gpa �v�Z�֐��i�������j


//���C���֐�
int main() {
	//���b�Z�[�W�̕\���i����̎菇�̐����j
	cout << "�`�g�����`" << endl;
	cout << "CAMPUSSQUARE�Ƀ��O�C�� -> ���� -> �ߋ����܂߂��S���т�I�� -> ��ʂɕ\��������N���b�N�@�̎菇�Ő��т�\�����CNo.1����Ō�܂ŁC�\�̂��ׂĂ̍��ڂ��R�s�[�������̂��ȉ��ɓ\��t���Ă�������" << endl;
	cout << "�`���ӎ����`" << endl;
	cout << "�e�L�X�g�\��t�����C�x�����o�邱�Ƃ�����܂����C�u�����I�ɓ\��t���v���N���b�N���Ė��Ȃ��ł��D" << endl << endl;
	/*���̓e�L�X�g�̃t�@�C���̕ۑ�*/
	ofstream outfile("seiseki.txt");
	//�t�@�C�����͎��s���̃��b�Z�[�W
	if (!outfile) {
		cout << "�t�@�C���̍쐬�Ɏ��s���܂����B" << endl;
		return 1;
	}

	cout << "�ȉ��Ɏw�肵���e�L�X�g����͂��Ă��������i�I������ɂ͉��s��CCtrl+Z�������Ă���enter�������Ă��������j:" << endl;
	string line2;
	//�e�񂲂ƂɃt�@�C���ۑ�
	while (getline(cin, line2)) {
		outfile << line2 << endl;
	}
	outfile.close();
	cout << "�t�@�C���̕ۑ����������܂����B" << endl;


	/*���͂��Ă������txt�t�@�C���̓ǂݍ���*/
	ifstream infile("seiseki.txt");
	vector<lecture>lectures;//lecture�^��vector�i���O��lectures�j
	string line;
	vector<string> elements;
	string nowcategory; // ���݂̉ȖڌQ
	string nowkinds;// ���݂̉Ȗڎ��

	//infile.imbue(locale("ja_JP.UTF-8")); // ���P�[���ƕ����Z�b�g��ݒ�

	while (getline(infile, line)) {

		splitString(line, elements);//�֐��̗��p

		//11�ɕ������Ƃ�()
		if (elements.size() == 11) {
			string category = elements[1];
			string kinds = elements[2];
			string num = elements[3];
			string name = elements[4];
			float unit = stof(elements[6]);//�������float�ɕϊ�
			string grade = elements[9];
			int value = convertGradeToValue(grade);
			int year = stoi(elements[7]);
			lecture lec(category, kinds, num, name, unit, value, year);
			lectures.push_back(lec);
		}
		//12�ɕ������Ƃ��i�j
		if (elements.size() == 12) {
			string category = elements[1];
			string kinds = elements[2];
			string num = elements[4];
			string name = elements[5];
			float unit = stof(elements[7]);//�������float�ɕϊ�
			string grade = elements[10];
			int value = convertGradeToValue(grade);
			int year = stoi(elements[8]);
			lecture lec(category, kinds, num, name, unit, value, year);
			lectures.push_back(lec);
		}
		elements.clear();
	}
	infile.close();
	cout << "�t�@�C�����m�F�ł��܂���" << endl;

	//�e�敪���ɒu����P�ʐ��̌v�Z�i�m�\�@�B��p�j
	vector<Unitnum3>num3;
	float u111 = unitsum(lectures, "���{�Ȗ�", "�s�s�E�Љ�E��");
	float u112 = unitsum(lectures, "���{�Ȗ�", "�Ȋw�E�Z�p�E�Y��");
	float u121 = unitsum(lectures, "��ՉȖ�", "�Љ�Ȋw�̈�");
	float u122 = unitsum(lectures, "��ՉȖ�", "���R�Ȋw�̈�");
	float u13 = unitsum(lectures, "��b�Ȗ�", "�L�����A����");

	float u1 = u111 + u112 + u121 + u122 + u13;
	float u2 = unitsum(lectures, "��b�Ȗ�", "��b�[�~�i�[��");
	float u3 = unitsum(lectures, "��b�Ȗ�", "���Ȗ�");
	float u4 = unitsum(lectures, "��b�Ȗ�", "���H�p��");
	float u5 = unitsum(lectures, "��b�Ȗ�", "���n���ʊ�b�Ȗ�");

	//�R�[�X���ʊ�b�Ȗځi�K�C�j
	float u61 = unitsum2(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "�H�Ɨ͊w");
	float u62 = unitsum3(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "�ޗ��͊w", "L0406");
	float u63 = unitsum3(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "�@�B���}", "L0413");//�@�B���}�T
	float u64 = unitsum2(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "�H�Ɛ��w");
	float u65 = unitsum2(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "�@�\�w");
	float u66 = unitsum3(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "�@�B���}", "L0422");//�@�B���}�U
	float u67 = unitsum2(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "�@�B�V�X�e����b����");
	float u68 = unitsum2(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "�@�B�H����K");

	float u6 = u61 + u62 + u63 + u64 + u65 + u66 + u67 + u68;

	//�R�[�X���ʊ�b�Ȗځi�I���j
	float u71 = unitsum2(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "�v���H�w");
	float u72 = unitsum3(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "�v���O���~���O���K", "L0407");//�v���O���~���O���K�T
	float u73 = unitsum2(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "��b�d�C��H");
	float u74 = unitsum2(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "���J�g���j�N�X@(Mechatronics)");
	float u75 = unitsum3(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "�@�B�͊w", "L0416");//�@�B�͊w�T
	float u76 = unitsum3(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "���̗͊w", "L0417");//���̗͊w�T
	float u77 = unitsum2(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "�M�͊w");
	float u78 = unitsum3(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "�V�X�e������", "L0426");//�V�X�e������T
	float u79 = unitsum2(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "�d�q��H");

	float u7 = u71 + u72 + u73 + u74 + u75 + u76 + u77 + u78 + u79;

	float u8 = unitsum(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��") - u6 - u7;

	float u9 = unitsum2(lectures, "��勳��Ȗ�", "�V�X�e���f�U�C���w��", "�m�\�@�B���p����");

	float u10 = u5 + u6 + u7 + u8;
	float u11 = u1 + u2 + u3 + u4 + u5 + u6 + u7 + u8;
	float u12 = u6 + u7 + u8;

	//�擾�P�ʐ��̊i�[
	Unitnum3 num(u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11, u12);
	num3.push_back(num);

	//�K�v�P�ʐ��̊i�[
	Unitnum3 nnum(14, 2, 2, 8, 20, 16, 10, 32, 2, 86, 112, 62);
	num3.push_back(nnum);

	//�K�v�P�ʐ��Ǝ擾�P�ʐ��̔�r
	compareUnits(num3[0], num3[1]);





	//�m�F
	/*for (const auto& lec : lectures) {
		cout << "    " << lec.category << "    " << lec.lecturekinds << "   " << lec.lecturenum << "   " << lec.lecturename << "     " << lec.unit << "      " << lec.value << "      " << lec.year << endl;
	}*/

	return 0;
}
