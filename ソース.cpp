#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

/*クラス*/
//授業クラスの定義（科目群，科目種類，科目名，単位，成績，年度）
struct lecture {
public:
	string category;//科目群の追加
	string lecturekinds;//科目種類の追加
	string lecturenum;
	string lecturename;
	float unit;
	int value;
	int year;

	lecture(const string& c, const string& k, const string& num, const string& name, float u, int v, int y)
		: category(c), lecturekinds(k), lecturenum(num), lecturename(name), unit(u), value(v), year(y)
	{}
};
//3年必要単位数クラスの定義（計算したものをここにあてはめていく）
struct Unitnum3 {
public:
	float unit1;//教養科目群，基盤科目群，キャリア教育の単位数//(3年:14以上，4年:14以上)

	float unit2;//基礎ゼミナール//(3年:2，4年:2)

	float unit3;//情報リテラシー実践//(3年:2，4年:2)

	float unit4;//言語科目（実践英語）//(3年:8，4年:8)

	float unit5;//理系共通基礎科目//(3年:20以上，4年:20以上)

	float unit6;//コース共通基礎科目（必修）：//(3年:16)

	float unit7;//コース共通基礎科目（選択）：//(3年:10以上)

	float unit8;//コース共通専門，コース専門科目群：//(32単位以上＊コース専門科目群：所属コース（知能 / 生体）の科目に限る)

	float unit9;//知能生体応用実験//(3年:2，4年:2)

	float unit10;//未修言語科目，保健体育科目，理系共通基礎科目，専門教育科目群：(3年:86以上,4年:104以上)

	float unit11;//総単位//(3年:112以上，4年:130以上)//

	float unit12;//専門教育科目群//(3年:62)

	Unitnum3(float u1, float u2, float u3, float u4, float u5, float u6, float u7, float u8, float u9, float u10, float u11, float u12)
		: unit1(u1), unit2(u2), unit3(u3), unit4(u4), unit5(u5), unit6(u6), unit7(u7), unit8(u8), unit9(u9), unit10(u10), unit11(u11), unit12(u12)
	{}
};
//4年必要単位数(卒業要件)クラスの定義（計算したものをここにあてはめていく）
struct Unitnum4 {
public:
	float unit1;//コース共通基礎など//(4年:66以上)

	float unit2;//特別研究//(4年:8)

	float unit3;//専門教育科目群//(4年:80)

	float unit4;//未修言語科目，保健体育科目，理系共通基礎科目，専門教育科目群//(4年:104以上)

	float unit5;//総単位//(4年:130以上)

};

/*関数*/
//文字入力をスペースで区切り，区切られた文字をクラスに格納する関数
void splitString(const string& line, vector<string>& elements) {
	// 半角スペースを全角スペースに置換する
	string replacedLine = line;
	for (char& c : replacedLine) {
		if (c == ' ') { // 半角スペースを全角スペースに置換
			c = '　';
		}
	}

	regex re("\\s+"); // 正規表現パターン: 1つ以上の空白文字（全角スペース）にマッチ
	sregex_token_iterator it(replacedLine.begin(), replacedLine.end(), re, -1); // イテレータの使用
	sregex_token_iterator end;
	while (it != end) {
		elements.push_back(*it++);
	}
}

//秀を4、優を3、良を2、可を1、不可を0の数値に変換する関数
int convertGradeToValue(const string& grade) {
	if (grade == "秀") return 4;
	else if (grade == "優") return 3;
	else if (grade == "良") return 2;
	else if (grade == "可") return 1;
	else if (grade == "不可")return 0;
	else return -1;// 未定義の成績が渡された場合のデフォルト値
}

//単位数計算関数
float unitsum(const vector<lecture>& lectures, const string& category, const string& kinds) {
	float unitSum = 0.0;
	for (const auto& lec : lectures) {
		if (lec.category == category && lec.lecturekinds == kinds) {
			unitSum += lec.unit;
		}
	}
	return unitSum;
}

