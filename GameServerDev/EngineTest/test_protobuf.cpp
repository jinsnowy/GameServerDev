#include "pch.h"
#include "Protocol/UserProtocol.pb.h"
#include "Protocol/ProtobufUtils.h"

TEST(TestProtobuf, 빈문자열_변환_테스트) {
	wstring src(L"");

	User::WideString wide;
	*wide.mutable_message() = ProtobufUtils::EncodeUtf16(src);

	User::WideString copy;
	copy.CopyFrom(wide);
	wstring dst = ProtobufUtils::DecodeUtf16WithOption(copy.message(), ProtobufUtils::IsLittleEndianSystem(), false);

	EXPECT_EQ(src, dst);
}

TEST(TestProtobuf, 빈문자열_BOM_변환_테스트) {
	wstring src(L"");

	User::WideString wide;
	*wide.mutable_message() = ProtobufUtils::EncodeUtf16WithOption(src, ProtobufUtils::IsLittleEndianSystem(), true);

	User::WideString copy;
	copy.CopyFrom(wide);
	wstring dst = ProtobufUtils::DecodeUtf16WithOption(copy.message(), ProtobufUtils::IsLittleEndianSystem(), true);

	EXPECT_EQ(src, dst);
}

TEST(TestProtobuf, 문자열_변환_예외_테스트) {
	string src = "asd";
	EXPECT_ANY_THROW(ProtobufUtils::DecodeUtf16(src));
}

TEST(TestProtobuf, 문자열_변환_실패_테스트) {
	string src = "asd";
	wstring out = L"";
	EXPECT_FALSE(ProtobufUtils::TryToDecodeUtf16(out, src, ProtobufUtils::IsLittleEndianSystem(), true));
}

TEST(TestProtobuf, 한국어_변환_테스트) {
	wstring src(L"안녕하세요");

	User::WideString wide;
	*wide.mutable_message() = ProtobufUtils::EncodeUtf16(src); 

	User::WideString copy;
	copy.CopyFrom(wide);
	wstring dst = ProtobufUtils::DecodeUtf16WithOption(copy.message(), true, false);

	EXPECT_EQ(src, dst);
}

TEST(TestProtobuf, 한국어_변환_BOM_테스트) {
	wstring src(L"안녕하세요");

	User::WideString wide;
	*wide.mutable_message() = ProtobufUtils::EncodeUtf16WithOption(src, ProtobufUtils::IsLittleEndianSystem(), true);

	string ss = wide.message();
	vector<unsigned char> sv;
	for (auto ch : ss) {
		sv.push_back(ch);
	}

	User::WideString copy;
	copy.CopyFrom(wide);
	wstring dst = ProtobufUtils::DecodeUtf16WithOption(copy.message(), ProtobufUtils::IsLittleEndianSystem(), true);

	EXPECT_EQ(src, dst);
}

TEST(TestProtobuf, 한국어_변환_이종_아키텍쳐_테스트) {
	wstring src(L"안녕하세요");

	User::WideString wide;
	*wide.mutable_message() = ProtobufUtils::EncodeUtf16WithOption(src, !ProtobufUtils::IsLittleEndianSystem(), false);

	string ss = wide.message();
	vector<unsigned char> sv;
	for (auto ch : ss) {
		sv.push_back(ch);
	}

	User::WideString copy;
	copy.CopyFrom(wide);
	wstring dst = ProtobufUtils::DecodeUtf16WithOption(copy.message(), !ProtobufUtils::IsLittleEndianSystem(), false);

	EXPECT_EQ(src, dst);
}

TEST(TestProtobuf, 한국어_변환_BE_BOM_테스트) {
	wstring src(L"안녕하세요");

	User::WideString wide;
	*wide.mutable_message() = ProtobufUtils::EncodeUtf16WithOption(src, !ProtobufUtils::IsLittleEndianSystem(), true);

	string ss = wide.message();
	vector<unsigned char> sv;
	for (auto ch : ss) {
		sv.push_back(ch);
	}

	User::WideString copy;
	copy.CopyFrom(wide);
	wstring dst = ProtobufUtils::DecodeUtf16WithOption(copy.message(), !ProtobufUtils::IsLittleEndianSystem(), true);

	EXPECT_EQ(src, dst);
}

