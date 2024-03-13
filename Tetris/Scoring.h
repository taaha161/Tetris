#pragma once
#include <fstream>
class score {
	int Score;
public:
		score() {
			Score = 0;
		}

		int getScore() {
			return Score;
	}
		void AddScore(int x) {
			Score += x;
		}
};
class level {
	int Level;
public:
	level() {
		Level = 1;
	}
	void IncreseLevel() {
		Level++;
		if (Level > 8) {
			Level = 1;
		}
	}
	int GetLevel() {
		return Level;
	}

};
class HighScores {
	int score1;
	int score2;
	int score3;
	int score4;
	int score5;
	ifstream read;
	ofstream write;
public:
	void setHighscores() {
		read.open("Highscores.txt");
		read >> score1 >> score2 >> score3 >> score4 >> score5;
		read.close();
	}
	void getHighscores() {
		cout << score1 << endl;
		cout << score2 << endl;
		cout << score3 << endl;
		cout << score4 << endl;
		cout << score5 << endl;
	}
	void UpdateHighScore(int score) {
		if (score > score1) {
			score5 = score4;
			score4 = score3;
			score3 = score2;
			score2 = score1;
			score1 = score;
		}
		else if (score > score2) {
			score5 = score4;
			score4 = score3;
			score3 = score2;
			score2 = score;
		
		}
		else if (score > score3) {
			score5 = score4;
			score4 = score3;
			score3 = score;
		
		}
		else if (score > score4) {
			score5 = score4;
			score4 = score;
			
		}
		else if (score > score5) {
			score5 = score;
		}
		 write.open("Highscores.txt", std::ios:: trunc);
		write << score1 <<endl << score2 <<endl << score3 <<endl << score4 << endl<< score5 << endl;
		write.close();
	}

};