//単位数計算関数(専門教育科目群専用)
float unitsum2(const vector<lecture>& lectures, const string& category, const string& kinds, const string& lecturename) {
	float unitSum = 0.0;
	for (const auto& lec : lectures) {
		if (lec.category == category && lec.lecturekinds == kinds && lec.lecturename == lecturename) {
			unitSum += lec.unit;
		}
	}
	return unitSum;
}

//単位数計算関数(授業番号ありバージョン)
float unitsum3(const vector<lecture>& lectures, const string& category, const string& kinds, const string& lecturename, const string& lecturenum) {
	float unitSum = 0.0;
	for (const auto& lec : lectures) {
		if (lec.category == category && lec.lecturekinds == kinds && lec.lecturename == lecturename && lec.lecturenum == lecturenum) {
			unitSum += lec.unit;
		}
	}
	return unitSum;
}

// 取得単位数と必要単位数を比較する関数
void compareUnits(const Unitnum3& acquired, const Unitnum3& required) {
	cout << "=== 取得単位数と必要単位数の比較 ===" << endl;
	// 各要素の比較を行い、結果に応じてメッセージを表示します
	if (acquired.unit1 >= required.unit1)
		cout << "取得単位数1 (" << acquired.unit1 << ") は十分です。" << endl;
	else
		cout << "取得単位数1 (" << acquired.unit1 << ") が不足しています。必要な単位数: " << required.unit1 << endl;

	if (acquired.unit2 >= required.unit2)
		cout << "取得単位数2 (" << acquired.unit2 << ") は十分です。" << endl;
	else
		cout << "取得単位数2 (" << acquired.unit2 << ") が不足しています。必要な単位数: " << required.unit2 << endl;

	// 各要素の比較を追加します
	if (acquired.unit3 >= required.unit3)
		cout << "取得単位数3 (" << acquired.unit3 << ") は十分です。" << endl;
	else
		cout << "取得単位数3 (" << acquired.unit3 << ") が不足しています。必要な単位数: " << required.unit3 << endl;

	if (acquired.unit4 >= required.unit4)
		cout << "取得単位数4 (" << acquired.unit4 << ") は十分です。" << endl;
	else
		cout << "取得単位数4 (" << acquired.unit4 << ") が不足しています。必要な単位数: " << required.unit4 << endl;

	if (acquired.unit5 >= required.unit5)
		cout << "取得単位数5 (" << acquired.unit5 << ") は十分です。" << endl;
	else
		cout << "取得単位数5 (" << acquired.unit5 << ") が不足しています。必要な単位数: " << required.unit5 << endl;

	if (acquired.unit6 >= required.unit6)
		cout << "取得単位数6 (" << acquired.unit6 << ") は十分です。" << endl;
	else
		cout << "取得単位数6 (" << acquired.unit6 << ") が不足しています。必要な単位数: " << required.unit6 << endl;

	if (acquired.unit7 >= required.unit7)
		cout << "取得単位数7 (" << acquired.unit7 << ") は十分です。" << endl;
	else
		cout << "取得単位数7 (" << acquired.unit7 << ") が不足しています。必要な単位数: " << required.unit7 << endl;

	if (acquired.unit8 >= required.unit8)
		cout << "取得単位数8 (" << acquired.unit8 << ") は十分です。" << endl;
	else
		cout << "取得単位数8 (" << acquired.unit8 << ") が不足しています。必要な単位数: " << required.unit8 << endl;

	if (acquired.unit9 >= required.unit9)
		cout << "取得単位数9 (" << acquired.unit9 << ") は十分です。" << endl;
	else
		cout << "取得単位数9 (" << acquired.unit9 << ") が不足しています。必要な単位数: " << required.unit9 << endl;

	if (acquired.unit10 >= required.unit10)
		cout << "取得単位数10 (" << acquired.unit10 << ") は十分です。" << endl;
	else
		cout << "取得単位数10 (" << acquired.unit10 << ") が不足しています。必要な単位数: " << required.unit10 << endl;

	if (acquired.unit11 >= required.unit11)
		cout << "取得単位数11 (" << acquired.unit11 << ") は十分です。" << endl;
	else
		cout << "取得単位数11 (" << acquired.unit11 << ") が不足しています。必要な単位数: " << required.unit11 << endl;

	if (acquired.unit12 >= required.unit12)
		cout << "取得単位数12 (" << acquired.unit12 << ") は十分です。" << endl;
	else
		cout << "取得単位数12 (" << acquired.unit12 << ") が不足しています。必要な単位数: " << required.unit12 << endl;

	// すべての要素の比較結果に応じた分岐を追加します
	if (acquired.unit1 >= required.unit1 && acquired.unit2 >= required.unit2 && acquired.unit3 >= required.unit3
		&& acquired.unit4 >= required.unit4 && acquired.unit5 >= required.unit5 && acquired.unit6 >= required.unit6
		&& acquired.unit7 >= required.unit7 && acquired.unit8 >= required.unit8 && acquired.unit9 >= required.unit9
		&& acquired.unit10 >= required.unit10 && acquired.unit11 >= required.unit11 && acquired.unit12 >= required.unit12)
	{
		// 条件がすべて満たされた場合の処理
		cout << "すべての条件を満たしています。" << endl;
	}
	else
	{
		// 条件が満たされなかった場合の処理
		cout << "必要な条件が満たされていません。" << endl;
	}
}