TEST(TestProtobuf, 중국어_변환_테스트) {
	LPCWSTR text = L"你好。 正在测试消息"
		L"法新社、美联社和英国《卫报》12日（当地时间）报道称，土耳其和叙利亚发生的强烈地震造成的死亡人数超过2.8万人，联合国观察称死亡人数可能增加一倍以上。 ."
		L"据土耳其当局和叙利亚人权组织统计，震后第六天，两国地震死亡人数均超过2.8万人"
		L"土耳其有24, 617人死亡，叙利亚有3, 574人确诊死亡，总数达到28, 191人"
		L"随着失踪人员搜寻工作的继续，死亡人数正在迅速上升"
		L"联合国主管人道主义和紧急救济事务的副秘书长马丁格里菲思说，死亡人数可能至少翻一番，甚至数万人。"
		L"请确认。 谢谢";


	wstring src(text);

	User::WideString wide;
	*wide.mutable_message() = ProtobufUtils::EncodeUtf16(src);

	User::WideString copy;
	copy.CopyFrom(wide);
	wstring dst = ProtobufUtils::DecodeUtf16(copy.message());

	EXPECT_EQ(src, dst);
}

TEST(TestProtobuf, 영어_변환_테스트) {
	LPCWSTR text = L"hello world";

	wstring src(text);

	User::WideString wide;
	*wide.mutable_message() = ProtobufUtils::EncodeUtf16(src);

	User::WideString copy;
	copy.CopyFrom(wide);
	wstring dst = ProtobufUtils::DecodeUtf16(copy.message());

	EXPECT_EQ(src, dst);
}

TEST(TestProtobuf, 러시아어_변환_테스트) {
	LPCWSTR text = L"AFP, Associated Press и британская ежедневная газета Guardian сообщили 12 числа (по местному времени), что число погибших в результате сильного землетрясения, поразившего Турцию и Сирию, превысило 28 000 человек, а по наблюдениям ООН число погибших может более чем удвоиться."
		L"По подсчетам турецких властей и сирийских правозащитных организаций, число погибших в результате землетрясения в обеих странах на шестой день после землетрясения превысило 28 тысяч человек."
		L"В Турции погибло 24 617 человек, в Сирии — 3 574 человека, в результате чего общее число погибших достигло 28 191 человека."
		L"Число погибших стремительно растет, поиски пропавших без вести продолжаются."
		L"Мартин Гриффитс, заместитель Генерального секретаря ООН по гуманитарной и чрезвычайной помощи, заявил, что число погибших может как минимум удвоиться, а число погибших может увеличиться на десятки тысяч человек.";

	wstring src(text);

	User::WideString wide;
	*wide.mutable_message() = ProtobufUtils::EncodeUtf16(src);

	User::WideString copy;
	copy.CopyFrom(wide);
	wstring dst = ProtobufUtils::DecodeUtf16(copy.message());

	EXPECT_EQ(src, dst);
}

//
//TEST(TestProtobuf, 빈_문자열_변환_테스트) {
//	wstring src(L"");
//
//	User::WideString wide;
//	*wide.mutable_message() = ProtobufUtils::ToProtobufWideString(src);
//
//	User::WideString copy;
//	copy.CopyFrom(wide);
//	wstring dst = ProtobufUtils::FromProtobufWideString(copy.message());
//
//	EXPECT_EQ(src, dst);
//}
//
//TEST(TestProtobuf, 일본어_변환_테스트) {
//	LPCWSTR text = L"こんにちは。 メッセージテスト中です。"
//		L"チュルキエとシリアを襲ったカンジンの死亡者が2万8千人を超えた中で死亡者数が2倍以上に増えることができるという国連の観測が提起されたと12日(現地時間)AFP・AP通信とイギリス日刊紙ガーディアンなどが報道 した。"
//		L"チュルキエ当局とシリア人権団体などの集計によれば、地震発生が犯されたこの日、両国の地震死者は2万8千人を超えた。"
//		L"チュルキエ死亡者が2万4千617人で、シリアで確認された死亡者が3千574人と合わせれば2万8千191人に達する。"
//		L"行方不明者の捜索が進むにつれて、死亡者数は急速に増えている。"
//		L"マーティン・グリフィス国連人道主義・緊急救援担当事務次長は、死亡者が数万人以上出て、少なくとも2倍以上に増えると予想した。"
//		L"確認お願いします。 ありがとうございます。";
//
//
//	wstring src(text);
//
//	User::WideString wide;
//	*wide.mutable_message() = ProtobufUtils::ToProtobufWideString(src);
//
//	User::WideString copy;
//	copy.CopyFrom(wide);
//	wstring dst = ProtobufUtils::FromProtobufWideString(copy.message());
//
//	EXPECT_EQ(src, dst);
//}
//

