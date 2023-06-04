#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <string>

/*
FILE FORMAT:
QuestionFile
question
question
question
[DO NOT END QUESTIONS WITH ANY MARKS. NO ., ?, !].

AwnserFile
1 2 &3% 4,
5 6 &7%,
[EACH LINE REPRESENTS THE QUESTIONFILE LINE, AE AwnserFile LINE 1 = QUESTIONFILE LINE 1. END EACH AWNSER WITH A , AND CORRECT AWNSER MUST BE BETWEEN & and %, AE &5%]
*/

void inputFile() {
	std::ifstream questionFile;
	questionFile.open("questionList.txt");
	std::vector<std::string>questionList;
	std::string line;

	//THIS WORKS.
	if (questionFile.is_open()) {
		while (std::getline(questionFile, line)) {
			questionList.push_back(line);
		}
		line.clear();
		questionFile.close();
	}

	// THIS ALSO WORKS.
	std::vector<std::string>awnserList;
	std::vector<std::string>awnserFormatted;
	std::vector<std::string>correctAwnser;
	std::ifstream awnserFile;
	awnserFile.open("awList.txt");

	if (awnserFile.is_open()) {
		while (std::getline(awnserFile, line)) {
			awnserList.push_back(line);
		}
		awnserFile.close();
	}
	//ISSUE HERE. <- SOLVED. // SPLIT AWNSERS INTO VECTIR
	for (int i = 0; i < awnserList.size(); i++) {
		std::string loopString = awnserList[i];
		std::string awnserString;
		std::string testString;
		std::size_t pos = loopString.find(",");
		if (pos != std::string::npos) {
			awnserString = loopString.substr(loopString.size() - pos - 1);
			awnserFormatted.push_back(awnserString);
		}
	}
	// FORMAT AWNSERS SO EACH LINE OF awList.txt IS ONE ELEMENT IN A VECTOR
	for (int i = 0; i < awnserFormatted.size(); i++) {
		std::string loopString = awnserFormatted[i];
		std::string awnserString;
		for (int k = 0; k < loopString.size(); k++) {
			std::size_t pos1 = loopString.find("&"); // Start
			std::size_t pos2 = loopString.find("%"); // End
			if (pos1 != std::string::npos && pos2 != std::string::npos) {
				awnserString = loopString.substr(pos1 + 1, pos2 - pos1 - 1);
				correctAwnser.push_back(awnserString);
				break;
			}
		}
	}
	
	int questionCount{ 0 };
	int gameStartNum{ 0 };
	std::string response;
	int awnserCounter{ 1 };
	int correctAwnsers{ 0 };
	int incorrectAwnsers{ 0 };
	int strCompare{};
	int breakOut{};
	for (int i = 0; i < questionList.size(); i++) {
		questionCount = i;
	}
	while (gameStartNum <= questionCount) {
		std::cout << "---------------------------------------------------------------" << std::endl;
		std::cout << "-----       Welcome to the dynamic guessing game          -----" << std::endl;
		std::cout << "----- If there is no correct indicator, you got it wrong. -----" << std::endl;
		std::cout << "-----                      Have fun                       -----" << std::endl; //27
		std::cout << "---------------------------------------------------------------" << std::endl;
		Sleep(2000);
		system("CLS");
		for (int i = 0; i < questionList.size(); i++) {
			for (int v = 0; v < awnserFormatted.size(); v++) {
				gameStartNum++;
				std::cout << "Question #" << gameStartNum << ": " << questionList[v] << std::endl;

				for (int j = 0; j < questionList.size(); j++) {
					breakOut++;
				}

				std::string loopString = awnserFormatted[v];
				std::size_t pos1 = loopString.find("&");
				std::size_t pos2 = loopString.find("%");
				if (gameStartNum == breakOut) {
					break;
				}
				if (!loopString.empty()) {
					loopString.replace(pos1, 1, "");
					loopString.replace(pos2 - 1, 1, "");
					std::cout << loopString << std::endl;

					std::cout << "Response: ";
					std::cin >> response;
					for (int k = 0; k < correctAwnser.size(); k++) {
						strCompare = response.compare(correctAwnser[k]);
						if (strCompare == 0) {
							correctAwnsers++;
							std::cout << "Correct!" << std::endl;
						}
						else if (response != correctAwnser[k]) {
							incorrectAwnsers++;
						}
					}
				}else { continue; } // IF LOOPSTRING IS EMPTY, HAPPENS BECAUSE OF FORMATTED AWNSER PUSHES AWNSER, BLANK LINE, AWNSER.
			}
			break;
		}
		incorrectAwnsers = gameStartNum - correctAwnsers;

		std::cout << "************************" << std::endl;
		std::cout << "***** Your Results *****" << std::endl;
		std::cout << "************************" << std::endl;
		std::cout << "Total Questions: " << gameStartNum << std::endl;
		std::cout << "Correct Awnsers: " << correctAwnsers << std::endl;
		std::cout << "Wrong Awnsers: " << incorrectAwnsers << std::endl;
		break;
	}
}

int main() {
	inputFile();
}