//gpa 計算関数（未実装）


//メイン関数
int main() {
	//メッセージの表示（操作の手順の説明）
	cout << "～使い方～" << endl;
	cout << "CAMPUSSQUAREにログイン -> 成績 -> 過去を含めた全成績を選択 -> 画面に表示するをクリック　の手順で成績を表示し，No.1から最後まで，表のすべての項目をコピーしたものを以下に貼り付けてください" << endl;
	cout << "～注意事項～" << endl;
	cout << "テキスト貼り付け時，警告が出ることがありますが，「強制的に貼り付け」をクリックして問題ないです．" << endl << endl;
	/*入力テキストのファイルの保存*/
	ofstream outfile("seiseki.txt");
	//ファイル入力失敗時のメッセージ
	if (!outfile) {
		cout << "ファイルの作成に失敗しました。" << endl;
		return 1;
	}

	cout << "以下に指定したテキストを入力してください（終了するには改行後，Ctrl+Zを押してからenterを押してください）:" << endl;
	string line2;
	//各列ごとにファイル保存
	while (getline(cin, line2)) {
		outfile << line2 << endl;
	}
	outfile.close();
	cout << "ファイルの保存が完了しました。" << endl;


	/*入力してもらったtxtファイルの読み込み*/
	ifstream infile("seiseki.txt");
	vector<lecture>lectures;//lecture型のvector（名前はlectures）
	string line;
	vector<string> elements;
	string nowcategory; // 現在の科目群
	string nowkinds;// 現在の科目種類

	//infile.imbue(locale("ja_JP.UTF-8")); // ロケールと文字セットを設定

	while (getline(infile, line)) {

		splitString(line, elements);//関数の利用

		//11つに分かれるとき()
		if (elements.size() == 11) {
			string category = elements[1];
			string kinds = elements[2];
			string num = elements[3];
			string name = elements[4];
			float unit = stof(elements[6]);//文字列をfloatに変換
			string grade = elements[9];
			int value = convertGradeToValue(grade);
			int year = stoi(elements[7]);
			lecture lec(category, kinds, num, name, unit, value, year);
			lectures.push_back(lec);
		}
		//12つに分かれるとき（）
		if (elements.size() == 12) {
			string category = elements[1];
			string kinds = elements[2];
			string num = elements[4];
			string name = elements[5];
			float unit = stof(elements[7]);//文字列をfloatに変換
			string grade = elements[10];
			int value = convertGradeToValue(grade);
			int year = stoi(elements[8]);
			lecture lec(category, kinds, num, name, unit, value, year);
			lectures.push_back(lec);
		}
		elements.clear();
	}
	infile.close();
	cout << "ファイルが確認できました" << endl;

	//各区分けに置ける単位数の計算（知能機械専用）
	vector<Unitnum3>num3;
	float u111 = unitsum(lectures, "教養科目", "都市・社会・環境");
	float u112 = unitsum(lectures, "教養科目", "科学・技術・産業");
	float u121 = unitsum(lectures, "基盤科目", "社会科学領域");
	float u122 = unitsum(lectures, "基盤科目", "自然科学領域");
	float u13 = unitsum(lectures, "基礎科目", "キャリア教育");

	float u1 = u111 + u112 + u121 + u122 + u13;
	float u2 = unitsum(lectures, "基礎科目", "基礎ゼミナール");
	float u3 = unitsum(lectures, "基礎科目", "情報科目");
	float u4 = unitsum(lectures, "基礎科目", "実践英語");
	float u5 = unitsum(lectures, "基礎科目", "理系共通基礎科目");

	//コース共通基礎科目（必修）
	float u61 = unitsum2(lectures, "専門教育科目", "システムデザイン学部", "工業力学");
	float u62 = unitsum3(lectures, "専門教育科目", "システムデザイン学部", "材料力学", "L0406");
	float u63 = unitsum3(lectures, "専門教育科目", "システムデザイン学部", "機械製図", "L0413");//機械製図Ⅰ
	float u64 = unitsum2(lectures, "専門教育科目", "システムデザイン学部", "工業数学");
	float u65 = unitsum2(lectures, "専門教育科目", "システムデザイン学部", "機構学");
	float u66 = unitsum3(lectures, "専門教育科目", "システムデザイン学部", "機械製図", "L0422");//機械製図Ⅱ
	float u67 = unitsum2(lectures, "専門教育科目", "システムデザイン学部", "機械システム基礎実験");
	float u68 = unitsum2(lectures, "専門教育科目", "システムデザイン学部", "機械工作実習");

	float u6 = u61 + u62 + u63 + u64 + u65 + u66 + u67 + u68;

	//コース共通基礎科目（選択）
	float u71 = unitsum2(lectures, "専門教育科目", "システムデザイン学部", "計測工学");
	float u72 = unitsum3(lectures, "専門教育科目", "システムデザイン学部", "プログラミング演習", "L0407");//プログラミング演習Ⅰ
	float u73 = unitsum2(lectures, "専門教育科目", "システムデザイン学部", "基礎電気回路");
	float u74 = unitsum2(lectures, "専門教育科目", "システムデザイン学部", "メカトロニクス@(Mechatronics)");
	float u75 = unitsum3(lectures, "専門教育科目", "システムデザイン学部", "機械力学", "L0416");//機械力学Ⅰ
	float u76 = unitsum3(lectures, "専門教育科目", "システムデザイン学部", "流体力学", "L0417");//流体力学Ⅰ
	float u77 = unitsum2(lectures, "専門教育科目", "システムデザイン学部", "熱力学");
	float u78 = unitsum3(lectures, "専門教育科目", "システムデザイン学部", "システム制御", "L0426");//システム制御Ⅰ
	float u79 = unitsum2(lectures, "専門教育科目", "システムデザイン学部", "電子回路");

	float u7 = u71 + u72 + u73 + u74 + u75 + u76 + u77 + u78 + u79;

	float u8 = unitsum(lectures, "専門教育科目", "システムデザイン学部") - u6 - u7;

	float u9 = unitsum2(lectures, "専門教育科目", "システムデザイン学部", "知能機械応用実験");

	float u10 = u5 + u6 + u7 + u8;
	float u11 = u1 + u2 + u3 + u4 + u5 + u6 + u7 + u8;
	float u12 = u6 + u7 + u8;

	//取得単位数の格納
	Unitnum3 num(u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11, u12);
	num3.push_back(num);

	//必要単位数の格納
	Unitnum3 nnum(14, 2, 2, 8, 20, 16, 10, 32, 2, 86, 112, 62);
	num3.push_back(nnum);

	//必要単位数と取得単位数の比較
	compareUnits(num3[0], num3[1]);





	//確認
	/*for (const auto& lec : lectures) {
		cout << "    " << lec.category << "    " << lec.lecturekinds << "   " << lec.lecturenum << "   " << lec.lecturename << "     " << lec.unit << "      " << lec.value << "      " << lec.year << endl;
	}*/

	return 0;
}