//
//TEST(TestProtobuf, 베트남어_변환_테스트) {
//	LPCWSTR text = L"Xin chào. Tin nhắn đang được thử nghiệm."
//		L"AFP, Associated Press và tờ Guardian hàng ngày của Anh đưa tin vào ngày 12 (giờ địa phương) rằng số người chết trong trận động đất mạnh xảy ra ở Thổ Nhĩ Kỳ và Syria đã vượt quá 28.000 người, và các quan sát của Liên Hợp Quốc đã đưa ra rằng số người chết có thể tăng hơn gấp đôi. ."
//		L"Theo thống kê của chính quyền Thổ Nhĩ Kỳ và các tổ chức nhân quyền của Syria, số người chết vì trận động đất ở cả hai quốc gia đã vượt quá 28.000 vào ngày thứ sáu sau trận động đất."
//		L"Có 24.617 người chết ở Thổ Nhĩ Kỳ và 3.574 người chết được xác nhận ở Syria, nâng tổng số lên 28.191."
//		L"Số người chết đang tăng lên nhanh chóng khi việc tìm kiếm những người mất tích vẫn tiếp tục."
//		L"Martin Griffiths, Phó Tổng thư ký LHQ về Cứu trợ Nhân đạo và Khẩn cấp, cho biết số người chết ít nhất có thể tăng gấp đôi, với hàng chục nghìn người nữa."
//		L"Vui lòng xác nhận.Cảm ơn";
//
//
//	wstring src(text);
//
//	User::WideString wide;
//	*wide.mutable_message() = ProtobufUtils::ToProtobufWideString(src);
//
//	User::WideString copy;
//	copy.CopyFrom(wide);
//	wstring dst = ProtobufUtils::FromProtobufWideString(copy.message());
//
//	EXPECT_EQ(src, dst);
//}
//
//TEST(TestProtobuf, 프랑스어_변환_테스트) {
//	LPCWSTR text = L"Bonjour. Le message est en cours de test."
//		L"L'AFP, l'Associated Press et le quotidien britannique Guardian ont rapporté le 12 (heure locale) que le nombre de morts du fort tremblement de terre qui a frappé la Turquie et la Syrie dépassait les 28 000, et des observations de l'ONU ont été faites selon lesquelles le nombre de morts pourrait plus que doubler."
//		L"Selon le décompte des autorités turques et des organisations syriennes de défense des droits de l'homme, le nombre de morts du tremblement de terre dans les deux pays a dépassé 28 000 le sixième jour après le tremblement de terre."
//		L"Il y a 24 617 décès en Turquie et 3 574 décès confirmés en Syrie, portant le total à 28 191."
//		L"Le nombre de morts augmente rapidement à mesure que la recherche des personnes disparues se poursuit."
//		L"Martin Griffiths, secrétaire général adjoint des Nations Unies pour l'aide humanitaire et d'urgence, a déclaré que le nombre de morts pourrait au moins doubler, avec des dizaines de milliers de plus."
//		L"Veuillez confirmer.merci";
//
//	wstring src(text);
//
//	User::WideString wide;
//	*wide.mutable_message() = ProtobufUtils::ToProtobufWideString(src);
//
//	User::WideString copy;
//	copy.CopyFrom(wide);
//	wstring dst = ProtobufUtils::FromProtobufWideString(copy.message());
//
//	EXPECT_EQ(src, dst);
//}
//
//TEST(TestProtobuf, 독일어_변환_테스트) {
//	LPCWSTR text = L"Hallo. Nachricht wird getestet."
//		L"AFP, Associated Press und die britische Tageszeitung Guardian berichteten am 12. (Ortszeit), dass die Zahl der Todesopfer durch das starke Erdbeben, das die Türkei und Syrien heimsuchte, 28.000 überstieg, und UN - Beobachtungen wurden gemacht, dass sich die Zahl der Todesfälle mehr als verdoppeln könnte."
//		L"Nach Angaben der türkischen Behörden und syrischer Menschenrechtsorganisationen überstieg die Zahl der Todesopfer des Erdbebens in beiden Ländern am sechsten Tag nach dem Erdbeben 28.000."
//		L"Es gibt 24.617 Todesfälle in der Türkei und 3.574 bestätigte Todesfälle in Syrien, was einer Gesamtzahl von 28.191 entspricht."
//		L"Die Zahl der Todesopfer steigt rapide an, während die Suche nach vermissten Personen fortgesetzt wird."
//		L"Martin Griffiths, UN - Untergeneralsekretär für humanitäre Hilfe und Nothilfe, sagte, die Zahl der Todesopfer könne sich mindestens verdoppeln, mit Zehntausenden mehr."
//		L"Bitte bestätigen.Danke";
//
//	wstring src(text);
//
//	User::WideString wide;
//	*wide.mutable_message() = ProtobufUtils::ToProtobufWideString(src);
//
//	User::WideString copy;
//	copy.CopyFrom(wide);
//	wstring dst = ProtobufUtils::FromProtobufWideString(copy.message());
//
//	EXPECT_EQ(src, dst);
//}
//
